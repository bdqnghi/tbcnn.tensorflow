package _tree._binary_search_tree._avl_tree;

import _tree._binary_search_tree.BinarySearchTree;

/**
 * 平衡二叉树
 * @author 734070824@qq.com
 * @date 2018/2/9 11:16
 */
public class AVLTree<V extends Comparable<V>>{

    private AVLNode<V> root;

    public AVLTree(V v) {
        root = new AVLNode(v);
    }


    /**
     * LL旋转
     *      6           6             4
     *    4   9 -->   4    9  -->   3   6    6(失衡点)
     *   3 5         3 5           2   5  9
     *              2
     *
     * @param key 失衡点
     * @return
     */
    public AVLNode<V> leftLeftRotation(AVLNode<V> key) {
        AVLNode tmp = key.left;
        key.left = tmp.right;
        tmp.right = key;
        key.height = max(height(key.left), height(key.right)) + 1;
        tmp.height = max(height(tmp.left), height(tmp.right)) + 1;
        return tmp;
    }

    /**
     * RR旋转
     * @param key 失衡点
     * @return
     */
    public AVLNode<V> rightRightRotation(AVLNode<V> key) {
        AVLNode tmp = key.right;
        key.right = tmp.left;
        tmp.left = key;
        key.height = max(height(key.left), height(key.right)) + 1;
        tmp.height = max(height(tmp.left), height(tmp.right)) + 1;
        return tmp;
    }

    /**
     *  LR旋转
     *
     *     8                     8                      6
     *  4       12  ---RR-->   6    12 ---LL-->      4   8
     *2   6                  4  7                  2    7  12
     *      7               2
     * @param key 失衡点
     * @return
     */
    public AVLNode<V> leftRightRotation(AVLNode<V> key) {
        //失衡点的左节点 RR
        key.left = rightRightRotation(key.left);
        //失衡点 LL
        return leftLeftRotation(key);
    }

    /**
     * RL 旋转
     * @param key 失衡点
     * @return
     */
    public AVLNode<V> rightLeftRotation(AVLNode<V> key) {
        //失衡点的右节点 LL
        key.right = leftLeftRotation(key.right);
        //失衡点 RR
        return rightRightRotation(key);
    }




    private int max(int a, int b) {
        return a>b ? a : b;
    }


    //获取树的高度
    private int height(AVLNode<V> tree) {
        if (tree != null)
            return tree.height;
        return 0;
    }

    public int height() {
        return height(root);
    }

}
