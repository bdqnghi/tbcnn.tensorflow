package quickSort;



public class Quicksort {
	
	
public static int partition(int arr[], int low, int high)
 {
     int pivot = arr[high]; 
     int i = (low-1); 
     for (int j=low; j<high; j++)
     {
         
         
         if (arr[j] <= pivot)
         {
             i++;

             
             int temp = arr[i];
             arr[i] = arr[j];
             arr[j] = temp;
         }
     }

     
     int temp = arr[i+1];
     arr[i+1] = arr[high];
     arr[high] = temp;

     return i+1;
 }


 
 public static void sort(int arr[], int low, int high)
 {
     if (low < high)
     {
         
         int pi = partition(arr, low, high);

         
         
         sort(arr, low, pi-1);
         sort(arr, pi+1, high);
     }
 }

 
 public static void printArray(int arr[])
 {
     int n = arr.length;
     for (int i=0; i<n; ++i)
         System.out.print(arr[i]+" ");
     System.out.println();
 }
 
 
 public static double findMedian(int arr[]) {
	 int length = arr.length;
	 if (length % 2 == 1) {
		 
		 return (double)arr[length/2];
	 }
	 
	 
	 return (double)(arr[length/2-1] + arr[(length/2)])/2;
 }

 
 public static void main(String args[])
 {
     int arr[] = {10, 7, 8, 4, 9, 1, 5};
     int n = arr.length;


     sort(arr, 0, n-1);

     System.out.println("sorted array");
     printArray(arr);
     
     System.out.println("median");
     System.out.println(findMedian(arr));
 }
}



	

