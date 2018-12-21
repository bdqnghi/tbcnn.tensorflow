import java.util.*; 

class quicksort{


  public void sort(int[] arr, int beg, int end)
  {
    if(end <= beg){return;} 
    
    int pivot = partition(arr, beg, end); 
    sort(arr, beg, pivot - 1); 
    sort(arr, pivot + 1, end); 
  }
  
  public int partition(int[] arr, int beg, int end)
  {

    int left = beg; 
    int right = end; 
    int pivot = arr[(beg+end)/2];
    int pivotIndex;
    while(right > left)
    {
      while(arr[right] > pivot)
      { 
        right--; 
      }
      while(arr[left] < pivot)
      { 
        left++; 
      }
      if(left <= right)
      { 
        swap(arr, left, right);
        left++;
        right--; 
      }

    } 
    
    
    return (pivotIndex = left - 1);
  }

  public void swap(int[] arr, int a, int b)
  {
    int temp = arr[a];
    arr[a] = arr[b]; 
    arr[b] = temp; 
  }

  public static void main(String[] args)
  {
    quicksort caller = new quicksort(); 
    
    int[] unorg = new int[]{2, 3, 5, 1, 0, 4, 3};
    caller.sort(unorg, 0, unorg.length-1);
    for(int num : unorg)
      System.out.println(num);
  }
}
