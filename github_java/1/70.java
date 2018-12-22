package trees;

public class BreadthFirstSearch {
    static class Node {
        int key;
        Node left,right;
        public Node (int key) {
            this.key = key;
            left = right = null;
        }
    }

    Node root;


    void getBFS(Node node, int height) {
        if (node==null)
            return;
        for (int i=1;i<=height;i++)
            getBFSLevel(node, i);
    }

    void getBFSLevel(Node node, int height) {
        if (node==null || height<1)
            return;
        if (height==1)
            System.out.print(node.key + " ");
        getBFSLevel(node.left, height-1);
        getBFSLevel(node.right, height-1);
    }

    int getHeight(Node node) {
        if (node == null)
            return 0;
        int height =1;
        int treeheight = height + Math.max(getHeight(node.left), getHeight(node.right));
        return treeheight;
    }

    public static void main(String[] args) {
        BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch();
        breadthFirstSearch.root = new Node(1);
        breadthFirstSearch.root.left = new Node(2);
        breadthFirstSearch.root.left.left = new Node(4);
        breadthFirstSearch.root.left.left.left = new Node(8);
        breadthFirstSearch.root.left.right = new Node(5);
        breadthFirstSearch.root.right = new Node(3);
        breadthFirstSearch.root.right.left = new Node(6);
        breadthFirstSearch.root.right.left.left = new Node(9);
        breadthFirstSearch.root.right.right = new Node(7);
        breadthFirstSearch.root.right.right.right = new Node(10);

        int height = breadthFirstSearch.getHeight(breadthFirstSearch.root);
        breadthFirstSearch.getBFS(breadthFirstSearch.root, height);


    }
}
