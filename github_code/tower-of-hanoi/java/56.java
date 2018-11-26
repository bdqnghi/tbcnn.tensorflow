package com.Stack;

import java.util.Stack;

public class TowerOfHanoi {
	public static void main(String[] args) {
		Stack<Integer> src = new Stack<Integer>();
		Stack<Integer> aux = new Stack<Integer>();
		Stack<Integer> dest = new Stack<Integer>();
		src.push(3);src.push(2);src.push(1);
		Tower(src,aux,dest);
		for(int i=0;i<=dest.size()+1;i++){
			System.out.println("dest : "+dest.pop());
		}
	}

	private static void Tower(Stack<Integer> src, Stack<Integer> aux,
			Stack<Integer> dest) {
		int ops = (int) (Math.pow(2, 3)-1);
		for(int i=1 ; i<=ops ; i++){
			//System.out.println("i%3 == "+(i%3));
			if(i%3==1){
				move(src,dest);
			}else if(i%3==2){
				move(src,aux);
			}else if(i%3==0){
				move(aux,dest);
			}
		}
	}

	private static void move(Stack<Integer> src, Stack<Integer> dest) {
		// TODO Auto-generated method stub
		int data;
		if(src.size()==0 && dest.size()>0){			
			data = dest.pop();
			src.push(data);
		}else if(dest.size()==0 && src.size()>0){
			data = src.pop();
			dest.push(data);
		}else if(src.peek() > dest.peek()){
			data = dest.pop();
			src.push(data);
		}else if(dest.peek() > src.peek()){
			data = src.pop();
			dest.push(data);
		}else{
			System.out.println("failed");
		}
	}

}
