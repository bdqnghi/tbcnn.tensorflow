package redblacktree;

import redblacktree.type.Color;

public class RedBlackTree {
    
    private RedBlackTree parent;
    
    private boolean isLhs;
    private boolean isRhs;
    
    private RedBlackTree lhs;
    private RedBlackTree rhs;
    
    private Color color;
   
    private final int value;
    
    RedBlackTree(final int value, final Color color) {
        this(value, color, null);
    }
    
    RedBlackTree(final int value, final Color color, final RedBlackTree parent) {
	this(value, color, parent, null, null);
    }
    
    RedBlackTree(final int value, final Color color, final RedBlackTree parent, final RedBlackTree lhs, final RedBlackTree rhs) {
	this.value = value;
	this.color = color;
        this.parent = parent;
	this.lhs = lhs;
	this.rhs = rhs;
    }
    
    public int getValue() {
	return value;
    }
    
    public void setColor(final Color color) {
        this.color = color;
    }
    
    public Color getColor() {
	return color;
    }
    
    public int getLevel() {
        return parent != null ? 1 + parent.getLevel(): 1;
    }
    
    public void setLHS(final boolean isLhs) {
        this.isLhs = isLhs;
    }
    
    public boolean isLHS() {
        return isLhs;
    }
    
    public void setRHS(final boolean isRhs) {
        this.isRhs = isRhs;
    }
    
    public boolean isRHS() {
        return isRhs;
    }
    
    public void setParent(final RedBlackTree parent) {
        this.parent = parent;
    }
    
    public RedBlackTree getParent() {
        return parent;
    }
    
    public void setLHS(final RedBlackTree lhs) {
        this.lhs = lhs;
        
        if (lhs != null) {
            this.lhs.setLHS(true);
        }
    }
    
    public RedBlackTree getLHS() {
	return lhs;
    }
    
    public void setRHS(final RedBlackTree rhs) {
        this.rhs = rhs;
        
        if (rhs != null) {
            this.rhs.setRHS(true);
        }
    }
    
    public RedBlackTree getRHS() {
	return rhs;
    }
    
    public void insert(final int value) {
        final RedBlackTree newNode = new RedBlackTree(value, Color.RED, null);
        
        if (value >= this.value) { // should go on right hand
            if (rhs != null) { // traverse rhs
                rhs.insert(value);
            } else { // insert to rhs
                newNode.setParent(this);
                setRHS(newNode);
            }
        } else { // should go on left hand
            if (lhs != null) {
                lhs.insert(value);
            } else { // insert to lhs
                newNode.setParent(this);
                setLHS(newNode);
            }
        }
        
        RedBlackTree currentNode = newNode;
        
        while (currentNode != null && currentNode.getParent() != null && currentNode.getColor() == Color.RED && currentNode.getParent().getParent() != null) {
            final RedBlackTree parent = currentNode.getParent();
            if (parent.isLHS()) { // left of grandparent CASE A
                final RedBlackTree grandParent = parent.getParent();
                if (grandParent != null) {
                    final RedBlackTree otherChild = grandParent.getRHS();
                    if (parent.getColor() == Color.RED && otherChild != null && otherChild.getColor() == Color.RED) { // case 1
                        // recolor parent, other child
                        parent.setColor(Color.BLACK);
                        otherChild.setColor(Color.BLACK);
                        
                        // recolor grandparent
                        grandParent.setColor(Color.RED);
                        
                        currentNode = grandParent;
                    } else {
                        if (currentNode.isRHS()) { // case 2
                            leftRotate(parent); // left rotate on parent
                            
                            currentNode = parent;
                        }
                        // case 3 - right rotate & recolor
                        
                        final RedBlackTree newParent = currentNode.getParent();
                        if (newParent != null) {
                            final RedBlackTree newGrandParent = newParent.getParent();
                            if (newGrandParent != null) {
                                rightRotate(newGrandParent); // right rotate on grand parent
                                
                                // recolor
                                
                                newParent.setColor(Color.BLACK);
                                newGrandParent.setColor(Color.RED);
                            }
                        }
                    }
                }
            } else { // right of grandparent CASE B
                final RedBlackTree grandParent = parent.getParent();
                if (grandParent != null) {
                    final RedBlackTree otherChild = grandParent.getLHS();
                    if (parent.getColor() == Color.RED && otherChild != null && otherChild.getColor() == Color.RED) { // case 1
                        // recolor parent, other child
                        parent.setColor(Color.BLACK);
                        otherChild.setColor(Color.BLACK);
                        
                        // recolor grandparent
                        grandParent.setColor(Color.RED);
                        
                        currentNode = grandParent;
                    } else {
                        if (currentNode.isLHS()) { // case 2
                            rightRotate(parent); // right rotate on parent

                            currentNode = parent;
                        }
                        // case 3 - left rotate & recolor
                        
                        final RedBlackTree newParent = currentNode.getParent();
                        if (newParent != null) {
                            final RedBlackTree newGrandParent = newParent.getParent();
                            if (newGrandParent != null) {
                                leftRotate(newGrandParent); // left rotate on grand parent
                                
                                // recolor
                                
                                newParent.setColor(Color.BLACK);
                                newGrandParent.setColor(Color.RED);
                            }
                        }
                    }
                } else {
                    currentNode = currentNode.getParent();
                }
            }
        }
    }
    
    public boolean find(final int value) {
        return value > this.value ? rhs != null && rhs.find(value) : value < this.value ? lhs != null && lhs.find(value) : true;
    }
    
    public boolean delete(final int value) {
        return false;
    }
    
    public int height() {
        return 1 + Math.max(lhs != null ? lhs.height() : 0, rhs != null ? rhs.height() : 0);
    }
    
    public int count() {
        return 1 + (lhs != null ? lhs.count() : 0) + (rhs != null ? rhs.count() : 0);
    }
    
    public void print() {
        RedBlackTree parent = this;
        while (parent != null) {
            RedBlackTree nextParent = parent.getParent();
            if (nextParent != null) {
                parent = nextParent; 
            } else {
                break;
            }
        }
        if (parent != null) {
            parent.recursivePrint();
        }
    }
    
    public void recursivePrint() {
        final int level = getLevel();
        for (int i = 0; i < level - 1; i ++) {
            System.out.print("\t");
        }
        System.out.println(value + " [" + color + "]");
        
        if (lhs != null) {
            lhs.recursivePrint();
        } else {
            for (int i = 0; i < level; i ++) {
                System.out.print("\t");
            }
            System.out.println("nil [BLACK]");
        }
        
        if (rhs != null) {
            rhs.recursivePrint();
        } else {
            for (int i = 0; i < level; i ++) {
                System.out.print("\t");
            }
            System.out.println("nil [BLACK]");
        }
    }
    
    private static void rightRotate(final RedBlackTree root) {
        final RedBlackTree lhs = root.getLHS();
        
        if (lhs != null) {
            final RedBlackTree lhsRhs = lhs.getRHS();
            
            lhs.setRHS(root);
            
            final RedBlackTree rootParent = root.getParent();
            if (rootParent != null) {
                if (root.isLHS()) {
                    rootParent.setLHS(lhs);
                } else if (root.isRHS()) {
                    rootParent.setRHS(lhs);
                }
            }
            lhs.setParent(rootParent);
            
            root.setParent(lhs);
            
            root.setLHS(lhsRhs);
            if (lhsRhs != null) {
                lhsRhs.setParent(root);
            }
        }
    }
    
    private static void leftRotate(final RedBlackTree root) {
        final RedBlackTree rhs = root.getRHS();
        
        if (rhs != null) {
            final RedBlackTree rhsLhs = rhs.getLHS();
            
            rhs.setLHS(root);
            
            final RedBlackTree rootParent = root.getParent();
            if (rootParent != null) {
                if (root.isLHS()) {
                    rootParent.setLHS(rhs);
                } else if (root.isRHS()) {
                    rootParent.setRHS(rhs);
                }
            }
            rhs.setParent(rootParent);
            
            root.setParent(rhs);
            
            root.setRHS(rhsLhs);
            if (rhsLhs != null) {
                rhsLhs.setParent(root);
            }
        }     
    }
}