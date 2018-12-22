public class Redblacktree{
    
    private Node NIL = new Node(Color.BLACK);
    private Node root = NIL; //root node pointer will be null for an empty tree
    
    public enum Color { RED, BLACK }
    
    /*Node
     * binary tree is built using this nested node class
     * each node stores one data elem, left,right,parent pointer, color
     */
    
    public static class Node{
        Node left;
        Node right;
        Node parent;
        int data;
        Color color;
        
        Node(int data){
            this.data = data;
        }
        
        Node(Color color){
            this.color = color;
            this.data = -1;
        }    
    }
    
    public void Insert(int data){
        Node node = new Node(data);
        node.color = Color.RED;
        Node parent = NIL;
        Node current = root;
        while(current != NIL){
            parent = current;
            if(data < current.data){
                current = current.left;
            }
            else{
                current = current.right;
            }
        }

        node.parent = parent;
        
        if(parent == NIL){
            root = node;
            root.parent = NIL;
        }
        else if(data <= parent.data){
            parent.left = node;
        }
        else{
            parent.right = node;
        }
        
        node.left = NIL;
        node.right = NIL;
        InsertFixUp(node);
    }
    
    public void InsertFixUp(Node z){
        while(z.parent.color == Color.RED){
            if(z.parent == z.parent.parent.left){
                Node y = z.parent.parent.right;
                //case 1
                if(y.color == Color.RED){
                    z.parent.color = Color.BLACK;
                    y.parent.color = Color.RED;
                    y.color = Color.BLACK;
                    z = z.parent.parent;
                }else{
                    //case 2
                    if(z == z.parent.right){
                        z = z.parent;
                        LeftRotate(z);
                    }
                    //case 3
                    z.parent.color = Color.BLACK;
                    z.parent.parent.color = Color.RED;
                    RightRotate(z.parent.parent);
                }
            }
            else{ //change right to left
                Node y = z.parent.parent.left;
                //case 4
                if(y.color == Color.RED){
                    z.parent.color = Color.BLACK;
                    y.parent.color = Color.RED;
                    y.color = Color.BLACK;
                    z = z.parent.parent;
                }else{
                    //case 5
                    if(z == z.parent.left){
                        z = z.parent;
                        RightRotate(z);
                    }
                    //case 6
                    z.parent.color = Color.BLACK;
                    z.parent.parent.color = Color.RED;
                    LeftRotate(z.parent.parent);
                }
            }
        }
        root.color = Color.BLACK;
    }
    
    public void LeftRotate(Node x){
        Node y = x.right;
        x.right = y.left;
        if(y.left != NIL)
            y.left.parent = x;
        y.parent = x.parent;
        if(x.parent == NIL)
            root = y;
        else if(x == x.parent.left)
            x.parent.left = y;
        else x.parent.right =y;
        y.left = x;
        x.parent = y;
    }
    
    public void RightRotate(Node x){
        Node y = x.left;
        x.left = y.right;
        if(y.right != NIL)
            y.right.parent = x;
        y.parent = x.parent;
        if(x.parent == NIL)
            root = y;
        else if(x == x.parent.right)
            x.parent.right = y;
        else x.parent.left =y;
        y.right = x;
        x.parent = y;
    }
    
    public void Delete(int data){
        Node deleteNode = search(data,root);
        Node temp;
        Node child;
        if(deleteNode.left == NIL || deleteNode.right == NIL)
            temp = deleteNode;
        else
            temp = successor(deleteNode);
        if(temp.left != NIL)
           child = temp.left;
           else
               child = temp.right;
           child.parent = temp.parent;
           if(temp.parent == NIL){
               root = child;
           }else{
               if(temp == temp.parent.left){
                   temp.parent.left = child;
               }else{
                   temp.parent.right = child;
               }
           }
           if(temp != deleteNode){
               deleteNode.data = temp.data;
           }
           if(temp.color == Color.BLACK){
               DeleteFixUp(child);
           }
    }
    
    public Node search(int data, Node node){
        if(data == node.data)
            return node;
        else{
            if(data > node.data){
                node = node.right;
            }
            else if(data < node.data)
                node = node.left;
            return search(data, node);
        }
    }
    
    public void DeleteFixUp(Node x){
        while(x!=root && x.color == Color.BLACK){
            if(x == x.parent.left){
                Node w = x.parent.right;
            if(w.color == Color.RED){
                w.color = Color.BLACK;
                x.parent.color = Color.RED;
                LeftRotate(x.parent);
                w = x.parent.right;
            }
            if(w.left.color == Color.BLACK && w.right.color == Color.BLACK){
                w.color = Color.RED;
                x = x.parent;
            }
            else if(w.right.color == Color.BLACK){
                w.left.color = Color.BLACK;
                w.color = Color.RED;
                RightRotate(w);
                w = x.parent.right;
            }
            w.color = x.parent.color;
            x.parent.color = Color.BLACK;
            w.right.color = Color.BLACK;
            LeftRotate(x.parent);
            x = root;
        }
        else{
            Node w = x.parent.left;
            if(w.color == Color.RED){
                w.color = Color.BLACK;
                x.parent.color = Color.RED;
                RightRotate(x.parent);
                w = x.parent.left;
            }
            if(w.right.color == Color.BLACK && w.left.color == Color.BLACK){
                w.color = Color.RED;
                x = x.parent;
            }
            else if(w.left.color == Color.BLACK){
                w.right.color = Color.BLACK;
                w.color = Color.RED;
                LeftRotate(w);
                w = x.parent.left;
            }
            w.color = x.parent.color;
            x.parent.color = Color.BLACK;
            w.left.color = Color.BLACK;
            RightRotate(x.parent);
            x = root;
        }
        }
        x.color = Color.BLACK;
        
    }
    
    public Node successor(Node node){
        if(node.right != NIL){
            return min(node.right);
        }
        else{
            Node parent = node.parent;
            while(parent != NIL && node == parent.right){
                node = parent;
                parent = node.parent;
            }
            return parent;
        }
    }
    
    public Node min(Node node){
        while(node.left != NIL){
            node = node.left;
        }
        return node;
    }
             
    public Node returnRoot()
    {
        return root;
    }
    
    public void preOrder(Node Root)
    {
        if(Root != NIL)
        {
            System.out.print(Root.data+":"+Root.color+" ");
            preOrder(Root.left);
            preOrder(Root.right);
         }
    }
  
    public void inOrder(Node Root)
    {
        if(Root != NIL)
        {
            inOrder(Root.left);
            System.out.print(Root.data+" ");
            inOrder(Root.right);
        }
    }
  
    public void postOrder(Node Root)
    {
        if(Root != NIL)
        {
            postOrder(Root.left);
            postOrder(Root.right);
            System.out.print(Root.data+" ");
        }
    }
    
    public static void main(String[] args) {
        Redblacktree rb = new Redblacktree();
        rb.Insert(34);
        rb.Insert(30);
        rb.Insert(38);
        rb.Insert(26);
        rb.Insert(32);
        rb.Insert(28);
        rb.Insert(59);
   
        
        System.out.println("Inorder traversal");
        rb.inOrder(rb.returnRoot());
        System.out.println(" ");
        System.out.println("Preorder traversal");
        rb.preOrder(rb.returnRoot());
        System.out.println(" ");
        System.out.println("Postorder traversal");
        rb.postOrder(rb.returnRoot());
        System.out.println("\n");
        
        System.out.println("Key 24 Inserted ->new Red Node");
        rb.Insert(24);
        System.out.println("Preorder traversal after insertion");
        rb.preOrder(rb.returnRoot());
        System.out.println("\n");
        
        System.out.println("Key 12 Inserted ->InsertFixUp");
        rb.Insert(12);
        System.out.println("Preorder traversal after insertion");
        rb.preOrder(rb.returnRoot());
        System.out.println("\n");
        
        System.out.println("Key 30 Deleted ->key has both child and DeleteFixUp");
        rb.Delete(30);
        System.out.println("Preorder traversal after deletion");
        rb.preOrder(rb.returnRoot());
        System.out.println(" ");
        
    }
}
    
        
        
       