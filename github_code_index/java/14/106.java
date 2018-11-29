package bst;

import Users.User;

/**
 *
 * @author Eduardo
 * 
 * Binary Search Tree
 */
public class Tree {
    private Node root;
    private Tree leftTree;
    private Tree rightTree;

    public Tree() {
      
    }

    public Tree getRightTree() {
        return rightTree;
    }

    public void setRightTree(Tree rightTree) {
        this.rightTree = rightTree;
    }

    public Tree getLeftTree() {
        return leftTree;
    }

    public void setLeftTree(Tree leftTree) {
        this.leftTree = leftTree;
    }

    public Node getRoot() {
        return root;
    }

    public void setRoot(Node root) {
        this.root = root;
    }
    
    public boolean insertUser(User user) {
        return insertNode(new Node(user));
    }

    public boolean insertNode(Node node) {
        if (this.root == null) {
            this.root = node;
            return true;
        } else {
            if (root.getUsuario().findSide(node.getUsuario()) == -1) {
                if (this.rightTree == null) {
                    this.rightTree = new Tree();
                }
                return this.rightTree.insertNode(node);
            } else if (root.getUsuario().findSide(node.getUsuario()) == 1) {
                if (this.leftTree == null) {
                    this.leftTree = new Tree();
                }
                return this.leftTree.insertNode(node);
            }
        }
        return false;
    }

    public boolean removeNode(int id) {
        if (this.root == null) {
            return false;
        }
        if (this.root.getUsuario().getId() == id) {
            if (this.leftTree == null && this.rightTree == null) {
                this.root = null;
            } else if (this.leftTree != null && this.rightTree == null) {
                this.root = this.leftTree.root;
                this.rightTree = this.leftTree.rightTree;
                this.leftTree = this.leftTree.leftTree;
            } else if (this.leftTree == null && this.rightTree != null) {
                this.root = this.rightTree.root;
                this.leftTree = this.rightTree.leftTree;
                this.rightTree = this.rightTree.rightTree;
            } else {
                Tree previous = this;
                Tree current = this.leftTree;
                while (current.rightTree != null) {
                    previous = current;
                    current = current.rightTree;
                }
                this.root = current.root;
                if (previous == this) {
                    this.leftTree = current.leftTree;
                } else {
                    previous.rightTree = current.leftTree;
                }
            }
            return true;
        }
        Tree previous = null;
        Tree current = this;
        while (current != null && current.root.getUsuario().getId() != id) {
            if (current.root.getUsuario().getId() > id) {
                previous = current;
                current = current.leftTree;
            } else {
                previous = current;
                current = current.rightTree;
            }
        }

        if (current == null) {
            return false;
        }

        if (current.leftTree == null && current.rightTree == null) {
            if (previous.leftTree == current) {
                previous.leftTree = null;
            } else {
                previous.rightTree = null;
            }
        } else if (current.leftTree != null && current.rightTree == null) {
            if (previous.leftTree == current) {
                previous.leftTree = current.leftTree;
            } else {
                previous.rightTree = current.leftTree;
            }
        } else if (current.leftTree == null && current.rightTree != null) {
            if (previous.leftTree == current) {
                previous.leftTree = current.rightTree;
            } else {
                previous.rightTree = current.rightTree;
            }
        } else {
            Tree previous2 = current;
            Tree current2 = current.leftTree;
            while (current2.rightTree != null) {
                previous2 = current2;
                current2 = current2.rightTree;
            }
            current.root = current2.root;
            if (previous2 == current) {
                current.leftTree = current2.leftTree;
            } else {
                previous2.rightTree = current2.leftTree;
            }
        }
        return true;
    }

    public User search(int id) {
        if (root == null) {
            return null;
        }

        if (root.getUsuario().getId() == id) {
            return root.getUsuario();
        }

        if (leftTree == null && rightTree == null) {
            return null;
        }

        if (root.getUsuario().getId() > id) {
            return leftTree.search(id);
        } else {
            return rightTree.search(id);
        }
    }

    public void scrollThroughInOrder() {
        if (root == null) {
            return;
        }

        if (leftTree != null) {
            leftTree.scrollThroughInOrder();
        }
        System.out.println(root.getUsuario().getId());
        if (rightTree != null) {
            rightTree.scrollThroughInOrder();
        }
    }
}