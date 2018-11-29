package ex5;

import java.util.*;

// red black tree implementation
// from Sedgewick "Algorithms in C++" third edition
public class RedBlackTree extends BinaryTree {
    public static final int red   = 0;
    public static final int black = 1;
    private int            color;

    public RedBlackTree() {
        super();
        color  = red;
    }

    public RedBlackTree(int x) {
        super(x);
        color  = red;
    }

    public RedBlackTree(int x,BinaryTree p) {
        super(x,p);
        color  = red;
    }

    public RedBlackTree(Observer a,int x) {
        super(a,x);
        color  = red;
    }

    public RedBlackTree(RedBlackTree x) {
        super(x);
        color  = red;
    }

    public RedBlackTree getRbParent() {
        return (RedBlackTree)parent;
    }

    public RedBlackTree getRbRight() {
        if (right != null) {
            return (RedBlackTree)right;
        } else {
            return null;
        }
    }

    public RedBlackTree getRbLeft() {
        if (left != null) {
            return (RedBlackTree)left;
        } else {
            return null;
        }
    }

    public BinaryTree newTree(int x,BinaryTree p) {
        return new RedBlackTree(x,p);
    }

    public BinaryTree newTree(BinaryTree t) {
        return new RedBlackTree((RedBlackTree)t);
    }

    protected void copy(RedBlackTree x) {
        super.copy(x);
        color  = x.color;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int c) {
        color = c;
    }


    public RedBlackTree insert(int k,RedBlackTree root) {
        RedBlackTree b;
        b = RBinsert(k,root,0);
        setColor(black);
        return b;
    }

    private RedBlackTree RBinsertLeft(int k,RedBlackTree root,int sw) {
        RedBlackTree l;
        RedBlackTree b;
        String       s = "RBinsertLeft ";

        l = getRbLeft();
        if (l == null) {
            left = b = new RedBlackTree(k,(BinaryTree)this);
            left.setModified();
            root.setChanged();
            root.notifyObservers(s + " : Inserted Left : " + Integer.toString(k));
        }
        else {
            b = l.RBinsert(k,root,sw);
        }
        return b;
    }

    private RedBlackTree RBinsertRight(int k,RedBlackTree root,int sw) {
        RedBlackTree r;
        RedBlackTree b;
        String       s = "RBinsertRight ";

        r = getRbRight();
        if (r == null) {
            right = b = new RedBlackTree(k,this);
            right.setModified();
            root.setChanged();
            root.notifyObservers(s + " : Inserted Right : " + Integer.toString(k));
        }
        else {
            b = r.RBinsert(k,root,sw);
        }
        return b;
    }

    private RedBlackTree RBinsert(int k,RedBlackTree root,int sw) {
        RedBlackTree b = null;
        RedBlackTree x;
        RedBlackTree l;
        RedBlackTree ll;
        RedBlackTree r;
        RedBlackTree rr;
        String       s = "RBinsert ";

        // if current node is a 4 node, split it by flipping its colors
        // if both children of this node are red, change this one to red
        // and the children to black
        l = getRbLeft();
        r = getRbRight();
        if ((l != null)&&(l.getColor()==red)&&(r != null)&&(r.getColor()==red)) {
            setColor(red);
            l.setColor(black);
            r.setColor(black);
        }

        // go left or right depending on key relationship
        if (k < getKey()) {
            // recursively insert
            b = RBinsertLeft(k,root,0);

            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            l = getRbLeft();
            if ((getColor() == red)&&(l != null)&&(l.getColor() == red)&&(sw == 1)) {
                x = (RedBlackTree)rotRight();
                if (x != null) {
                    // copy returned node to 'this'
                    copy(x);
                    setModified();
                }
                root.setChanged();
                root.notifyObservers(s + " : Rotated Right : "+ Integer.toString(getKey()));
            }

            // flip the color bits
            l = getRbLeft();
            if (l != null) {
                ll = l.getRbLeft();
                if (ll != null) {
                    if ((l.getColor() == red)&&(ll.getColor() == red)) {
                        x = (RedBlackTree)rotRight();
                        if (x != null) {
                            // copy returned node to 'this'
                            copy(x);
                            setModified();
                        }
                        setColor(black);
                        r = getRbRight();
                        if (r != null) {
                            r.setColor(red);
                        }
                        root.setChanged();
                        root.notifyObservers(s + " : Rotated Right : "+ Integer.toString(getKey()));
                    }
                }
            }
        }
        else {
            b = RBinsertRight(k,root,1);

            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            r = getRbRight();
            if ((getColor() == red)&&(r != null)&&(r.getColor() == red)&&(sw == 0)) {
                x = (RedBlackTree)rotLeft();
                if (x != null) {
                    // copy returned node to 'this'
                    copy(x);
                    setModified();
                }
                root.setChanged();
                root.notifyObservers(s + " : Rotated Left : "+ Integer.toString(getKey()));
            }

            // flip the color bits
            r = getRbRight();
            if (r != null) {
                rr = r.getRbRight();
                if (rr != null) {
                    if ((r.getColor() == red)&&(rr.getColor() == red)) {
                        x = (RedBlackTree)rotLeft();
                        if (x != null) {
                            // copy returned node to 'this'
                            copy(x);
                            setModified();
                        }
                        setColor(black);
                        l = getRbLeft();
                        if (l != null) {
                            l.setColor(red);
                        }
                        root.setChanged();
                        root.notifyObservers(s + " : Rotated Left : "+ Integer.toString(getKey()));
                    }
                }
            }
        }


        // allow observers to update
        if (isModifiedR() == true) {
            root.setChanged();
            root.notifyObservers("RBInserted");
        }

        return b;
    }

    public void balance(RedBlackTree root) {
        // no balancing in Redblack tree but use this to signal done
        root.setChanged();
        root.notifyObservers(null);
    }

}
