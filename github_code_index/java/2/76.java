package com.neu.struct.tree;

/**
 * 问题：AVL树
 *     在构造二叉排序树的过程中，每当插入一个节点时，首先检查是否因插入而破坏了树的平衡性，
 *     如果是因插入节点而破坏了树的平衡性，则找出其中最小不平衡子树，在保持二叉排序树特性的前提下，
 *     调整最小不平衡子树中各结点之间的连接关系，以达到新的平衡，通常将这样得到的平衡二叉排序树称为AVL树
 * 定义：
 *     平衡二叉树：若T是一棵非空二叉树，其左、右子树为LT和RT，另lh和rh分别为左、右子树的深度。
 *               当且仅当：①LT和RT都是平衡二叉树
 *                       ②|lh-rh|≤1
 *               时，则T为平衡二叉树。
 *     平衡因子：定义|hl-hr|为二叉平衡树的平衡因子。平衡二叉树上所有节点的平衡因子可能是-1、0、-1。
 *             换言之，若一棵二叉树上的任一节点的平衡因子的绝对值都不大于1，则该树就是一棵平衡二叉树。
 *     最小不平衡子树：
 *             以离插入节点最近，且平衡因子的绝对值大于1的结点作为根节点的子树，设该结点为A。
 *             调整该子树的规律可归纳为下列四种情况：
 *        ①LL型：新节点x插在A的左孩子的左子树里，其中B为A的左孩子。
 *               以A、B之间的路径为轴，以B为轴心，将A节点从B的右上方调整到B的右下方，使A成为B的右孩子。
 *        ②RR型：新节点x插在A的右孩子的右子树里，其中B为A的右孩子。
 *               以A、B之间的路径为轴，以B为轴心，将A节点从B的左上方调整到B的左下方，使A成为B的左孩子。
 *        ③LR型：新节点x插在A的左孩子的右子树里，其中B为A的左孩子。
 *               以x、B之间的路径为轴，以x为轴心，将节点B从x的左上方调整到x的左下方，使B成为x的左孩子，
 *               x成为A的左孩子，此时转变为LL型。
 *               以A、x之间的路径为轴，以x为轴心，将A节点从x的右上方调整到x的右下方，使A成为x的右孩子。
 *        ④RL型：新节点x插在A的右孩子的左子树里，其中B为A的右孩子。
 *               以x、B之间的路径为轴，以x为轴心，将节点B从x的右上方调整到x的右下方，使B成为x的右孩子。
 *               x成为A的右孩子，此时转变为RR型。
 *               以A、x之间的路径为轴，以x为轴心，将节点A从x的左上方调整到x的左下方，使A成为x的左孩子。
 * Created by lihongyan on 2015/11/9.
 */
public class AvlTree<T extends Comparable<? super T>> {

    private AvlNode<Integer> nil = new AvlNode<Integer>(0);
    //定义AVL树中的节点
    private static class AvlNode<T>{
        private T element;            //节点中的数据
        private AvlNode<T> left;
        private AvlNode<T> right;
        private AvlNode<T> parent;
        private int height;       //节点的高度
        public AvlNode(T element){
            this.element = element;
            this.left = null;
            this.right = null;
            this.parent = null;
            this.height = 0;
        }
        public AvlNode(T element,AvlNode<T> lt,AvlNode<T> rt){
            this.element = element;
            this.left = lt;
            this.right = rt;
            this.parent = null;
            this.height = 0;
        }
        public AvlNode<T> getParent() {
            return parent;
        }
        public void setParent(AvlNode<T> parent) {
            this.parent = parent;
        }
        public T getElement() {
            return element;
        }
        public void setElement(T element) {
            this.element = element;
        }
        public AvlNode<T> getLeft() {
            return left;
        }
        public void setLeft(AvlNode<T> left) {
            this.left = left;
        }
        public AvlNode<T> getRight() {
            return right;
        }
        public void setRight(AvlNode<T> right) {
            this.right = right;
        }
        public int getHeight() {
            return height;
        }
        public void setHeight(int height) {
            this.height = height;
        }

        @Override
        public String toString() {
            String result = this.getElement().toString();
            return result;
        }
    }



    private AvlNode<T> root;//定义AVL树根
    public AvlNode<T> getRoot() {return root;}
    public void setRoot(AvlNode<T> root) {this.root = root;}
    public AvlTree(){ this.root = null;}


    /*
    * 最大最小关键字节点
    * */
    public AvlNode<T> avl_tree_minimum(AvlNode<T> local){
        while(local.left!=null){
            local = local.left;
        }
        return local;
    }
    public AvlNode<T> avl_tree_maximum(AvlNode<T> local){
        while(local.right!=null){
            local = local.right;
        }
        return local;
    }
    /*
    * 旋转
    * */
    public void avl_tree_left_rotate(AvlTree<T> tree,AvlNode<T> A){

    }
    public void avl_tree_right_rotate(AvlTree<T> tree,AvlNode A){

    }
    /*
    * 插入
    * */
    public void avl_tree_insert(AvlTree<T> tree,T key){
        tree.setRoot(avl_tree_insert_fixup(tree.getRoot(),key));
    }
    public AvlNode<T> avl_tree_insert_fixup(AvlNode<T> local,T key){
        if(local==null){
            return new AvlNode<T>(key);
        }else{
            int compare = key.compareTo(local.getElement());
            if(compare<0){
                local.left = avl_tree_insert_fixup(local.left,key);
                local.left.parent = local;
                if(height(local.left)-height(local.right)>1){//打破平衡
                    if(key.compareTo(local.left.getElement())<0){//LL
                        local = LL(local);
                    }else{//LR
                        local = LR(local);
                    }
                }
            }else if(compare>0){
                local.right = avl_tree_insert_fixup(local.right,key);
                local.right.parent = local;
                if(height(local.right)-height(local.left)>1){//打破平衡
                    if(key.compareTo(local.right.getElement())>0){//RR
                        local = RR(local);
                    }else{//RL
                        local = RL(local);
                    }
                }
            }else{;}
            local.setHeight(Math.max(height(local.left),height(local.right))+1);
            return local;
        }
    }
    public AvlNode<T> LL(AvlNode<T> A){
        AvlNode<T> B = A.left;
        if(B==null){
            A.left = null;
        }else{
            A.left = B.right;
        }
        if(B.right!=null){
            B.right.parent = A;
        }
        if(A.parent==null){
            this.root = B;
            B.parent = null;
        }else{
            B.parent = A.parent;
        }
        B.right = A;
        A.parent = B;
        A.setHeight(Math.max(height(A.left),height(A.right)) - 1);
        B.setHeight(Math.max(height(B.left), height(A)) + 1);
        return B;
    }
    public AvlNode<T> RR(AvlNode<T> A){
        AvlNode<T> B = A.getRight();
        A.right = B.left;
        if(B==null){
            A.right = null;
        }else{
            A.right = B.left;
        }
        if(B.left!=null){
            B.left.parent = A;
        }
        if(A.parent==null){
            this.root = B;
            B.parent = null;
        }else{
            B.parent = A.parent;
        }
        B.left = A;
        A.parent = B;
        A.setHeight(Math.max(height(A.left),height(A.right)) - 1);
        B.setHeight(Math.max(height(B.right),height(A)) + 1);
        return B;
    }
    public AvlNode<T> LR(AvlNode<T> A){
        A.left = RR(A.getLeft());
        return LL(A);
    }
    public AvlNode<T> RL(AvlNode<T> A){
        A.right = LL(A.getRight());
        return RR(A);
    }
    public int height(AvlNode<T> node){
        return node==null?-1:node.getHeight();
    }
    /*
    * 删除
    * ①如果z仅有一个孩子，且该孩子为z的右孩子，这个右孩子可以是null，也可以不是。
    *   当z的右孩子为null，归为z没有孩子节点，直接删除z；
    *   当z的右孩子非null，这种情况就是z仅有一个孩子的情况，
    *   该孩子为z的右孩子。用z的右孩子替换z。
    * ②如果z仅有一个孩子，且该孩子为z的左孩子，那么用其左孩子来替换z。
    * ③z既有左孩子又有右孩子，在z的右子树中查找z的后继（y位于z的右子树，且y没有左孩子）。
    *   根据y的位置又可以分成两种情况：（两种情况下，y的左孩子均为null）
    *   a.y是z的右孩子：
    *        保留y的右孩子，将y移出原来的位置；使z的左孩子成为y的左孩子；用y替换z。
    *   b.y不是z的右孩子，但是y位于z的右子树中：
    *        将y移出原来的位置；用y的右孩子替换y原来的位置；
    *        将y变为z的右孩子r的新的父节点，使r成为y的右孩子。
    * */
    public void avl_tree_delete(T key){
        AvlNode<T> z = avl_tree_get_node(key);
        if(z.getLeft()==null){//情况1  z仅有右孩子。在这种情况中z的右孩子可以是null，也可以不是null
            avl_tree_replace(z,z.right);
        }else if(z.getRight()==null){//情况2  z仅有左孩子
            avl_tree_replace(z,z.left);
        }else{//情况3，z既有左孩子，又有右孩子，在这种情况下又可以分两种情况：
              // z的后继y为z的右孩子；z的后继y不是z的右孩子
            AvlNode<T> y = avl_tree_minimum(z.right);
            if(y==z.getRight()){//情况3下的情况1：y是z的右孩子
                y.left = z.left;
                z.left.parent = y;
                avl_tree_replace(z,y);
            }else{ //情况3下的情况2：y不是z的右孩子
                AvlNode<T> x = y.right;
                //使用y的右孩子x替换y
                y = avl_tree_replace(y,x);
                y.setHeight(z.getHeight()-1);
                avl_tree_replace(z,y);
            }
        }
    }
    public AvlNode<T> avl_tree_replace(AvlNode<T> u,AvlNode<T> v){
        if(u.parent==null){
            this.root = v;
            v.parent = null;
        }else if(u==u.parent.left){
            u.parent.left = v;
        }else{
            u.parent.right = v;
        }
        if(v!=null){
            v.parent = u.parent;
            u.parent.setHeight(u.getHeight()-1);
        }
        return u;
    }
    /*
    * 获取：给定一个关键字，获取节点
    * */
    public AvlNode<T> avl_tree_get_node(T key){
        AvlNode<T> temp = this.getRoot();
        if(temp==null){
            return null;
        }else{
            while(temp!=null){
                if(key.compareTo(temp.getElement())<0){
                    temp = temp.left;
                }else if(key.compareTo(temp.getElement())>0){
                    temp = temp.right;
                }else{
                    System.out.println();
                    return temp;
                }
            }
            return temp;
        }
    }
    /*
    * 遍历
    * */
    public void avl_tree_pre_order(AvlNode<T> localRoot){
        if(localRoot!=null){
            System.out.print(localRoot.getElement()+" ");
            avl_tree_pre_order(localRoot.left);
            avl_tree_pre_order(localRoot.right);
        }
    }
    public void avl_tree_in_order(AvlNode<T> localRoot){
        if(localRoot!=null){
            avl_tree_in_order(localRoot.left);
            System.out.print(localRoot.getElement() + " ");
            avl_tree_in_order(localRoot.right);
        }
    }
    public void avl_tree_post_order(AvlNode<T> localRoot){
        if(localRoot!=null){
            avl_tree_post_order(localRoot.left);
            avl_tree_post_order(localRoot.right);
            System.out.print(localRoot.getElement() + " ");
        }
    }




    public static void main(String[] args){
        AvlTree<Integer> avl = new AvlTree<Integer>();
        int[] nodes = {4,5,7,2,1,3,6};
        for(int i=0;i<nodes.length;i++){
            avl.avl_tree_insert(avl,nodes[i]);
        }
        avl.avl_tree_pre_order(avl.getRoot());
        System.out.println();
        avl.avl_tree_in_order(avl.getRoot());
        System.out.println();
        avl.avl_tree_post_order(avl.getRoot());
        System.out.println();
        //delete
        avl.avl_tree_delete(7);
        avl.avl_tree_delete(5);
        avl.avl_tree_pre_order(avl.getRoot());
        System.out.println();
        avl.avl_tree_in_order(avl.getRoot());
        System.out.println();
        avl.avl_tree_post_order(avl.getRoot());
        System.out.println();
    }
}
