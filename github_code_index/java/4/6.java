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
        
        // 인덱스 0은 이미 정렬된 것으로 볼 수 있다.
        for (i = 1; i < n; i++) {
            key = list[i]; // 현재 삽입될 숫자인 i번쨰 정수를 key 변수로 복사
            
            // 현재 정렬된 배열은 i-1까지이므로 i-1번째부터 역순으로 조사한다.
            // j값은 음수가 아니어야 하고
            // key 값보다 정렬된 배열에 있는 값이 크면 j번째를 j+1번째로 이동
            for (j = i - 1; j >= 0 && list[j] > key; j--) {
                list[j+1] = list[j];
            }
            
            list[j+1] = key;
        }
    }
}
