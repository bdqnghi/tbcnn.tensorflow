   /* Class node is defined as :
    class Node 
       int val;   //Value
       int ht;      //Height
       Node left;   //Left child
       Node right;   //Right child

   */

// https://www.hackerrank.com/challenges/self-balancing-tree

static int getHeight(Node root) {
    if (root == null)
        return -1;
    return root.ht;
}

static Node rightRotate(Node root) {
    Node temp = root.left;
    root.left = temp.right;
    temp.right = root;
    
    // adjust heights
    int l, r;
    l = getHeight(root.left);
    r = getHeight(root.right);
    root.ht = (l > r ? l : r) + 1;
    
    l = getHeight(temp.left);
    r = getHeight(temp.right);
    temp.ht = (l > r ? l : r) + 1;

    return temp;
}

static Node leftRotate(Node root) {
    Node temp = root.right;
    root.right = temp.left;
    temp.left = root;
    
    // adjust heights
    int l, r;
    l = getHeight(root.left);
    r = getHeight(root.right);
    root.ht = (l > r ? l : r) + 1;
    
    l = getHeight(temp.left);
    r = getHeight(temp.right);
    temp.ht = (l > r ? l : r) + 1;
    return temp;
}

static Node _insert(Node root, Node newNode) {
    // insert node
    if (root == null)
        return newNode;
    else if (newNode.val < root.val)
        root.left = _insert(root.left, newNode);
    else
        root.right = _insert(root.right, newNode);

    // subtree heights
    int l = getHeight(root.left);
    int r = getHeight(root.right);

    // balance factor
    int bf = l - r;
    
    // balance by rotation
    // right-*
    if (bf == -2) {
        int rl = getHeight(root.right.left);
        int rr = getHeight(root.right.right);
        int rbf = rl - rr;
        // right - left unbalance
        if (rbf == 1)
            root.right = rightRotate(root.right);
        return leftRotate(root);
    }
    // left - *
    else if (bf == 2) {
        int ll = getHeight(root.left.left);
        int lr = getHeight(root.left.right);
        int lbf = ll - lr;
        // left - right
        if (lbf == -1)
            root.left = leftRotate(root.left);
        return rightRotate(root);
    }
    // simply update root height
    else {
        root.ht = (l > r ? l : r) + 1;
        return root;
    }
}

static Node insert(Node root, int val)
{
    Node newNode = new Node();
    newNode.val = val;
    newNode.left = null;
    newNode.right = null;
    newNode.ht = 0;
    return _insert(root, newNode);
}
