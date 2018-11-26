import java.util.Arrays;
class SortingHeap{

void heapify(int arr[],int size,int i)
{
	int swapwith=i;
	int l=2*i+1;
	int r=2*i+2;
	
	
	
	if(l<size && arr[l]>arr[swapwith]) //ensuring max is the root
	{
		swapwith=l;
	}
	if(r<size && arr[r]>arr[swapwith]) //what the fuck just happened? if i replace swapwith with i in both the conditions, then result changes. WTF
	{
		swapwith=r;
	}	
	
	if(swapwith != i)
	{
		int tmp =arr[i];
		arr[i] = arr[swapwith];
		arr[swapwith] = tmp;

		heapify(arr,size,swapwith); //heapify the affected sub-tree
	}	
		
}	
void sort(int arr[],int size)
{
	for(int i=(size/2)-1;i>=0;i--)
	{
		//System.out.println(Arrays.toString(arr));
		heapify(arr,size,i);
	}
	
	for (int i=size-1; i>=0; i--)
    {
        // Move current root to end
        //swap(arr[0], arr[i]);
		int tmp =arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		
		//System.out.println(Arrays.toString(arr));
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }	
	 // for(int i=0;i<size;i++)
	 // {
		 // int tmp =arr[0];
		 // arr[0] = arr[size-i-1];
		 // arr[size-i-1] = tmp;
		
		 // this.heapify(arr,size-i-1,0); //heapify from root i.e node 0
	 // }
}
}
class Heapsort{

public static void main(String args[])
{
int[] arr = {12, 11, 13, 5, 6, 7};//{1,4,3,2,8,7};
SortingHeap obj=new SortingHeap();
obj.sort(arr,6);

for(int i=0;i<6;i++)
	System.out.print(arr[i]+" ")	;
}}