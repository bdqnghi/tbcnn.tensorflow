import java.util.ArrayList;

/* 
 * Properties: 
 *  1. A node is either red or black.
 *  2. The root is black. (This rule is sometimes omitted)
 *  3. All leaves (NIL) are black. (All leaves are same color as the root.)
 *  4. Every red node must have two black child nodes.
 *  	- Threatened When...
 *  		- Adding a Red Node
 *  		- Rotating
 *  		- Repainting Black node Red
 *  5. Every path from a given node to any of its descendant leaves contains the same number of black nodes.
 *  	- Threatened When...
 *  		- Adding a Black Node
 *  		- Repainting a Red Node Black
 *  		- Repainting a Black Node Red
 *  		- Rotation
 *  
 * Rules for Insertion (Node A): 
 *  - Insert (Node A) following the BinarySearch method
 *  - Color (Node A) red, give item two null children (leaves) colored black
 *  - Check for property 4 : "Every red node must have two black child nodes"
 *  	- Broken if (Node A) has red parent
 *  
 *  Solving insertion issues 
 *  - Case 1: Current Node is at Root
 *  	- Repaint Black
 *  - Case 2: Current Node has Black Parent
 *  	- Do Nothing
 *  - Case 3: Parent && Uncle are Red
 *  	- Paint Grandparent Red
 *  	- Paint Parent + Uncle Black
 *  	- Set Grandparent = Current -> Recursively Call
 *  - Case 4: 
 *  Parent  = Red
 *  Uncle   = Black
 *  Current = Right Child
 *  Parent  = Left Child
 *  	- Left Rotation on parent P
 *  	- Use Case 5 on former parent P
 *  			
 *  - Case 5:
 *  Parent = Red
 *  Uncle = Black
 *  Current = Left Child
 *  Parent = Left Child
 *  	- Right Rotation on Grandparent
 *  	- Parent = Black
 *  	- Grandparent = Red
 *  	
 *  Right Rotation
 *  	- Parent Right = Grandparent
 *  	- Grandparent Left = Parent Old Right
 *  Left Rotation
 *  	- Parent Left = Grandparent
 *  	- Grandparent Right = Parent Old Left
 *  
 *    
 *  
 *  
 *   
 */
public class RedBlackTree {

    public final static String COLOR_BLACK = "black";
    public final static String COLOR_RED = "red";

    public final static String SIDE_LEFT = "left";
    public final static String SIDE_RIGHT = "right";

    public RBNode root;

    public RBNode add(Object data) {
        if (this.isEmpty()) {
            RBNode rbNode = new RBNode(data, null, null, null, COLOR_BLACK, null);
            this.root = rbNode;
            return rbNode;
            
        } else {
            RBNode node = root;
            RBNode nodeToInsert = new RBNode(data, null, null, null, COLOR_RED, null);
            boolean finished = false;
            while (!finished) {
                if (node.compareTo(data) > 0) {
                    if (node.left == null) {
                        nodeToInsert.side = SIDE_LEFT;
                        nodeToInsert.parent = node;
                        node.left = nodeToInsert;
                        finished = true;
                    } else {
                        node = node.left;
                    }
                } else {
                    if (node.right == null) {
                        nodeToInsert.side = SIDE_RIGHT;
                        nodeToInsert.parent = node;
                        node.right = nodeToInsert;
                        finished = true;
                    } else {
                        node = node.right;
                    }
                }
            }
            return nodeToInsert;
        }
    }
    
    public void insert(Object data) {
        this.checkInsertCases(this.add(data));
    }
    
    private void checkInsertCases(RBNode current) {
        boolean finished = false;
        while (!finished) {
            System.out.println("Current: " + current.data);
            if(current == this.root) {
                finished = true;
            } else if (current.parent.isBlack()) {
                System.out.println("Reached Insert Case 1");
                finished = true;
            } else if (current.getUncle() == null || current.getUncle().isBlack()) {
                if (current.parent.side == SIDE_LEFT) {
                    if (current.side == SIDE_LEFT) {
                        System.out.println("Reached Insert Case 2");
                        current.parent.paintBlack();
                        current.getGrandParent().paintRed();
                        this.rotateRight(current.getGrandParent());
                        finished = true;
                    } else {
                        System.out.println("Reached Insert Case 3");
                        current.getGrandParent().paintRed();
                        current.paintBlack();
                        this.leftRightRotation(current);
                        finished = true;
                    }
                } else {
                    if (current.side == SIDE_RIGHT) {
                        System.out.println("Reached Insert Case 4");
                        current.getGrandParent().paintRed();
                        current.parent.paintBlack();
                        this.rotateLeft(current.getGrandParent());
                        finished = true;
                    } else {
                        System.out.println("Reached Insert Case 5");
                        current.getGrandParent().paintRed();
                        current.paintBlack();
                        this.rightLeftRotation(current);
                        finished = true;
                    }
                }
            } else {
                System.out.println("Reached Insert Case 6");
                current.parent.paintBlack();
                current.getUncle().paintBlack();
                if(current.getGrandParent() == this.root) {
                    finished = true;
                } else {
                    current.getGrandParent().paintRed();
                    current = current.getGrandParent();
                }
            }
        }
    }

    private boolean isEmpty() {
        return (this.root == null);
    }

    public void printTree() {
        this.root.printNodes();
    }

    public RBNode rotateRight(RBNode current) {
        RBNode leftChild = current.left;
        current.left = leftChild.right;
        
        if(current.left != null) {
            current.left.parent = current;
            current.left.side = SIDE_LEFT;
        }

        leftChild.right = current;
        leftChild.side = current.side;
        leftChild.parent = current.parent;

        // Moves up the tree and updates relationships
        RBNode parent = current.parent;
        RBNode child = leftChild;
        while (parent != null) {
            if (child.side == SIDE_LEFT) {
                parent.left = child;
            } else {
                parent.right = child;
            }
            child = parent;
            parent = parent.parent;
        }
        this.root = child;

        current.parent = leftChild;
        current.side = SIDE_RIGHT;

        return leftChild;
    }

    public RBNode rotateLeft(RBNode current) {
        RBNode rightChild = current.right;
        current.right = rightChild.left;
        
        if(current.right != null) {
            current.right.parent = current;
            current.right.side = SIDE_RIGHT;
        }
        

        rightChild.left = current;
        rightChild.side = current.side;
        rightChild.parent = current.parent;

        // Moves up the tree and updates relationships
        RBNode parent = current.parent;
        RBNode child = rightChild;
        while (parent != null) {
            if (child.side == SIDE_LEFT) {
                parent.left = child;
            } else {
                parent.right = child;
            }
            child = parent;
            parent = parent.parent;
        }
        this.root = child;

        current.parent = rightChild;
        current.side = SIDE_LEFT;

        return rightChild;
    }

    public void printTreePreOrder() {
        this.root.printPreOrder();
    }

    public ArrayList<RBNode> getNodesPreOrder(ArrayList<RBNode> nodes, RBNode current) {
        if (current == null) {
            return nodes;
        }
        nodes.add(current);
        this.getNodesPreOrder(nodes, current.left);
        this.getNodesPreOrder(nodes, current.right);

        return nodes;
    }
    
    public void leftRightRotation(RBNode b) {
        RBNode c = b.getGrandParent();
        RBNode a = b.parent;
        
        a.right = b.left;
        if(a.right != null) {
            a.right.side = SIDE_RIGHT;
            a.right.parent = a;
        }
        b.left = a;
        a.parent = b;
        b.side = c.side;
        
        b.parent = c.parent;
        if(b.parent != null) {
            if(b.side == SIDE_LEFT) {
                b.parent.left = b;
            } else {
                b.parent.right = b;
            }
        }
        
        c.left = b.right;
        if(c.left != null) {
            c.left.side = SIDE_LEFT;
            c.left.parent = c;
        }
        b.right = c;
        c.parent = b;
        
        if(c == this.root) {
            this.root = b;
        }
        
    }
    
    public void rightLeftRotation(RBNode b) {
        RBNode c = b.getGrandParent();
        RBNode a = b.parent;
        
        a.left = b.right;
        if(a.left != null) {
            a.left.side = SIDE_LEFT;
            a.left.parent = a;
        }
        b.right = a;
        a.parent = b;
        b.side = c.side;
        
        b.parent = c.parent;
        if(b.parent != null) {
            if(b.side == SIDE_LEFT) {
                b.parent.left = b;
            } else {
                b.parent.right = b;
            }
        }
        
        c.right = b.left;
        if(c.right != null) {
            c.right.side = SIDE_RIGHT;
            c.right.parent = c;
        }
        b.left = c;
        c.parent = b;
        
        if(c == this.root) {
            this.root = b;
        }
    }

}
