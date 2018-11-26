package RedBlackTree;

public class RBTDemo {
    public static void main(String [] args) {
        //red black tree with Integer 
        rbtInt();
        //red black tree with Characters
        rbtChar();
        //red black tree with Strings
        rbtString();
        //red black tree with Floats
        rbtFloat();
    }

    public static void rbtInt() {
        RedBlackTree<Integer> rbt = new RedBlackTree<Integer>();
        for(int i=0; i<10; i++) {
            rbt.insert(i);
        }
        System.out.println("in order traversal from low to high:");
        rbt.inOrderAZ();
        System.out.println("in order traversal from high to low:");
        rbt.inOrderZA();

        System.out.println("tree after deleting numbers 8 & 2"); 
        rbt.delete(8);
        rbt.delete(2);
        rbt.inOrderAZ();

        System.out.println("level order traversal of tree");
        rbt.levelOrder();
    }

    public static void rbtChar() {
        RedBlackTree<Character> rbt = new RedBlackTree<Character>();
        for(int i=0; i<10; i++) {
            int num = 97 + i;
            char input = (char) num;
            rbt.insert(input);
        }
        System.out.println("in order traversal from low to high:");
        rbt.inOrderAZ();
        System.out.println("in order traversal from high to low:");
        rbt.inOrderZA();

        System.out.println("tree after deleting characters e & h"); 
        rbt.delete('e');
        rbt.delete('h');
        rbt.inOrderAZ();

        System.out.println("level order traversal of tree");
        rbt.levelOrder();
    }

    public static void rbtString() {
        RedBlackTree<String> rbt = new RedBlackTree<String>();
        for(int i=0; i<10; i++) {
            String input = "red-black-tree" + i;
            rbt.insert(input);
        }
        System.out.println("in order traversal from low to high:");
        rbt.inOrderAZ();
        System.out.println("in order traversal from high to low:");
        rbt.inOrderZA();

        System.out.println("tree after deleting strings red-black-tree2 & red-black-tree5"); 
        rbt.delete("red-black-tree2");
        rbt.delete("red-black-tree5");
        rbt.inOrderAZ();

        System.out.println("level order traversal of tree");
        rbt.levelOrder();
    }

    public static void rbtFloat() {
        RedBlackTree<Float> rbt = new RedBlackTree<Float>();
        for(int i=0; i<10; i++) {
            rbt.insert((float)i);
        }
        final float PI = (float)3.14;
        final float EULER = (float)2.718;
        rbt.insert(PI);
        rbt.insert(EULER);
        System.out.println("in order traversal from low to high:");
        rbt.inOrderAZ();
        System.out.println("in order traversal from high to low:");
        rbt.inOrderZA();

        System.out.println("tree after deleting numbers 2.0 & PI"); 
        rbt.delete((float)2.0);
        rbt.delete((float)PI);
        rbt.inOrderAZ();

        System.out.println("level order traversal of tree");
        rbt.levelOrder();
    }
}