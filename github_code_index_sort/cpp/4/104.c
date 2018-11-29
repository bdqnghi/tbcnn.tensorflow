// 
// File:          sort_HeapSort_Impl.hxx
// Symbol:        sort.HeapSort-v0.1
// Symbol Type:   class
// Babel Version: 1.4.0 (Revision: 6607 release-1-4-0-branch)
// Description:   Server-side implementation for sort.HeapSort
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

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


// DO-NOT-DELETE splicer.begin(sort.HeapSort._hincludes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(sort.HeapSort._hincludes)

namespace sort { 

  /**
   * Symbol "sort.HeapSort" (version 0.1)
   * 
   * Heap sort
   */
  class HeapSort_impl : public virtual ::sort::HeapSort 
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(sort.HeapSort._inherits)

  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(sort.HeapSort._implementation)
    // Put additional implementation details here...
    // DO-NOT-DELETE splicer.end(sort.HeapSort._implementation)

  public:
    // default constructor, used for data wrapping(required)
    HeapSort_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    HeapSort_impl( struct sort_HeapSort__object * ior ) : StubBase(ior,true) , 
      _wrapped(false) {_ctor();}


    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~HeapSort_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // true if this object was created by a user newing the impl
    inline bool _isWrapped() {return _wrapped;}

    // static class initializer
    static void _load();

  public:


    /**
     * Sort elements using Heap Sort.
     */
    void
    sort_impl (
      /* in */::sort::Container& elems,
      /* in */::sort::Comparator& comp
    )
    ;


    /**
     * Return heap sort.
     */
    ::std::string
    getName_impl() ;
  };  // end class HeapSort_impl

} // end namespace sort

// DO-NOT-DELETE splicer.begin(sort.HeapSort._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(sort.HeapSort._hmisc)

#endif
