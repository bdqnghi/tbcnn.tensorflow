package com.sakthi.datastructure.recursion;

public class TowerOfHanoi
{
	
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		TowerOfHanoi tower = new TowerOfHanoi();
		tower.towerOfHanoi(4, 1, 3, 2);
	}
	
	private void towerOfHanoi(final int n, final int fromPeg, final int toPeg, final int axPeg)
	{
		if (n == 1)
		{
			System.out.println("Move disk " + n + " from " + fromPeg + " to " + toPeg);
			return;
		}
		// A to B -> C
		towerOfHanoi(n - 1, fromPeg, axPeg, toPeg);
		System.out.println("Move disk " + n + " from " + fromPeg + " to " + toPeg);
		// B to C -> A
		towerOfHanoi(n - 1, axPeg, toPeg, fromPeg);
	}
}
