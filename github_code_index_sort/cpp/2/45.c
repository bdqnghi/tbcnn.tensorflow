#include <MergeSort.h>


#include "MergeSort.inc"

void MergeSort::_instance_init() {
    _I_("Doing initialisation for class: MergeSort");
    
}


//#line 14 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10FieldDecl_c

//#line 15 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10FieldDecl_c

//#line 17 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10ConstructorDecl_c
void MergeSort::_constructor(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > gr)
{
    this->x10::lang::Object::_constructor();
    
    //#line 14 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(tmp) =
      x10aux::class_cast_unchecked<x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > >(x10aux::null);
    
    //#line 15 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(size) =
      ((x10_int)0);
    
    //#line 19 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    x10aux::placeCheck(((x10aux::ref<MergeSort>)this))->
      FMGL(tmp) =
      gr;
    
    //#line 20 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
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



//#line 23 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10MethodDecl_c
void MergeSort::sort() {
    
    //#line 25 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
    x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux =
      x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> >::_make(((x10aux::ref<MergeSort>)this)->
                                                                                                  FMGL(size));
    
    //#line 26 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      ((x10aux::ref<MergeSort>)this)->
        FMGL(tmp),
      aux,
      ((x10_int)0),
      ((x10aux::ref<MergeSort>)this)->
        FMGL(size));
}

//#line 29 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10MethodDecl_c
x10_int MergeSort::mergeSort(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmp,
                             x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
                             x10_int low,
                             x10_int high) {
    
    //#line 33 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10If_c
    if (((((x10_int) ((high) - (low)))) <= (((x10_int)1))))
    {
        
        //#line 35 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10Return_c
        return ((x10_int)0);
        
    }
    
    //#line 38 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
    x10_int middle = ((x10_int) ((low) + (((x10_int) ((((x10_int) ((high) - (low)))) / (((x10_int)2)))))));
    
    //#line 39 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      tmp,
      aux,
      low,
      middle);
    
    //#line 40 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    ((x10aux::ref<MergeSort>)this)->mergeSort(
      tmp,
      aux,
      middle,
      high);
    
    //#line 41 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
    ((x10aux::ref<MergeSort>)this)->merge(
      tmp,
      aux,
      low,
      middle,
      high);
    
    //#line 43 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10Return_c
    return ((x10_int)0);
    
}

//#line 46 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10MethodDecl_c
void MergeSort::merge(x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > tmp,
                      x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > > aux,
                      x10_int low,
                      x10_int middle,
                      x10_int high) {
    
    //#line 50 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
    x10_int i = low;
    
    //#line 51 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
    x10_int j = middle;
    
    //#line 53 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.For_c
    {
        x10_int k;
        for (
             //#line 53 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
             k = low; ((k) < (high)); 
                                      //#line 53 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
                                      k +=
                                        ((x10_int)1))
        {
            
            //#line 55 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10If_c
            if ((x10aux::struct_equals(i,
                                       middle)))
            {
                
                //#line 57 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      j +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            
            //#line 59 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10If_c
            if ((x10aux::struct_equals(j,
                                       high)))
            {
                
                //#line 61 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
                (aux)->set((tmp)->apply((__extension__ ({
                    x10_int t =
                      i +=
                      ((x10_int)1);
                    ((x10_int) ((t) - (((x10_int)1))));
                }))
                ), k);
            }
            else
            
            //#line 63 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10If_c
            if ((x10aux::struct_equals((CompareTo::strcmp(
                                          (tmp)->apply(j)->
                                            FMGL(first),
                                          (tmp)->apply(i)->
                                            FMGL(first))),
                                       ((x10_int)-1))))
            {
                
                //#line 65 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
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
                
                //#line 69 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
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
    
    //#line 73 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.For_c
    {
        x10_int k;
        for (
             //#line 73 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10LocalDecl_c
             k = low; ((k) < (high)); 
                                      //#line 73 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
                                      k +=
                                        ((x10_int)1))
        {
            
            //#line 75 "/home/han6/x10MapReduce/MergeSort.x10": polyglot.ast.Eval_c
            (tmp)->set((aux)->apply(k), k);
        }
    }
    
}

//#line 79 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10MethodDecl_c
x10aux::ref<x10::util::GrowableRail<x10::util::Pair<x10aux::ref<x10::lang::String>, x10_int> > >
  MergeSort::getVariable(
  ) {
    
    //#line 81 "/home/han6/x10MapReduce/MergeSort.x10": x10.ast.X10Return_c
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
