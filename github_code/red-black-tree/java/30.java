/*
 * Write a function which checks a Red-Black-Tree that the max depth isn't > than 2 * min depth.
 * It must return a boolean. 
 */
public class Solution {

	private static class Node {
	    Node left;
	    Node right;

	    public Node() {
	        left = null;
	        right = null;
	    }
	}
	
	private static boolean checkDepth(Node root) {
		int minDepth = getDepth(root, false);
        int maxDepth = getDepth(root, true);
        return minDepth * 2 > maxDepth;
	}
	
	private static int getDepth(Node root, boolean getMax) {
		if (root == null) {
            return 0;
        }
        if (getMax) {
            return Math.max(1 + getDepth(root.left, getMax), 1 + getDepth(root.right, getMax));
        } else {
		    return Math.min(1 + getDepth(root.left, getMax), 1 + getDepth(root.right, getMax));
        }
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Node a = new Node();
		Node b = new Node();
		Node c = new Node();
		Node d = new Node();
		Node e = new Node();
		Node f = new Node();
		a.left = b;
		a.right = c;
		b.left = d;
		b.right = e;
		c.left = f;
		System.out.println(checkDepth(a));
	}

}
