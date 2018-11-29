package week5.BalancedSearchTree;

public class RedBlackTree<Key extends Comparable<Key>, Value> {
	private Node root;

	private class Node {
		Key key;
		Value value;
		Node left, right;

		public Node(Key key, Value value) {
			this.key = key;
			this.value = value;
		}
	}


	public Value get(Key key) {
		Node node = root;
		while (node != null) {
			int cmp = node.key.compareTo(key);
			if (cmp < 0)
				node = node.left;
			else if (cmp > 0)
				node = node.right;
			else
				return node.value;
		}
		return null;
	}

	public void put(Key key, Value value) {
		root = put(root, key, value);
	}

	private Node put(Node cur, Key key, Value value) {
		if (cur == null)
			return new Node(key, value);
		int cmp = cur.key.compareTo(key);
		if (cmp < 0)
			cur.right = put(cur.right, key, value);
		else if (cmp > 0)
			cur.left = put(cur.left, key, value);
		else
			cur.value = value;
		return cur;
	}

}
