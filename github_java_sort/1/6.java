package Sorting;

public class InsertionSort_JAVA {

    public static void main(String[] args) {
        int test[] = {8, 5, 6, 2, 4};
        System.out.println("삽입정렬 전");
        for (int data : test) {
            System.out.print(data + ", ");
        }
        
        insertionSort(test, test.length);
        
        System.out.println("\n삽입정렬 후");
        for (int data : test) {
            System.out.print(data + ", ");
        }
    }
    
    public static void insertionSort(int[] list, int n) {
        int i, j, key;
        
        
        for (i = 1; i < n; i++) {
            key = list[i]; 
            
            
            
            
            for (j = i - 1; j >= 0 && list[j] > key; j--) {
                list[j+1] = list[j];
            }
            
            list[j+1] = key;
        }
    }
}
