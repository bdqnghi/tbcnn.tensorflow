package tree;

import queue.IEvent;

public class RedBlackTree
{
	public static final int COLOR_RED = 0;
	public static final int COLOR_BLACK = 1;
	public int key;
	public int color;
	public RedBlackTree left;
	public RedBlackTree right;
	public RedBlackTree parent;

	public RedBlackTree(int key)
	{
		super();
		this.key = key;
	}

	public RedBlackTree(int key, int leftKey, int rightKey)
	{
		this.key = key;
		left = new RedBlackTree(leftKey);
		right = new RedBlackTree(rightKey);
	}

	public RedBlackTree(int key, RedBlackTree left, RedBlackTree right)
	{
		this.key = key;
		this.left = left;
		this.right = right;
	}

	public static class Util
	{

	}

}
