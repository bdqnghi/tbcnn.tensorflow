









#include "sort_HeapSort_Impl.hxx"




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



sort::HeapSort_impl::HeapSort_impl() : StubBase(reinterpret_cast< void*>(
  ::sort::HeapSort::_wrapObj(reinterpret_cast< void*>(this))),false) , _wrapped(
  true){ 
  
  
  
}


void sort::HeapSort_impl::_ctor() {
  
  
  
}


void sort::HeapSort_impl::_dtor() {
  
  
  
}


void sort::HeapSort_impl::_load() {
  
  
  
}





void
sort::HeapSort_impl::sort_impl (
  ::sort::Container& elems,
  ::sort::Comparator& comp ) 
{
  
  int32_t i;
  const int32_t num = elems.getLength();
  ::sort::Counter cmp = getCompareCounter();
  ::sort::Counter swp = getSwapCounter();
  
  for(i = ((num/2) - 1); i >= 0; --i) {
    remakeHeap(elems, comp, cmp, swp, num, i);
  }
  
  i = num - 1;
  while (i > 0) {
    swp.inc();
    elems.swap(0, i);
    remakeHeap(elems, comp, cmp, swp, i--, 0);
  }
  
}


::std::string
sort::HeapSort_impl::getName_impl () 

{
  
  return "Heap sort";
  
}






