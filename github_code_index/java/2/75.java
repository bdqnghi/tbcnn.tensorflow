package com.eagle.test.tree.traversal;

import com.eagle.test.tree.TreeNode;

import java.util.HashSet;
import java.util.Set;

public class AVL {

  public static void main(String[] args) {
    Set<String> sets = new HashSet<>();
    AVL avl = new AVL();
    TreeNode root = avl.insert(null, 5);
    root = avl.insert(root, 3);
    root = avl.insert(root, 2);
    System.out.println(root);
  }

  public TreeNode insert(TreeNode root, int data) {
    if (root == null) {
      root = new TreeNode(data);
      return root;
    }
    if (data < root.val) {
      root.left = insert(root.left, data);
      if (height(root.left) - height(root.right) == 2) {
        if (data < root.left.val) {
          root = leftLeftRotate(root);
        } else {
          root = leftRightRotate(root);
        }
      }
    } else if (data > root.val) {
    }
    return null;
  }

  public TreeNode leftLeftRotate(TreeNode root) {
    TreeNode left = root.left;
    root.left = left.right;
    left.right = root;
    return left;
  }

  public TreeNode rightRightRotate(TreeNode root) {
    TreeNode right = root.right;
    root.right = right.left;
    right.left = root;
    return right;
  }

  public TreeNode leftRightRotate(TreeNode root) {
    root.left = rightRightRotate(root.left);
    return leftLeftRotate(root);
  }

  public TreeNode rightLeftRotate(TreeNode root) {
    root.right = leftLeftRotate(root.right);
    return rightRightRotate(root);
  }

  public int height(TreeNode root) {
    if (root == null) return -1;
    return root.height;
  }
}
