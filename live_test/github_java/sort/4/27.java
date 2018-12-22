
import static java.nio.file.Files.size;
import java.util.Random;
import java.util.Scanner;

public class heapsort 
{
    private static int[] a;
    private static int n;
    private static int left;
    private static int right;
    private static int largest;

    
    public static void buildheap(int []a){
        n=a.length-1;
        for(int i=n/2;i>=0;i--){
            maxheap(a,i);
        }
    }
    
    public static void maxheap(int[] a, int i){ 
        left=2*i;
        right=2*i+1;
        if(left <= n && a[left] > a[i]){
            largest=left;
        }
        else{
            largest=i;
        }
        
        if(right <= n && a[right] > a[largest]){
            largest=right;
        }
        if(largest!=i){
            exchange(i,largest);
            maxheap(a, largest);
        }
    }
    
    public static void exchange(int i, int j){
        int t=a[i];
        a[i]=a[j];
        a[j]=t; 
        }
    
    public static void sort(int []a0){
        a=a0;
        buildheap(a);
        
        for(int i=n;i>0;i--){
            exchange(0, i);
            n=n-1;
            maxheap(a, 0);
        }
    }
    
    public static void main(String[] args) 
    {
             Scanner scan = new Scanner( System.in );
             int i,s,r;
             System.out.println("Enter Array Size: \n");             
              s = scan.nextInt();
             System.out.println("Enter range of numbers : \n");
		r = scan.nextInt();
                scan.close();
                int[] arr = new int[s];
		Random random = new Random(); 
		for(i=0; i<s; i++)
		{ 
		 arr[i]= random.nextInt(r); 
		}
      
        
        System.out.println("\nElements after sorting ");        
        for (i = 0; i < s; i++)
            System.out.print(arr[i]+" ");            
        System.out.println();
        }
    }

