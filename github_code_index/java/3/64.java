package com.lz.Demo4;

public class TowerOfHanoi {
	public static void main(String[] args) {
		int[] startPole = {1,2,3,4,5};
		int[] tempPole = {0,0,0,0,0};
		int[] endPole = {0,0,0,0,0};
		for (int i = 0; i < startPole.length; i++) {
			System.out.print(endPole[i]);
		}
		method(4,startPole,tempPole,endPole);
	}
	public static void method(int numberOfDisks,int[] startPole,int[] tempPole,int[] endPole ){
		if(numberOfDisks==0){
			endPole[numberOfDisks] = startPole[numberOfDisks];
			startPole[numberOfDisks] = 0;
		}else{
			//startPole�������һ������  �����Ķ��ƶ���tmpePole��
			method(numberOfDisks-1,startPole,endPole,tempPole);
			method(numberOfDisks-1,tempPole,startPole,endPole);
		}
	};

}
