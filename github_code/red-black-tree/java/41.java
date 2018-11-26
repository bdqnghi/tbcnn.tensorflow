package org.ljc.april2012.map;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/**
 * Red-black tree implementation (sans delete and other operations)
 */
public class RedBlackTree<K,V> implements Map<K, V>{
	RedBlackTreeNode<K,V> root;
	
	public RedBlackTree() {
		root = null;
	}

	public void add(RedBlackTreeNode<K, V> node) {
		if (root != null) {
			root.add(node);
		} else {
			root = node;
		}
		node.redBlackCheck();
	}

	public V get(Object key) {
		if (root == null) {
			return null;
		}
		RedBlackTreeNode<K, V> node = root.find((K) key);
		return (node==null)?null:node.value;
	}
	
	public void setRoot(RedBlackTreeNode<K, V> newRoot) {
		this.root = newRoot;
	}

	public void clear() {
		root = null;
	}

	public boolean containsKey(Object key) {
		V val = get(key);
		return val!=null;
	}

	public boolean containsValue(Object value) {
		return false;
	}

	public Set<java.util.Map.Entry<K, V>> entrySet() {
		if (root == null) {
			return new HashSet<Map.Entry<K,V>>();
		}
		TreeSet<java.util.Map.Entry<K, V>> result = new TreeSet<Map.Entry<K,V>>();
		root.inOrder(result);
		return result;
	}

	public boolean isEmpty() {
		return root==null;
	}

	public Set<K> keySet() {
		return null;
	}

	public V put(K key, V value) {
		if (root!=null) {
			RedBlackTreeNode<K, V> node = root.find((K) key);
			if (node != null) {
				// node already exists, update and return previous
				V result = node.value;
				node.value = value;
				return result;
			} else {
				// node doesnt exist, add
				add(new RedBlackTreeNode<K, V>(key, value, this));
			}
		} else {
			// add first node
			add(new RedBlackTreeNode<K, V>(key, value, this));
		}
		return null;
	}

	public void putAll(Map<? extends K, ? extends V> m) {
		
	}

	public V remove(Object key) {
		return null;
	}

	public int size() {
		return (root==null)?0:root.size();
	}

	public Collection<V> values() {
		return null;
	}
}
