package com.mmc.data.structure.system.tree.val;

/**
 * @packageName：com.mmc.data.structure.system.tree.val
 * @desrciption:
 * @author: gaowei
 * @date： 2017-11-03 17:27
 * @history: (version) author date desc
 */
public class AutoAvlTree<T extends Comparable> {


    private AvlTreeNode<T> root;
    private int size;

    /**
     *
     */
    public AutoAvlTree() {
        this.root = null;
        this.size = 0;
    }

    public void insert(T element) {
        this.root = insertNode(element, root);
    }

    /**
     * avl平衡二叉树插入节点
     * @param element
     * @param node
     * @return
     */
    private AvlTreeNode<T> insertNode(T element, AvlTreeNode<T> node) {
        if (node == null) {
            return new AvlTreeNode<T>(element);
        }
        if (element == null) {
            throw new IllegalArgumentException();
        }
        // 比较插入数据与父节点大小
        int compareResult = element.compareTo(node.element);
        if (compareResult > 0) {
            // 右树插入数据
            node.right = insertNode(element, node.right);
            // 验证是否平衡
            if (height(node.right) - height(node.left) == 2) {
                if (element.compareTo(node.right.element) > 0) {
                    // 单旋转
                    node = rotateWithRightChild(node);
                } else {

                }
            }
        }

        return null;
    }

    /**
     * 右-左，左-右，双旋转
     * @param node
     * @return
     */
    private AvlTreeNode<T> doubleWithRightChild(AvlTreeNode<T> node) {

        return null;
    }

    /**
     * 右边往左单旋转
     * @param node
     * @return
     */
    private AvlTreeNode<T> rotateWithRightChild(AvlTreeNode<T> node) {
        AvlTreeNode<T> right1 = node.right;
        right1.left = node;
        right1.right = right1.right;
        node.height = Math.max(height(node.right), height(node.left) + 1);
        right1.height = Math.max(height(right1.right), height(right1.left) + 1);
        return right1;
    }


    private int height(AvlTreeNode<T> node) {
        return node == null ? -1 : node.height;
    }

    /**
     * Avl平衡二叉树节点
     * @param <T>
     */
    private static class AvlTreeNode<T> {
        private T element;
        private AvlTreeNode<T> left;
        private AvlTreeNode<T> right;
        private int height;

        public AvlTreeNode(T element_i) {
            this(element_i, null, null);
        }

        public AvlTreeNode(T element_i, AvlTreeNode<T> left_i, AvlTreeNode<T> right_i) {
            this.element = element_i;
            this.left = left_i;
            this.right = right_i;
            this.height = 0;
        }
    }
}
