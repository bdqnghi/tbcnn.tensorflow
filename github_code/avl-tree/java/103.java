package AVLTreeTest;

/**
 * Describe：平衡二叉树
 * Author：sunqiushun
 * Date：2018-08-07 15:54:33
 */
public class AVLTree {
    private AVLTreeNode root = null; // 根节点
    private int countRotate = 0; // 统计旋转的次数

    /**
     * 插入操作
     *
     * @param data
     * @return
     */
    public void insert(int data) {
        root = insert(root, data);
    }

    /**
     * 先序遍历
     */
    public void preOrder() {
        preOrder(root);
    }

    /**
     * 中序遍历
     */
    public void inOrder() {
        inOrder(root);
    }

    /**
     * 后序遍历
     */
    public void postOrder() {
        postOrder(root);
    }

    /**
     * 删除指定的节点
     *
     * @param val
     */
    public void remove(int val) {
        AVLTreeNode node = new AVLTreeNode(val);
        if (findAVLNode(root, node)) remove(root, node);
    }

    public int getCountRotate() {
        return countRotate;
    }

    public void setCountRotate(int countRotate) {
        this.countRotate = countRotate;
    }

    private AVLTreeNode remove(AVLTreeNode curNode, AVLTreeNode node) {
        if (curNode == null) return null; // 没有找到删除的节点
        if (node.getData() < curNode.getData()) { // 在左子树上删除
            curNode.setLeft(remove(curNode.getLeft(), node));
            if (Height(curNode.getRight()) - Height(curNode.getLeft()) > 1) { // 在左子树上删除，右子树高度一定不小于左子树高度
                if (Height(curNode.getRight().getLeft()) > Height(curNode.getRight().getRight())) {
                    curNode = doubleRotateRight(curNode); // RL 对curNode.right进行右旋转 再对curNode进行左旋转
                } else {
                    curNode = singleRotateLeft(curNode); // RR 对curNode进行左旋转
                }
            }
        } else if (node.getData() > curNode.getData()) { // 在root的右子树上查找删除节点
            curNode.setRight(remove(curNode.getRight(), node));
            if (Height(curNode.getLeft()) - Height(curNode.getRight()) > 1) {
                if (Height(curNode.getLeft().getLeft()) > Height(curNode.getLeft().getRight())) {
                    curNode = singleRotateRight(curNode); // LL 对curNode进行右旋转
                } else {
                    curNode = doubleRotateLeft(curNode); // LR 对curNode.left左旋转 对curNode进行右旋转
                }
            }
        } else { // 找到删除的节点
            if (curNode.getLeft() != null && curNode.getRight() != null) { // 删除的节点既有左子树又有右子树
                curNode.setData(findNextNode(curNode).getData()); // 将失衡点的data域更改为其直接后继节点的data域
                curNode.setRight(remove(curNode.getRight(), curNode)); // 将问题转换为从其右孩子开始删除其直接后继节点 然后重新开始递归删除
            } else { // 只有左子树或者只有右子树或者为叶子结点
                curNode = (curNode.getLeft() == null) ? curNode.getRight() : curNode.getLeft();
            }
        }
        if (curNode != null) { // 更新root的高度值
            curNode.setHeight(Math.max(Height(curNode.getLeft()), Height(curNode.getRight())) + 1);
        }
        return curNode;
    }

    /**
     * 获取node节点的后继节点(中序遍历)
     *
     * @param node
     * @return
     */
    private AVLTreeNode findNextNode(AVLTreeNode node) {
        if (node == null) return null;
        node = node.getRight();
        while (node != null && node.getLeft() != null) node = node.getLeft();
        return node;
    }

    /**
     * 查找节点
     *
     * @param curNode
     * @param node
     * @return
     */
    private boolean findAVLNode(AVLTreeNode curNode, AVLTreeNode node) {
        if (curNode == null) return false;
        if (node.getData() > curNode.getData()) {
            return findAVLNode(curNode.getRight(), node);
        } else if (node.getData() < curNode.getData()) {
            return findAVLNode(curNode.getLeft(), node);
        } else {
            return true;
        }
    }

    //插入操作
    private AVLTreeNode insert(AVLTreeNode node, int data) {
        if (node == null) { //若节点为空，生成节点
            node = new AVLTreeNode(data);
        } else if (data < node.getData()) { // 左节点
            node.setLeft(insert(node.getLeft(), data)); // 左递归
            if (Height(node.getLeft()) - Height(node.getRight()) == 2) {// 判断当前节点左右高度差
                if (data < node.getLeft().getData()) { // 若为左孩子的左节点 进行RR旋转
                    node = singleRotateRight(node);
                } else { // 若为左孩子的右节点 进行LR旋转
                    node = doubleRotateLeft(node);
                }
            }
        } else if (data > node.getData()) { // 右节点
            node.setRight(insert(node.getRight(), data)); // 右递归
            if (Height(node.getRight()) - Height(node.getLeft()) == 2) { // 判断当前节点右左高度差
                if (data > node.getRight().getData()) { // 若为右孩子的右节点 进行LL旋转
                    node = singleRotateLeft(node);
                } else { // 若为右孩子的左节点 进行RL旋转
                    node = doubleRotateRight(node);
                }
            }
        }
        node.setHeight(Math.max(Height(node.getLeft()), Height(node.getRight())) + 1);   // 设置当前节点的高度
        return node;
    }

    //LL旋转
    private AVLTreeNode singleRotateRight(AVLTreeNode node) {
        countRotate++;
        AVLTreeNode left = node.getLeft();
        node.setLeft(left.getRight());
        left.setRight(node);
        node.setHeight(Math.max(Height(node.getLeft()), Height(node.getRight())) + 1);
        // 理论上需要设置 在insert函数中不需要旋转时也需要设置节点高度 合并为insert中的一次设置
        // left.setHeight(Math.max(Height(left.getLeft()), Height(left.getRight())) + 1);
        return left;
    }

    //RR旋转
    private AVLTreeNode singleRotateLeft(AVLTreeNode node) {
        countRotate++;
        AVLTreeNode right = node.getRight();
        node.setRight(right.getLeft());
        right.setLeft(node);
        node.setHeight(Math.max(Height(node.getRight()), Height(node.getLeft())) + 1);
        // 理论上需要设置 在insert函数中不需要旋转时也需要设置节点高度 合并为insert中的一次设置
        // right.setHeight(Math.max(Height(right.getLeft()), Height(right.getRight())) + 1);
        return right;
    }

    //LR旋转
    private AVLTreeNode doubleRotateLeft(AVLTreeNode node) {
        node.setLeft(singleRotateLeft(node.getLeft())); // 对node.left进行右旋转（在node.left和node.left.right之间旋转)
        return singleRotateRight(node);// 对node进行左旋转（在node和node.left之间旋转）
    }

    //RL旋转
    private AVLTreeNode doubleRotateRight(AVLTreeNode node) {
        node.setRight(singleRotateRight(node.getRight()));// 对node.right进行左旋转（在node.right和node.right.left之间旋转)
        return singleRotateLeft(node);// 对node进行右旋转（在node和node.right之间旋转)
    }

    //求树的高度
    private int Height(AVLTreeNode root) {
        return root == null ? -1 : root.getHeight();
    }

    private void preOrder(AVLTreeNode avlTreeNode) {
        if (avlTreeNode != null) {
            System.out.print(avlTreeNode.getData() + " ");
            preOrder(avlTreeNode.getLeft());
            preOrder(avlTreeNode.getRight());
        }
    }

    private void inOrder(AVLTreeNode avlTreeNode) {
        if (avlTreeNode != null) {
            inOrder(avlTreeNode.getLeft());
            System.out.print(avlTreeNode.getData() + " ");
            inOrder(avlTreeNode.getRight());
        }
    }

    private void postOrder(AVLTreeNode avlTreeNode) {
        if (avlTreeNode != null) {
            postOrder(avlTreeNode.getLeft());
            postOrder(avlTreeNode.getRight());
            System.out.print(avlTreeNode.getData() + " ");
        }
    }

}
