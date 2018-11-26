/**
 * Created by Barnabas_Ravindranath on 4/19/17.
 */

import java.io.*;
import java.util.Scanner;
import java.lang.String;


public class AVL {


    public static void main(String[] args) {

        Create_Tree("AVLinput.txt"); //call to create AVL Tree

    }



    //Method to create AVL Tree from File Input
    public static void Create_Tree(String file){

        AVLTREE node = new AVLTREE();

        Scanner scan = null;

        try {
            scan = new Scanner(new File(file));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }


        //Will scan for two objects:
        // First Object: a String, either "+" or "-". ("+" indicating we add something amd "-" we delete something)
        // Second Object: a number String (Converted to an integer that represents the value of the node inserted or deleted)
        while (scan.hasNext()) {

            //first object
            String line = scan.next().replaceAll(",", "");

            //second object
            int y = Integer.parseInt((scan.next().replaceAll(",", "")));

                //if string == "+" then insert node
                if(line.compareTo("+") == 0) node.insertnode(y);

                //if string == "-" then delete node if the value is already in the tree
                else { if (node.search(y)) node.delete(y); }

        }

        System.out.println("\n" + "In-Order AVL Tree Traversal\n\n");

        node.inorder(); //prints out In-Order Traversal


        System.out.println("\n\n" + "Pre-Order AVL Tree Traversal\n\n" );

        node.preorder(); //prints out Pre-Order Traversal

        
        scan.close();

    }





}
