package ru.spbstu.telematics.student_Vasilevsky.lab02;

import java.util.Iterator;

public class RedBlackTree<T extends Comparable<T>> implements IRedBlackTree<T>, Iterable<T> {
	private Node<T> root;	
	
	public Node<T> getRoot() {
		return root;
	}
	
	public void setRoot(Node<T> root) {
		this.root = root;
	}
	
	private Node<T> minNode(Node<T> aNode) {
		if (aNode.getLeft().isNull() == false) {
			return minNode(aNode.getLeft());
		}
		return aNode;
	}
	
	private Node<T> getNextNode(Node<T> aNode) {
		if (aNode.getRight().isNull() == false) {
			return minNode(aNode.getRight());
		}
		Node<T> y = aNode.getParent();
		while (y != null && aNode == y.getRight()) {
			aNode = y;
			y = y.getParent();
		}
		return y;
	}
	
	class RBIterator implements Iterator<T> {	
		private Node<T> firstNode;
		private Node<T> currentNode;
		
		public RBIterator() {
			super();
			firstNode = RedBlackTree.this.minNode(getRoot());
			currentNode = firstNode;
		}
		
		@Override
		public boolean hasNext() {
			if (getNextNode(currentNode) != null) {
				return true;
			}
			return false;
		}

		@Override
		public T next() {
			if (currentNode == firstNode) {
				firstNode = null;
				return currentNode.getStoredObject();
			} 
			if (this.hasNext()) {
				currentNode = getNextNode(currentNode);
				return currentNode.getStoredObject();
			}
			throw new NoSuchMethodError();
		}

		@Override
		public void remove() {
			System.out.println("Oops");
			throw new IllegalStateException();
		}
	}
	
	@Override
	public Iterator<T> iterator() {
		return new RBIterator();
	}
	
	@Override
	public void add(T e) {
		this.insert(e, this.getRoot());
	}
	
	@Override
	public boolean remove(T o) {
		boolean returnValue = false;
		Node<T> nodeToRemove = this.find(o, this.getRoot());
		while (nodeToRemove != null) {
			this.deleteNode(nodeToRemove);
			returnValue = true;
			nodeToRemove = this.find(o, this.getRoot());
		}
		
		return returnValue;
	}

	@Override
	public boolean contains(T o) {
		if (this.find(o, this.getRoot()) != null)
			return true;
		return false;
	}

	private void insert(T e, Node<T> parent) {
		if (parent == null && this.getRoot() == null) {
			parent = new Node<T>(null, e);
			this.setRoot(parent);
			parent.setRed(false);
		}
		//если e больше, чем предок
		else if (e.compareTo(parent.getStoredObject()) >= 0) {
			if (parent.getRight().isNull() == true) {
				parent.setRight(new Node<T>(parent, e));
				//проверка баланса
				this.checkBalance1(parent.getRight());
			} else {
				this.insert(e, parent.getRight());
			}
		}
		//если е меньше чем предок
		else {
			if (parent.getLeft().isNull() == true) {
				parent.setLeft(new Node<T>(parent, e));
				//проверка баланса
				this.checkBalance1(parent.getLeft());
			} else {
				this.insert(e, parent.getLeft());
			}
		}
	}

	private void checkBalance0(Node<T> aNode) {
		if (aNode.getParent() == null) {
			aNode.setRed(false);
		}
		else {
			this.checkBalance1(aNode);
		}
		
	}
	
	private void checkBalance1(Node<T> aNode) {	
		if (aNode.getParent().isRed() == false) {
			return;
		}
		else {
			this.checkBalance2(aNode);
		}
	}

	private void checkBalance2(Node<T> aNode) {
		if ((aNode.getUncle().isNull() == false) && (aNode.getUncle().isRed() == true) && (aNode.getParent().isRed() == true)) {
			aNode.getParent().setRed(false);
			aNode.getUncle().setRed(false);
			aNode.getGrandParent().setRed(true);
			checkBalance0(aNode.getGrandParent());
		}
		else {
			checkBalance3(aNode);
		}
	}

	private void checkBalance3(Node<T> aNode) {
		if ((aNode == aNode.getParent().getRight()) && (aNode.getParent() == aNode.getGrandParent().getLeft())) {
			this.rotateLeft(aNode.getParent());
			aNode = aNode.getLeft();
		}
		else if ((aNode == aNode.getParent().getLeft()) && (aNode.getParent() == aNode.getGrandParent().getRight())) {
			this.rotateRight(aNode.getParent());
			aNode = aNode.getRight();
		}
		this.checkBalance4(aNode);
	}

	private void checkBalance4(Node<T> aNode) {
		aNode.getParent().setRed(false);
		aNode.getGrandParent().setRed(true);
		if ((aNode == aNode.getParent().getLeft()) && (aNode.getParent() == aNode.getGrandParent().getLeft())) {
			this.rotateRight(aNode.getGrandParent());
		} else {
			this.rotateLeft(aNode.getGrandParent());
		}
		
	}
	
	private void rotateLeft(Node<T> aNode) {	
		Node<T> y = aNode.getRight();
		aNode.setRight(y.getLeft());
		
		if (y.getLeft().isNull() == false) {
			y.getLeft().setParent(aNode);
		}
		y.setParent(aNode.getParent());
		
		if (aNode.getParent() == null) {
			this.setRoot(y);
		} else {
			if (aNode == aNode.getParent().getLeft()) {
				aNode.getParent().setLeft(y);
			} else {
				aNode.getParent().setRight(y);
			}
		}
		y.setLeft(aNode);
		aNode.setParent(y);
	}
	
	private void rotateRight(Node<T> aNode) {	
		Node<T> y = aNode.getLeft();
		aNode.setLeft(y.getRight());
		
		if (y.getRight().isNull() == false) {
			y.getRight().setParent(aNode);
		}
		y.setParent(aNode.getParent());
		
		if (aNode.getParent() == null) {
			this.setRoot(y);
		} else {
			if (aNode == aNode.getParent().getRight()) {
				aNode.getParent().setRight(y);
			} else {
				aNode.getParent().setLeft(y);
			}
		}
		y.setRight(aNode);
		aNode.setParent(y);
	}

	private Node<T> find(T desiredObject, Node<T> parent) {
		if (this.getRoot() == null) {
			return null;
		}
		
		if (parent.isNull() == true) {
			return null;
		}
		if (desiredObject.compareTo(parent.getStoredObject()) == 0) {
			return parent;
		}
		else if (desiredObject.compareTo(parent.getStoredObject()) > 0) {
			parent = parent.getRight();
			return this.find(desiredObject, parent);
		}
		else if (desiredObject.compareTo(parent.getStoredObject()) < 0) {
			parent = parent.getLeft();
			return this.find(desiredObject, parent);
		}
		return null;
		
	}
	
	private Node<T> sibling(Node<T> aNode) {
		if (aNode == aNode.getParent().getLeft()) {
			return aNode.getParent().getRight();
		}
		else {
			return aNode.getParent().getLeft();
		}
	}
	
	public void deleteNode(Node<T> aNode) {
		if (aNode.getLeft().isNull() == false && aNode.getRight().isNull() == false) {		//если у удаляемого узла два потомка
			this.deleteTwoChilds(aNode);
		} else { 								//если у удаляемого узла не более одного потомка
			this.deleteOneChild(aNode);
		}
	}
	
	private void deleteTwoChilds (Node<T> aNode) {
		Node<T> successor = this.successor(aNode);
		aNode.setStoredObject(successor.getStoredObject());
		this.deleteNode(successor);		
	}

	private Node<T> successor(Node<T> aNode) {
		if (aNode.getLeft().isNull() == false) {
			aNode = aNode.getLeft();
			while (aNode.getRight().isNull() == false) {
				aNode = aNode.getRight();
			}
			return aNode;
		}
		return null;
	}
	
	private void deleteOneChild (Node<T> aNode) {		
		Node<T> child;
		if (aNode.getRight().isNull())
			child = aNode.getLeft();
		else
			child = aNode.getRight();
		
		this.replaceNode(aNode, child);
		if (aNode.isRed() == false) {
			if (child.isRed() == true) {
				child.setRed(false);
			}
			else {
				this.deleteCase1(child);
			}
		}
	}

	private void replaceNode(Node<T> aNode, Node<T> child) {
		if (aNode.getParent() != null) {
			if (aNode == aNode.getParent().getLeft())
				aNode.getParent().setLeft(child);
			else
				aNode.getParent().setRight(child);
			child.setParent(aNode.getParent());
		}
		else
			this.setRoot(child);	
	}

	private void deleteCase1(Node<T> aNode) {		
		if (aNode.getParent().isNull() == false)
			deleteCase2(aNode);
	}

	private void deleteCase2(Node<T> aNode) {		
		Node<T> s = this.sibling(aNode);
		if (s.isRed() == true) {
			aNode.getParent().setRed(true);
			s.setRed(false);
			if (aNode == aNode.getParent().getLeft())
				this.rotateLeft(aNode.getParent());
			else
				this.rotateRight(aNode.getParent());
		}
		this.deleteCase3(aNode);
		
	}

	private void deleteCase3(Node<T> aNode) {
		Node<T> s = this.sibling(aNode);
		
		if ((aNode.getParent().isRed() == true) &&
			(s.isRed() == false) &&
			(s.getLeft().isRed() == false) &&
			(s.getRight().isRed() == false)) {
			s.setRed(true);
			aNode.getParent().setRed(false);
		}
		else
			deleteCase5(aNode);
		
	}

	private void deleteCase5(Node<T> aNode) {
		Node<T> s = this.sibling(aNode);
		
		if (s.isRed() == false) {
			if (aNode == aNode.getParent().getLeft() &&
				s.getRight().isRed() == false &&
				s.getLeft().isRed() == true) {
				s.setRed(true);
				s.getLeft().setRed(false);
				this.rotateRight(s);
			}
			else if ((aNode == aNode.getParent().getRight()) &&
					(s.getLeft().isRed() == false) &&
					(s.getRight().isRed() == true)) {
				s.setRed(true);
				s.getRight().setRed(false);
				this.rotateLeft(s);
			}
		}
		this.deleteCase6(aNode);
		
	}

	private void deleteCase6(Node<T> aNode) {		
		Node<T> s = this.sibling(aNode);
		
		s.setRed(aNode.getParent().isRed());
		aNode.getParent().setRed(false);
		
		if (aNode == aNode.getParent().getLeft()) {
			s.getRight().setRed(false);
			this.rotateLeft(aNode.getParent());
		}
		else {
			s.getLeft().setRed(false);
			this.rotateRight(aNode.getParent());
		}
	}
}