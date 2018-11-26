package structure.tree;

import common.utils.ObjectUtils;

/**
 * Created by boyce on 2014/8/4.
 */
public class IAVLTree<T extends Comparable> extends IBinaryTree<T> {

    public static void main(String[] args) {

        IAVLTree tree = new IAVLTree();
        tree.insert(3);
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        tree.insert(16);
        tree.insert(15);
        tree.insert(14);
        tree.insert(13);
        tree.insert(12);
        tree.insert(11);
        tree.insert(10);
        tree.insert(8);
        tree.insert(9);

        tree.display();

        tree.remove(7);

        tree.display();

        System.out.println(tree.validate());
    }

    /**
     * 重写二叉树删除方法，每一次删除都要保证树平衡
     * @param element
     * @param node
     * @return
     */
    @Override
    protected Node remove(T element, Node node) {
        if (null == node)
            return node;

        int compareResult = element.compareTo(node.element);
        if (compareResult < 0) {
            node.leftNode = remove(element, node.leftNode);

            //删除左子树导致右子树高度比左子树高度大2（右右右），执行右单旋转
            if (this.height(node.rightNode) - this.height(node.leftNode) == 2)
                node = this.rotateWithRightChild(node);
        }

        else if (compareResult > 0) {
            node.rightNode = remove(element, node.rightNode);

            //删除右子树导致左子树高度比右子树高度大2（左左左），执行左单旋转
            if (this.height(node.leftNode) - this.height(node.rightNode) == 2)
                 node = this.rotateWithLeftChild(node);
        }

        else if (null != node.rightNode && null != node.leftNode){
            T leftMax = this.findMax(node.leftNode);
            node.element = leftMax;
            node.leftNode = remove(leftMax, node.leftNode);

            //删除左子树导致右子树高度比左子树高度大2（右右右），执行右单旋转
            if (this.height(node.rightNode) - this.height(node.leftNode) == 2)
                node = this.rotateWithRightChild(node);
        }
        else
            node = null != node.rightNode ? node.rightNode : node.leftNode;

        //重新更新节点高度
        if (null != node)
            node.height = Math.max(this.height(node.rightNode), this.height(node.leftNode)) + 1;

        return node;
    }


    /**
     * 重写二叉树插入方法，每一次插入都要保证树平衡
     * @param element
     * @param node
     * @return
     */
    @Override
    protected Node insert(T element, Node node) {
        if (null == node)
            return new Node(element);

        int compareResult = element.compareTo(node.element);

        if (compareResult < 0) {
            node.leftNode = insert(element, node.leftNode);

            //在左子树中插入导致左子树高度比右子树高度大2，执行左旋转
            if (this.height(node.leftNode) - this.height(node.rightNode) == 2) {

                //左左右，左双旋转
                if (element.compareTo(node.leftNode.element) > 0)
                    node = this.doubleWithLeftChild(node);

                //左左左，左单旋转
                else
                    node = this.rotateWithLeftChild(node);
            }
        }

        else if (compareResult > 0) {
            node.rightNode = insert(element, node.rightNode);

            //在右子树中插入导致右子树高度比左子树高度大2，执行右旋转
            if (this.height(node.rightNode) - this.height(node.leftNode) == 2) {

                //右右左，右双旋转
                if (element.compareTo(node.rightNode.element) < 0)
                    node = this.doubleWithRightChild(node);

                //右右右，右单旋转
                else
                    node = this.rotateWithRightChild(node);
            }
        }

        //重新更新节点高度
        node.height = Math.max(this.height(node.rightNode), this.height(node.leftNode)) + 1;
        return node;
    }

    /**
     * 右子树单旋转 （右右右）
     * @param node 被旋转的子树的根节点
     * @return 旋转后的子树的根节点
     */
    protected Node rotateWithRightChild(Node node) {

        //保留根节点的右节点，将根节点的右节点调整为原右节点的左节点，将原右节点的左节点指向根节点
        Node right = node.rightNode;
        node.rightNode = right.leftNode;
        right.leftNode = node;

        //重新计算根节点和原右节点的高度，其他节点高度不变
        node.height = Math.max(this.height(node.leftNode), this.height(node.rightNode)) + 1;
        right.height = Math.max(this.height(right.rightNode), node.height) + 1;

        //将原右节点作为根节点返回，相当于将原右节点提起来，根节点下层至原右节点的左节点
        return right;
    }

    /**
     * 左子树单旋转（左左左）
     * @param node 被旋转的子树的根节点
     * @return 旋转后的子树的根节点
     */
    protected Node rotateWithLeftChild(Node node) {

        //保留根节点的左节点，将根节点的左节点调整为原左节点的右节点，将原左节点的右节点指向根节点
        Node left = node.leftNode;
        node.leftNode = left.rightNode;
        left.rightNode = node;

        node.height = Math.max(this.height(node.leftNode), this.height(node.rightNode)) + 1;
        left.height = Math.max(this.height(left.leftNode), node.height) + 1;

        //将原左节点作为根节点返回，相当于将原左节点提起来，根节点下层至原左节点的右节点
        return left;
    }

    /**
     * 右子树双旋转（右右左）
     * @param node 被旋转的子树的根节点
     * @return 旋转后的子树的根节点
     */
    protected Node doubleWithRightChild(Node node) {

        //将根节点的右节点进行一次单左旋转，再对根节点进行一次右旋转
        node.rightNode = this.rotateWithLeftChild(node.rightNode);
        return this.rotateWithRightChild(node);
    }

    /**
     * 左子树双旋转（左左右）
     * @param node 被旋转的子树的根节点
     * @return 旋转后的子树的根节点
     */
    protected Node doubleWithLeftChild(Node node) {

        //将根节点的左节点进行一次单右旋转，再对根节点进行一次左旋转
        node.leftNode = this.rotateWithRightChild(node.leftNode);
        return this.rotateWithLeftChild(node);
    }

    /**
     * O(nlgn)
     * validate avl-tree node high and avl-tree balance
     * @return
     */
    public boolean validate() {
        return this.validate(root);
    }

    //validate  avl-tree node high and node balance
    private boolean validate(Node node) {
        if (ObjectUtils.isNull(node))
            return -1 == this.height(node);

        if (node.isLeaf())
           return 0 == node.height;

        else if (node.onlyLeftChild())
            return
                this.validate(node.leftNode) &&
                node.height == node.leftNode.height + 1 &&
                node.height < 2;

        else if(node.onlyRightChild())
            return
                this.validate(node.rightNode) &&
                node.height == node.rightNode.height + 1 &&
                node.height < 2;

        else {
            int left = node.leftNode.height;
            int right = node.rightNode.height;

            return
                this.validate(node.rightNode) &&
                this.validate(node.leftNode) &&
                node.height == (left > right ? left + 1 : right + 1) &&
                Math.abs(node.rightNode.height - node.leftNode.height) < 2;
        }
    }

}
