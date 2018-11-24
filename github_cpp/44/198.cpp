#include "Dalvik.h"

//#define SYNC_STACK_ONLY

#define READWRITEFUNC(type, size, ntoh, hton)                                 \
  static void write##size(FifoBuffer* fb, type v) {                           \
    v = hton(v);                                                              \
    auxFifoPushData(fb, (char*)&v, sizeof(v));                                \
  }                                                                           \
  static type read##size(FifoBuffer* fb) {                                    \
    type v;                                                                   \
    auxFifoReadBuffer(fb, (char*)&v, sizeof(v));                              \
    return ntoh(v);                                                           \
  }

READWRITEFUNC(u1, U1, , );
//READWRITEFUNC(u2, U2, ntohs, htons);
READWRITEFUNC(u4, U4, ntohl, htonl);
READWRITEFUNC(u8, U8, ntohll, htonll);

void offPushAllStacks(FifoBuffer* fb) {
  Thread* thread;
  for(thread = gDvm.threadList; thread; thread = thread->next) {
    if(thread->offLocal && !thread->offGhost) {
      offPushStack(fb, thread);
    }
  }
  /* Push strategy for debugging.  We need to revert to the old strategy before
   * we can get failure recovery. */
/*
  thread = dvmThreadSelf();
  if(thread->offLocal && !thread->offGhost) {
    offPushStack(fb, thread);
  }
*/

  writeU4(fb, (u4)-1);
}

void offPullAllStacks(FifoBuffer* fb) {
  u4 tid;
  for(tid = readU4(fb); tid != (u4)-1; tid = readU4(fb)) {
    offPullStack(fb, tid);
  }
}

static bool isParamObject(Method* method, int param) {
  int ind = param + (dvmIsStaticMethod(method) ? 1 : 0);
  return ind == 0 || method->shorty[ind] == 'L';
}

static bool isParamLong(Method* method, int param) {
  int ind = param + (dvmIsStaticMethod(method) ? 1 : 0);
  return ind != 0 && (method->shorty[ind] == 'J' ||
                      method->shorty[ind] == 'D');
}

void offPushStack(FifoBuffer* fb, Thread* thread) {
  InterpSaveState* sst = &thread->interpSave;
  writeU4(fb, thread->threadId);
  writeU1(fb, thread->interrupted);

  if(thread->threadObj) offAddTrackedObject(thread->threadObj);
  if(thread->exception) offAddTrackedObject(thread->exception);
  writeU4(fb, auxObjectToId(thread->threadObj));
  writeU4(fb, auxObjectToId(thread->exception));
  offTransmitMonitors(thread, fb);

  if(!gDvm.isServer && thread->offLocalOnly) {
    writeU4(fb, 0);
    writeU4(fb, 0);
    writeU4(fb, (u4)-1);
    return;
  }
    
/*
#ifdef SYNC_STACK_ONLY
  assert(0 && "not supported yet");
  void* fp = gDvm.isServer || thread == dvmThreadSelf() ?
        thread->curFrame : NULL;
#else
*/
  u4* fp = sst->curFrame;
  writeU4(fb, fp ? (thread->interpStackStart - (u1*)fp) +
                   sizeof(StackSaveArea) : 0U);
  writeU4(fb, thread->breakFrames);

//TODO: Get this working
thread->offSyncStackStop = NULL;
//#endif
  while(fp != thread->offSyncStackStop) {
    const StackSaveArea* saveArea = SAVEAREA_FROM_FP(fp);
    Method* method = (Method*)saveArea->method;

    if(dvmIsBreakFrame(fp)) {
      /* Just write the invalid method id to indicate break frame. */
      writeU4(fb, 0);
    } else if(dvmIsNativeMethod(method)) {
      writeU4(fb, method->clazz->pDvmDex->id << 24 |
                  PACK_METHOD_IDX(method));
      writeU8(fb, (u8)(uintptr_t)saveArea->xtra.localRefCookie);

      if(saveArea->prevFrame &&
         SAVEAREA_FROM_FP(saveArea->prevFrame)->method == method) {
        writeU1(fb, 0);
      } else {
        writeU1(fb, 1);

        /* Native methods have their parameters stored where the registers
         * normally are stored. */
        int i, j;
        const u4* framePtr = (const u4*)fp;
        for(i = j = 0; i < method->registersSize; i++, j++) {
          u4 rval = *framePtr++;
          if(isParamObject(method, j)) {
            Object* obj = (Object*)rval;
            if(obj) offAddTrackedObject(obj);
            rval = auxObjectToId(obj);
          } else if(isParamLong(method, j)) {
            writeU4(fb, rval);
            rval = *framePtr++; i++;
          }
          writeU4(fb, rval);
        }
      }
    } else {
      /* Otherwise write out the method and pc first. */
      int addr = saveArea->xtra.currentPc - method->insns;
      writeU4(fb, method->clazz->pDvmDex->id << 24 |
                  PACK_METHOD_IDX(method));
      writeU4(fb, addr);

      /* Then transmit the stack information. */
      const RegisterMap* pMap = dvmGetExpandedRegisterMap(method);
      const u1* regVector = pMap ? dvmRegisterMapGetLine(pMap, addr) : NULL;
      if(regVector == NULL) {
        ALOGE("MISSING REGMAPS %s %s", method->clazz->descriptor, method->name);
      }
      assert(method->clazz->status >= CLASS_INITIALIZING);
      assert(regVector && "No register maps found");

//ALOGI("SENDING %s %s %d", method->clazz->descriptor, method->name, addr);

      int i;
      u2 bits = 1 << 1;
      const u4* framePtr = (const u4*)fp;
      for(i = 0; i < method->registersSize; i++) {
        u4 rval = *framePtr++;

        bits >>= 1;
        if(bits == 1) {
          bits = *regVector++ | 0x100;
        }

        if(bits & 0x01) {
          /* Register is a non-null object. */
          Object* obj = (Object*)rval;
          if(obj) offAddTrackedObject(obj);
          rval = auxObjectToId(obj);
        }

        writeU4(fb, rval);
      }
      dvmReleaseRegisterMapLine(pMap, regVector);
    }
    fp = saveArea->prevFrame;
  }
  writeU4(fb, (u4)-1);

  thread->offSyncStackStop = sst->curFrame ?
      SAVEAREA_FROM_FP(sst->curFrame)->prevFrame : NULL;
}

Thread* offPullStack(FifoBuffer* fb, u4 tid) {
  Thread* thread = offIdToThread(tid);
  InterpSaveState* sst = &thread->interpSave;
  u4* fp;
  u1* stackPtr,* basePtr;

  u4 mid;
  FifoBuffer stack = auxFifoCreate();
  Queue frameQueue = auxQueueCreate();

  thread->interrupted = (bool)readU1(fb);
  thread->threadObj = offIdToObject(readU4(fb));
  thread->exception = offIdToObject(readU4(fb));
  offReceiveMonitors(thread, fb);

  u4 stackOffset = readU4(fb);
  thread->breakFrames = readU4(fb);
  for(mid = readU4(fb); mid != (u4)-1; mid = readU4(fb)) {
    StackSaveArea saveArea;
    memset(&saveArea, 0, sizeof(saveArea));
    auxQueuePushI(&frameQueue, auxFifoSize(&stack) + sizeof(saveArea));

    if(mid == 0) {
      /* Break frame */
      auxFifoPushData(&stack, (char*)&saveArea, sizeof(saveArea));
    } else {
      Method* method = auxMethodByIdx(offIdToDex(mid >> 24),
                                    GET_METHOD_IDX(mid), GET_METHOD_STATIC(mid),
                                    GET_METHOD_DIRECT(mid), false);
      assert(method->clazz->status == CLASS_INITIALIZED ||
             method->clazz->status == CLASS_INITIALIZING);

      if(dvmIsNativeMethod(method)) {
        /* Although this value may be a pointer it's OK to send back and forth
         * as only the endpoint that's actually responsible for the native frame
         * will read this value. */
        saveArea.xtra.localRefCookie =
            (typeof(saveArea.xtra.localRefCookie))(uintptr_t)readU8(fb);
        saveArea.method = method;
        auxFifoPushData(&stack, (char*)&saveArea, sizeof(saveArea));

        u1 hasParams = readU1(fb);
        if(hasParams) {
          int i, j;
          for(i = j = 0; i < method->registersSize; i++, j++) {
            u4 rval = readU4(fb);
            if(isParamObject(method, j)) {
              rval = (u4)offIdToObject(rval);
            } else if(isParamLong(method, j)) {
              auxFifoPushData(&stack, (char*)&rval, sizeof(rval));
              rval = readU4(fb); i++;
            }
            auxFifoPushData(&stack, (char*)&rval, sizeof(rval));
          }
        }
        continue;
      }

      int addr = readU4(fb);
      saveArea.xtra.currentPc = method->insns + addr;
      saveArea.method = method;
      auxFifoPushData(&stack, (char*)&saveArea, sizeof(saveArea));

      const RegisterMap* pMap = dvmGetExpandedRegisterMap(method);
      const u1* regVector = pMap ? dvmRegisterMapGetLine(pMap, addr) : NULL;
      if(regVector == NULL) {
        ALOGE("MISSING REGMAPS %s %s", method->clazz->descriptor, method->name);
      }
      assert(regVector && "No register maps found");

      int i;
      u2 bits = 1 << 1;
      for(i = 0; i < method->registersSize; i++) {
        u4 rval = readU4(fb);

        bits >>= 1;
        if(bits == 1) {
          bits = *regVector++ | 0x100;
        }

        if(bits & 0x01) {
          /* Register is a non-null object. */
          rval = (u4)offIdToObject(rval);
        }

        auxFifoPushData(&stack, (char*)&rval, sizeof(rval));
      }
      dvmReleaseRegisterMapLine(pMap, regVector);
    }
  }

  if(auxFifoSize(&stack) != stackOffset) {
    ALOGE("FAIL %d %d", auxFifoSize(&stack), stackOffset);
  }
  assert(auxFifoSize(&stack) == stackOffset);

  /* Copy in the stack now that we've built it. */
  if(stackOffset == 0 && auxQueueEmpty(&frameQueue)) {
    sst->curFrame = NULL;
    goto noframes;
  }

  assert(!auxQueueEmpty(&frameQueue));
  assert(auxFifoSize(&stack) <= (u4)thread->interpStackSize);
  assert(auxFifoSize(&stack) <= stackOffset);
  stackPtr = thread->interpStackStart - stackOffset;
  basePtr = stackPtr;
  assert(thread->interpStackEnd <= basePtr);
  sst->curFrame = (u4*)(basePtr + auxQueuePop(&frameQueue).i);

  while(!auxFifoEmpty(&stack)) {
    u4 sz = auxFifoGetBufferSize(&stack);
    memcpy(stackPtr, auxFifoGetBuffer(&stack), sz);
    auxFifoPopBytes(&stack, sz);
    stackPtr += sz;
  }
  auxFifoDestroy(&stack);

  /* Fix up the prevFrame pointers. */
  fp = sst->curFrame;
  while(1) {
    StackSaveArea* saveArea = SAVEAREA_FROM_FP(fp);
//TODO: this is a problem
    if(auxQueueEmpty(&frameQueue)) {
      saveArea->prevFrame = NULL;
      break;
    }
    fp = saveArea->prevFrame = (u4*)(basePtr + auxQueuePop(&frameQueue).i);
    saveArea->savedPc = SAVEAREA_FROM_FP(fp)->xtra.currentPc;
    assert((u1*)saveArea->prevFrame <= thread->interpStackStart);
  }
  auxQueueDestroy(&frameQueue);

noframes:
  #ifdef DEBUG
  /* Do a quick debug check. */
  fp = sst->curFrame;
  u4 breaks = 0;
  while(fp) {
    StackSaveArea* saveArea = SAVEAREA_FROM_FP(fp);
    assert((uintptr_t)saveArea->prevFrame > (uintptr_t)fp ||
           saveArea->prevFrame == NULL);
    if(dvmIsBreakFrame(fp)) breaks++;
    fp = saveArea->prevFrame;
  }
  assert(breaks == thread->breakFrames);
  #endif

  thread->offSyncStackStop = sst->curFrame ?
      SAVEAREA_FROM_FP(sst->curFrame)->prevFrame : NULL;

  return thread;
}

#ifdef DEBUG
bool offCheckBreakFrames() {
  u4 breaks = 0;
  Thread* self = dvmThreadSelf();
  InterpSaveState* sst = &self->interpSave;
  u4* fp = sst->curFrame;
  while(fp) {
    if(dvmIsBreakFrame(fp)) breaks++;
    fp = SAVEAREA_FROM_FP(fp)->prevFrame;
  }
  return breaks == self->breakFrames;
}

int offDebugStack(const Thread* thread) {
  const InterpSaveState* sst = &thread->interpSave;
  u4* fp = sst->curFrame;
  while(fp) {
    const StackSaveArea* saveArea = SAVEAREA_FROM_FP(fp);
    const Method* method = saveArea->method;
    if(dvmIsBreakFrame(fp)) {
      ALOGI("BREAK");
    } else {
      int addr = saveArea->xtra.currentPc - method->insns;
      ALOGI("%s %s %d\n", method->clazz->descriptor, method->name, addr);
    }
    fp = saveArea->prevFrame;
  }
  return thread->threadId;
}
#endif
