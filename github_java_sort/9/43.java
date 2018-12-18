

package relearn1;
import java.util.*;

public class desmath {
      
    public static void select(int[] array){  
        
        for (int i=0;i<array.length-1;i++)  
        {  
            int index=i; 
            for (int j=i+1;j<array.length;j++){
                if (array[j]<array[index]){  
                    index=j;
                }  
            }  
            int small=array[index];  
            array[index]=array[i];  
            array[i]=small;  
            
            
        }  
    }  
    public static void main(String a[]){ 

            int[] test = {350,420,69,911,72,711,80085,1};

            System.out.println("Numbers before they are sorted"); 

            for(int i=0;i<test.length; i++){  
                System.out.print(test[i]+" ");  
            }  

            System.out.println();  

            select(test);

            System.out.println("Numbers after they are sorted");  

            for(int i=0; i<test.length;i++){  
                System.out.print(test[i]+" ");  
            }  

    }
}