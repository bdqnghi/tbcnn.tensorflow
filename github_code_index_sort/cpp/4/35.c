// 
// File:          sort_HeapSort_Impl.cxx
// Symbol:        sort.HeapSort-v0.1
// Symbol Type:   class
// Babel Version: 1.4.0 (Revision: 6607 release-1-4-0-branch)
// Description:   Server-side implementation for sort.HeapSort
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "sort_HeapSort_Impl.hxx"

// 
// Includes for all method dependencies.
// 
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
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(sort.HeapSort._includes)
// Put additional includes or other arbitrary code here...
static void remakeHeap(::sort::Container &elem,
                       ::sort::Comparator &comp,
                       ::sort::Counter &cmp,
                       ::sort::Counter &swp,
                       const int32_t last,
                       int32_t first)
{
  const int32_t half = (last >> 1) - 1;
  int32_t child;
  while (first <= half) {
    child = first + first + 1;
    if ((child+1) < last) {
      cmp.inc();
      if (elem.compare(child, child+1, comp) < 0) ++child;
    }
    cmp.inc();
    if (elem.compare(first, child, comp) >= 0) break;
    swp.inc();
    elem.swap(first, child);
    first = child;
  }
}
// DO-NOT-DELETE splicer.end(sort.HeapSort._includes)

// special constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
sort::HeapSort_impl::HeapSort_impl() : StubBase(reinterpret_cast< void*>(
  ::sort::HeapSort::_wrapObj(reinterpret_cast< void*>(this))),false) , _wrapped(
  true){ 
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._ctor2)
  // Insert-Code-Here {sort.HeapSort._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(sort.HeapSort._ctor2)
}

// user defined constructor
void sort::HeapSort_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(sort.HeapSort._ctor)
}

// user defined destructor
void sort::HeapSort_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(sort.HeapSort._dtor)
}

// static class initializer
void sort::HeapSort_impl::_load() {
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._load)
  // guaranteed to be called at most once before any other method in this class
  // DO-NOT-DELETE splicer.end(sort.HeapSort._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Sort elements using Heap Sort.
 */
void
sort::HeapSort_impl::sort_impl (
  /* in */::sort::Container& elems,
  /* in */::sort::Comparator& comp ) 
{
  // DO-NOT-DELETE splicer.begin(sort.HeapSort.sort)
  int32_t i;
  const int32_t num = elems.getLength();
  ::sort::Counter cmp = getCompareCounter();
  ::sort::Counter swp = getSwapCounter();
  /* make the heap */
  for(i = ((num/2) - 1); i >= 0; --i) {
    remakeHeap(elems, comp, cmp, swp, num, i);
  }
  /* put top of heap at back and remake the heap */
  i = num - 1;
  while (i > 0) {
    swp.inc();
    elems.swap(0, i);
    remakeHeap(elems, comp, cmp, swp, i--, 0);
  }
  // DO-NOT-DELETE splicer.end(sort.HeapSort.sort)
}

/**
 * Return heap sort.
 */
::std::string
sort::HeapSort_impl::getName_impl () 

{
  // DO-NOT-DELETE splicer.begin(sort.HeapSort.getName)
  return "Heap sort";
  // DO-NOT-DELETE splicer.end(sort.HeapSort.getName)
}


// DO-NOT-DELETE splicer.begin(sort.HeapSort._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(sort.HeapSort._misc)

