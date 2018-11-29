package src.MyTree;

public class AVLTree {
    //AVL树的节点
    class AVLTreeNode {
        private int data;
        private int high;
        public AVLTreeNode left;
        public AVLTreeNode right;

        public AVLTreeNode(int data) {
            this.data = data;
        }

        public int getData() {
            return data;
        }

        public void setData(int data) {
            this.data = data;
        }

        public int getHigh() {
            return high;
        }

        public void setHigh(int high) {
            this.high = high;
        }
    }

    private AVLTreeNode root;

    //返回给定节点的高度
    private int height(AVLTreeNode t) {
        return t.high;
    }

    //左单旋转
    private AVLTreeNode rotateWithLeftChild(AVLTreeNode k2) {
        AVLTreeNode k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        k2.setHigh(Math.max(height(k2.left), height(k2.right)));
        k1.setHigh(Math.max(height(k1.left), height(k1.right)));
        return k1;
    }

    //右单旋转
    private AVLTreeNode rotateWithRightChild(AVLTreeNode k1) {
        AVLTreeNode k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        k1.setHigh(Math.max(height(k1.left), height(k2.right)));
        k2.setHigh(Math.max(height(k2.left), height(k2.right)));
        return k2;
    }

    //左双旋转
    private AVLTreeNode doubleWithLeftChild(AVLTreeNode k3){
        k3.left = rotateWithRightChild(k3.left);
        return rotateWithLeftChild(k3);
    }

    //右双旋转
    private AVLTreeNode doubleWithRightChild(AVLTreeNode k3){
        k3.right = rotateWithLeftChild(k3.right);
        return  rotateWithRightChild(k3);
    }

    public AVLTreeNode insert(int data) {
        return insert(data,root);
    }

    private AVLTreeNode insert(int data, AVLTreeNode t) {
        if(t==null){
            return new AVLTreeNode(data);
        }
        if(data>t.getData()){
            t.right=insert(data,t.right);
            if(height(t.right)-height(t.left)==2){
                if(data>t.right.getData()){
                    rotateWithRightChild(t);
                }
                else{
                    doubleWithRightChild(t);
                }
            }
        }
        else if(data<t.getData()){
            t.left = insert(data,t.left);
            if(data<t.left.getData()){
                rotateWithLeftChild(t);
            }
            else{
                doubleWithLeftChild(t);
            }
        }
        t.setHigh(Math.max(t.left.getHigh(),t.right.getHigh()));
        return t;
    }
}

