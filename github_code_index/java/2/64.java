/*
* AVL-Tree implementation
* srv_twry
* */

class Node{
    public static int data,height;
    Node left,right;

    public Node(int data){
        this.data=data;
        height=1;
        left=null;
        right=null;
    }
}

class AVLTree{

    public static Node root;

    public AVLTree(){
        root=null;
    }

    // A utility function to get height of the tree
    int height(Node N) {
        if (N == null)
            return 0;

        return N.height;
    }

    // A utility function to get maximum of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }



}