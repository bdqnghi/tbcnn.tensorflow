/*Implement Merge Sort */
 
    public static int[] merge_sort(int arr[]){
      if(arr.length <= 1) return arr;
      
      int middle = arr.length / 2;
      int leftArray[] = new int[middle];
      int rightArray[] = new int [arr.length - middle];
      
      //Populate left array with left half of input array
      for(int i = 0; i < middle; i++)
        leftArray[i] = arr[i];
      
      //Populate right array with right half of input array
      int rIndex = 0;
      for(int j = middle; j < arr.length; j++)
       rightArray[rIndex++] = arr[j];
      
      //Recursive calls on left array and on right array
      leftArray = merge_sort(leftArray);
      rightArray = merge_sort(rightArray);
      
      //Merge the results and return
      return  merge(leftArray, rightArray);
      
    }
    
    public static int[] merge(int left[],int right[]){
      int result[]  = new int[left.length + right.length];
      int lIndex = 0;
      int rIndex = 0;
      int resultIndex = 0;
      
      while(lIndex < left.length || rIndex < right.length){
      
        //Condition 1. We have elements on both sides
          if(lIndex < left.length && rIndex < right.length){
            if(left[lIndex] <= right[rIndex])
              result[resultIndex++] = left[lIndex++];
            else  
              result[resultIndex++] = right[rIndex++]; 
        
          }else{
         
         //Condition 2. We only have elements on left side
          if(lIndex < left.length)    
          result[resultIndex++] = left[lIndex++];
         
         //Condition 3. We only have elements on the right side
          if(rIndex < right.length)
          result[resultIndex++] = right[rIndex++];
        }
      }
      return result;
    }

