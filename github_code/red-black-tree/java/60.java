package com.alg.graph.bst;

import java.util.ArrayList;

public class RedBlackTree<T extends Comparable<? super T>>
{
    T root;
    RedBlackTree<T> left;
    RedBlackTree<T> right;
    RedBlackTree<T> parent;
    int size;
    int color = 1; // 1 for Black, 0 for Red
    boolean DEBUG = false;
    int occurences = 1;
    boolean colorAdjust = true;
    
    public RedBlackTree(T root)
    {
        super();
        this.root = root;
        if (root != null)
        {
            this.size = 1;
        }
    }
    
    public boolean isDEBUG()
    {
        return DEBUG;
    }

    public void setDEBUG(boolean dEBUG)
    {
        DEBUG = dEBUG;
    }
    
    public int getOccurences()
    {
        return occurences;
    }

    public void setOccurences(int occurences)
    {
        this.occurences = occurences;
    }

    public void printDebug(String str)
    {
        if (DEBUG)
        {
            System.out.println(str);
        }
    }

    public boolean isRootTree()
    {
        return parent == null;
    }

    public T getRoot()
    {
        return root;
    }
    
    public void setRoot(T root)
    {
        this.root = root;
    }

    public RedBlackTree<T> getLeft()
    {
        return left;
    }

    private void setLeft(RedBlackTree<T> left)
    {
        this.left = left;
        if (left != null)
        {
            left.setParent(this);
        }
    }

    public RedBlackTree<T> getRight()
    {
        return right;
    }

    private void setRight(RedBlackTree<T> right)
    {
        this.right = right;
        if (right != null)
        {
            right.setParent(this);
        }
    }

    public RedBlackTree<T> getParent()
    {
        return parent;
    }

    private void setParent(RedBlackTree<T> parent)
    {
        this.parent = parent;
    }

    public int getSize()
    {
        return size;
    }

    private void setSize(int size)
    {
        this.size = size;
    }

    public int getColor()
    {
        return color;
    }

    private void setColor(int color)
    {
        this.color = color;
    }
    
    public int compareTo(T a, T b)
    {
        if (a == null)
        {
            if (b == null)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (b == null)
        {
            return -1;
        }
        else
        {
            return a.compareTo(b);
        }
    }
    
    public RedBlackTree<T> locate(T elem)
    {
        int cmp = compareTo(elem, root);
        if (cmp == 0)
        {
            return this;
        }
        else if (cmp < 0) // Value is less than root
        {
            if (left == null)
            {
                return null;
            }
            else
            {
                return left.locate(elem);
            }
        }
        else // value is higher than root
        {
            if (right == null)
            {
                return null;
            }
            else
            {
                return right.locate(elem);
            }
        }
    }
    public RedBlackTree<T> max()
    {
        RedBlackTree<T> bst = this;
        while (bst.right != null)
        {
            bst = bst.right;
        }
        return bst;
    }

    public RedBlackTree<T> min()
    {
        RedBlackTree<T> bst = this;
        while (bst.left != null)
        {
            bst = bst.left;
        }
        return bst;
    }
    
    public RedBlackTree<T> predecessor(T elem)
    {
        // Not Implemented
        RedBlackTree<T> bstElem = locate(elem);
        if (bstElem == null)
        {
            return null;
        }
        if (bstElem.left != null)
        {
            return bstElem.left.max();
        }
        else
        {
            RedBlackTree<T> bst = bstElem.parent;
            while (bst != null && compareTo(bst.root, bstElem.root) > 0)
            {
                bst = bst.parent;
            }
            if (bst == null)
            {
                return null;
            }
            else if (compareTo(bst.root, bstElem.root) > 0)
            {
                return null;
            }
            else
            {
                return bst;
            }
        }
    }
    
    public RedBlackTree<T> predecessor(RedBlackTree<T> reference)
    {
        if (reference == null)
        {
            return null;
        }
        if (reference.left != null)
        {
            return reference.left.max();
        }
        else
        {
            RedBlackTree<T> bst = reference.parent;
            while (bst != null && compareTo(bst.root, reference.root) > 0)
            {
                bst = bst.parent;
            }
            if (bst == null)
            {
                return null;
            }
            else if (compareTo(bst.root, reference.root) > 0)
            {
                return null;
            }
            else
            {
                return bst;
            }
        }
    }

    public RedBlackTree<T> successor(T elem)
    {
        // Not Implemented
        RedBlackTree<T> bstElem = locate(elem);
        if (bstElem == null)
        {
            return null;
        }
        if (bstElem.right != null)
        {
            return bstElem.right.min();
        }
        else
        {
            RedBlackTree<T> bst = bstElem.parent;
            while (bst != null && compareTo(bst.root, bstElem.root) < 0)
            {
                bst = bst.parent;
            }
            if (bst == null)
            {
                return null;
            }
            else if (compareTo(bst.root, bstElem.root) < 0)
            {
                return null;
            }
            else
            {
                return bst;
            }
        }
    }
    
    public RedBlackTree<T> select(int pos)
    {
        // Returns the element at indicated position. Position is zero based
        if (pos < 0 || pos > size - 1)
        {
            return null;
        }
        int currentPosition = 0;
        if (left != null)
        {
            currentPosition = left.size;
        }
        if (pos >= currentPosition && pos < currentPosition + occurences)
        {
            return this;
        }
        else if (pos < currentPosition)
        {
            return left.select(pos);
        }
        else
        {
            if (right == null)
            {
                return null;
            }
            else
            {
                return right.select(pos - currentPosition - occurences);
            }
        }
    }
    
    public RedBlackTree<T> medianTree()
    {
        if (size == 0)
        {
            return null;
        }
        int pos = size / 2;
        if (size % 2 == 0)
        {
            pos -= 1;
        }
        return select(pos);
    }
    
    public T median()
    {
        RedBlackTree<T> mTree = medianTree();
        if (mTree == null)
        {
            return null;
        }
        return mTree.root;
    }

    public int rank(T elem, int startRank)
    {
        // Returns the zero based rank of an element
        int currentPosition = startRank;
        if (left != null)
        {
            currentPosition += left.size;
        }
        int cmp = compareTo(elem, root);
        if (cmp == 0)
        {
            if (left != null)
            {
                int posInLeftTree = left.rank(elem, startRank);
                return posInLeftTree != -1 ? posInLeftTree : currentPosition;
            }
            else
            {
                return currentPosition;
            }
        }
        else if (cmp < 0)
        {
            if (left == null)
            {
                return -1;
            }
            else
            {
                return left.rank(elem, startRank);
            }
        }
        else
        {
            if (right == null)
            {
                return -1;
            }
            else
            {
                return right.rank(elem, currentPosition + 1);
            }
        }
    }
    
    public int rank(T elem)
    {
        return rank(elem, 0);
    }
    
    public ArrayList<T> orderedArray()
    {
        ArrayList<T> arr = new ArrayList<>();
        if (left != null)
        {
            arr.addAll(left.orderedArray());
        }
        if (root != null)
        {
            arr.add(root);
        }
        if (right != null)
        {
            arr.addAll(right.orderedArray());
        }
        return arr;
    }

    public RedBlackTree<T> otherChild(RedBlackTree<T> child)
    {
        if (left != null && left == child)
        {
            return right;
        }
        else if (right != null && right == child)
        {
            return left;
        }
        else
        {
            return null;
        }
    }

    public RedBlackTree<T> grandParent()
    {
        if (parent == null)
        {
            return null;
        }
        return parent.parent;
    }
    
    public RedBlackTree<T> uncle()
    {
        RedBlackTree<T> G = grandParent();
        if (G == null)
        {
            return null;
        }
        return G.otherChild(parent);
    }

    private RedBlackTree<T> insertBST(T elem)
    {
        // Regular BST Insert; no color adjustment
        if (root == null)
        {
            root = elem;
            size = 1;
            color = 1;
            occurences = 1;
            this.colorAdjust = true;
            return this;
        }
        int cmp = compareTo(elem, root);
        if (cmp == 0) // If equal, just increment occurences
        {
            occurences += 1;
            size += 1;
            this.colorAdjust = false;
            return this;
        }
        else if (cmp < 0) // If less choose the left subtree
        {
            if (left == null)
            {
                RedBlackTree<T> left = new RedBlackTree<T>(elem);
                this.setLeft(left);
                size += 1;
                left.colorAdjust = true;
                return left;
            }
            else
            {
                size += 1;
                return left.insertBST(elem);
            }
        }
        else // Choose the right subtree
        {
            if (right == null)
            {
                RedBlackTree<T> right = new RedBlackTree<T>(elem);
                this.setRight(right);
                size += 1;
                right.colorAdjust = true;
                return right;
            }
            else
            {
                size += 1;
                return right.insertBST(elem);
            }
        }
    }
    
    public RedBlackTree<T> insertCase1(RedBlackTree<T> N)
    {
        if (N.isRootTree())
        {
            /*
             * Case 1: N is root node
             */
            printDebug("Case 1");
            N.setColor(1);
            return N;
        }
        else
        {
            return insertCase2(N);
        }
    }
    
    public RedBlackTree<T> insertCase2(RedBlackTree<T> N)
    {
        /*
         * Case 2: N's parent P is black
         */
        RedBlackTree<T> P = N.parent;
        if (P.getColor() == 1)
        {
            printDebug("Case 2");
            return this;
        }
        else
        {
            return insertCase3(N);
        }
    }

    public RedBlackTree<T> insertCase3(RedBlackTree<T> N)
    {
        /*
         * Case 3: N's parent(P) and uncle(U) are red
         */
        RedBlackTree<T> P = N.parent;
        RedBlackTree<T> G = N.grandParent();
        RedBlackTree<T> U = N.uncle();
        printDebug("Case 3 Parent: " + P.getRoot() + "-" + P.getColor());
        if (U != null)
        {
            printDebug("Case 3 Uncle: " + U.getRoot() + "-" + U.getColor());
        }
        
        if (P.getColor() == 0 && (U != null && U.getColor() == 0))
        {
            printDebug("Case 3");
            P.setColor(1);
            U.setColor(1);
            G.setColor(0);
            return insertCase1(G);
        }
        else
        {
            return insertCase4(N);
        }
    }
    
    public RedBlackTree<T> insertCase4(RedBlackTree<T> N)
    {
        /*
         * Case 4: parent(P) is Red but uncle(U) is black.
         *   Also, N is the right child of P and P is the left child of its parent G 
         *   Or, N is the left child of P and P is the right child of its parent G
         */
        printDebug("Case 4");
        RedBlackTree<T> P = N.parent;
        RedBlackTree<T> G = N.grandParent();
        
        if ( N == P.right && P == G.left)
        {
            printDebug("Rotate Left in Case 4");
            rotateLeft(P);
            N = P;
        }
        else if ( N == P.left && P == G.right)
        {
            printDebug("Rotate Right in Case 4");
            rotateRight(P);
            N = P;
        }
        return insertCase5(N);
    }

    public RedBlackTree<T> insertCase5(RedBlackTree<T> N)
    {
        printDebug("Case 5");
        RedBlackTree<T> G = N.grandParent();
        N.parent.setColor(1);
        G.setColor(0);
        if (N == N.parent.left)
        {
            printDebug("Rotate right in Case 5");
            return rotateRight(G);
        }
        else
        {
            printDebug("Rotate left in Case 5");
            return rotateLeft(G);
        }
    }
    
    public RedBlackTree<T> rotateLeft(RedBlackTree<T> P)
    {
        RedBlackTree<T> N = P.right;
        if (N == null)
        {
            return this;
        }
        RedBlackTree<T> G = P.parent;
        RedBlackTree<T> POrig = P;
        RedBlackTree<T> NLeft = N.left;
        printDebug(String.format("N = %s, P = %s, G = %s", N.root, P.root, G == null ? null : G.root));
        if (G != null)
        {
            if (G.left == POrig)
            {
                G.setLeft(N);
            }
            else
            {
                G.setRight(N);
            }
        }
        else
        {
            N.setParent(null);
        }
        N.setLeft(POrig);
        POrig.setRight(NLeft);
        if (N.left != null)
        {
            N.left.computeSize();
        }
        if (N.right != null)
        {
            N.right.computeSize();
        }
        N.computeSizeAllUpwards();
        if (G == null)
        {
            return N;
        }
        else
        {
            return this;
        }
    }

    public RedBlackTree<T> rotateRight(RedBlackTree<T> P)
    {
        RedBlackTree<T> N = P.left;
        if (N == null)
        {
            return this;
        }
        RedBlackTree<T> G = P.parent;
        RedBlackTree<T> POrig = P;
        RedBlackTree<T> NRight = N.right;
        printDebug(String.format("N = %s, P = %s, G = %s", N.root, P.root, G == null ? null : G.root));
        if (G != null)
        {
            if (G.left == POrig)
            {
                G.setLeft(N);
            }
            else
            {
                G.setRight(N);
            }
        }
        else
        {
            N.setParent(null);
        }
        N.setRight(POrig);
        POrig.setLeft(NRight);
        if (N.left != null)
        {
            N.left.computeSize();
        }
        if (N.right != null)
        {
            N.right.computeSize();
        }
        N.computeSizeAllUpwards();
        if (G == null)
        {
            return N;
        }
        else
        {
            return this;
        }
    }
    
    public RedBlackTree<T> insert(T elem)
    {
        RedBlackTree<T> N = insertBST(elem);
        
        /* 
         * Set N's color to Red
         */
        if (N.colorAdjust)
        {
            N.setColor(0);
            if (DEBUG)
            {
                printDebug("*** " + this);
            }
            
            N = insertCase1(N);
            return N;
        }
        else
        {
            return this;
        }
    }
 
    private void computeSize()
    {
        this.size = occurences + (this.left == null ? 0 : this.left.size) + (this.right == null ? 0 : this.right.size);
    }

    private void computeSizeAllUpwards()
    {
        computeSize();
        RedBlackTree<T> p = this.parent;
        while (p != null)
        {
            p.computeSize();
            p = p.parent;
        }
    }

    public int computeHeight()
    {
        int leftHeight = 0;
        int rightHeight = 0;
        if (left != null)
        {
            leftHeight = left.computeHeight();
        }
        if (right != null)
        {
            rightHeight = right.computeHeight();
        }
        return Math.max(leftHeight, rightHeight) + 1;
    }
    
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        if (left != null)
        {
            sb.append(left.toString());
        }
        sb.append(":");
        sb.append((root == null ? "" : root.toString()) + "(" + size + ")" + "*" + color + "*");
        sb.append(":");
        if (right != null)
        {
            sb.append(right.toString());
        }
        sb.append("]");
        return sb.toString();
    }
    
    public int getLeftSize()
    {
        return left == null ? 0 : left.size;
    }
    
    public int getRightSize()
    {
        return right == null ? 0 : right.size;
    }

    public boolean checkTree()
    {
        if (root == null && size == 0 && getLeftSize() == 0 && getRightSize() == 0)
        {
            return true;
        }
        if (size != getLeftSize() + occurences + getRightSize())
        {
            // System.out.println("Failed Size check at " + root);
            // System.out.println(String.format("Size = %d, left = %d, right = %d", getLeftSize(), getRightSize()));
            return false;
        }
        if (left != null)
        {
            if (compareTo(left.root, root) > 0)
            {
                // System.out.println(String.format("Value = %s, left = %s", root, left.root));
                return false;
            }
            if (this != left.parent)
            {
                System.out.println(String.format("Left Child mismatch: Value = %s, left = %s", root, left.root));
                return false;
            }
            if (! left.checkTree())
            {
                return false;
            }
        }
        if (right != null)
        {
            if (compareTo(right.root, root) <= 0)
            {
                // System.out.println(String.format("Value = %s, right = %s", root, right.root));
                return false;
            }
            if (this != right.parent)
            {
                System.out.println(String.format("Right Child mismatch: Value = %s, left = %s", root, right.root));
                return false;
            }
            if (! right.checkTree())
            {
                return false;
            }
        }
        return true;
    }
    
    private boolean isBalanced(RedBlackTree<T> x, int black) 
    {
        if (x == null) return black == 0;
        if (x.color == 1) black--;
        return isBalanced(x.left, black) && isBalanced(x.right, black);
    }
    
    public boolean isBalanced() 
    { 
        int black = 0;     // number of black links on path from root to min
        RedBlackTree<T> x = this;
        while (x != null) 
        {
            if (x.color == 1) black++;
            x = x.left;
        }
        return isBalanced(this, black);
    }
    
    

}
