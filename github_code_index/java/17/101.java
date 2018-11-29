package hw4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class Node {
	public static final int red = 1;
	public static final int black = 0;
	
	public int val;
	public Node left, right, p;
	public int color;

	public Node(int newval) {
		val = newval;
		left = makeNIL();
		right = makeNIL();
		left.p = this;
		right.p = this;
		p = makeNIL();
		color = red; // red = 1, black = 0 , 수정 필요할 수 있음
	}
	public Node() {
		val = 0;
		left = null;
		right = null;
		p = null;
		color = black; // red = 1, black = 0 , 수정 필요할 수 있음
	}
	public static Node makeNIL() {
		return new Node();
	}
}

class RedblackBST {
	
	
	
	public Node root;

	public RedblackBST() {
		root = Node.makeNIL(); // val이 0인 노드들은 leaf node, 초창기 root node
		
	}

	public void RBTree_insert(Node T, Node z) { // 체크 완료
		
		Node y = Node.makeNIL(); // 2차 수정
		Node x = root;
		while (x.val != 0) {
			y = x;
			if (z.val < x.val) {
				x = x.left;
			} else {
				x = x.right;
			}
		}
		z.p = y;
		if (y.val == 0) { // 2차 수정
			root = z;
		} else if (z.val < y.val) {
			y.left = z;
		} else {
			y.right = z;
		}
		 /* z.left = Node.makeNIL(); // 수정
		z.left.p = z;
		z.right = Node.makeNIL(); // 수정
		z.right.p = z;
		z.color = 1;  */
		RB_insert_fixup(T, z);
	}

	public void RB_insert_fixup(Node t, Node z) { // 체크 완료
		
		while (z.p.color == Node.red) {
			if (z.p == z.p.p.left) {
				Node y = z.p.p.right;
				if (y.color == Node.red) {
					z.p.color = Node.black;
					y.color = Node.black;
					z.p.p.color = Node.red;
					z = z.p.p;
				} else {
					if (z == z.p.right) {
						z = z.p;
						left_rotate(t, z);
					}
					z.p.color = Node.black;
					z.p.p.color = Node.red;
					right_rotate(t, z.p.p);
				}
			} else {
				if(z.p == z.p.p.right) {
					Node y = z.p.p.left;
					if (y.color == Node.red) {
						z.p.color = Node.black;
						y.color = Node.black;
						z.p.p.color = Node.red;
						z = z.p.p;
					} else {
						if (z == z.p.left) {

							z = z.p;
							right_rotate(t, z);
						}
						z.p.color = Node.black;
						z.p.p.color = Node.red;
						left_rotate(t, z.p.p);
					}
				}
			}
			}
		root.color = Node.black;
	
		}
		

	public void left_rotate(Node t, Node x) { // 체크 완료
		
		Node y = x.right;
		x.right = y.left;
		if(y.left.val != 0) {
			y.left.p = x;
		}
		y.p = x.p;
		if (x.p.val == 0) {
			root = y;
		} else if (x == x.p.left) {
				x.p.left = y;
			} else {
				x.p.right = y;
		}
		y.left = x;
		x.p = y;
	}

	public void right_rotate(Node t, Node x) { // 체크 완료
		
		Node y = x.left;
		x.left = y.right;
		if(y.right.val != 0) {
			y.right.p = x;
		}
		y.p = x.p;
		if (x.p.val == 0) {
			root = y;
		} else if (x == x.p.right) {
				x.p.right = y;
			} else {
				x.p.left = y;
		}
		y.right = x;
		x.p = y;
	}

	public void RBTree_delete(Node t, int v) {

		Node z = Tree_search(t, v); // 수정 가능
		if (z.val == 0) {
			return;
		}
		
		
		Node y = z;
		Node x;
		int yoricolor = y.color;
		
		if (z.left.val == 0) {
			x = z.right; // 추가
			RBTransplant(root, z, z.right);
		} else if (z.right.val == 0) {
			x = z.left; // 추가
			RBTransplant(root, z, z.left);
		} else {
			y = RBTree_minimum(z.right);
			yoricolor = y.color; // 추가
			x = y.right; // 추가
			if (y.p == z) {
				x.p = y;
			} else {
				RBTransplant(root, y, y.right);
				y.right = z.right;
				y.right.p = y;
			}
			RBTransplant(root, z, y);
			y.left = z.left;
			y.left.p = y;
			y.color = z.color;
		}
		if (yoricolor == Node.black)
			RB_delete_fixup(t, x);
	}

	public void RB_delete_fixup(Node t, Node x) {
		Node w;
		while (x != root && x.color == Node.black) { // leaf node일 때도 fixup 필요없음
			if (x == x.p.left) {
				w = x.p.right;
				if (w.color == Node.red) { // case 1
					w.color = Node.black;
					x.p.color = Node.red;
					left_rotate(t, x.p);
					w = x.p.right;
				}
				if (w.left.color == Node.black && w.right.color == Node.black) {
					w.color = Node.red; // case 2
					x = x.p;
				} else {
					if (w.right.color == Node.black) { // case 3
						w.left.color = Node.black;
						w.color = Node.red;
						right_rotate(t, w);
						w = x.p.right;
					}
					w.color = x.p.color; // case 4
					x.p.color = Node.black;
					w.right.color = Node.black;
					left_rotate(t, x.p);
					x = root;
				}
			} 
			else {
				w = x.p.left;
				if (w.color == Node.red) { // case 5
					w.color = Node.black;
					x.p.color = Node.red;
					right_rotate(t, x.p);
					w = x.p.left;
				}
                if(w.right.color == Node.black && w.left.color == Node.black) {
					w.color = Node.red; // case 6
					x = x.p;
				} else {
					if (w.left.color == Node.black) { // case 7
						w.right.color = Node.black;
						w.color = Node.red;
						left_rotate(t, w);
						w = x.p.left;
					}
					w.color = x.p.color; // case 8
					x.p.color = Node.black;
					w.left.color = Node.black;
					right_rotate(t, x.p);
					x = root;
				}
			}
		}
		x.color = Node.black;
	}

	public Node RBTree_minimum(Node x) {
		while (x.left.val != 0) {
			x = x.left;
		}
		return x;
	}

	public void RBTransplant(Node T, Node u, Node v) {
		if (u.p.val == 0) { // 2차 수정
			root = v;
		} else if (u == u.p.left)
			u.p.left = v;
		else {
			u.p.right = v;
		}
			v.p = u.p;
		
	}

	public Node Tree_search(Node tree, int val) {
	 	if (tree.val == 0)
	      return Node.makeNIL();
	    else if (val == tree.val)
	      return tree;
	    else if (val < tree.val)
	      return Tree_search(tree.left,val);
	    else
	      return Tree_search(tree.right,val);
  	}


	public void Tree_print(Node tree, int level) {
		if (tree.right.val != 0)
			Tree_print(tree.right, level + 1);
		for (int i = 0; i < level; i++)
			System.out.print("    ");
		System.out.println(tree.val);
		if (tree.left.val != 0)
			Tree_print(tree.left, level + 1);
	}
	public void inorder(Node tree) {
    	if (tree.val == 0)
      		return;
   		else {
	      inorder(tree.left);
	      System.out.println(tree.val);
	      inorder(tree.right);
   		 }
 	 }
	public int NodeCount(Node tree){
 	 	int c = 1;
 	 	if( tree.right.val!=0) { 
 	 		c+= NodeCount(tree.right); 
 	 		}
 	 	if( tree.left.val!=0) { 
 	 		c+= NodeCount(tree.left); 
 	 		}

 	 	return c;
  	}
	public int BlackNodeCount(Node tree){	
		int c = 0;
		if(tree.left.val != 0) 
			c+=BlackNodeCount(tree.left);
		if(tree.right.val!=0) 
			c+=BlackNodeCount(tree.right);
		if(tree.color == Node.black) 
			c+=1;
		return c;
	}
	public int BlackHeight(Node tree){
		if(tree.val == 0){
			return 0;
		}
		else if(tree.color== Node.black){
			return BlackHeight(tree.left) + 1;
		}
		else
			return BlackHeight(tree.left);
	}

}

public class Redblacktree {
	public static void main(String[] args) throws IOException {
		RedblackBST bst = new RedblackBST();
		BufferedReader br = new BufferedReader(new FileReader("input.txt"));
		while (true) {
			String str = br.readLine();
			str = str.trim();
			int number = Integer.parseInt(str);
			if (number > 0)
				bst.RBTree_insert(bst.root, new Node(number));

			else if (number < 0)
				bst.RBTree_delete(bst.root, Math.abs(number));

			else
				break;

		}
		br.close();
		
		System.out.println("total = " + bst.NodeCount(bst.root));
        System.out.println("nb = " + bst.BlackNodeCount(bst.root));
        System.out.println("bh = " + bst.BlackHeight(bst.root));
        bst.inorder(bst.root);

	}
}
