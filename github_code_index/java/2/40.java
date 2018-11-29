/******************************************
 *    Adam Lindsey                        *
 *    CIS313 -- Fall 2014                 *
 *    Assignment #6 -- Lab #3             *
 *    AVLtree.java                        *
 ******************************************/
 //This is the AVLtree class that will use the AVLnode class.
 
public class AVLtree {
   
   //the root of the tree
   AVLnode root;
   
   //simple default constructor
   public AVLtree() {this.root = new AVLnode();}
   
   //empty the tree of data
   public void makeEmpty() {this.root = new AVLnode();}
   
   //internal method for the height of node
   private int height(AVLnode n) {
      if(n==null)n=new AVLnode();
      return n.getHeight();
   }
   
   //insert data into tree
   public void insert(String title) {
      if(this.root.getData()=="") this.root.setData(title);
      else this.root = insert(title,this.root);
   }
   //recursively insert data
   private AVLnode insert(String title, AVLnode n){
      if(n.getData()!=""||n.getData()!=null){
         if(title.compareTo(n.getData())<0) {
            if(n.getRight()==null) n.right = new AVLnode(title);
            else {
               insert(title,n.getRight());
               if(height(n.left)-height(n.right) == 2) {
                  if(title.compareTo(n.left.data) < 0)
                     n = rotateLeft(n);
                  else n = rotateDblLeft(n);
               }
            }
         } else {
            if(n.getLeft()==null) n.left = new AVLnode(title);
            else {
               insert(title,n.getLeft());
               if(height(n.right)-height(n.left)==2) {
                  if(title.compareTo(n.right.data) > 0)
                     n = rotateRight(n);
                  else n = rotateDblRight(n);
               }
            }
         }
      } else n.setData(title);
      n.setHeight(Math.max(height(n.left),height(n.right))+1);
      return n;
   }
   
   //search tree for an element
   public boolean find(String title) { return find(title,this.root);}
   //recursively search for element
   private boolean find(String title, AVLnode n){
      if(n!=null) {
         if(title.equals(n.getData())) return true;
         if(title.compareTo(n.getData())<0) 
            return find(title,n.getRight());
         else return find(title, n.getLeft());
      }else return false;
   }
   
   //remove a given element from the tree 
   //(as derivation of the search function)
   public boolean remove(String s) {
      if(find(s)) {
         this.root = remove(s,root);
         return true;
      } else return false;
   }
   //recursively get to node
   public AVLnode remove(String title, AVLnode n) {
      if(n!=null) {
         if(title.equals(n.getData())) {
            n = deleteNode(n);
            return n;
         }
         if(title.compareTo(n.getData())<0) {
            n = remove(title,n.getRight());
            if(height(n.right)-height(n.left)==2) {
               if(title.compareTo(n.right.data) > 0)
                  n = rotateRight(n);
               else n = rotateDblRight(n);
            } 
         } else {
            n = remove(title, n.getLeft());
            if(height(n.left)-height(n.right) == 2) {
               if(title.compareTo(n.left.data) < 0)
                  n = rotateLeft(n);
               else n = rotateDblLeft(n);
            }
         }
      }else return n;
      return n;
   }
   //remove that node and return
   public AVLnode deleteNode(AVLnode n){
      AVLnode empty = new AVLnode();
      if(n.left==null && n.right==null) return empty;
      n = findNext(n);
      return n;
   }
   //recursively find the replacement node
   public AVLnode findNext(AVLnode n){
      
      if(n.right!=null) n=findNext(n.right);
      if(n.right==null&&n.left!=null) n=findNext(n.left);
      return n;
   }
   
   //now for some balancing methods
   //rotate left
   private AVLnode rotateLeft(AVLnode y) {
      AVLnode x = y.left;
      y.left = x.right;
      x.right = y;
      y.setHeight(Math.max(height(y.left),height(y.right)) + 1);
      x.setHeight(Math.max(height(x.left),y.getHeight()) + 1);
      return x;
   }
   //rotate right
   private AVLnode rotateRight(AVLnode x) {
      AVLnode y = x.right;
      x.right = y.left;
      y.left = x;
      x.setHeight(Math.max(height(x.left),height(x.right)) + 1);
      y.setHeight(Math.max(height(y.right),x.getHeight()) + 1);
      return y;
   }
   //double rotate left
   private AVLnode rotateDblLeft(AVLnode z){
      z.left = rotateRight(z.left);
      return rotateLeft(z);
   }
   //double rotate right
   private AVLnode rotateDblRight(AVLnode x){
      x.right = rotateLeft(x.right);
      return rotateRight(x);
   }
}