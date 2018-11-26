package kh.java.oop.method.recursion;

import java.util.Scanner;
///////////////////////////////////////////////
//disc3   2   1
///////////////////////////////////////////////
//hanoi(2, '시작기둥', '목표기둥','보조기둥');
//	hanoi(1, '시작기둥','보조기둥','목표기둥');
//		hanoi(0)    
//		Move disc 1 from 시작기둥 to 목표기둥 //1
//		hanoi(0)
//	Move disc 2 from 시작기둥 to 보조기둥 //2

//hanoi(1,'목표기둥','시작기둥','보조기둥');
//	hanoi(0)    
//	Move disc 1 from 목표기둥 to 보조기둥 //3
//	hanoi(0)

//Move disc 3 from 시작기둥 to 목표기둥 //4

//hanoi(2, '보조기둥','시작기둥', '목표기둥');
//	hanoi(1, '보조기둥','목표기둥','시작기둥');
//		hanoi(0)    
//		Move disc 1 from 보조기둥 to 시작기둥//5
//		hanoi(0)
//	Move disc 2 from 보조기둥 to 목표기둥//6

//	hanoi(1,'시작기둥','보조기둥','목표기둥');
//		hanoi(0)    
//		Move disc 1 from 시작기둥 to 목표기둥//7
//		hanoi(0)


public class TowerOfHanoi {
    int count = 0;//전체 횟수
    public static void main(String[] args) {
          
           Scanner sc = new Scanner(System.in);
           System.out.print("원반개수를 입력하세요 => ");
           int n = sc.nextInt();

           TowerOfHanoi towerOfHanoi = new TowerOfHanoi();

           towerOfHanoi.hanoi(n, "시작기둥", "보조기둥", "목표기둥");
           towerOfHanoi.showResult();
    }

    public void hanoi(int n, String src, String aux, String des) {
           //src : 원반들이 있던 탑
           //aux : 보조탑.
           //dex : 원반들을 옮길 목적지 탑
           if (n == 1) {
                   ++count;
                   System.out.println("Move disc "+n+" : "+src+ " -> " +des);
           } else {
                   hanoi( n - 1, src, des, aux);
                   //마지막탑을 보조탑으로 이용하여 첫번째탑에 있는 n-1개의 원반들을 중간에 있는 탑으로 이동한다.
                   ++count;
                   System.out.println("Move disc "+n+" : "+src+ " -> " +des);
                   hanoi(n - 1, aux, src, des);
                   //첫번째탑을 보조탑으로 이용하여 중간탑에 있는 n-1개의 원반들을 목적지 탑으로 이동한다.
                  
           }
          
    }
   
    public void showResult(){
           System.out.println("총 이동 횟수 : "+count);
    }
}
