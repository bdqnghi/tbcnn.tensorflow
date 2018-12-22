/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package 树;

/**
 * 对于一个红黑树而言，它的高度最高不高于2lgN，因为红黑树的最坏情况就是它所对应的2-3树中构成最左边的路径节点全部都是3-节点，而其余都是2-节点
 * 红黑树所满足的条件：
 * 1.红链接均为左链接
 * 2.没有任何一个节点同时和两个红链接相连
 * 3.该树是完美黑色平衡的，即任何空链接到根节点的路径上的黑链接数量相同
 */
public class BlackRedTree {
    public static void main(String args[]){
       BlackRedTree bt = new BlackRedTree();
       bt.put(7, "7");
       bt.put(5,"5");
       bt.put(3,"3");
       bt.delete(1);
       System.out.println(bt.root.val);
       
    }
    private static final boolean Red = true;
    private static final boolean Black = false;
    public Node root;
    
    private class Node{
        int key;
        String val;
        Node left;
        Node right;
        int total;
        boolean color;
        
        Node(int key,String val, int total, boolean color){
            this.key = key;
            this.val = val;
            this.total = total;
            this.color = color;
        }
    }
    
    private boolean isRed(Node x){
        if(x ==null) return false;
        return x.color == Red;
    }
    
    private String get(Node x, int key){
        if(x==null) return null;
        if(key>x.key){
            return(get(x.right,key));
        }else if(key<x.key){
            return(get(x.left,key));
        }else{
            return x.val;
        }
    }
    
    public int min(){
        return min(root).key;   
    }
    
    private Node min(Node x){
        if(x.left==null) return x;
        return min(x.left);
    }
    
    public int size(){
        return(size(root));
    }
    
    private int size(Node x){
        if(x==null) return 0;
        else return x.total;
    }
    
    public void put(int key, String val){       // 红黑树插入节点的时候，总会在树的底部新增一个节点，但总是用红链接将节点和它的父节点相连
        root = put(root,key,val);
        root.color = Black;
    }
    
    public Node put(Node h,int key, String val){
        if(h==null) return new Node(key,val,1,Red);
        if(h.key>key){
            h.left = put(h.left,key,val);
        }
        else if(h.key<key){
            h.right = put(h.right,key,val);
        }else{
            h.val =val;
        }
        
        if(isRed(h.right) &&!isRed(h.left)) h = rotateLeft(h);
        if(isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if(isRed(h.left) && isRed(h.right)) flipColors(h);
        
        h.total = size(h.left)+size(h.right) +1;
        return h;
    }
    
    Node rotateLeft(Node h){
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = Red;
        x.total = h.total;
        h.total = size(h.left) +size(h.right)+1;
        return x;
    }
    
    Node rotateRight(Node h){
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = Red;
        x.total = h.total;
        h.total = size(h.left)+size(h.right)+1;
        return x;
    }
    
    void flipColors(Node h){       // 这是用于插入的颜色转换
        h.color = Red;              // 当前节点的左边与右边都是红色时，意味着这三个节点在3-2中表示为一个节点，我们需要将中间的节点提出并不断的向上结合
        h.left.color = Black;       // 在颜色的转换中，始终设置根节点为黑色， 但是当根节点由黑变红的时候，说明树的高度加一了，之后，我们再次将根节点设置为黑色
        h.right.color = Black;     
    }
    
    /**
    * 红黑树的删除操作：
    *   当删除最大值或最小值的时候，该节点如果是一个2-节点，删除他以后会改变红黑树的平衡性，我们就需要不断的组合节点让其不是2-节点
    * 1.删除当前的节点不能是2-节点
    * 2.如果有必要可以是4-节点
    * 3.从底部删除节点
    * 4.向上fix过程中，消除4-节点      
    */
    void moveflipColors(Node h ){   //  这是用于删除节点的flipColor方法，该方法用于节点的合并，将父节点中的部分给与子节点
        h.color = Black;            
        h.left.color = Red;       
        h.right.color = Red;
    }
    private Node moveRedLeft(Node h){
        /**
         * 当前节点的左右子节点都是2-节点，左右节点需要从父节点中借一个节点
         * 如果该节点的右节点的左节点是红色节点，说明兄弟节点不是2-节点，可以从兄弟节点中借一个
         */
        moveflipColors(h);     // 从父节点中借一个
        if(isRed(h.right.left)){    // 判断兄弟节点，如果是非红节点，也从兄弟节点中借一个
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            moveflipColors(h);  // 在从兄弟节点借了一个以后，我们就需要还一个节点给父节点了，因为一开始从父节点那里借了一个
        }
        return h;
    }
    
    public void deleteMin(){
        if(!isRed(root.left) && !isRed(root.right)){
            root.color = Red;   // 如果根节点的左右子节点是2-节点，我们可以将根设为红节点，这样才能进行后面的moveRedLeft操作，因为左子要从根节点借一个
        }
        root = deleteMin(root);
        root.color = Black;  // 借完以后，我们将根节点的颜色复原
    }
    
    private Node deleteMin(Node x){
        if(x.left == null) return null;
        if(!isRed(x.left) && !isRed(x.left))    // 判断x的左节点是不是2-节点
            x = moveRedLeft(x);
        x.left = deleteMin(x.left);
        return balance(x);  //   解除临时组成的4-节点
    }
    
    private Node balance(Node h){
        if (isRed(h.right)) h = rotateLeft(h);
        if (isRed(h.right) && !isRed(h.left)) h=rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h=rotateRight(h);
        if (isRed(h.left) && isRed(h.right))    flipColors(h);
        h.total = size(h.left)+size(h.right)+1;
        return h;
    }
    
    // 删除最大键
    private Node moveRedRight(Node h){
        moveflipColors(h);
        if(isRed(h.left.left)){         // 在这里对于兄弟节点的判断都是.left，因为红色节点只会出现在左边
            h=rotateRight(h);
            moveflipColors(h);
        }
        return h;
    }
    public void deleteMax(){
        if(!isRed(root.left) && isRed(root.right)){
            root.color = Red;
        }
        root = deleteMax(root);
        root.color = Black;
    }
    
    private Node deleteMax(Node h){
        if(isRed(h.left)){             
        /**
         * 这里比deleteMin多了一步操作，因为右子节点从父节点中获得节点的时候，我们需要将左边节点给于到右边节点，如果我们不移动的话，会破坏树的平衡
         *          5,6
         *      1,2     9       对于所展示的这个红黑树，如果不把5从左边移到右边的话，我们会直接删除9，这样会导致树的不平衡，因为红节点总是在左边的，我们进行删除操作的时候，直接将结点给予，只需要改变颜色即可，不需要移动
         *                      对于红黑树而言，6是黑结点，再删除的时候，是不需要移动的，我们移动的是5这样的红结点
         *      
        */                                         
            h = rotateRight(h);
        }
        if(h.right == null){
            return null;
        }
        if(!isRed(h.right) && !isRed(h.right.left)){
            h = moveRedRight(h);
        }
        h.right = deleteMax(h.right);
        return balance(h);
    }
    
    public void delete(int key){
        if(!isRed(root.left)&& !isRed(root.right)){
            root.color = Red;
        }
        root = delete(root,key);
        root.color = Black;
    }
    
    private Node delete(Node h, int key){
        if(key<h.key){          // 当目标键小于当前键的时候，我们做类似于寻找最小是的操作，向树左边移动，合并父子结点来消除2-结点
            if(h.left == null){
                return null;
            }
            if(isRed(h.left) && !isRed(h.left.left)){
                h = moveRedLeft(h);
            }
            h.left = delete(h.left,key);
        }else{                  // 当目标键大于当前键的时候，我们向右移动，并做与deleteMax相同的操作，如果相同的话，我们使用和二叉树的删除一样的操作，获取当前键的右子树的最小健，然后交换，并将目标键删除
            if(isRed(h.left)){
                h = rotateRight(h);
            }
            if(key != h.key && h.right == null){    // 我们没有找到目标键，我们将其删除
                return null;
            }
            if(!isRed(h.right) && isRed(h.right.left)){
                h = moveRedRight(h);
            }
            if(key == h.key){
                h.val = get(h.right,min(h.right).key);
                h.key = min(h.right).key;
                h.right = deleteMin(h.right);
            }
            else h.right = delete(h.right,key);
        }
        return balance(h);
    }
   
}
