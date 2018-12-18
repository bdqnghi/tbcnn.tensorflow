

public class MyInsertionSort {

    

    public static void main(String[] args) {
        
        int arr1 []= {3,6,3,8,7,0,12,32,-1,100};


        int[] arr2=insertsort(arr1);

        for (int i:arr2){
            System.out.print(i);
            System.out.print(", ");
        }

   }
 public static int[] insertsort(int [] input){


     int temp;
     for (int i =0; i<input.length; i++){
         for (int j=i; j>0; j--)
         {
           if(input[j]<input[j-1]){
             temp=input[j];
             input[j]=input[j-1];
             input[j-1]=temp;
         }
         }
     }
     return input;
         }
 }


