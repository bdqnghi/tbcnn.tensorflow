import java.util.Arrays;
import java.util.Random;


public class Heapify {

	
	public static void main(String[] args) {
		
		
		
		int x = 10;
		 
	
		
		int [] A = odwrocona(x);
		   
		
	
	
   
  
	
	
	System.out.println("Heap-Sort przed: "+ Arrays.toString(A));
	long start= System.currentTimeMillis();	
	
	long stop = System.currentTimeMillis();
	System.out.println("Heap-Sort po"+ Arrays.toString(heapsort(A)));
	System.out.println("Czas dzia�ania Heap-Sort:"+ (stop-start));
		
	 
		
		
	   
	  
			


		System.out.println("Insert-Sort przed: "+ Arrays.toString(A));
		long startInsert= System.currentTimeMillis();	
		insertSort(A);
		long stopInsert = System.currentTimeMillis();
		System.out.println("Insert-Sort po: "+ Arrays.toString(insertSort(A)));
		
		System.out.println("Czas dzia�ania INSERT:"+ (stopInsert-startInsert));
	
	 
	 
	
   
	
		
	System.out.println("Merge-Sort przed: "+ Arrays.toString(A));
	long startMerge= System.currentTimeMillis();
	mergeSort(A);
	long stopMerge = System.currentTimeMillis();
    System.out.println("Merge-Sort po: "+ Arrays.toString(mergeSort(A)));
	System.out.println("Czas dzia�ania Merge-Sort:"+ (stopMerge-startMerge));
	 
	 
	
	
   
  
		 
	;		 
	int r= A.length-1;
	int p = 0;
	System.out.println("Quick-Sort przed: "+Arrays.toString(A));
	long startQuick= System.currentTimeMillis();
	Quicksort(A, p, r);
	long stopQuick= System.currentTimeMillis();
	System.out.println("Quick-Sort po: "+Arrays.toString(Quicksort(A, p, r)));

	
	System.out.println("Czas dzia�ania Quicksorta:"+ (stopQuick-startQuick));
	
	 
	

	
	}
	
	
	
	
	
   
  
	
	public static int []  heapsort(int [] A){
		int [] tab = new int[A.length];
		System.arraycopy(A, 0, tab, 0, A.length);
		
		for(int c=A.length-1;c>=1;c--){	
		
		int largest ;
		int pomoc ;
		int dlugosc = (c-1)/2;
	
		for(int j = dlugosc; j>=0; j--){
			for(int i=dlugosc;i>=0;i--){
				int left = (2*i)+1;
				int right = (2*i)+2;
				if((left <=c) && (right<=c)){
			
			if(tab[right] >= tab[left]){
				largest=right;
			}
			else
			{
				largest=left;
			}
		}
		else{
			if(right>c){
				largest=left;
			}
			else{
				largest=right;
			}
		}
		
		if(tab[largest] > tab[i])
		{
			pomoc = tab[largest];
			tab[largest]= tab[i];
			tab[i]= pomoc;
			
		}
		}
		}
		
		pomoc = tab[0];
		tab[0]= tab[c];
		tab[c]= pomoc;
	
		
		
	
	}
		return tab;
	}

	
	
   
  
	
	public static int [] insertSort(int[] A){	
		int [] tab = new int[A.length];
		System.arraycopy(A, 0, tab, 0, A.length);
		int i,j,x =0;
		int n= tab.length;
		for (i=n-2;i>=0;i--){
			x= tab[i];
			j =i+1;
			while ((j<n) && (x>tab[j])){
				tab[j-1]= tab[j];
				j++;
			}
			tab[j-1]=x;
		}
		return tab;
	}
	
	
   
  

	public static int [] mergeSort(int A[]){
		int [] tab = new int[A.length];
		int k=0;
		for (int i= A.length-1; i>=0; i --){
			tab[k]= A[i];
			k++;
		}
		if (tab.length>1){
			
			int [] lewaPolowa = left(tab);
			int [] prawaPolowa = right(tab);
			
			mergeSort(lewaPolowa);
			mergeSort(prawaPolowa);
			
			merge(tab,lewaPolowa,prawaPolowa);
		}
		return tab;
		
	}

	
	
	public static int[] left(int [] A){
		int size = A.length/2;
		int [] left = new int[size];
		for (int i=0; i<size;i++){
			left[i] = A[i];
		}
		return left;
	}
	
	public static int[] right(int [] A ){
		int size1 = A.length/2;
		int size2 = A.length -size1;
		int [] right = new int [size2];
		for(int i=0; i<size2;i++){
			right[i] = A[i+size1];
		}
		return right;
	}
	
	
	
	public static void merge(int[] B, int[] lewaPolowa, int[] prawaPolowa){
		int i1 = 0;	
		int i2 = 0;
		for(int i =0; i<B.length; i++){	
		if(i2 >= prawaPolowa.length || (i1 < lewaPolowa.length && lewaPolowa[i1] <=prawaPolowa[i2])){
			B[i]=lewaPolowa[i1];
			i1++;
		 }
		else
		{
			B[i]=prawaPolowa[i2];
			i2++;
		}
		}
		
	}
	
	
   
  
	
	public static int [] Quicksort(int [] A, int p, int r){
		int [] tab = new int[A.length];
		int k=0;
		for (int i= A.length-1; i>=0; i --){
			tab[k]= A[i];
			k++;
		}
		if (p<r){
		
			int q = Partiton(tab, p, r);
			Quicksort(tab, p, q-1);
			Quicksort(tab,q+1,r);
			
		}
		return tab;
	}
	
	
	public static int Partiton(int [] A, int p, int r)
	{
		int x = A[r];
		int i = p-1;
		
		for(int j=p; j<r-1;j++){
			 if(A[j]<=x){
				 i=i+1;
				 int pomoc = A[i];
					A[i]=A[j];
					A[j]= pomoc;
			 }
		}
		 
			
			
				
		return i+1;
		
	}
	
	public static int [] poKolei( int x){
	
			
			int [] A = new int [x];
			for (int i=0;i<x;i++){
				A[i]=i;
			}
		
			return A;	
	}
	
	public static int [] losowa(int x){
		
	
			 
			
			int liczby=100;
			int [] A = new int[x];
			Random rand = new Random();
			for(int j=0;j<x;j++){
				
				A[j]= rand.nextInt(liczby);
			}
			return A;
		
	}
	
	public static int [] odwrocona(int x){
		
		 
		int k=0;
		int [] A = new int[x];
		for (int j=x; j>0;j--){
			A[k] = j;
			k++;
		
		}
		
		return A;
	}

}