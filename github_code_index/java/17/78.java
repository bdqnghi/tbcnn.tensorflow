// An implementation of red-black trees.
// (c) 2000, 2001 duane a. bailey

// The nodes of a red-black tree are colored red or black.
// The following properties are true of every red-black tree:
//  1. Every child of every leaf is considered black.
//  2. Every red node has two black children.
//  3. Every path from a node to a descendant leaf contains the same
//     number of black nodes.

package structure;

public class RedBlackTree
{
    // the nodes directly associated with this node
    protected RedBlackTree left, right, parent;
    // the value stored in this node - tree will be ordered by this value
    protected Comparable value;
    // the color of this node - red or black (not red)
    protected boolean isRed;
    // the unique empty node; used as children on leaf trees and
    // as empty search trees.
    public static final RedBlackTree EMPTY = new RedBlackTree();

    /**
     * @post construct the EMPTY tree; leaves have EMPTY as children
    */
    protected RedBlackTree()
    {
        value = null;
        parent = null;
        left = right = this;
        isRed = false;  // empty trees below the leaves should be black
    }

    /**
     * @pre v is a non-null Comparable
     * @post constructs a single node red-black tree
     */
    public RedBlackTree(Comparable v)
    {
        value = v;
        parent = null;
        left = right = EMPTY;
        isRed = false;  // roots of tree should be colored black
    }

    /**
     * @post returns whether or not this node is red
    */
    protected boolean isRed()
    {
        return isRed;
    }

    /**
     * @post returns whether or not this node is red
    */
    protected boolean isBlack()
    {
        return !isRed;
    }

    /**
     * @post sets this node red 
    */
    protected void setRed()
    {
        isRed = true;
    }

    /**
     * @post sets this node red or black, depending on boolean isRed
    */
    protected void setRed(boolean isRed)
    {
        this.isRed = isRed;
    }

    /**
     * @post sets this node black
    */
    protected void setBlack()
    {
        isRed = false;
    }

    /**
     * @post return the value associated with this node
    */
    protected Object value()
    {
        return value;
    }

    /**
     * @post returns the tree rooted at left; may not be valid red-black
    */
    protected RedBlackTree left()
    {
        return left;
    }

    /**
     * @post returns the tree rooted a right; may not be valid red-black
    */
    protected RedBlackTree right()
    {
        return right;
    }

    /**
     * @post returns the parent of this tree
    */
    protected RedBlackTree parent()
    {
        return parent;
    }

    /**
     * @post sets parent of this node - even if EMPTY
    */
    protected void setParent(RedBlackTree newParent)
    {
        parent = newParent;
    }

    /**
     * @pre newLeft is a non-null RedBlackTree node, possibly EMPTY
     * @post does nothing to the EMPTY node;
     *       else makes newLeft a left child of this, 
     *       and this newLeft's parent
    */
    protected void setLeft(RedBlackTree newLeft)
    {
        if (isEmpty()) return;
        if (left.parent() == this) left.setParent(null);
        left = newLeft;
        left.setParent(this);
    }

    /**
     * @pre newRight is a non-null RedBlackTree node, possibly EMPTY
     * @post does nothing to the EMPTY node;
     *       else makes newRight a right child of this, 
     *       and this newRight's parent
    */
    protected void setRight(RedBlackTree newRight)
    {
        if (isEmpty()) return;
        if (right.parent() == this) right.setParent(null);
        right = newRight;
        right.setParent(this);
    }

    /**
     * @pre this node not EMPTY or root
     * @post returns true iff this child is a left child
    */
    protected boolean isLeftChild()
    {
        return !isRoot() && parent().left() == this;
    }

    /**
     * @pre this node not EMPTY or root
     * @post returns true iff this child is a left child
    */
    protected boolean isRightChild()
    {
        return !isRoot() && parent().right() == this;
    }

    /**
     * @post returns whether or not this child contains data
    */
    public boolean isEmpty()
    {
        return this == EMPTY;
    }

    /**
     * @post returns whether or not this node has a parent
    */
    protected boolean isRoot()
    {
        return parent == null;
    }

    /**
     * @pre this node not EMPTY
     * @post returns the root of the tree holding this node
    */
    protected RedBlackTree root()
    {
        RedBlackTree result = this;
        while (!result.isRoot()) {
            result = result.parent();
        }
        return result;
    }

    /**
     * @pre this node has a left subtree
     * @post rotates local portion of tree so left child is root
    */
    protected void rotateRight()
    {
        // all of this information must be grabbed before
        // any of the references are set.  Draw a diagram for help
        RedBlackTree parent = parent();
        RedBlackTree newRoot = left();
        // is the this node a child; if so, a right child?
        boolean wasChild = !isRoot();
        boolean wasLeftChild = isLeftChild();

        // hook in new root (sets newRoot's parent, as well)
        setLeft(newRoot.right());

        // puts pivot below it (sets this's parent, as well)
        newRoot.setRight(this);
        /**
         */

        if (wasChild) {
            if (wasLeftChild) parent.setLeft(newRoot);
            else              parent.setRight(newRoot);
        } else Assert.post(newRoot.isRoot(),"Rotate at root preserves root.");
    }

    /**
     * @pre this node has a right subtree
     * @post rotates local portion of tree so right child is root
    */
    protected void rotateLeft()
    {
        // all of this information must be grabbed before
        // any of the references are set.  Draw a diagram for help
        RedBlackTree parent = parent();  // could be null
        RedBlackTree newRoot = right();
        // is the this node a child; if so, a left child?
        boolean wasChild = !isRoot();
        boolean wasRightChild = isRightChild();

        // hook in new root (sets newRoot's parent, as well)
        setRight(newRoot.left());

        // put pivot below it (sets this's parent, as well)
        newRoot.setLeft(this);

        if (wasChild) {
            if (wasRightChild) parent.setRight(newRoot);
            else               parent.setLeft(newRoot);
        } else Assert.post(newRoot.isRoot(),"Left rotate at root preserves root.");
    }

    /**
     * @pre c is a non-null Comparable value
     * @post adds a comparable value to the red-black tree;
     *       returns the modified tree
    */
    public RedBlackTree add(Comparable c)
    {
        RedBlackTree tree = insert(c);  // first, do a plain insert
        tree.setRed();  // we insert nodes as red nodes - a first guess
        tree.redFixup();  // now, rebalance the tree
        return tree.root();  // return new root
    }

    /**
     * @pre c is a non-null Comparable value
     * @post c is inserted into search tree rooted at this
    */
    protected RedBlackTree insert(Comparable c)
    {
        // trivial case - tree was empty:
        if (isEmpty()) return new RedBlackTree(c);

        // decide to insert value to left or right of root:
        if (c.compareTo(value()) < 0) {

            // if to left and no left child, we insert value as leaf 
            if (left().isEmpty()) {
                RedBlackTree result = new RedBlackTree(c);
                setLeft(result);
                return result;
            } else {
                // recursively insert to left
                return left().insert(c);
            }
        } else {

            // if to right and no left child, we insert value as leaf
            if (right().isEmpty()) {
                RedBlackTree result = new RedBlackTree(c);
                setRight(result);
                return result;
            } else {
                // recursively insert to right
                return right().insert(c);
            }
        }
    }

    /**
     * @pre this node is a red node; if parent is red, violates property
     * @post red nodes of the tree are adjusted to maintain properties
    */
    public void redFixup()
    {
        if (isRoot() || !parent().isRed()) {
            // ensure that root is black (might have been insertion pt)
            root().setBlack();
        } else {
            RedBlackTree parent = parent();  // we know parent exists
            // since parent is red, it is not root; grandParent exists & black
            RedBlackTree grandParent = parent.parent();
            RedBlackTree aunt;  // sibling of parent (may exist)

            if (parent.isLeftChild())
            {
                aunt = grandParent.right();
                if (aunt.isRed()) {
                    // this:red, parent:red, grand:black, aunt:red
                    // push black down from gp to parent-aunt, but
                    // coloring gp red may introduce problems higher up
                    grandParent.setRed();
                    aunt.setBlack();
                    parent.setBlack();
                    grandParent.redFixup();
                } else {
                    if (isRightChild()) {
                        // this:red, parent:red, grand:black, aunt:black
                        // ensure that this is on outside for later rotate
                        parent.rotateLeft();
                        parent.redFixup(); // parent is now child of this
                    } else {
                        // assertion: this is on outside
                        // this:red, parent:red, gp: black, aunt:black
                        // rotate right @ gp, and make this & gp red sibs
                        // under black parent
                        grandParent.rotateRight();
                        grandParent.setRed();
                        parent.setBlack();
                    }
                }
            } else // parent.isRightChild()
            {
                aunt = grandParent.left();
                if (aunt.isRed()) {
                    // this:red, parent:red, grand:black, aunt:red
                    // push black down from gp to parent-aunt, but
                    // coloring gp red may introduce problems higher up
                    grandParent.setRed();
                    aunt.setBlack();
                    parent.setBlack();
                    grandParent.redFixup();
                } else {
                    if (isLeftChild()) {
                        // this:red, parent:red, grand:black, aunt:black
                        // ensure that this is on outside for later rotate
                        parent.rotateRight();
                        parent.redFixup(); // parent is now child of this
                    } else {
                        // assertion: this is on outside
                        // this:red, parent:red, gp: black, aunt:black
                        // rotate right @ gp, and make this & gp red sibs
                        // under black parent
                        grandParent.rotateLeft();
                        grandParent.setRed();
                        parent.setBlack();
                    }
                }
            }
        }
    }

    /**
     * @pre c is non-null
     * @post the value is removed; resulting tree is returned
    */
    public RedBlackTree remove(Comparable c)
    {
        // find the target node - the node whose value is removed
        RedBlackTree target = locate(c);
        if (target.isEmpty()) return root();

        // determine the node to be disconnected:
        // two cases: if degree < 2 we remove target node;
        //            otherwise, remove predecessor
        RedBlackTree freeNode;
        if (target.left().isEmpty() ||
            target.right().isEmpty()) // simply re-root tree at right
        {
            // < two children: target node is easily freed
            freeNode = target;
        } else {
            // two children: find predecessor
            freeNode = target.left();
            while (!freeNode.right().isEmpty())
            {
                freeNode = freeNode.right();
            }
            // freeNode is predecessor
        }

        target.value = freeNode.value; // move value reference

        // child will be orphaned by the freeing of freeNode;
        // reparent this child carefully (it may be EMPTY)
        RedBlackTree child;
        if (freeNode.left().isEmpty())
        {
            child = freeNode.right();
        } else {
            child = freeNode.left();
        }

        // if child is empty, we need to set its parent, temporarily
        child.setParent(freeNode.parent());
        if (!freeNode.isRoot())
        {
            if (freeNode.isLeftChild())
            {
                freeNode.parent().setLeft(child);
            } else {
                freeNode.parent().setRight(child);
            }
        }

        // Assertion: child has been reparented
        RedBlackTree result = child.root();     
        if (freeNode.isBlack()) child.blackFixup();
        return result.root();
    }

    /**
     * @pre a black node has just been removed above this;
     *      this node is the root of a black-height balanced tree, but
     *      the ancestors of this node are shy one black node on this branch
     * @post the tree is black-height balanced
    */
    protected void blackFixup()
    {
        // if root - we're actually balanced; if red, set to black
        if (isRoot() || isRed())
        {
            setBlack();
        } else {
            RedBlackTree sibling, parent; // temporary refs to relates
            // we hold onto our parent because the nodes shift about
            parent = parent();

            if (isLeftChild())
            {
                // our sibling: can't be a leaf (see text)
                sibling = parent.right();

                if (sibling.isRed()) // and, thus, parent is black
                {
                    // lower this, but leave black heights the same
                    // then reconsider node with a red parent
                    sibling.setBlack();
                    parent.setRed();
                    parent.rotateLeft();
                    blackFixup(); // this node might have adopted 
                } else
                if (sibling.left().isBlack() && sibling.right().isBlack())
                {
                    // sibling black with black children: sib can be red
                    // remove sib as one black node in sibling paths, and
                    // push missing black problem up to parent
                    sibling.setRed();
                    parent.blackFixup();
                } else {
                    if (sibling.right().isBlack())
                    {
                        // this:black, sib:black, sib.l:red, sib.r:black
                        // heighten sibling tree, making sib:r red and
                        // sib.l black (both sib.l's children were black)
                        sibling.left().setBlack();
                        sibling.setRed();
                        sibling.rotateRight();
                        sibling = parent.right();
                    }
                    // this: black, sib:black, sib:l black, sib.r:red 
                    // this tree deepens with parent as new black node
                    // sibling holds the previous parent color and
                    // sibling color (black) moves down to right;
                    // this adds a black node to all paths in this tree
                    // so we're done; finish by checking color of root
                    sibling.setRed(parent.isRed()); // copy color
                    parent.setBlack();
                    sibling.right().setBlack();
                    parent.rotateLeft();
                    root().blackFixup(); // finish by coloring root
                }
            } else { // isRightChild
                // our sibling: can't be a leaf (see text)
                sibling = parent.left();

                if (sibling.isRed()) // and, thus, parent is black
                {
                    // lower this, but leave black heights the same
                    // then reconsider node with a red parent
                    sibling.setBlack();
                    parent.setRed();
                    parent.rotateRight();
                    blackFixup(); // this node might have adopted 
                } else
                if (sibling.left().isBlack() && sibling.right().isBlack())
                {
                    // sibling black with black children: sib can be red
                    // remove sib as one black node in sibling paths, and
                    // push missing black problem up to parent
                    sibling.setRed();
                    parent.blackFixup();
                } else {
                    if (sibling.left().isBlack())
                    {
                        // this:black, sib:black, sib.r:red, sib.l:black
                        // heighten sibling tree, making sib:l red and
                        // sib.r black (both sib.r's children were black)
                        sibling.right().setBlack();
                        sibling.setRed();
                        sibling.rotateLeft();
                        sibling = parent.left();
                    }
                    // this: black, sib:black, sib:r black, sib.l:red 
                    // this tree deepens with parent as new black node
                    // sibling holds the previous parent color and
                    // sibling color (black) moves down to left;
                    // this adds a black node to all paths in this tree
                    // so we're done; finish by checking color of root
                    sibling.setRed(parent.isRed()); // copy color
                    parent.setBlack();
                    sibling.left().setBlack();
                    parent.rotateRight();
                    root().blackFixup(); // finish by coloring root
                }
            } 
        }
    }

    /**
     * @pre c is non-null
     * @post returns true iff c is contained within the tree
    */
    public boolean contains(Comparable c)
    {
        return locate(c) != null;
    }

    /**
     * @pre c is non-null
     * @post returns a node of this tree that contains c, or null
    */
    protected RedBlackTree locate(Comparable c)
    {
        if (isEmpty()) return null;
        int relation = c.compareTo(value());
        if (relation == 0) return this;
        if (relation < 0) return left().locate(c);
        else return right().locate(c);
    }

    /**
     * @pre c is non-null
     * @post returns a c-equivalent value from tree, or null
     */
    public Comparable get(Comparable c)
    {
        RedBlackTree n = locate(c);
        if (n == null) return null;
        else return (Comparable)n.value();
    }

    /**
     * @post returns true if this node is consistently structured
    */
    public boolean consistency()
    {
        return wellConnected(null) && redConsistency() && blackConsistency();
    }

    /**
     * @pre tree is black-height balanced
     * @post returns the black height of this subtree
    */
    protected int blackHeight()
    {
        if (isEmpty()) return 0;
        if (isBlack()) return 1 + left().blackHeight();
        else return  left().blackHeight();
    }

    /**
     * @post returns true if no red node in subtree has red children
    */
    protected boolean redConsistency()
    {
        if (isEmpty()) return true;
        if (isRed() && (left().isRed() || right().isRed())) return false;
        return left().redConsistency() && right().redConsistency();
    }

    /**
     * @post returns true if black properties of tree are correct
    */
    protected boolean blackConsistency()
    {
        if (!isRoot()) // must be called on root
        {
            Assert.debug("Tree consistency not tested at root.");
            return false;
        }
        if (!isBlack()) // root must be black
        {
            Assert.debug("Root is not black.");
            return false;
        }
        // the number of black nodes on way to any leaf must be same
        if (!consistentlyBlackHeight(blackHeight()))
        {
            Assert.debug("Black height inconsistent.");
            return false;
        }
        return true;
    }

    /**
     * @post checks to make sure that the black height of tree is height
     */
    protected boolean consistentlyBlackHeight(int height)
    {
        if (isEmpty()) return height == 0;
        if (isBlack()) height--;
        return left().consistentlyBlackHeight(height) &&
            right().consistentlyBlackHeight(height);
    }

    /**
     */
    public boolean wellConnected(RedBlackTree expectedParent)
    {
        boolean ok = true;
        if (isEmpty())
        {
            /*if (parent != null) {
                ok = false;
                Assert.debug("EMPTY parent not null.");
                }*/
            if (left != this) {
                ok = false;
                Assert.debug("EMPTY left not self.");
            }
            if (right != this) {
                ok = false;
                Assert.debug("EMPTY right not self.");
            }
        } else {
            if (expectedParent != parent()) 
            {   
                Object expectedParentValue;
                ok = false;
                if (expectedParent == null) expectedParentValue = "null";
                else expectedParentValue = expectedParent.value();
                Object parentValue;
                if (parent == null) parentValue = "null";
                else parentValue = parent.value();
                Assert.debug("Parent of "+value()+" was not "+expectedParentValue+", but "+parentValue);
            }
            if (value == null) {
                ok = false;
                Assert.debug("null value found in tree");
            }
            ok = ok & left().wellConnected(this) &
                right().wellConnected(this);
        }
        return ok;
    }

    /**
     */
    public void print()
    {
        if (isEmpty()) return;
        left().print();
        System.out.println(value());
        right().print();
    }

    /**
     * @post computes hash code associated with values of tree
     */
    public int hashCode()
    {
        if (isEmpty()) return 0;
        int result = left().hashCode() + right().hashCode();
        if (value() != null) result += value().hashCode();
        return result;
    }


    /**
     * @pre returns string representation of red-black tree
     */
    public String toString()
    {
        if (isEmpty()) return "";
        if (isRed()) return "(" + left() + value() + right() +")";
        else         return "[" + left() + value() + right() +"]";
    }
}
