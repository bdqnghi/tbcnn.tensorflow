package com.bhanu.towerOfHanoi;

import java.util.Stack;
public class Tower {
 public static void main(String[] args) {

	Tower tower = new Tower();
	
	Stack<String> stackA = new Stack<String>();
	Stack<String> temp =new Stack<String>();
	Stack<String> dest = new Stack<String>();
	
	stackA.push("A");
	stackA.push("B");
	stackA.push("C");
	stackA.push("D");
	stackA.push("E");
	stackA.push("F");
	stackA.push("G");
	
	System.out.println("before stackA :"+stackA);
	System.out.println("destination : "+dest);
	System.out.println("temp : "+temp);
	
	tower.towerOfHanoi(2, stackA, dest, temp);
	
	System.out.println("after stackA :"+stackA);
	System.out.println("destination : "+dest);
	System.out.println("temp : "+temp);
}
 public void move(Stack<String> stackA, Stack<String> stackB){
	 String top;
	 top = stackA.pop();
	 stackB.push(top);
 }
 
 public void towerOfHanoi(int number, Stack<String> source, Stack<String> destination,Stack<String> temp){
	 if(number > 1){
		 towerOfHanoi(number-1, source, temp, destination);
		 move(source,destination);
		 towerOfHanoi(number-1, temp, destination, source);
	 }
 }
 
}
