/*
   * ===========================================================================
   *  Coder Information
   *        Name: Michael Liut
   *        SID: 1132938
   *        MacID: liutm
   *  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   *  Submission:
   *        To: Dr. Antoine Deza
   *        Class: CAS 6O03
   *        Dept: Computing and Software,
   *              Faculty of Engineering,
   *              McMaster University
   *  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   *  Description: 
   *        Rod Cutting (Stick Cutting) problem. Solved with the use of the
   *        Huffman Tree in O(n^2) time.
   *  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   *  References:
   *        Introduction to Algorithms, 3rd Edition, Cormen et. al., MIT Press
   *        https://en.wikipedia.org/wiki/Huffman_coding
   * ===========================================================================
*/

/* Imports */
import java.util.*;
import java.lang.*;

/* Begin RodCutting Class */
public class RodCutting {

    /*
     * =========================================================================
     *  Begin Tree Structure aka Tree Node Class
     * =========================================================================
    */
    class Tree implements Comparable<Tree> {
        /* Attribute Declarations */
        private Tree right, left;
        private long weight;
        
        /* Default Constructor */
        public Tree() {
            this.weight = 0;
            this.right = null;
            this.left = null;
        }

        /* Constructor */
        public Tree(long weight) {
            this.weight = weight;
            this.right = null;
            this.left = null;
        }

        /* Method - Returns the Right Child Node */
        public Tree getRightChild() {
            return this.right;
        }

        /* Method - Returns the Left Child Node */
        public Tree getLeftChild() {
            return this.left;
        }

        /* Method - Adds a Right Child Node */
        public void addRightChild(Tree rightChild) {
            this.right = rightChild;
        }

        /* Method - Adds a Left Child Node */
        public void addLeftChild(Tree leftChild) {
            this.left = leftChild;
        }

        /* Method - Returns the Weight of the Node */
        public long getWeight() {
            return this.weight;
        }

        /* METHOD OVERRIDE - Comparison of Nodes */
        @Override
        public int compareTo(Tree node) {
            if (this.weight < node.getWeight()) {return -1;}
            else {
                if (this.weight > node.getWeight()) {return 1;}
                else{return 0;}
            }
        }

    } // End of Tree Class

    /*
     * =========================================================================
     *   Begin HuffmanTree Class
     * =========================================================================
    */
    class HuffmanTree {
        /* Attribute Declarations */
        private Tree node;
        private long weight;

        /* Default Constructor */        
        public HuffmanTree() {
            this.node = null;
            this.weight = 0;
        }

        /* Constructor */
        public HuffmanTree(Tree node) {
            this.node = node;
            this.weight = node.getWeight();
        }

        /* Method - Returns the Weight of the Node */
        public long getWeight() {
            return this.weight;
        }

        /* Method - HuffmanTree created on array parameter (length of rods) */
        public boolean createHuffmanTree(ArrayList<Long> longList) {
            /* Tree Structure Variable Declarations */
            Tree tempOne, tempTwo, parentTree;
            
            /* Tree Structure Variable Initialization */
            tempOne = null;
            tempTwo = null; 
            parentTree = null;

            /* Initialize Variable to hold total node weight */
            long totalWeight = 0;

            /* ArrayList Tree Structure Instantiation */
            ArrayList<Tree> treeList = new ArrayList<Tree>();
            for (Long i : longList) {
                Tree newNode = new Tree(i);
                treeList.add(newNode);
            }

            /* Iterates Through Data Structure */
            while (treeList.size() > 1) {
                tempOne = Collections.min(treeList);
                treeList.remove(tempOne);

                tempTwo = Collections.min(treeList);
                treeList.remove(tempTwo);

                totalWeight = tempOne.getWeight() + tempTwo.getWeight();

                parentTree = new Tree(totalWeight);

                parentTree.addLeftChild(tempOne);
                parentTree.addRightChild(tempTwo);
                treeList.add(parentTree);

                this.weight += parentTree.getWeight();
            }

            if (treeList.size() < 1){
                return false;
            } else {
                this.node = treeList.get(0);
                return true;
            }
        } // End of HuffmanTree Method

    } // End of HuffmanTree Class

    /*
     * =========================================================================
     *   Main Method
     * =========================================================================
    */
    public static void main(String[] args) throws IllegalArgumentException{

        try{
            if(args.length < 2){
                throw new IllegalArgumentException("Invalid Number of Arguments!"); 
            }

            long total = Long.parseLong(args[0]);
            long occurences = Long.parseLong(args[1]);

            if (occurences != args.length-2){
                throw new IllegalArgumentException("Invalid Number of Arguments!");
            } else {
                ArrayList<Long> length = new ArrayList<Long>();
                length.add(Long.parseLong(args[2]));
                
                for(int i = 2; i < args.length-1; i++){
                    length.add(Long.parseLong(args[i+1])-Long.parseLong(args[i]));
                }

                length.add(total-Long.parseLong(args[args.length-1]));
                
                /* Instantiate a HuffmanTree Object start */
                RodCutting start = new RodCutting();
                RodCutting.HuffmanTree cutting = start.new HuffmanTree();
                cutting.createHuffmanTree(length);
                System.out.printf(String.valueOf(cutting.getWeight())+"\n");

            }
        } catch(IllegalArgumentException e) {
            System.out.println("Error! Invalid Argument(s)!");
            System.out.println("Trying to break my program is not nice...");
        } 
    } // End of Main Method
} // End of RodCutting Class
/*
   * ===========================================================================
   * ===========================================================================
   *                            END OF PROGRAM
   * ===========================================================================
   * ===========================================================================
*/