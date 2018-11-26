package p01_AVLTreeImplementation;

public class Startup {
    public static void main(String[] args) {
        AVLTree<Integer> avlTree = new AVLTree<>();
//        avlTree.add(20);
//
//        avlTree.add(25);
//        avlTree.add(12);
//
//        avlTree.add(26);
//        avlTree.add(17);
//        avlTree.add(8);
//
//        avlTree.add(4);
//        avlTree.add(10);
//        avlTree.add(15);
//        avlTree.add(19);
//
//        avlTree.add(16);
//
//        avlTree.add(3);
//        avlTree.add(5);
//
//        avlTree.add(6);
//-----------------------------------

//        avlTree.add(20);
//        avlTree.add(26);
//        avlTree.add(15);
//        avlTree.add(10);
//        avlTree.add(5);
//--------------------------------------

//        avlTree.add(20);
//        avlTree.add(10);
//        avlTree.add(25);
//
//        avlTree.add(5);
//        avlTree.add(22);
//        avlTree.add(30);
//
//        avlTree.add(21);
//        avlTree.add(24);
//        avlTree.add(27);
//        avlTree.add(33);
//
//        avlTree.add(28);

//        avlTree.add(4);
//        avlTree.add(3);
//
//        avlTree.add(28);
//        avlTree.add(29);
//
//        avlTree.add(34);
//        avlTree.add(35);

        //-----------------------------------------------------------

        avlTree.add(30);
        avlTree.add(20);
        avlTree.add(50);

        avlTree.add(10);
        avlTree.add(40);
        avlTree.add(55);

        avlTree.add(35);
        avlTree.add(48);
        avlTree.add(52);
        avlTree.add(65);

        avlTree.add(49);
        avlTree.add(41);
        avlTree.add(42);
        avlTree.add(44);


// -----------------------------------------------------------

//        avlTree.add(5);
//        avlTree.add(10);
//        avlTree.add(8);
        print(avlTree.getRoot(), 1);

        System.out.println(avlTree.contains(55));

    }

    private static void print(Node<Integer> node, int indent) {
        System.out.println(newString(" ", indent) + node.getValue());

        if (node.getLeftChild() != null) {
            print(node.getLeftChild(), indent + 1);
        }

        if (node.getRightChild() != null) {
            print(node.getRightChild(), indent + 1);
        }
    }

    private static String newString(String str, int count) {
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < count; i++) {
            builder.append(str);
        }

        return builder.toString();
    }
}
