

package sort;

import sidl.BaseClass;
import sidl.BaseInterface;
import sidl.ClassInfo;
import sidl.RuntimeException;
import sort.Comparator;
import sort.Container;
import sort.Counter;
import sort.SortingAlgorithm;






public class HeapSort_Impl extends HeapSort
{

  
  
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
  


  static { 
  
  
  

  }

  
  public HeapSort_Impl(long IORpointer){
    super(IORpointer);
    
    
    

  }

  
  public HeapSort_Impl(){
    d_ior = _wrap(this);
    
    
    

  }

  
  public void dtor() throws Throwable{
    
    
    

  }

  
  public void finalize() throws Throwable{
    
    
    

  }

  

  
  
  public void sort_Impl (
     sort.Container elems,
     sort.Comparator comp ) 
    throws sidl.RuntimeException.Wrapper
  {
    
    
     int i;
     int num = elems.getLength();
     sort.Counter cmp = getCompareCounter();
     sort.Counter swp = getSwapCounter();
     
     for(i = ((num/2) - 1); i >= 0; --i) {
       remakeHeap(elems, comp, cmp, swp, num, i);
     }
     
     i = num - 1;
     while (i > 0) {
       swp.inc();
       elems.swap(0, i);
       remakeHeap(elems, comp, cmp, swp, i--, 0);
     }
     return ;
    

  }

  
  public java.lang.String getName_Impl () 
    throws sidl.RuntimeException.Wrapper
  {
    
    
    return new java.lang.String("Heap sort");

    

  }


  
  
  

} 

