import java.util.Random;
import java.util.Scanner;

/*Red black tree implementation.
* This one is Left leaning red-black tree.A red black tree with red nodes in left leaning position
* SOURCE - https://www.youtube.com/watch?v=lKmLBOJXZHI
* 
*/
public class RedBlackTree {
	public static final boolean RED=true;
	public static final boolean BLACK=false;


	static node2 root=null;
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int n=10000;
		Random random=new Random();
		for(int i=0;i<n;i++)
			root=createTree(root, random.nextInt());
		node2 temp=searchTree(sc.nextInt(), root);
		if(temp!=null)
			System.out.println("got the value.");
		else
			System.out.println("value not found.");
	}
	static node2 createTree(node2 h,int val)
	{
		if(h==null)
			return new node2(val);
		int cmp=h.compareTo(val);
		if(cmp<0)h.left=createTree(h.left, val);
		else if(cmp>0)h.right=createTree(h.right, val);
		else if(cmp==0)h.val=val;
		/*
		  The order in which below operations are placed is
		  also important.
		  If we hit the second 'if' condition,we might end up
		  with two red siblings hence flipcolor() has been
		  placed at the end.
		  Same way If we do rotate left then we might end up with
		  (left,left.left) situation hence it is second condition.
		*/
		if(!isRed(h.left)&& isRed(h.right))
			h=rotateLeft(h);
		if(isRed(h.left) && isRed(h.left.left))
			h=rotateRight(h);
		if(isRed(h.right) && isRed(h.left))
			flipColors(h);

			return h;
	}
	static node2 rotateLeft(node2 h)
	{
		node2 x=h.right;
		h.right=x.left;
		x.left=h;
		x.color=h.color;
		h.color=RED;
		return x;
	}
	static node2 rotateRight(node2 h)
	{
		node2 x=h.left;
		h.left=x.right;
		x.right=h;
		x.color=h.color;
		h.color=RED;
		return x;
	}
	static void flipColors(node2 h)
	{
		h.color=RED;
		h.right.color=BLACK;
		h.left.color=BLACK;
	}
	static boolean isRed(node2 h){
		if(h==null)
			return false;
		return h.color;
	}
	static node2 searchTree(int val,node2 h)
	{
		while(h!=null)
		{
			int cmp=h.compareTo(val);
			if(cmp<0) h=h.left;
			if(cmp>0) h=h.right;
			else if(cmp==0) return h;
		}
		return null;
	}

}





class node2 implements Comparable<Integer>{
	int val;
	node2 right=null;
	node2 left=null;
	boolean color;
	node2(int val)
	{
		color=true;
		this.val=val;
	}
	@Override
	public int compareTo(Integer o) {
		if(this.val>o.intValue())
			return 1;
		else if(this.val<o.intValue())
			return -1;
		else
			return 0;
	}

}
