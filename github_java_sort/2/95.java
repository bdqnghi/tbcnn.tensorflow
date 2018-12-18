
{
import java.util.*;
class Merge_Sort
{
	static void printArray(int arr[])
    {
        int n = arr.length;
        for (int i=0; i<n; ++i)
            System.out.print(arr[i] + " ");
        System.out.println();
    }
    static void mergeSort(int arr[], int l, int r)
    {
        GfG g = new GfG();
        if (l < r)
        {
            int m = (l+r)/2;
            mergeSort(arr, l, m);
            mergeSort(arr , m+1, r);
            g.merge(arr, l, m, r);
        }
    }
	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		while(T>0)
		{
			int n = sc.nextInt();
			Merge_Sort ms = new Merge_Sort();
			int arr[] = new int[n];
			for(int i=0;i<n;i++)
				arr[i] = sc.nextInt();
			GfG g = new GfG();
			mergeSort(arr,0,arr.length-1);
			ms.printArray(arr);
		T--;
		}
	}
}

}




class GfG
{
   
   
    void merge(int arr[], int l, int m, int r)
    {
         
         int[] temp = new int[r-l+1];
         int t=0, i=l, j=m+1;
         while(i<=m && j<=r){
             if(arr[i]<=arr[j]) temp[t++] = arr[i++];
             else temp[t++] = arr[j++];
         }
         while(i<=m) temp[t++] = arr[i++];
         while(j<=r) temp[t++] = arr[j++];
         
         for(t=0, i=l; i<=r;) arr[i++] = temp[t++];
    }
}
 
