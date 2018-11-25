










#ifndef included_sort_HeapSort_Impl_hxx
#define included_sort_HeapSort_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_sort_HeapSort_IOR_h
#include "sort_HeapSort_IOR.h"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sort_Comparator_hxx
#include "sort_Comparator.hxx"
#endif
#ifndef included_sort_Container_hxx
#include "sort_Container.hxx"
#endif
#ifndef included_sort_Counter_hxx
#include "sort_Counter.hxx"
#endif
#ifndef included_sort_HeapSort_hxx
#include "sort_HeapSort.hxx"
#endif
#ifndef included_sort_SortingAlgorithm_hxx
#include "sort_SortingAlgorithm.hxx"
#endif






namespace sort { 

  
  class HeapSort_impl : public virtual ::sort::HeapSort 
  
  
  

  {

  
  
  protected:

    bool _wrapped;

    
    
    

  public:
    
    HeapSort_impl();
    
    
    
    HeapSort_impl( struct sort_HeapSort__object * ior ) : StubBase(ior,true) , 
      _wrapped(false) {_ctor();}


    
    void _ctor();

    
    virtual ~HeapSort_impl() { _dtor(); }

    
    void _dtor();

    
    inline bool _isWrapped() {return _wrapped;}

    
    static void _load();

  public:


    
    void
    sort_impl (
      ::sort::Container& elems,
      ::sort::Comparator& comp
    )
    ;


    
    ::std::string
    getName_impl() ;
  };  

} 





#endif
