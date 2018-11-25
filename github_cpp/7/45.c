#include <MergeSort.h>


#include "MergeSort.inc"

void MergeSort::_instance_init() {
    _I_("Doing initialisation for class: MergeSort");
    
}







void MergeSort::_constructor(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > gr)
{
    this->x10::lang::Object::_constructor();
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(tmp) =
      x10aux::class_cast_unchecked<x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > >(x10aux::null);
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(size) =
      ((x10_int)0);
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(tmp) =
      gr;
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(size) =
      (gr)->length();
    
}
x10aux::ref<MergeSort> MergeSort::_make(
  x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > gr)
{
    x10aux::ref<MergeSort> this_ = new (x10aux::alloc<MergeSort>()) MergeSort();
    this_->_constructor(gr);
    return this_;
}




void MergeSort::sort() {
    
    
    x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux =
      x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> >::_make(((x10aux::ref<MergeSort>)this)->
                                                                                                  FMGL(size));
    
    
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      ((x10aux::ref<MergeSort>)this)->
        FMGL(tmp),
      aux,
      ((x10_int)0),
      ((x10aux::ref<MergeSort>)this)->
        FMGL(size));
}


x10_int MergeSort::mergeSort(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmp,
                             x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
                             x10_int low,
                             x10_int high) {
    
    
    if (((((x10_int) ((high) - (low)))) <= (((x10_int)1))))
    {
        
        
        return ((x10_int)0);
        
    }
    
    
    x10_int middle = ((x10_int) ((low) + (((x10_int) ((((x10_int) ((high) - (low)))) / (((x10_int)2)))))));
    
    
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      tmp,
      aux,
      low,
      middle);
    
    
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      tmp,
      aux,
      middle,
      high);
    
    
    ((x10aux::ref<MergeSort>)this)->merge(
      tmp,
      aux,
      low,
      middle,
      high);
    
    
    return ((x10_int)0);
    
}


void MergeSort::merge(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmp,
                      x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
                      x10_int low,
                      x10_int middle,
                      x10_int high) {
    
    
    x10_int i = low;
    
    
    x10_int j = middle;
    
    
    {
        x10_int k;
        for (
             
             k = low; ((k) < (high)); 
                                      
                                      k +=
                                        ((x10_int)1))
        {
            
            
            if ((x10aux::struct_equals(i,
                                       middle)))
            {
                
                
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      j +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            
            
            if ((x10aux::struct_equals(j,
                                       high)))
            {
                
                
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      i +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            
            
            if ((x10aux::struct_equals((CompareTo::strcmp(
                                          (tmp)->apply(j)->
                                            FMGL(first),
                                          (tmp)->apply(i)->
                                            FMGL(first))),
                                       ((x10_int)-1))))
            {
                
                
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      j +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            {
                
                
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      i +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            
        }
    }
    
    
    {
        x10_int k;
        for (
             
             k = low; ((k) < (high)); 
                                      
                                      k +=
                                        ((x10_int)1))
        {
            
            
            (tmp)->set((aux)->apply(k), k);
        }
    }
    
}


x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > >
  MergeSort::getVariable(
  ) {
    
    
    return ((x10aux::ref<MergeSort>)this)->
             FMGL(tmp);
    
}
const x10aux::serialization_id_t MergeSort::_serialization_id = 
    x10aux::DeserializationDispatcher::addDeserializer(MergeSort::_deserializer<x10::lang::Object>);

void MergeSort::_serialize_body(x10aux::serialization_buffer& buf) {
    x10::lang::Object::_serialize_body(buf);
    
}

void MergeSort::_deserialize_body(x10aux::deserialization_buffer& buf) {
    x10::lang::Object::_deserialize_body(buf);
    
}

x10aux::RuntimeType MergeSort::rtt;
void MergeSort::_initRTT() {
    if (rtt.initStageOne(&rtt)) return;
    const x10aux::RuntimeType* parents[1] = { x10aux::getRTT<x10::lang::Object>()};
    rtt.initStageTwo("MergeSort", 1, parents, 0, NULL, NULL);
}
