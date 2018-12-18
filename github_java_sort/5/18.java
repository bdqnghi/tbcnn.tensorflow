package Sorting;

public class BubbleSort_JAVA {
    public static void main(String[] args) {
        int[] test = {7, 4, 5, 1, 3};
        
        System.out.println("소팅 전");
        for (int data : test) {
            System.out.print(data + ", "); 
        }
        
        bubbleSort(test, test.length);
        
        System.out.println("\n소팅 후");
        for (int data : test) {
            System.out.print(data + ", "); 
        }
    }
    
    public static void bubbleSort(int[] list, int n) {
        int i, j, tmp;
        
        for (i = n - 1; i > 0; i--) {
            System.out.print("gg");
            for (j = 0; j < i; j++) {
                if (list[j] > list[j + 1]) {
                    tmp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = tmp;
                }
            }
        }
    }
}
