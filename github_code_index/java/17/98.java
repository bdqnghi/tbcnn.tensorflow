package uk.ac.cam.josi2.DataStructures;

/**
 * Created by Joe on 07/04/2015.
 */
public class RedBlackTree<T extends Comparable<T>, U>  {

    private RedBlackTreeNode mRoot;

    public RedBlackTree(T key, U data){
        mRoot = new RedBlackTreeNode(key, data, RedBlackTreeNode.BLACK);
    }

    public void insert(T key, U data){
        RedBlackTreeNode x = mRoot;
        RedBlackTreeNode y = null;

        //This addition will be red.
        RedBlackTreeNode toInsert = new RedBlackTreeNode(key, data, RedBlackTreeNode.RED);


        while(x != null){
            y = x;
            if(x.mKey.compareTo(toInsert.mKey) >= 0)
                //mKey > key
                x = x.mLeft;
            else{
                x = x.mRight;
            }
        }

        if(y == null) {
            mRoot = toInsert;
            mRoot.mColour = RedBlackTreeNode.BLACK;
            toInsert.mParent = null;
            //don't need to correct the colour as the tree will have one
            //node and this node will be black.
            return;
        }
        else if(y.mKey.compareTo(toInsert.mKey) >= 0)
            y.mLeft = toInsert;
        else
            y.mRight = toInsert;


        toInsert.mParent = y;

        insertColourCorrect(toInsert);
    }

    public U search(T key){
        RedBlackTreeNode tmp = getNode(key);
        if (tmp == null)
            return null;
        return tmp.mData;
    }

    public void delete(T key){delete(getNode(key));}


    private void delete(RedBlackTreeNode node) {
        RedBlackTreeNode sec = node;
        boolean originalColour = node.mColour;
        if(node == null)
            return;

        RedBlackTreeNode replacment;
        if(node.mLeft == null){
            replacment = node.mRight;
            //swap with right, right may be null
            node.swap(node.mRight);
        }
        else if(node.mRight == null){
            replacment = node.mLeft;
            //swap with left
            node.swap(node.mLeft);
        }
        else{
            sec = node.mRight.treeMin();
            originalColour = sec.mColour;
            replacment = sec.mRight;
            if(sec.mParent != node){
                if(replacment != null)
                    replacment.mParent = sec;
            }
            else{
                sec.swap(sec.mRight);
                sec.mRight = node.mRight;
                sec.mRight.mParent = sec;
            }
            //Now the node can be swapped with it's successor.
            node.swap(sec);
            sec.mLeft = node.mLeft;
            sec.mLeft.mParent = sec;
            sec.mColour = node.mColour;
        }
        if(originalColour == RedBlackTreeNode.BLACK)
            deleteColourCorrect(replacment);
    }

    private void deleteColourCorrect(RedBlackTreeNode node) {
        if(node == null)
            return;
        while (node != mRoot && node.mColour == RedBlackTreeNode.BLACK){
            if(node.mParent.mLeft == node) {//left side.
                RedBlackTreeNode sibling = node.mParent.mRight;
                if(sibling.mColour == RedBlackTreeNode.RED){
                    sibling.mColour = RedBlackTreeNode.RED;
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.leftRotate();
                    sibling = node.mParent.mRight;
                }
                if(sibling.mLeft.mColour == RedBlackTreeNode.BLACK && sibling.mRight.mColour == RedBlackTreeNode.BLACK){
                    sibling.mColour = RedBlackTreeNode.RED;
                    node = node.mParent;
                }
                else if(sibling.mRight.mColour = RedBlackTreeNode.BLACK){
                    sibling.mColour = RedBlackTreeNode.RED;
                    sibling.mRight.mColour = RedBlackTreeNode.BLACK;
                    sibling.rightRotate();
                    sibling = node.mParent.mRight;
                }
                sibling.mRight.mColour = RedBlackTreeNode.BLACK;
                sibling.mColour = node.mParent.mColour;
                node.mParent.mColour = RedBlackTreeNode.BLACK;
                node.mParent.leftRotate();
                node = mRoot;
            }
            else{//right side.
                RedBlackTreeNode sibling = node.mParent.mLeft;
                if(sibling.mColour == RedBlackTreeNode.RED){
                    sibling.mColour = RedBlackTreeNode.RED;
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.rightRotate();
                    sibling = node.mParent.mLeft;
                }
                if(sibling.mLeft.mColour == RedBlackTreeNode.BLACK && sibling.mRight.mColour == RedBlackTreeNode.BLACK){
                    sibling.mColour = RedBlackTreeNode.RED;
                    node = node.mParent;
                }
                else if(sibling.mLeft.mColour = RedBlackTreeNode.BLACK){
                    sibling.mColour = RedBlackTreeNode.RED;
                    sibling.mLeft.mColour = RedBlackTreeNode.BLACK;
                    sibling.leftRotate();
                    sibling = node.mParent.mLeft;
                }
                sibling.mLeft.mColour = RedBlackTreeNode.BLACK;
                sibling.mColour = node.mParent.mColour;
                node.mParent.mColour = RedBlackTreeNode.BLACK;
                node.mParent.rightRotate();
                node = mRoot;
            }
        }
        node.mColour = RedBlackTreeNode.BLACK;
    }

    private void insertColourCorrect(RedBlackTreeNode node) {
        //the inserted nodes
        while(node.mParent != null && node.mParent.mColour == RedBlackTreeNode.RED) {
            if(node.mParent.mParent.mLeft == node.mParent) {
                RedBlackTreeNode uncle = node.mParent.mParent.mRight;
                if (uncle != null && uncle.mColour == RedBlackTreeNode.RED) {
                    uncle.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mParent.mColour = RedBlackTreeNode.RED;
                    node = node.mParent.mParent;
                } else {
                    if (node == node.mParent.mRight) {
                        node = node.mParent;
                        node.leftRotate();
                    }
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mParent.mColour = RedBlackTreeNode.RED;
                    node.mParent.mParent.rightRotate();
                }
            }
            else{
                RedBlackTreeNode uncle = node.mParent.mParent.mLeft;
                if(uncle != null && uncle.mColour == RedBlackTreeNode.RED) {
                    uncle.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mParent.mColour = RedBlackTreeNode.RED;
                    node = node.mParent.mParent;
                }
                else{
                    if(node.mParent.mLeft == node) {
                        node = node.mParent;
                        node.mParent.mParent.rightRotate();
                    }
                    node.mParent.mColour = RedBlackTreeNode.BLACK;
                    node.mParent.mParent.mColour = RedBlackTreeNode.RED;
                    node.mParent.mParent.leftRotate();

                }
            }
        }
        mRoot.mColour = RedBlackTreeNode.BLACK;
    }

    private RedBlackTreeNode getNode(T key){
        RedBlackTreeNode tail = mRoot;

        while(tail != null && tail.mKey.compareTo(key) != 0){
            //go on the left side.
            if (tail.mKey.compareTo(key) > 0) {
                tail = tail.mLeft;
            }
            //go on the right side
            else {
                tail = tail.mRight;
            }
        }
        if(tail != null)
            return tail;
        return null;
    }

    private class RedBlackTreeNode{
        private static final boolean BLACK = true;
        private static final boolean RED = false;

        private boolean mColour;
        private T mKey;
        private U mData;
        private RedBlackTreeNode mLeft, mRight, mParent;

        RedBlackTreeNode(T key, U data, boolean colour){
            mKey = key;
            mData = data;
            mColour = colour;
        }

        //
        //       x                   y
        //      / \    leftRotate   / \
        //     a   y    ----->     x   c
        //        / \             / \
        //       b   c           a   b

        private void leftRotate(){leftRotate(this);}

        private void leftRotate(RedBlackTreeNode x) {
            if(x == null || x.mRight == null)
                return;
            RedBlackTreeNode y = x.mRight;
            x.mRight = y.mLeft;
            if(y.mLeft != null)
                y.mLeft.mParent = x;

            y.mParent = x.mParent;
            //If x is the root
            if(x.mParent == null){
                mRoot = y;
            }
            else if(x.mParent.mLeft == x)
                x.mParent.mLeft = y;
            else
                x.mParent.mRight = y;
            y.mLeft = x;
            x.mParent = y;
        }

        //
        //       y                   x
        //      / \   rightRotate   / \
        //     a   x    <-----     y   c
        //        / \             / \
        //       b   c           a   b

        private void rightRotate(){rightRotate(this);}

        private void rightRotate(RedBlackTreeNode x) {
            if(x == null || x.mLeft == null)
                return;
            RedBlackTreeNode y = x.mLeft;
            x.mLeft = y.mRight;
            if(x.mLeft != null) {
                x.mLeft.mParent = x;
            }

            y.mParent = x.mParent;
            //If x is the root
            if(x.mParent == null){
                mRoot = y;
            }
            else if(x.mParent.mLeft == x)
                x.mParent.mLeft = y;
            else
                x.mParent.mRight = y;
            y.mRight = x;
            x.mParent = y;
        }

        private RedBlackTreeNode treeMax(RedBlackTreeNode t){

            while (t.mRight != null) {
                t = t.mRight;
            }
            return t;
        }

        private RedBlackTreeNode treeMax(){
            return treeMax(this);
        }

        private RedBlackTreeNode treeMin(){
            return treeMin(this);
        }

        private RedBlackTreeNode treeMin(RedBlackTreeNode t){
            while (t.mLeft != null) {
                t = t.mLeft;
            }
            return t;
        }

        private RedBlackTreeNode successor(){
            RedBlackTreeNode t = this;
            if(t == null)
                return null;
            if(t.mRight != null) {
                return treeMin(t.mRight);
            }
            else {
                RedBlackTreeNode parent = t.mParent;
                while (parent != null && t == parent.mRight){
                    t = parent;
                    parent = parent.mParent;
                }
                return parent;
            }
        }

        private void swap(RedBlackTreeNode with){
            RedBlackTreeNode node = this;
            if(node.mParent == null)
                mRoot = with;
            else if (node.mParent.mLeft == node)
                node.mParent.mLeft = with;
            else
                node.mParent.mRight = with;

            if (with != null)
                with.mParent = node.mParent;
        }
    }
}
