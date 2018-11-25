

#include <iostream>
#include <random>
#include <algorithm>

#include <cm/cm.h>
#include "..\common\bitmap_helpers.h"
#include "..\common\cm_rt_helpers.h"
#include "..\common\isa_helpers.h"

#include "radixsort.h"

#ifdef CMRT_EMU
extern "C" void PerThreadHist(uint numKeys, uint radixPos, uint keysPerThread, svmptr_t ibuf, svmptr_t obuf);
extern "C" void ScanHist(svmptr_t ibuf, svmptr_t obuf);
extern "C" void ScanKeys(uint numKeys, uint radixPos, svmptr_t ibuf, svmptr_t ibufHist, svmptr_t obuf);
extern "C" void ScanKeysUncoalesced(uint numKeys, uint radixPos, svmptr_t ibuf, svmptr_t ibufHist, svmptr_t obuf);
#endif

double getSeconds() {
  LARGE_INTEGER freq, val;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&val);
  return (double)val.QuadPart / (double)freq.QuadPart;
}

struct SortResults {
  std::string algorithm = "";
  size_t numKeys = 0;

  double totalGPUTimeMS = 0.0;
  double totalCPUTimeMS = 0.0;
  double throughputMKeys = 0.0;

  void print() {
    std::cout << "---- ALGORITHM: " << algorithm << " ----" << std::endl;
    std::cout << "Total time GPU clock:       " << totalGPUTimeMS << " ms" << std::endl;
    std::cout << "Total time CPU clock:       " << totalCPUTimeMS << " ms" << std::endl;
    std::cout << "Throughput:                 " << throughputMKeys << " MKeys/s" << std::endl;
    std::cout << std::endl;
  }
};

SortResults sortVectorCM(KeyType *&keys, uint32_t numKeys) {
  
  CmDevice *device = nullptr;
  unsigned int version = 0;
  cm_result_check(::CreateCmDevice(device, version));

  
  std::string isa_code = cm::util::isa::loadFile("radixsort_genx.isa");
  if (isa_code.size() == 0) {
    std::cout << "Error: empty ISA binary" << std::endl;
    exit(1);
  }

  CmProgram *program = nullptr;
  cm_result_check(device->LoadProgram(const_cast<char*>(isa_code.data()), isa_code.size(), program));

  
  CmKernel *HistKernel = nullptr;
  cm_result_check(device->CreateKernel(program, CM_KERNEL_FUNCTION(PerThreadHist), HistKernel));

  CmKernel *HistScanKernel = nullptr;
  cm_result_check(device->CreateKernel(program, CM_KERNEL_FUNCTION(ScanHist), HistScanKernel));

  CmKernel *KeyScanKernel = nullptr;
#ifdef SLM_COALESCE
  cm_result_check(device->CreateKernel(program, CM_KERNEL_FUNCTION(ScanKeys), KeyScanKernel));
#else
  cm_result_check(device->CreateKernel(program, CM_KERNEL_FUNCTION(ScanKeysUncoalesced), KeyScanKernel));
#endif

  
#ifdef CMRT_EMU
  CmThreadSpace *tsHist = nullptr;
  CmThreadSpace *tsHistScan = nullptr;

  cm_result_check(device->CreateThreadSpace(GPU_THREADS, 1, tsHist));
  cm_result_check(device->CreateThreadSpace(1, 1, tsHistScan));
#else
  CmThreadGroupSpace *tsHist = nullptr;
  CmThreadGroupSpace *tsHistScan = nullptr;

  cm_result_check(device->CreateThreadGroupSpace(WG_SIZE, 1, GPU_THREADS / WG_SIZE, 1, tsHist));
  cm_result_check(device->CreateThreadGroupSpace(1, 1, 1, 1, tsHistScan));
#endif

  
  CmBufferSVM *histBuff = nullptr;
  CmBufferSVM *histScanBuff = nullptr;
  CmBufferSVM *inputBuff = nullptr;
  CmBufferSVM *outputBuff = nullptr;

  
  void *inputBuffData = keys;
  void *outputBuffData = nullptr;
  void *histBuffData = nullptr;
  void *histScanBuffData = nullptr;

  
  cm_result_check(device->CreateBufferSVM(numKeys * sizeof(KeyType), inputBuffData, CM_SVM_ACCESS_FLAG_DEFAULT, inputBuff));
  cm_result_check(device->CreateBufferSVM(numKeys * sizeof(KeyType), outputBuffData, CM_SVM_ACCESS_FLAG_DEFAULT, outputBuff));

  cm_result_check(device->CreateBufferSVM((GPU_THREADS * RADIX_SIZE) * sizeof(uint32_t), histBuffData, CM_SVM_ACCESS_FLAG_DEFAULT, histBuff));
  cm_result_check(device->CreateBufferSVM(((GPU_THREADS + 1) * RADIX_SIZE) * sizeof(uint32_t), histScanBuffData, CM_SVM_ACCESS_FLAG_DEFAULT, histScanBuff));

  
  CmTask *HistTask = nullptr;
  cm_result_check(device->CreateTask(HistTask));
  cm_result_check(HistTask->AddKernel(HistKernel));

  CmTask *HistScanTask = nullptr;
  cm_result_check(device->CreateTask(HistScanTask));
  cm_result_check(HistScanTask->AddKernel(HistScanKernel));

  CmTask *KeyScanTask = nullptr;
  cm_result_check(device->CreateTask(KeyScanTask));
  cm_result_check(KeyScanTask->AddKernel(KeyScanKernel));

  
  CmQueue *taskQueue = nullptr;
  cm_result_check(device->CreateQueue(taskQueue));

  
  CmEvent *HistTaskEvent = nullptr;
  CmEvent *HistScanTaskEvent = nullptr;
  CmEvent *KeyScanTaskEvent = nullptr;

  
  uint64_t histKernelTime = 0;
  uint64_t histScanKernelTime = 0;
  uint64_t keyScanKernelTime = 0;
  uint64_t totalGPUTime = 0;
  double cpuTimeStart = getSeconds();

  
  for (uint32_t radixPos = 0; radixPos < KEY_DIGITS; radixPos += RADIX_DIGITS) {
    
    cm_result_check(HistKernel->SetKernelArg(0, sizeof(numKeys), &numKeys));
    cm_result_check(HistKernel->SetKernelArg(1, sizeof(radixPos), &radixPos));
    cm_result_check(HistKernel->SetKernelArg(2, sizeof(void *), &inputBuffData));
    cm_result_check(HistKernel->SetKernelArg(3, sizeof(void *), &histBuffData));

    cm_result_check(HistScanKernel->SetKernelArg(0, sizeof(void *), &histBuffData));
    cm_result_check(HistScanKernel->SetKernelArg(1, sizeof(void *), &histScanBuffData));

    cm_result_check(KeyScanKernel->SetKernelArg(0, sizeof(numKeys), &numKeys));
    cm_result_check(KeyScanKernel->SetKernelArg(1, sizeof(radixPos), &radixPos));
    cm_result_check(KeyScanKernel->SetKernelArg(2, sizeof(void *), &inputBuffData));
    cm_result_check(KeyScanKernel->SetKernelArg(3, sizeof(void *), &histScanBuffData));
    cm_result_check(KeyScanKernel->SetKernelArg(4, sizeof(void *), &outputBuffData));

    
    
#ifdef CMRT_EMU
    cm_result_check(taskQueue->Enqueue(HistTask, HistTaskEvent, tsHist));
    cm_result_check(HistTaskEvent->WaitForTaskFinished());

    cm_result_check(taskQueue->Enqueue(HistScanTask, HistScanTaskEvent, tsHistScan));
    cm_result_check(HistScanTaskEvent->WaitForTaskFinished());

    cm_result_check(taskQueue->Enqueue(KeyScanTask, KeyScanTaskEvent, tsHist));
    cm_result_check(KeyScanTaskEvent->WaitForTaskFinished());
#else
    cm_result_check(taskQueue->EnqueueWithGroup(HistTask, HistTaskEvent, tsHist));
    cm_result_check(HistTaskEvent->WaitForTaskFinished());

    cm_result_check(taskQueue->EnqueueWithGroup(HistScanTask, HistScanTaskEvent, tsHistScan));
    cm_result_check(HistScanTaskEvent->WaitForTaskFinished());

    cm_result_check(taskQueue->EnqueueWithGroup(KeyScanTask, KeyScanTaskEvent, tsHist));
    cm_result_check(KeyScanTaskEvent->WaitForTaskFinished());
#endif

    
    cm_result_check(HistTaskEvent->GetExecutionTime(histKernelTime));
    cm_result_check(HistScanTaskEvent->GetExecutionTime(histScanKernelTime));
    cm_result_check(KeyScanTaskEvent->GetExecutionTime(keyScanKernelTime));

    totalGPUTime += histKernelTime + histScanKernelTime + keyScanKernelTime;

    
    cm_result_check(taskQueue->DestroyEvent(HistTaskEvent));
    cm_result_check(taskQueue->DestroyEvent(HistScanTaskEvent));
    cm_result_check(taskQueue->DestroyEvent(KeyScanTaskEvent));

    
    std::swap(outputBuffData, inputBuffData);
  }

  double cpuTimeEnd = getSeconds();

  
  SortResults sr;
  sr.algorithm = "genradixsort";
  sr.numKeys = numKeys;
  sr.totalCPUTimeMS = (cpuTimeEnd - cpuTimeStart) * 1E3;
  sr.totalGPUTimeMS = totalGPUTime / 1E6;
  sr.throughputMKeys = (float(numKeys) / (cpuTimeEnd - cpuTimeStart)) / 1E6;

  return sr;
}

SortResults sortVectorSTD(std::vector<KeyType> &keys) {
  
  double tStart = getSeconds();
  std::sort(keys.begin(), keys.end());
  double tEnd = getSeconds();
  double cpuTime = float(tEnd - tStart);

  
  SortResults sr;
  sr.algorithm = "std::sort";
  sr.numKeys = keys.size();
  sr.totalCPUTimeMS = cpuTime * 1E3;
  sr.totalGPUTimeMS = -1.0;
  sr.throughputMKeys = (float(keys.size()) / cpuTime) / 1E6;

  return sr;
}

int main(int argc, char *argv[]) {
  uint32_t numKeys = 32 * 1024;
  std::vector<KeyType> inputVector;
  KeyType* inputPtr = (KeyType*) _aligned_malloc(numKeys * sizeof(KeyType), 4096);

  
  std::random_device r;
  std::default_random_engine e1(0);
  std::uniform_int_distribution<KeyType> uniform_dist(0, KeyType(std::numeric_limits<KeyType>::max));

  for (uint32_t i = 0; i < numKeys; i+=1) {
    KeyType v = uniform_dist(e1);
    inputVector.push_back(v);
    inputPtr[i] = v;
  }

  
  SortResults cmSR = sortVectorCM(inputPtr, numKeys);

  
  SortResults stdSR = sortVectorSTD(inputVector);

  
  bool isValid = true;
  for (size_t i = 0; i < numKeys; i++) {
    if (inputPtr[i] != inputVector[i]) {
      isValid = false;
      break;
    }
  }

  if (isValid) {
    std::cout << "Sort Is Valid" << std::endl;
    std::cout << std::endl;

    cmSR.print();
    stdSR.print();
  } else {
    std::cout << "Sort Is Not Valid" << std::endl;
    return 1;
  }

  return 0;
}
