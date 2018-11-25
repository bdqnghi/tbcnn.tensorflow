







#include "DecafEmulator.h"

#include "java/lang/Object.h"
#include "sun/misc/LRUCache.h"

class JavaLangObject$$1D;



extern int decafDynamicCounter();
extern int decafStaticCounter();
extern int decafTopCounter();
extern int decafCatchCounter();
class SunMiscLRUCacheDecafReflection : DECAF_INHERITANCE JavaLangClass {
public:
  SunMiscLRUCacheDecafReflection(DecafClassInfo* inputMetadata);
};
JavaLangClass* SunMiscLRUCache::getClass() { decafClassInit(); return class_; };


SunMiscLRUCache* SunMiscLRUCache::decafNew(dint size) {   SunMiscLRUCache* newObject = new SunMiscLRUCache();   newObject->init(size);   return newObject; }
void SunMiscLRUCache::init(dint size)
{
  JavaLangObject::init();
  oa_ = ((JavaLangObject$$1D *)(NULL));
  this->size_ = size;
}

void SunMiscLRUCache::moveToFront(JavaLangObject$$1D * oa, dint i)
{
  JavaLangObject *ob = (*nil_chk(oa))[i];
  for (dint j = i; j > 0; j--) (*oa)[j] = $JavaLangObject((*oa)[j - 1]);
  (*oa)[0] = ob;
}

DECAF_RETURN(JavaLangObject *) SunMiscLRUCache::forName(JavaLangObject * name)
{
  if (oa_ == NULL) {
    oa_ = ($JavaLangObject$$1D(JavaLangObject$$1D::decafNew(size_)));
  }
  else {
    for (dint i = 0; i < nil_chk(oa_)->length_; i++) {
      JavaLangObject *ob = (*oa_)[i];
      if (ob == NULL) continue;
      if (this->hasName(ob, name)) {
        if (i > 0) SunMiscLRUCache::moveToFront(oa_, i);
        return ob;
      }
    }
  }
  JavaLangObject *ob = $JavaLangObject(this->create(name));
  (*oa_)[nil_chk(oa_)->length_ - 1] = ob;
  SunMiscLRUCache::moveToFront(oa_, ((dint)(oa_->length_ - 1)));
  return ob;
}

DECAF_RETURN(JavaLangObject *) SunMiscLRUCache::decafMethod0(JavaLangObject * obj, JavaLangObject$$1D * args)
{
  return SunMiscLRUCache::decafNew((dint)$JavaLangInteger((*args)[0])->intValue());
}

DECAF_RETURN(JavaLangObject *) SunMiscLRUCache::decafMethod1(JavaLangObject * obj, JavaLangObject$$1D * args)
{
  SunMiscLRUCache::moveToFront($JavaLangObject$$1D((*args)[0]), ( dint)$JavaLangInteger((*args)[1])->intValue());
  return null;
}

DECAF_RETURN(JavaLangObject *) SunMiscLRUCache::decafMethod2(JavaLangObject * obj, JavaLangObject$$1D * args)
{
  return $SunMiscLRUCache(obj)->forName($JavaLangObject((*args)[0]));
}

dlong SunMiscLRUCache::decafField0()
{
  SunMiscLRUCache* obj = new SunMiscLRUCache(); return decafOffset((const char*)obj, (const char*)(&($SunMiscLRUCache(obj)->oa_)));
}

SunMiscLRUCacheDecafReflection * SunMiscLRUCache::decafLoadClass()
{
  static DecafMethodInfo methods[] = {
    { NULL, NULL, NULL, 0x1, 0x1, -1, 0, -1, -1, -1, -1 },
    { NULL, NULL, "V", 0x9, 0x2, -1, 1, -1, -1, -1, -1 },
    { NULL, NULL, "LJavaLangObject;", 0x1, 0x1, -1, 2, -1, 3, -1, -1 },
  };
  methods[0].selector = "init";
  methods[0].methodPointer = SunMiscLRUCache::decafMethod0;
  methods[1].selector = "moveToFront";
  methods[1].methodPointer = SunMiscLRUCache::decafMethod1;
  methods[2].selector = "forName";
  methods[2].methodPointer = SunMiscLRUCache::decafMethod2;
  static DecafFieldInfo fields[] = {
    { NULL, "oa", "[LJavaLangObject;", .constantValue.asLong = 0, 0x2, 4, -1, 5, -1 },
    { NULL, "size", "I", .constantValue.asLong = 0, 0x12, 6, -1, -1, -1 },
  };
  fields[0].fieldMethod = SunMiscLRUCache::decafField0;
  
  static DecafClassInfo classInfo = { "LRUCache", "sun.misc", NULL, methods, fields, 7, 0x401, 3, 2, 0, 0, -1, -1, -1 };
  SunMiscLRUCacheDecafReflection* newClass = new SunMiscLRUCacheDecafReflection(&classInfo);
  JavaLangClass::decafRegisterClass(newClass);
  return newClass;
}

DECAF_ARRAY_IMPL(SunMiscLRUCache, SunMiscLRUCache, SunMiscLRUCache*, SunMiscLRUCache)
SunMiscLRUCacheDecafReflection::SunMiscLRUCacheDecafReflection(DecafClassInfo* inputMetadata) {
  metadata_ = inputMetadata;
};

SunMiscLRUCacheDecafReflection* SunMiscLRUCache::decafClass = DECAF_LOAD_CLASS(SunMiscLRUCache);
JavaLangClass* SunMiscLRUCache::class_ = SunMiscLRUCache::decafClass;

void* SunMiscLRUCache::decafCastStatic(JavaLangClass* targetType) {
  DECAF_CAST_STATIC(targetType, JavaLangObject)
  DECAF_CAST_STATIC(targetType, SunMiscLRUCache)
  return NULL;
};

SunMiscLRUCache* SunMiscLRUCache::decafCast(JavaLangObject* p) {
  if (p == NULL) return NULL;
  SunMiscLRUCache* ret = reinterpret_cast<SunMiscLRUCache*>(p->decafCastStatic(SunMiscLRUCache::class_));
  if (ret != NULL) {
    return ret;
  }
  return dynamic_cast<SunMiscLRUCache*>(p);
};
void* SunMiscLRUCache$$1D::decafCastStatic(JavaLangClass* targetType) {
  DECAF_CAST_STATIC(targetType, JavaLangObject$$1D)
  DECAF_CAST_STATIC(targetType, SunMiscLRUCache$$1D)
  return NULL;
};

SunMiscLRUCache$$1D* SunMiscLRUCache$$1D::decafCast(JavaLangObject* p) {
  if (p == NULL) return NULL;
  SunMiscLRUCache$$1D* ret = reinterpret_cast<SunMiscLRUCache$$1D*>(p->decafCastStatic(SunMiscLRUCache$$1D::class_));
  if (ret != NULL) {
    return ret;
  }
  return dynamic_cast<SunMiscLRUCache$$1D*>(p);
};
void* SunMiscLRUCache$$2D::decafCastStatic(JavaLangClass* targetType) {
  DECAF_CAST_STATIC(targetType, JavaLangObject$$2D)
  DECAF_CAST_STATIC(targetType, SunMiscLRUCache$$2D)
  return NULL;
};

SunMiscLRUCache$$2D* SunMiscLRUCache$$2D::decafCast(JavaLangObject* p) {
  if (p == NULL) return NULL;
  SunMiscLRUCache$$2D* ret = reinterpret_cast<SunMiscLRUCache$$2D*>(p->decafCastStatic(SunMiscLRUCache$$2D::class_));
  if (ret != NULL) {
    return ret;
  }
  return dynamic_cast<SunMiscLRUCache$$2D*>(p);
};
void* SunMiscLRUCache$$3D::decafCastStatic(JavaLangClass* targetType) {
  DECAF_CAST_STATIC(targetType, JavaLangObject$$3D)
  DECAF_CAST_STATIC(targetType, SunMiscLRUCache$$3D)
  return NULL;
};

SunMiscLRUCache$$3D* SunMiscLRUCache$$3D::decafCast(JavaLangObject* p) {
  if (p == NULL) return NULL;
  SunMiscLRUCache$$3D* ret = reinterpret_cast<SunMiscLRUCache$$3D*>(p->decafCastStatic(SunMiscLRUCache$$3D::class_));
  if (ret != NULL) {
    return ret;
  }
  return dynamic_cast<SunMiscLRUCache$$3D*>(p);
};
void* SunMiscLRUCache$$4D::decafCastStatic(JavaLangClass* targetType) {
  DECAF_CAST_STATIC(targetType, JavaLangObject$$4D)
  DECAF_CAST_STATIC(targetType, SunMiscLRUCache$$4D)
  return NULL;
};

SunMiscLRUCache$$4D* SunMiscLRUCache$$4D::decafCast(JavaLangObject* p) {
  if (p == NULL) return NULL;
  SunMiscLRUCache$$4D* ret = reinterpret_cast<SunMiscLRUCache$$4D*>(p->decafCastStatic(SunMiscLRUCache$$4D::class_));
  if (ret != NULL) {
    return ret;
  }
  return dynamic_cast<SunMiscLRUCache$$4D*>(p);
};
