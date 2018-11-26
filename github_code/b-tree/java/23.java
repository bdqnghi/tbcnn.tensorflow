
public class bTree {


/*    Node root;
    bTree left_child;
    bTree right_child;

    public bTree(){

    }
    
    public bTree(Node root, bTree left_child, bTree right_child){
        this.root = root;
        this.left_child = left_child;
        this.right_child = right_child;
    }

    public bTree insertElement(int element){
        if (root==null)
            return new bTree(new Node(element, true), null, null);
        else {
            if (root.isLeaf()){
                root.setLeaf(false);
                if (element < root.getValue())
                    return new bTree(root, new bTree(new Node(element, true), null, null), null);
                else
                    return new bTree(root, null, new bTree(new Node(element, true), null, null));
            } else {
                if (element < root.getValue())
                    if (left_child!=null)
                        return new bTree(root, left_child.insertElement(element), right_child);
                    else
                        return new bTree(root, new bTree(new Node(element, true), null, null), right_child);
                else
                    if (right_child!=null)
                        return new bTree(root, left_child, right_child.insertElement(element));
                    else
                        return new bTree(root, left_child, new bTree(new Node(element, true), null, null));
            }
        }
    }

    public bTree getLeftChild(){
        return left_child;
    }

    public bTree getRightChild(){
        return right_child;
    }

    public void setLeftChild(bTree tree){
        this.left_child = tree;
    }

    public void setRightChild(bTree tree){
        this.right_child = tree;
    }

    public bTree buildBinaryTree(int[] elements){
        if (elements.length==0)
            return null;
        else{
            bTree tree = new bTree(new Node(elements[0], true), left_child, right_child);
            for (int i=1;i<elements.length;i++){
                tree = tree.insertElement(elements[i]);
            }
            return tree;
        }
    }

    public void traversePreOrder(){
        if (root!=null)
            System.out.print(root.getValue() + " ");
        if (left_child!=null)
            left_child.traversePreOrder();
        if (right_child!=null)
            right_child.traversePreOrder();
    }

    public void traverseInOrder(){
        if (left_child!=null)
            left_child.traverseInOrder();
        if (root!=null)
            System.out.print(root.getValue() + " ");
        if (right_child!=null)
            right_child.traverseInOrder();
    }
    public void traversePostOrder(){
        if (left_child!=null)
            left_child.traversePostOrder();
        if (right_child!=null)
            right_child.traversePostOrder();
        if (root!=null)
            System.out.print(root.getValue() + " ");
    }*/

    public static void main(String[] args){
    	

        
        dNode NodeA = new dNode("A");
        dNode NodeB = new dNode("B");
        dNode NodeC = new dNode("C");
        dNode NodeD = new dNode("D");
        dNode NodeE = new dNode("E");
        dNode NodeF = new dNode("F");
        
        
        NodeA.lChild = NodeB;
        NodeA.rChild = NodeC;
        
        NodeB.lChild = NodeD;
        NodeB.rChild = NodeE;
        
        NodeC.rChild = NodeF;
        
        insertValue(NodeA);
        
        
        System.out.println(NodeA.toString());
        System.out.println(NodeB.toString());
        System.out.println(NodeC.toString());
        System.out.println(NodeD.toString());
        System.out.println(NodeE.toString());
        System.out.println(NodeF.toString());
        
    }

	static int  index=1;
	
    public static void insertValue(dNode node){
    	

    	
		if(node == null){
		  // No tree, 
		  return;
		}
	      
		
		node.lValue = index;
		index = index+1;
		System.out.println(node.toString());

		insertValue(node.lChild);



    }
}