package red_black_tree_set.rbtree_ser;

import java.util.Iterator;


public class RedBlackTree<T extends Comparable<T>> implements Set<T> {

		private RedBlackTreeNode<T> nil = new RedBlackTreeNode<T>();
		private RedBlackTreeNode<T> root = nil;

		public RedBlackTree() {
	        root.left = nil;
	        root.right = nil;
	        root.parent = nil;
	    }

		private void leftRotate(RedBlackTreeNode<T> x){
			RedBlackTreeNode<T> y;
			y = x.right;
			x.right = y.left;
			if (!(y.left==nil))
				y.left.parent = x;
			y.parent = x.parent;
			if ((x.parent==nil))
				root = y;
			else if (x.parent.left == x)
				x.parent.left = y;
			else
				x.parent.right = y;
			y.left = x;
			x.parent = y;
		}

		private void rightRotate(RedBlackTreeNode<T> y){
	        RedBlackTreeNode<T> x = y.left;
	        y.left = x.right;
	        if (!(x.right==nil))
	            x.right.parent = y;
	        x.parent = y.parent;
	        if ((y.parent==nil))
	            root = x;
	        else if (y.parent.right == y)
	            y.parent.right = x;
	        else
	            y.parent.left = x;
	        x.right = y;
	        y.parent = x;
		}

		public void add(T Key) {
				RedBlackTreeNode<T> z = new RedBlackTreeNode<T>(Key);
				RedBlackTreeNode<T> y = nil;
				RedBlackTreeNode<T> x = root;
				while (!(x==nil)){
					y = x;
					if (z.key.compareTo(x.key) < 0){
						x = x.left;
					}
					else{
						x = x.right;
					}
				}
				z.parent = y;
				if (y==nil)
					root = z;
				else if (z.key.compareTo(y.key) < 0)
					y.left = z;
				else
					y.right = z;
				z.left = nil;
				z.right = nil;
				z.color = RedBlackTreeNode.RED;
				FixInsert(z);
		}

		private void FixInsert(RedBlackTreeNode<T> z){
			RedBlackTreeNode<T> y = nil;
			while (z.parent.color == RedBlackTreeNode.RED){
				if (z.parent == z.parent.parent.left){
					y = z.parent.parent.right;
					if (y.color == RedBlackTreeNode.RED){
						z.parent.color = RedBlackTreeNode.BLACK;
						y.color = RedBlackTreeNode.BLACK;
						z.parent.parent.color = RedBlackTreeNode.RED;
						z = z.parent.parent;
					}
					else if (z == z.parent.right){
						z = z.parent;
						leftRotate(z);
					}
					else{
						z.parent.color = RedBlackTreeNode.BLACK;
						z.parent.parent.color = RedBlackTreeNode.RED;
						rightRotate(z.parent.parent);
					}
				}
				else{
					y = z.parent.parent.left;
					if (y.color == RedBlackTreeNode.RED){
						z.parent.color = RedBlackTreeNode.BLACK;
						y.color = RedBlackTreeNode.BLACK;
						z.parent.parent.color = RedBlackTreeNode.RED;
						z = z.parent.parent;
					}
					else if (z == z.parent.left){
						z = z.parent;
						rightRotate(z);
					}
					else{
						z.parent.color = RedBlackTreeNode.BLACK;
						z.parent.parent.color = RedBlackTreeNode.RED;
						leftRotate(z.parent.parent);
					}
				}
			}
		root.color = RedBlackTreeNode.BLACK;
		}


		public RedBlackTreeNode<T> treeSuccessor(RedBlackTreeNode<T> x){
			if (!(x.right==nil) )
				return treeMin(x.right);
			RedBlackTreeNode<T> y = x.parent;
			while (!(y==nil) && x == y.right){
				x = y;
				y = y.parent;
			}
			return y;
		}

		public void remove(RedBlackTreeNode<T> v){
			RedBlackTreeNode<T> z = search(v.key);
			RedBlackTreeNode<T> x = nil;
			RedBlackTreeNode<T> y = nil;
			if ((z.left==nil) || (z.right==nil))
				y = z;
			else y = treeSuccessor(z);
			if (!(y.left==nil))
				x = y.left;
			else
				x = y.right;
			x.parent = y.parent;
			if (y.parent==nil)
				root = x;
			else if (!(y.parent.left==nil) && y.parent.left == y)
				y.parent.left = x;
			else if (!(y.parent.right==nil) && y.parent.right == y)
				y.parent.right = x;
			if (y != z){
				z.key = y.key;
			}
			if (y.color == RedBlackTreeNode.BLACK)
				fixRemove(x);
		}

		public RedBlackTreeNode<T> treeMin(RedBlackTreeNode<T> node){
			while (!(node.left==nil))
				node = node.left;
			return node;
		}
		
		private void fixRemove(RedBlackTreeNode<T> x){
			RedBlackTreeNode<T> w;
			while (x != root && x.color == RedBlackTreeNode.BLACK){
				if (x == x.parent.left){
					w = x.parent.right;
					if (w.color == RedBlackTreeNode.RED){
						w.color = RedBlackTreeNode.BLACK;
						x.parent.color = RedBlackTreeNode.RED;
						leftRotate(x.parent);
						w = x.parent.right;
					}
					if (w.left.color == RedBlackTreeNode.BLACK &&
								w.right.color == RedBlackTreeNode.BLACK){
						w.color = RedBlackTreeNode.RED;
						x = x.parent;
					}
					else{
						if (w.right.color == RedBlackTreeNode.BLACK){
							w.left.color = RedBlackTreeNode.BLACK;
							w.color = RedBlackTreeNode.RED;
							rightRotate(w);
							w = x.parent.right;
						}
						w.color = x.parent.color;
						x.parent.color = RedBlackTreeNode.BLACK;
						w.right.color = RedBlackTreeNode.BLACK;
						leftRotate(x.parent);
						x = root;
					}
				}
				else{
					w = x.parent.left;
					if (w.color == RedBlackTreeNode.RED){
						w.color = RedBlackTreeNode.BLACK;
						x.parent.color = RedBlackTreeNode.RED;
						rightRotate(x.parent);
						w = x.parent.left;
					}
					if (w.right.color == RedBlackTreeNode.BLACK &&
								w.left.color == RedBlackTreeNode.BLACK){
						w.color = RedBlackTreeNode.RED;
						x = x.parent;
					}
					else{
						 if (w.left.color == RedBlackTreeNode.BLACK){
							w.right.color = RedBlackTreeNode.BLACK;
							w.color = RedBlackTreeNode.RED;
							leftRotate(w);
							w = x.parent.left;
						}
						w.color = x.parent.color;
						x.parent.color = RedBlackTreeNode.BLACK;
						w.left.color = RedBlackTreeNode.BLACK;
						rightRotate(x.parent);
						x = root;
					}
				}
			}
			x.color = RedBlackTreeNode.BLACK;
		}

		public RedBlackTreeNode<T> search(T key){
			RedBlackTreeNode<T> current = root;
			while (!(current==nil)){
				if (current.key.equals(key))
					return current;
				else if (current.key.compareTo(key) > 0)
					current = current.left;
				else
					current = current.right;
			}
			return null;
		}

		public Iterator<T> iterator() {
            return (new RedBlackTreeIterator<T>(this));
        }

        private static class RedBlackTreeIterator<T extends Comparable<T>> implements Iterator<T> {
        	private RedBlackTreeNode<T> min;
            private RedBlackTree<T> tree;
            
            protected RedBlackTreeIterator(RedBlackTree<T> t) {
                this.tree = t; 
                min = t.treeMin(t.root);
            }

            public boolean hasNext() {
            	if (min!=tree.nil) return true; 
                return false;
            }
            
            public T next() {
                T nex = min.key;
                min = tree.treeSuccessor(min);
                return nex;
            }
        }
}



