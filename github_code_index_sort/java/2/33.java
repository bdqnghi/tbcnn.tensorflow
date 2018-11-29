package arithmetic;
//归并排序
public class MergeSort {
	private long[] theArray;
	private int nElems;
	
	public MergeSort(int max){
		theArray = new long[max];
		nElems = 0;
	}
	public void insert(long value){
		theArray[nElems] = value;
		nElems++;
	}
	public void display(){
		for(int j=0;j<nElems;j++){
			System.out.print(theArray[j]+" ");
		}
		System.out.println("");
	}
	public void mergeSort(){
		long[] workSpace = new long[nElems];
		recMergeSort(workSpace,0,nElems-1);
	}
	private void recMergeSort(long[] workSpace,int lowerBound,int upperBound){
		if(lowerBound==upperBound){
			return;
		}else{
			int mid = (lowerBound+upperBound)/2;
			recMergeSort(workSpace, lowerBound, mid);
			recMergeSort(workSpace, mid+1, upperBound);
			merge(workSpace,lowerBound,mid+1,upperBound);
		}
	}
	private void merge(long[] workSpace,int lowPtr,int highPtr,int upperBound){
		int j=0;
		int lowerBound = lowPtr;
		int mid = highPtr-1;
		int n = upperBound-lowerBound+1;
		while(lowPtr<=mid&&highPtr<=upperBound){
			if(theArray[lowPtr]<theArray[highPtr]){
				workSpace[j++]=theArray[lowPtr++];
			}else{
				workSpace[j++] = theArray[highPtr++];
			}
		}
		while(lowPtr<=mid){
			workSpace[j++]=theArray[lowPtr++];
		}
		while(highPtr<=upperBound){
			workSpace[j++]=theArray[highPtr++];
		}
		for(j=0;j<n;j++){
			theArray[lowerBound+j]=workSpace[j];
		}
	}
	public static void main(String[] args) {
		int maxSize = 100;
		MergeSort mergeSort;
		mergeSort = new MergeSort(maxSize);
		
		mergeSort.insert(64);
		mergeSort.insert(21);
		mergeSort.insert(33);
		mergeSort.insert(70);
		mergeSort.insert(12);
		mergeSort.insert(85);
		mergeSort.insert(44);
		mergeSort.insert(3);
		mergeSort.insert(99);
		mergeSort.insert(0);
		mergeSort.insert(108);
		mergeSort.insert(36);
		
		mergeSort.display();
		mergeSort.mergeSort();
		mergeSort.display();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
