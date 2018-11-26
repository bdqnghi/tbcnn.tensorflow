package com.mosby.ch04;

public class AvlTree<T extends Comparable<? super T>> {
    //??????
    public AvlTree(){
        root = null;
    }
    //??????? AvlNode ???? element ??????????????? AvlNode ????????????????��??????????????
    public void insert(T x){
        root = insert(x, root);
    }
    private AvlNode<T> insert(T x, AvlNode<T> t){
        if(t == null){
            return new AvlNode<>(x);
        }else if(x.compareTo(t.element) < 0){
            t.left = insert(x, t.left);
            if(height(t.left) - height(t.right) == 2){
                if(x.compareTo(t.left.element) < 0){
                    t = rotateWithLeftChild(t);
                }else{
                    t = doubleWithLeftChild(t);
                }
            }
        }else if(x.compareTo(t.element) > 0){
            if(height(t.right) - height(t.left) == 2){
                t.right = insert(x, t.right);
                if(x.compareTo(t.right.element) > 0){
                    t = rotateWithRightChild(t);
                }else{
                    t = doubleWithRightChild(t);
                }
            }
        }else{
            System.out.println("�ظ��ڵ㣬�����κβ���");
        }
        t.height = max(height(t.left), height(t.right)) + 1;
        return t;
    }
    
    /**
     * ???????? 1 ????????????????????????????????????��??????????????????????????��??
     * ???? 1 ???????(?????)????????????(??????????????��??)??
     * 
     * @param k2
     * @return
     */
    private static <T extends Comparable<? super T>> AvlNode<T> rotateWithLeftChild(AvlNode<T> k2){
        AvlNode<T> k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        k1.height = max(height(k1.left), height(k1.right)) + 1;
        k2.height = max(height(k2.right), height(k1.right)) + 1;
        return k2;
    }
    /**
     * ???????? 3 ????????
     * @return
     */
    public static <T extends Comparable<? super T>> AvlNode<T> rotateWithRightChild(AvlNode<T> k1){
        AvlNode<T> k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        k1.height = max(height(k1.left), height(k1.right)) + 1;
        k2.height = max(height(k2.right), height(k1.right))    + 1;
        return k2;
    }
    
    /**
     * ???????? 2 ????????
     * @param k3
     * @return
     */
    private static <T extends Comparable<? super T>> AvlNode<T> doubleWithLeftChild(AvlNode<T> k3){
        k3.left = rotateWithLeftChild(k3.left);
        return rotateWithLeftChild(k3);
    }
    
    private static<T extends Comparable<? super T>> AvlNode<T> doubleWithRightChild(AvlNode<T> k1){
        k1.right = rotateWithLeftChild(k1.right);
        return rotateWithRightChild(k1);
    }
    
    //?? ?????????????????????? t
    private static <T extends Comparable<? super T>> int height(AvlNode<T> t){
        return t == null ? -1 : t.height;
    }
    private static int max(int leftHeight, int rightHeight){
        return leftHeight > rightHeight ? leftHeight : rightHeight;
    }
    
    //??? AvlTree
    private void printTree(AvlNode<T> t){
        if(t != null){
            printTree(t.left);
            System.out.println(t.element);
            printTree(t.right);
        }
    }
    
    private AvlNode<T> root;
    
    /**
     * ?????????????? AvlTree ????
     * @param <T>
     */
    private static class AvlNode<T extends Comparable<? super T>>{
        AvlNode(T element){
            this(element, null, null);
        }
        AvlNode(T element, AvlNode<T> left, AvlNode<T> right){
            this.element = element;
            this.left = left;
            this.right = right;
        }
        @Override
        public String toString(){
            return "val = " + element.toString();
        }
        T element;
        AvlNode<T> left;
        AvlNode<T> right;
        int height;
    }

    /**
     * ???????????????????AVL??????????
     *                 3
     *               /   \
     *             2      6
     *                  /   \
     *                 4     7
     * 
     * ????????????????????AVL?????????????? 8?????????????????AVL??????????????????????? AVL ??????????
     *                  6
     *              /      \
     *             3        7
     *           /   \       \
     *          2     4       8
     * ?????????????????????????AVL?????????????? 5???????????????????????????? AVL ?????????????
     * 
     */
    public static void main(String[] args) {
        AvlTree<Integer> avlTree = new AvlTree<Integer>();
        avlTree.insert(2);
        avlTree.insert(3);
        avlTree.insert(4);
        avlTree.insert(6);
        avlTree.insert(7);
        avlTree.printTree(avlTree.root);
        avlTree.insert(8);
    }
}

































