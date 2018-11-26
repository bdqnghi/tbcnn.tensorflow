package com.ds.algo.recursionandbacktracking;

import java.util.Stack;

public class TowerOfHanoi {

	private Stack<Integer> source,destinaton,auxiliary;
	
	public TowerOfHanoi(int i) {
		source  = new Stack<Integer>();
		while(i>0) {
			source.push(i--);
		}
		destinaton = new Stack<Integer>();
		auxiliary = new Stack<Integer>();
	}

	public static void main(String[] args) {
		TowerOfHanoi towerOfHanoi = new TowerOfHanoi(3);
		
		System.out.println("Before "+towerOfHanoi.destinaton);
		
		towerOfHanoi.solveTH(towerOfHanoi.source,towerOfHanoi.destinaton,towerOfHanoi.auxiliary,towerOfHanoi.source.size());
		
		System.out.println("After  "+towerOfHanoi.destinaton);
		
	}

	private void solveTH(Stack<Integer> source, Stack<Integer> destinaton, Stack<Integer> auxiliary,int size) {
		if(size == 0)
			return;
		
		solveTH(source, auxiliary, destinaton,size-1);
//		System.out.println("----------------------");
//		printerState(); 
		destinaton.push(source.pop());
//		System.out.println(".......................");
//		printerState();
//		System.out.println("----------------------");
		solveTH(auxiliary,destinaton,source,size-1);
		 
	}

	private void printerState() {
		System.out.println("src "+this.source);
		System.out.println("des "+this.destinaton);
		System.out.println("aux "+this.auxiliary);
	}
	
	
	
}
