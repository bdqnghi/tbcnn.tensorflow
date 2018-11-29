package com.ds.karumanchi.recursion;

public class TowerOfHanoi {

	public static void main(String[] args) {
		towerOfHanoi(4, 'A', 'B', 'C');
	}
	
	public static void towerOfHanoi(int n, char from, char aux, char to) {
		
		if(n == 1) {
			System.out.println(String.format("There is only 1 disk and moving from %s to %s", from, to));
			return;
		}
		
		towerOfHanoi(n-1, from, to, aux);
		System.out.println(String.format("Moving from %s -> %s", from, to));
		towerOfHanoi(n-1, aux, from, to);
	}
}
