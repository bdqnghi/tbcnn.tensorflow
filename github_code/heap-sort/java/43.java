/*package code;

import given.AbstractArraySort;


 * Implement the heap-sort algorithm here. You can look at the slides for the pseudo-code.
 * Make sure to use the swap and compare functions given in the AbstractArraySort!
 * 
 

public class HeapSort<K extends Comparable<K>> extends AbstractArraySort<K> {

  // Add any fields here

  public HeapSort() {
    name = "Heapsort";

    // Initialize anything else here
  }

  @Override
  public void sort(K[] inputArray) {
    // TODO: Implement the heap-sort algorithm
	  int n =inputArray.length;
	  heapify(inputArray);
	  while(n>1){
		 n--;
		  swap(inputArray,0,n);
		  downheap(inputArray,0);
	  }
	  int k=inputArray.length-1;
	  while(k>0){
		  swap(inputArray,0,k);
		  k--;
		  downheap(inputArray,k);
	  }

  }

  // Public since we are going to check its output!
  public void heapify(K[] inputArray) {
    // TODO: Heapify the array. See the slides for an O(n) version which uses
    // downheap
	 for(int i=inputArray.length/2-1;i>=0;i--){
		 downheap(inputArray,i);
	 }
  }
  
  // The below methods are given given as suggestion. You do not need to use them.
  // Feel free to add more methods
  
  protected void downheap(K[] inputArray, int i) {
    // TODO: Implement the downheap method to help with the algorithm
	  int w=2*i+1;    // first descendant of v
      while (w<inputArray.length)
      {
          if (w+1<inputArray.length)    // is there a second descendant?
              if (compare(inputArray[w+1],inputArray[w])>0) w++;
          // w is the descendant of v with maximum label

          if (compare(inputArray[i],inputArray[w])>=0) return;  // v has heap property
          // otherwise
          swap(inputArray,i, w);  // exchange labels of v and w
          i=w;        // continue
          w=2*i+1;
      }

  }
 
}
*/


/*
 * Implement the heap-sort algorithm here. You can look at the slides for the pseudo-code.
 * Make sure to use the swap and compare functions given in the AbstractArraySort!
 * 
 */

public class HeapSort{

  // Add any fields here

  

  
  public void sort(int[] inputArray) {
    // TODO: Implement the heap-sort algorithm
	  
	  heapify(inputArray);
	  int n =inputArray.length-1;
	  while(n>0){
		 int temp = inputArray[0];
		 inputArray[0]=inputArray[n];
		 inputArray[n]=temp;
		  n--;
		  
		  downheap(inputArray,0,n);
	  }
	  /*int k=inputArray.length-1;
	  while(k>0){
		  swap(inputArray,0,k);
		  k--;
		  downheap(inputArray,k);
	  }*/

  }

  // Public since we are going to check its output!
  public void heapify(int[] inputArray) {
    // TODO: Heapify the array. See the slides for an O(n) version which uses
    // downheap
	 for(int i=inputArray.length/2;i>=0;i--){
		 //asd
		 downheap(inputArray,i,inputArray.length-1);
	 }
  }
  
  // The below methods are given given as suggestion. You do not need to use them.
  // Feel free to add more methods
  
  protected void downheap(int[] inputArray, int i,int k) {
	  int index = i;
	  int lc = 2*i+1;
	  int rc = 2*i+2;
	  if(lc<=k&&inputArray[lc]>inputArray[index]){
		  index=lc;
		 
	  }
	  if(rc<=k&&(inputArray[rc]>inputArray[index])){
		  index=rc;
	  }
	  if(index!=i){
		  int temp = inputArray[i];
			 inputArray[i]=inputArray[index];
			 inputArray[index]=temp;
		  downheap(inputArray,index,k);
	  }
  }
}
