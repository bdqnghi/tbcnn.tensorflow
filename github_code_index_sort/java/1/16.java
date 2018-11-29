/**************************************************************************************************/
/***************************SULEYMAN YILDIRIM******************************************************/
/********************************ODEV_1************************************************************/
/**************************************************************************************************/

import java.util.*;
public class homework1{
	/**
	 * @S�leymanY�ld�r�m 
	 * 
	 */
	 public static final int N = 200000; 
     public static final int K = 400;
     public static void main(String[ ] args){
     int i;                      // Array index	
     int[ ] merge = new int[N];   //saf merge.sort i�in array
     int[ ] ins = new int[N];  //insertion.sort i�in array
     int[ ] melez = new int[N];  //melez merge.sort i�in array
     Random r = new Random();	 //random say� ureten degisken
     //dizi elemanlari rasgele �retiliyor
     for (i=0;i<N;i++) {
    	 merge[i]=r.nextInt(N);//uretilen dizi elemanlar� saf merge.sort i�in saklan�yor
    	 ins[i]=merge[i]; //uretilen dizi elemanlar� insertion.sort i�in saklan�yor
    	 melez[i]=merge[i]; //uretilen dizi elemanlar� melez merge.sort i�in saklan�yor
    	 }
    System.out.println("Values Before the sort:");
	System.out.print("---------------------"+"  	 ");
	System.out.print("---------------------"+"   ");
	System.out.println("---------------------"+"");
     for(i = 0; i <merge.length; i++){ 
    	if (i==0){
    		System.out.print("PURE-MERGE-SORT ARRAY 	 ");
    		System.out.print("INSERTION-SORT ARRAY 	 ");
    		System.out.println("MELEZ-MERGE-SORT ARRAY 	 ");
    		System.out.print("---------------------"+"  	 ");
    		System.out.print("---------------------"+"   ");
    		System.out.println("---------------------"+"");
    	}
        System.out.print(merge[i]+"				");
        System.out.print(ins[i]+"				");
        System.out.println(melez[i]+"	");
          }//end-for
         System.out.println();  
     /***************MERGE-SORT �ALI�MA ZAMANI HESAPLAMASI********************/    
     Calendar pure1 = Calendar.getInstance();	//sure hesab� i�in obje yarat�ld� 
     long s1=pure1.getTimeInMillis();			//sure ba�lad�
     mergeSortPure(merge,0, N-1); 
     Calendar pure2 = Calendar.getInstance();
     long s2=pure2.getTimeInMillis();			//sure bitti
     long s3=s2-s1;  
     /*************** INSERTION-SORT  �ALI�MA ZAMANI HESAPLAMASI*****************/    
     Calendar inst1 = Calendar.getInstance();	//sure hesab� i�in obje yarat�ld� 
     long s4=inst1.getTimeInMillis();			//sure ba�lad�
     insertionSort(ins,N-1);
     Calendar inst2 = Calendar.getInstance();	
     long s5=inst2.getTimeInMillis();			//sure bitti
     long s6=s5-s4;
     /***************Melez MERGE-SORT �ALI�MA ZAMANI HESAPLAMASI***********************/    
     Calendar melez1 = Calendar.getInstance();	//sure hesab� i�in obje yarat�ld� 
     long s7=melez1.getTimeInMillis();			//sure ba�lad�
     mergeSortMelez(melez,0, N-1); 
     Calendar melez2 = Calendar.getInstance();
     long s8=melez2.getTimeInMillis();			//sure bitti
     long s9=s8-s7;   
     System.out.print("Values after PURE-MERGE-SORT:\n");
       for(i = 0; i <merge.length; i++){ 
    	if ((i%30)==0)System.out.println();
    	System.out.print(merge[i]+"  ");
      	}
     	System.out.println(" ");
     System.out.print("Values after INSERTION-SORT:\n");
     for(i = 0; i <ins.length; i++){ 
        if ((i%30)==0)System.out.println();
       	System.out.print(ins[i]+"  ");
      	}
        System.out.println();
     System.out.print("Values after MELEZ MERGE-SORT:\n");
     for(i = 0; i <melez.length; i++){ 
        if ((i%30)==0)System.out.println();
       	System.out.print(melez[i]+"  ");
      	}
        System.out.println();    
        System.out.println ("RUNNING TIME for MERGE-SORT : " + s3 + " msec");
        System.out.println ("RUNNING TIME for INSERTION-SORT : " + s6 + " msec");
        System.out.println ("RUNNING TIME for MELEZ MERGE-SORT : " + s9 + " msec");     
}//end main()

public static void mergeSortPure(int array[],int lo, int n){
     int low = lo;
	 int high = n;   
	 if (low>=high) {
	    return;
	 }
	 int middle = (low + high) / 2;
	 //dizinin sol taraf� rek�rsif olarak ayri�t�r�l�yor
	 mergeSortPure(array, low, middle);  
	 //dizinin sag taraf� rek�rsif olarak ayr��t�r�l�yor
	 mergeSortPure(array, middle + 1, high); 
	 //Birlestirme i�lemi basliyor
     int end_low = middle;
	 int start_high = middle + 1;
	 while ((low <= end_low) && (start_high <= high)) {
		 if (array[low] < array[start_high]) {
	        low++;
	        } else {
	               int Temp = array[start_high];
	               for (int k = start_high- 1; k >= low; k--) {
	               array[k+1] = array[k];
	               }//end-for
	               array[low] = Temp;
	               low++;
	               end_low++;
	               start_high++;
	     }//end-if
     }//end-while //Birle�tirme i�leminin sonu
   } //end-MergeSortPure	
   
public static void mergeSortMelez(int array[],int lo, int n){
     int A; //surekli azalan N degerini temsil eden degisken
	 int low = lo;
	 int high = n;  
	 int middle = (low + high) / 2;
	 A=high-low; //A=N-K
	 //parcalara ayr�lan dizi eleman� K'ya ulast�g� anda insertion sort algoritmas�na ge�ilir.
	 if (A<=K) {
		 insertionSort(array,high);
		 return;
	 }//end-if
  	 //dizinin sol taraf� rek�rsif olarak ayri�t�r�l�yor
	 mergeSortMelez(array, low, middle);  
	 //dizinin sag taraf� rek�rsif olarak ayr��t�r�l�yor
	 mergeSortMelez(array, middle + 1, high);
  	 //Birlestirme i�lemi basliyor
	 int end_low = middle;
	 int start_high = middle + 1;
	 while ((low <= end_low) && (start_high <= high)) {
		 if (array[low] < array[start_high]) {
			 low++;
		 } else {
			    int Temp = array[start_high];
			    for (int k = start_high- 1; k >= low; k--) {
				  array[k+1] = array[k];
			    }//end-for
			    array[low] = Temp;
			  	low++;
			  	end_low++;
			  	start_high++;
         }//end-if
    }//end-while//Birle�tirme i�leminin sonu
} //end-MergeSortMelez
    	
    //insertionSort() fonksiyonu 
static void insertionSort(int[] arr,int lo) {
     int i, j, newValue;
     for (i = 1; i <= lo; i++) {
          newValue = arr[i];
          j = i;
          while (j > 0 && arr[j - 1] > newValue) {
                  arr[j] = arr[j - 1];
                  j--;
           }
           arr[j] = newValue;
     }//end-for
  }//end-insertionSort
}//end "class" merge

