// Copyright 2017 ManOf Logan. All Rights Reserved.
package com.manoflogan.ds;

import java.util.ArrayList;
import java.util.List;

/**
 * Implementation of AVL Tree Data Structure.
 */
public class AVLTree<T extends Comparable<T>> {
  
  static class Node<T extends Comparable<T>> implements Comparable<Node<T>> {
    
    T value;
    
    Node<T> left;
    
    Node<T> right;
  
  
    @Override
    public int compareTo(Node<T> o) {
      return this.value.compareTo(o.value);
    }
  
    @Override
    public String toString() {
      return new StringBuilder(this.getClass().getName()).append("[Value = ").
          append(this.value != null ? this.value.toString() : "").append("]").toString();
    }
  }
  
  private Node<T> startNode;
  
  public AVLTree() {
    this.startNode = null;
  }
  
  public void insert(T value) {
    this.startNode = this.insert(this.startNode, value);
  }
  
  public List<T> preOrder() {
    List<T> list = new ArrayList<>();
    this.preOrder(this.startNode, list);
    return list;
  }
  
  private void preOrder(Node<T> node, List<T> list) {
    if (node != null) {
      list.add(node.value);
      preOrder(node.left, list);
      preOrder(node.right, list);
    }
  }
  
  /**
   * Get the height of the node.
   */
  int getHeight(Node<T> node) {
    if (node == null) {
      return -1;
    }
    int leftHeight = 1 + this.getHeight(node.left);
    int rightHeight = 1 + this.getHeight(node.right);
    return Math.max(leftHeight, rightHeight);
  }
  
  int getBalance(Node<T> left, Node<T> right) {
    return this.getHeight(left) - this.getHeight(right);
  }
  
  private Node<T> rightRotate(Node<T> node) {
    Node<T> left = node.left;
    Node<T> rightOfLeft = left.right;
    left.right = node;
    node.left = rightOfLeft;
    return left;
  }
  
  private Node<T> leftRotate(Node<T> node) {
    Node<T> right = node.right;
    Node<T> leftOfRight = right.left;
    right.left = node;
    node.right = leftOfRight;
    return right;
  }
  
  /**
   * Inserts the node at an appropriate position.
   *
   * @param node node in which the value is to be inserted
   * @param value value to be inserted
   * @return inserted node.
   */
  private Node<T> insert(Node<T> node, T value) {
    if (node == null) {
      node = new Node<>();
      node.value = value;
      return node;
    }
    // Start balancing.
    if (value.compareTo(node.value) > 0) {
        node.right = this.insert(node.right, value);
    } else {
       node.left = this.insert(node.left, value);
    }
    int balance = this.getBalance(node.left, node.right);
    // More left nodes than right nodes.
    if (balance > 1) {
      // Left Left case.
     if (value.compareTo(node.left.value) < 0) {
      node = this.rightRotate(node);
    } else if (value.compareTo(node.left.value) > 0) {
       // Left right case.
       node.left = this.leftRotate(node.left);
       node = this.rightRotate(node);
      }
    } else if (balance < -1) {
      // Right Right case (Right than the value of the right node)
      if (value.compareTo(node.right.value) > 0) {
        node = this.leftRotate(node);
      } else {
        node.right = this.rightRotate(node.right);
        node = this.leftRotate(node);
      }
    }
    return node;
  }
}
