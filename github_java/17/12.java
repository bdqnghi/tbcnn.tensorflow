package redBlackTree;

import java.util.Collection;
import java.util.Comparator;

public class RedBlackTree<T> {
	 class RedBlackNode implements PrintNode{
		   T data;
		   RedBlackNode left;
		   RedBlackNode right;
		   RedBlackNode parent;
		   int color;
		   public RedBlackNode(){
			   this.data = null;
			   this.left = null;
			   this.right = null;
			   this.parent = null;
			   this.color = RedBlackTree.BLACK;
		   }
		   @SuppressWarnings("unchecked")
		public RedBlackNode(T d){
			   data = d;
			   left = RedBlackTree.this.Nil;
			   right  = RedBlackTree.this.Nil;
			   parent = RedBlackTree.this.Nil;
			   color = RedBlackTree.RED;
		   }
		   @SuppressWarnings("unchecked")
		public RedBlackNode(T d, RedBlackNode parent){
			   this.data = d;
			   left = RedBlackTree.this.Nil;
			   right = RedBlackTree.this.Nil;
			   this.parent = parent;
			   
		   }
		@Override
		public PrintNode getLeft() {
			// TODO Auto-generated method stub
			return this.left;
		}
		@Override
		public PrintNode getRight() {
			// TODO Auto-generated method stub
			return this.right;
		}
		@Override
		public char[] getPrintChars() {
			// TODO Auto-generated method stub
			if(this.color == RedBlackTree.BLACK){
				String intString = data.toString()+"(B)";
				return intString.toCharArray();
				
			}else{
				String intString = data.toString()+"(R)";
				return intString.toCharArray();
			}
			
		}
	   }
  private static final int BLACK = 0;
  private static final int RED = 1;
  RedBlackNode Nil;
  RedBlackNode root;
  private Comparator<T> comp;
  
   
   public RedBlackTree(){
	   
	   this.Nil = new RedBlackNode();
	   this.comp  = null;
	   this.root = Nil;
   }
   public RedBlackTree(Collection<? extends T> col){
	   
   }
   
   public RedBlackTree(Comparator<? extends T> comp){
	   this.comp  = (Comparator<T>) comp;
	   
	   this.Nil = new RedBlackNode();
	   this.root = Nil;
   }
   public void insert(T val){
	   RedBlackNode newNode = new RedBlackNode(val);
	   RedBlackNode tempRoot = this.root;
	   RedBlackNode temp = Nil;
	   while(tempRoot != Nil){
		   temp = tempRoot;
		   if( this.isLessOrEqual(val,tempRoot.data)){
			   tempRoot = tempRoot.left;
		   }else{
			   tempRoot = tempRoot.right;
		   }
	   }
	   if( temp == Nil ){
		   this.root = newNode;
		   this.root.parent = this.Nil;
	   }else{
		   if( this.isLessOrEqual(val, temp.data)){
			   temp.left = newNode;
			   newNode.parent = temp;
		   }else{
			   temp.right = newNode;
			   newNode.parent = temp;	   
		   }
		 
	   }
	   insertFixup(newNode);
   }
   private void insertFixup(RedBlackNode currentNode){
	   while(currentNode.parent.color != RedBlackTree.BLACK){
		   if(currentNode.parent.parent.left == currentNode.parent){
			   if(currentNode.parent.parent.right.color == RedBlackTree.RED){
				   currentNode.parent.color = RedBlackTree.BLACK;
				   currentNode.parent.parent.color = RedBlackTree.RED;
				   currentNode.parent.parent.right.color = RedBlackTree.BLACK;
				   currentNode = currentNode.parent.parent;
			   }else{
				    RedBlackNode temp = currentNode.parent.parent;
				   if(currentNode.parent.right == currentNode){
					   rotateLeft(currentNode.parent);
				   }
				   rotateRight(temp);
				   temp.color = RedBlackTree.RED;
				   temp.parent.color = RedBlackTree.BLACK;
				   break;
			   }
		   }else{
			   if(currentNode.parent.parent.left.color == RedBlackTree.RED){
			     currentNode.parent.color  = RedBlackTree.BLACK;
			     currentNode.parent.parent.color = RedBlackTree.RED;
			     currentNode.parent.parent.left.color = RedBlackTree.BLACK;
			     currentNode = currentNode.parent.parent;
			   }else{
				   RedBlackNode temp = currentNode.parent.parent;
				   if( currentNode.parent.left == currentNode){
					   rotateRight(currentNode.parent);
				   }
				   rotateLeft(temp);
				   temp.color = RedBlackTree.RED;
				   temp.parent.color = RedBlackTree.BLACK;
				   break;
			   }
		   }
	   }
	   this.root.color = RedBlackTree.BLACK;
   }
   /*
    *      x
    *     / \
    *    /   \
    *AsubTree \
    *          Y
    *          /\
    *         /  \
    *        /    \
    *     BsubTree cSubTree 
    */
   private void rotateLeft(RedBlackNode x){
	   RedBlackNode xParent = x.parent;
	   RedBlackNode y = x.right;
	   RedBlackNode BSubTree = y.left;
	   y.left = x;
	   x.parent = y;
	   x.right = BSubTree;
	   //analyse whether need to have Nil check in this code
	   BSubTree.parent = x;
	   if(xParent == this.Nil){
		   this.root = y;
		   y.parent = this.Nil;
	   }else if(xParent.left == x){
		   xParent.left = y;
		   y.parent = xParent;
	   }else{
		   xParent.right = y;
		   y.parent = xParent;
	   }
	 
   }
   /*
    *         X
    *        / \
    *       /   \
    *      Y    CsubTree
    *     / \
    *    /   \
    *   /     \
    *Asubtree BsubTree
    * 
    */
   private RedBlackNode rotateRight(RedBlackNode x){
	   RedBlackNode xParent = x.parent;
	   RedBlackNode BSubTree  = x.left.right;
	   RedBlackNode y = x.left;
	   y.right = x;
	   x.parent = y;
	   x.left = BSubTree;
	   //Need to anlayse whether Nil check need to have or Not
	   BSubTree.parent = x;
	   if( xParent == this.Nil){
		   this.root = y;
	   }else if(xParent.left == x){
		   xParent.left = y;
	   }else{
		   xParent.right = y;
	   }
	   y.parent = xParent;
	   return y;
   }
   boolean isLessOrEqual(T operand1, T operand2){
	   if( comp == null ){
		   Comparable<T> tempComp = (Comparable<T>)operand1;
		   if( tempComp.compareTo(operand2) > 0 ){
			   return false;
		   }else{
			   return true;
		   }
		   
	   }else{ 
		   int result = this.comp.compare(operand1, operand2);
		   if( result > 0){
			   return false;
		   }
		   return true;
	   }
   }
}
