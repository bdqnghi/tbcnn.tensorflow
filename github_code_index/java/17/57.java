package algorithm.data.structure;
//http://blog.csdn.net/v_JULY_v/article/details/6105630
public class RedBlackTree {
	public RedBlackTreeNode root,NULL;
	public void leftRotate(RedBlackTreeNode x){
		RedBlackTreeNode y = x.right;
		x.right = y.left;
		y.left.parent = x;
		if(x.parent == NULL){
			root = y;
		}else if(x == x.parent.left){
			x.parent.left = y;
		}else{
			x.parent.right = y;
		}
		y.left = x;
		x.parent = y;
	}
	public void rightRotate(RedBlackTreeNode y){
		RedBlackTreeNode x = y.left;
		y.left = x.right;
		x.right.parent = y;
		if(y.parent == NULL){
			root = x;
		}else if(y == y.parent.left){
			y.parent.left = x;
		}else{
			y.parent.right = x;
		}
		x.right = y;
		y.parent = x;
	}
	public void insert(RedBlackTreeNode z){
		RedBlackTreeNode y = NULL,x = root;
		while(x != NULL){
			y = x;
			if(z.key < x.key){
				x = z.left;
			}else{
				x = z.right;
			}
		}
		z.parent = y;
		if(y == NULL){
			root = z;
		}else if(z.key < y.key){
			y.left = z;
		}else{
			y.right = z;
		}
		z.left = NULL;
		z.right = NULL;
		z.color = RedBlackTreeNode.RED;
		insertFixup(z);
	}
	private void insertFixup(RedBlackTreeNode z){
		while(z.parent.color == RedBlackTreeNode.RED){
			if(z.parent == z.parent.parent.left){
				RedBlackTreeNode y = z.parent.parent.right;
				if(y.color == RedBlackTreeNode.RED){
					z.parent.color = RedBlackTreeNode.BLACK;
					y.color = RedBlackTreeNode.BLACK;
					z.parent.parent.color = RedBlackTreeNode.RED;
					z = z.parent.parent;
				}else if(z == z.parent.right){
					z = z.parent;
					leftRotate(z);
				}
				z.parent.color = RedBlackTreeNode.BLACK;
				z.parent.parent.color = RedBlackTreeNode.RED;
				rightRotate(z.parent.parent);
			}else{
				RedBlackTreeNode y = z.parent.parent.left;
				if(y.color == RedBlackTreeNode.RED){
					z.parent.color = RedBlackTreeNode.BLACK;
					y.color = RedBlackTreeNode.BLACK;
					z.parent.parent.color = RedBlackTreeNode.RED;
					z = z.parent.parent;
				}else if(z == z.parent.left){
					z = z.parent;
					rightRotate(z);
				}
					z.parent.color = RedBlackTreeNode.BLACK;
					z.parent.parent.color = RedBlackTreeNode.RED;
					leftRotate(z.parent.parent);
			}
		}
		root.color = RedBlackTreeNode.BLACK;
	}
	public RedBlackTreeNode delete(RedBlackTreeNode z){
		RedBlackTreeNode y,x;
		if(z.left == NULL || z.right == NULL){
			y = z;
		}else{
			y = successor(z);
		}
		if(y.left != NULL){
			x = y.left;
		}else{
			x = y.right;
		}
		if(x != NULL){
			x.parent = y.parent;
		}
		if(y.parent == NULL){
			root = x;
		}else if(y == y.parent.left){
			y.parent.left = x;
		}else{
			y.parent.right = x;
		}
		if(y != z){
			z.key = y.key;
			//����y��data��z
		}
		if(y.color == RedBlackTreeNode.BLACK){
			deleteFixup(x);
		}
		return y;
	}
	private void deleteFixup(RedBlackTreeNode x){
		RedBlackTreeNode w;
		while(x != root && x.color == RedBlackTreeNode.BLACK){
			if(x == x.parent.left){
				w = x.parent.right;
				if(w.color == RedBlackTreeNode.RED){
					w.color = RedBlackTreeNode.BLACK;
					x.parent.color = RedBlackTreeNode.RED;
					leftRotate(x.parent);
					w = x.parent.right;
				}
				if(w.left.color == RedBlackTreeNode.BLACK && w.right.color == RedBlackTreeNode.BLACK){
					w.color = RedBlackTreeNode.RED;
					x = x.parent;
				}else if(w.right.color == RedBlackTreeNode.BLACK){
					w.left.color = RedBlackTreeNode.BLACK;
					w.color = RedBlackTreeNode.RED;
					rightRotate(w);
					w = x.parent.right;
				}
				w.color = x.parent.color;
				x.parent.color = RedBlackTreeNode.BLACK;
				w.right.color = RedBlackTreeNode.BLACK;
				leftRotate(x.parent);
				x= root;
			}else{
				w = x.parent.left;
				if(w.color == RedBlackTreeNode.RED){
					w.color = RedBlackTreeNode.BLACK;
					x.parent.color = RedBlackTreeNode.RED;
					rightRotate(x.parent);
					w = x.parent.left;
				}
				if(w.right.color == RedBlackTreeNode.BLACK && w.left.color == RedBlackTreeNode.BLACK){
					w.color = RedBlackTreeNode.RED;
					x = x.parent;
				}else if(w.left.color == RedBlackTreeNode.BLACK){
					w.right.color = RedBlackTreeNode.BLACK;
					w.color = RedBlackTreeNode.RED;
					leftRotate(w);
					w = x.parent.left;
				}
				w.color = x.parent.color;
				x.parent.color = RedBlackTreeNode.BLACK;
				w.left.color = RedBlackTreeNode.BLACK;
				rightRotate(x.parent);
				x= root;
			}
		}
		x.color = RedBlackTreeNode.BLACK;
	}
	public RedBlackTreeNode successor(RedBlackTreeNode z){
		if(z.right != NULL){
			z = z.right;
			while(z.left != NULL){
				z = z.left;
			}
			return z;
		}else if(z.parent.left == z){
			return z.parent;
		}else{
			while(z.parent.left != z){
				z = z.parent;
			}
			return z.parent;
		}
	}
	public RedBlackTreeNode presuccessor(RedBlackTreeNode z){
		if(z.left != NULL){
			z = z.left;
			while(z.right != NULL){
				z = z.right;
			}
			return z;
		}else if(z.parent.right == z){
			return z.parent;
		}else{
			while(z.parent.right != z){
				z = z.parent;
			}
			return z.parent;
		}
	}
}
