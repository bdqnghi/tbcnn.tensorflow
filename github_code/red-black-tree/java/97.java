/*
 * Hai Vo 
 * hqvo@ucsc.edu
 * this is my java code for a red black tree
 */
import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;
import java.util.*;

/*
 * The main class for my Red Black Tree.
 */

public class RedBlackTree {
    
    static void scanfile (Scanner input, String filename) {
        Tree redBlackTree = new Tree();
        while(input.hasNext()){
            String word = input.next();
            if(word.equals("i")){// the insertion
                int key = input.nextInt();
                node newNode = new node();
                newNode.key = key;
                redBlackTree.insertion(newNode);
            }
            else if(word.equals("f")){//searching for node
                int key = input.nextInt();
                redBlackTree.search(key);
            }
            else if(word.equals("pt")){// printing tree
                redBlackTree.printOut();
            }
            else if(word.equals("pn")){//printing node
                redBlackTree.printNode();
            }
            else if(word.equals("max")){// the max node
                System.out.println("the max is :" + redBlackTree.max);
            }
            else if(word.equals("min")){// the min node
                System.out.println("the min is :" + redBlackTree.min);
            }
            else if(word.equals("s")){// the successor
                redBlackTree.successor();
            }
            else if(word.equals("p")){// the predecessor 
                redBlackTree.predecessor();
            }else{//if there is no such command
                System.out.println("improper command");
            }
        }
    }

    
    /*
     * main is the main function in the program and is mostly 
     * use to read in a file or stdin and check if the file 
     * exists. All of the call are done in scanfile
     * @param args is where the user can enter in a file they
     * plan to read.
     */
    public static void main(String[] args) {
      try {
        if (args.length == 0) {// if no arguements take from stdin
            scanfile (new Scanner (in), "<stdin>");
        }else {
            try {
                String filename = args[0];//read in file
                Scanner input = new Scanner (new File (filename));
                scanfile (input, filename);
                input.close();//close file
            }catch (IOException error) {//error checking
                System.err.println(error);
            }
        }
      }catch(PatternSyntaxException error) {//error checking
         System.err.println(error);
      }
    }

}
