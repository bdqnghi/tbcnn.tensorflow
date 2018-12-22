package Sorting;

import java.util.Iterator;

// 선택 정렬 (selection sort)
// => 제자리 정렬(in-place sorting) 알고리즘의 하나
//    - 입력 배열(정렬되지 않은 값들) 이외의 다른 추가 메모리를 요구하지 않는 정렬 방법
// => 해당 순서에 원소를 넣을 위치는 이미 정해져 있고, 어떤 원소를 넣을지 선택하는 알고리즘
//    - 첫 번째 순서에는 첫 번째 위치에 가장 최솟값을 넣는다.
//    - 두 번째 순서에는 두 번째 위치에 남은 값 중에서의 최솟값을 넣는다.
//    - ...
// => 과정 설명
//    1. 주어진 배열 중 최솟값을 찾는다.
//    2. 그 값을 맨 앞에 위치한 값과 교체한다(패스(pass))
//    3. 맨 처음 위치를 뺸 나머지 리스트를 같은 방법으로 교체한다.
//    4. 하나의 원소만 남을 때까지 위의 1~3 과정을 반복한다.
//
// 선택 정렬 (selection sort) 알고리즘의 특징
// => 장점
//    - 자료 이동 횟수가 미리 결정된다.
// => 단점
//    - 안정성을 만족하지 않는다.
//    - 즉, 값이 같은 레코드가 있는 경우에 상대적인 위치가 변경될 수 있다.
//
// 선택 정렬(selection sort)의 시간복잡도
// => 비교 횟수
//    - 두 개의 for 루프의 실행 횟수
//    - 외부 루프 : (n-1)번
//    - 내부 루프 (최솟값 찾기) : n-1, n-2, ... , 2, 1 번
// => 교환 횟수
//    - 외부 루프의 실행 횟수와 동일. 즉, 상수 시간 작업
//    - 한 번 교환하기 위하여 3번의 이동(SWAP 함수의 작업)이 필요하므로 3(n-1)번
// => T(n) = (n-1) + (n-2) + ... + 2 + 1 = n(n-1)/2 = O(n^2)
//
// n 개의 원소를 가진 배열을 정렬할 때, 계속해서 바꾸는 것이 아니라 비교하고 있는 값의 index를 저장해둔다.
// 그리고 최종적으로 한 번만 바꿔준다. 하지만 여러 번 비교를 하는 것은 마찬가지이다.
public class SelectionSort_JAVA {
    public static void sorting (int[] list, int n) {
        int i, j, least, temp;
        
        for (i = 0; i < n - 1; i++) {
            least = i;
            
            
            // 최솟값을 탐색한다.
            for (j = i + 1; j < n; j++) {
                if (list[j] < list[least]) {
                    least = j;
                }
            }
            
            // 최솟값이 자기 자신이면 자료 이동 X.
            if (i != least) {
                temp = list[i];
                list[i] = list[least];
                list[least] = temp;
            }
        }
    }
    
    public static void main(String[] args) {
        int test[]  = {10, 9, 2, 7, 80};
        
        sorting(test, test.length);
        
        for (int data : test) {
            System.out.print(data + ", ");
        }
    }
}
