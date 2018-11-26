package com.bhanu.towerOfHanoi;

import java.util.Stack;

public class TowerOfHanoi {
	private void move(Stack<String> source , Stack<String> destination ){
		String temp;
		temp = source.pop();
		destination.push(temp);
	}
	
	public void moverTower(Stack<String> source , Stack<String> destionation , Stack<String> temp , int n){
		if(n>0){
			System.out.println("---------N := "+n+" :---dfdsfsdf------");
			System.out.println(" source "+source);
			System.out.println(" temp "+temp);
			System.out.println("destionation"+destionation);
			
			moverTower(source, temp, destionation, n-1);
			move(source, destionation);
			moverTower(temp, destionation, source, n-1);
		}
	}
	
	public static void main(String[] args) {
		
		TowerOfHanoi towerOfHanoi = new TowerOfHanoi();
		Stack<String> source = new Stack<String>();
		Stack<String> temp = new Stack<String>();
		Stack<String> destination = new Stack<String>();
		
		source.push("A");
		source.push("B");
		source.push("C");
		source.push("D");
		
		towerOfHanoi.moverTower(source, destination, temp, 3);
		System.out.println("Hello World this is tower of hanoi");
		System.out.println(source);
		System.out.println(destination);
	}
}
