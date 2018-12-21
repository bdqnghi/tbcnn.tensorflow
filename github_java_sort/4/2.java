
Code Description :

*maxheap(int[] a, int i) : It helps us to maintain the property of Max-Heap i.e. the root value is always greater than the child value and it takes a time of O(lg n). Therefore, we can say that the running time of maxheap(int [] a, int i) on a tree of height h  is O(h). 

*buildheap(int[] a) : We use the maxheap() function in a bottom-up manner to create an array A[1..n], where n=A.length, into a Max-Heap. The function buildheap() goes through the remaining elements i.e. A[(n/2)+1, n] thus it take linear time, produces a max-heap from an unordered input array. 


public class HeapSort 
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
    
    public static void main(String[] args) {
        int []a1={4,1,3,2,16,9,10,14,8,7};
        sort(a1);
        for(int i=0;i<a1.length;i++){
            System.out.print(a1[i] + " ");
        }
    }
}

OUTPUT :

1 2 3 4 7 8 9 10 14 16 
