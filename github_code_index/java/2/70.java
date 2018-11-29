package com.joshua.bst;

public class AVLTree<T extends Comparable<T>> implements BstType<T>{
	
	private BNode<T> root = null;
	
	AVLTree(T node){
		root = new BNode<T>(node);
	}
	
	@Override
	public void inOrder(BNode<T> n) {
		if(n == null) return;
		inOrder(n.getLeft());
		System.out.println(n.toString());
		inOrder(n.getRight());
	}

	@Override
	public void postOrder(BNode<T> n) {
		if(n == null) return;
		postOrder(n.getLeft());
		postOrder(n.getRight());
		System.out.println(n.toString());
	}

	@Override
	public void preOrder(BNode<T> n) {
		if(n == null);
		System.out.println(n.toString());
		preOrder(n.getLeft());
		postOrder(n.getRight());
	}

	//should initially take in root
	@Override
	public void insert(T val, BNode<T> temp) {
		//the data is equal
		if(val.compareTo(temp.getData()) == 0){
			//return false since data is in list
			return;
		} else if(val.compareTo(temp.getData()) < 0){
			if(temp.getLeft() == null){
				temp.setLeft(new BNode<T>(val));
				return;
			}else{
				insert(val, temp.getLeft());
				return;
			}
		} else if(val.compareTo(temp.getData()) > 0){
			if(temp.getRight() == null){
				temp.setRight(new BNode<T>(val));
				return;
			}else{
				insert(val, temp.getRight());
				return;
			}
		}
	}

	public BNode<T> getRoot() {
		return root;
	}

	public void setRoot(BNode<T> root) {
		this.root = root;
	}

	@Override
	public boolean delete(T val) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean balance() {
		// TODO Auto-generated method stub
		return false;
	}

}
