#include <MergeSortRail.h>


#include "MergeSortRail.inc"

void MergeSortRail::_instance_init() {
    _I_("Doing initialisation for class: MergeSortRail");
    
}







void MergeSortRail::_constructor(x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > t)
{
    this->x10::lang::Object::_constructor();
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSortRail>)this))->
      FMGL(size) =
      ((x10_int)0);
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSortRail>)this))->
      FMGL(tmpRail) =
      x10aux::class_cast_unchecked<x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > >(x10aux::null);
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSortRail>)this))->
      FMGL(size) =
      x10aux::nullCheck(t)->x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> >::length();
    
    
    x10aux::placeCheck(((x10aux::ref<MergeSortRail>)this))->
      FMGL(tmpRail) =
      t;
    
}
x10aux::ref<MergeSortRail> MergeSortRail::_make(
  x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > t)
{
    x10aux::ref<MergeSortRail> this_ = new (x10aux::alloc<MergeSortRail>()) MergeSortRail();
    this_->_constructor(t);
    return this_;
}




void MergeSortRail::sortRail() {
    
    
    x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux =
      x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> >::make(((x10aux::ref<MergeSortRail>)this)->
                                                                                         FMGL(size));
    
    
    ((x10aux::ref<MergeSortRail>)this)->mergeSortRail(
      ((x10aux::ref<MergeSortRail>)this)->
        FMGL(tmpRail),
      aux,
      ((x10_int)0),
      ((x10aux::ref<MergeSortRail>)this)->
        FMGL(size));
}


x10_int MergeSortRail::mergeSortRail(x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmpRail,
                                     x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
                                     x10_int low,
                                     x10_int high) {
    
    
    if (((((x10_int) ((high) - (low)))) <= (((x10_int)1))))
    {
        
        
        return ((x10_int)0);
        
    }
    
    
    x10_int middle = ((x10_int) ((low) + (((x10_int) ((((x10_int) ((high) - (low)))) / (((x10_int)2)))))));
    
    
    ((x10aux::ref<MergeSortRail>)this)->mergeSortRail(
      tmpRail,
      aux,
      low,
      middle);
    
    
    ((x10aux::ref<MergeSortRail>)this)->mergeSortRail(
      tmpRail,
      aux,
      middle,
      high);
    
    
    ((x10aux::ref<MergeSortRail>)this)->mergeRail(
      tmpRail,
      aux,
      low,
      middle,
      high);
    
    
    return ((x10_int)0);
    
}


void MergeSortRail::mergeRail(x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmpRail,
                              x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
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
                
                
                (aux)->set((tmpRail)->apply((__extension__ ({
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
                
                
                (aux)->set((tmpRail)->apply((__extension__ ({
                    x10_int t =
                      i +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            
            
            if ((x10aux::struct_equals((CompareTo::strcmp(
                                          (tmpRail)->apply(j)->
                                            FMGL(first),
                                          (tmpRail)->apply(i)->
                                            FMGL(first))),
                                       ((x10_int)-1))))
            {
                
                
                (aux)->set((tmpRail)->apply((__extension__ ({
                    x10_int t =
                      j +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            {
                
                
                (aux)->set((tmpRail)->apply((__extension__ ({
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
            
            
            (tmpRail)->set((aux)->apply(k), k);
        }
    }
    
}


x10aux::ref<x10::lang::Rail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > >
  MergeSortRail::getVariable(
  ) {
    
    
    return ((x10aux::ref<MergeSortRail>)this)->
             FMGL(tmpRail);
    
}
const x10aux::serialization_id_t MergeSortRail::_serialization_id = 
    x10aux::DeserializationDispatcher::addDeserializer(MergeSortRail::_deserializer<x10::lang::Object>);

void MergeSortRail::_serialize_body(x10aux::serialization_buffer& buf) {
    x10::lang::Object::_serialize_body(buf);
    
}

void MergeSortRail::_deserialize_body(x10aux::deserialization_buffer& buf) {
    x10::lang::Object::_deserialize_body(buf);
    
}

x10aux::RuntimeType MergeSortRail::rtt;
void MergeSortRail::_initRTT() {
    if (rtt.initStageOne(&rtt)) return;
    const x10aux::RuntimeType* parents[1] = { x10aux::getRTT<x10::lang::Object>()};
    rtt.initStageTwo("MergeSortRail", 1, parents, 0, NULL, NULL);
}
