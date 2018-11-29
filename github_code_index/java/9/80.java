/*
 * File:          HeapSort_Impl.java
 * Symbol:        sort.HeapSort-v0.1
 * Symbol Type:   class
 * Babel Version: 1.4.0 (Revision: 6563M trunk)
 * Description:   Server-side implementation for sort.HeapSort
 * 
 * WARNING: Automatically generated; only changes within splicers preserved
 * 
 */

package sort;

import sidl.BaseClass;
import sidl.BaseInterface;
import sidl.ClassInfo;
import sidl.RuntimeException;
import sort.Comparator;
import sort.Container;
import sort.Counter;
import sort.SortingAlgorithm;

// DO-NOT-DELETE splicer.begin(sort.HeapSort._imports)
// Put additional imports here...
// DO-NOT-DELETE splicer.end(sort.HeapSort._imports)

/**
 * Symbol "sort.HeapSort" (version 0.1)
 * 
 * Heap sort
 */
public class HeapSort_Impl extends HeapSort
{

  // DO-NOT-DELETE splicer.begin(sort.HeapSort._data)
  // Put additional private data here...
  static void remakeHeap(sort.Container elem,
                         sort.Comparator comp,
                         sort.Counter cmp,
                         sort.Counter swp,
                         int last,
                         int first)
  {
    int half = (last >> 1) - 1;
    int child;
    while (first <= half) {
      child = first + first + 1;
      if ((child+1) < last) {
        cmp.inc();
        if (elem.compare(child, child+1, comp) < 0) ++child;
      }
      cmp.inc();
      if (elem.compare(first, child,comp) >= 0) break;
      swp.inc();
      elem.swap(first, child);
      first = child;
    }
  }
  // DO-NOT-DELETE splicer.end(sort.HeapSort._data)


  static { 
  // DO-NOT-DELETE splicer.begin(sort.HeapSort._load)
  // Put load function implementation here...
  // DO-NOT-DELETE splicer.end(sort.HeapSort._load)

  }

  /**
   * User defined constructor
   */
  public HeapSort_Impl(long IORpointer){
    super(IORpointer);
    // DO-NOT-DELETE splicer.begin(sort.HeapSort.HeapSort)
    // add construction details here
    // DO-NOT-DELETE splicer.end(sort.HeapSort.HeapSort)

  }

  /**
   * Back door constructor
   */
  public HeapSort_Impl(){
    d_ior = _wrap(this);
    // DO-NOT-DELETE splicer.begin(sort.HeapSort._wrap)
    // Insert-Code-Here {sort.HeapSort._wrap} (_wrap)
    // DO-NOT-DELETE splicer.end(sort.HeapSort._wrap)

  }

  /**
   * User defined destructing method
   */
  public void dtor() throws Throwable{
    // DO-NOT-DELETE splicer.begin(sort.HeapSort._dtor)
    // add destruction details here
    // DO-NOT-DELETE splicer.end(sort.HeapSort._dtor)

  }

  /**
   * finalize method (Only use this if you're sure you need it!)
   */
  public void finalize() throws Throwable{
    // DO-NOT-DELETE splicer.begin(sort.HeapSort.finalize)
    // Insert-Code-Here {sort.HeapSort.finalize} (finalize)
    // DO-NOT-DELETE splicer.end(sort.HeapSort.finalize)

  }

  // user defined static methods: (none)

  // user defined non-static methods:
  /**
   * Sort elements using Heap Sort.
   */
  public void sort_Impl (
    /*in*/ sort.Container elems,
    /*in*/ sort.Comparator comp ) 
    throws sidl.RuntimeException.Wrapper
  {
    // DO-NOT-DELETE splicer.begin(sort.HeapSort.sort)
    // insert implementation here
     int i;
     int num = elems.getLength();
     sort.Counter cmp = getCompareCounter();
     sort.Counter swp = getSwapCounter();
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
     return ;
    // DO-NOT-DELETE splicer.end(sort.HeapSort.sort)

  }

  /**
   * Return heap sort.
   */
  public java.lang.String getName_Impl () 
    throws sidl.RuntimeException.Wrapper
  {
    // DO-NOT-DELETE splicer.begin(sort.HeapSort.getName)
    // insert implementation here
    return new java.lang.String("Heap sort");

    // DO-NOT-DELETE splicer.end(sort.HeapSort.getName)

  }


  // DO-NOT-DELETE splicer.begin(sort.HeapSort._misc)
  // Put miscellaneous code here
  // DO-NOT-DELETE splicer.end(sort.HeapSort._misc)

} // end class HeapSort

