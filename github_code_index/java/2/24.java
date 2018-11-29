// File: AVL.java

import java.io.*;
import java.util.*;

/** 
 * CSC B63 Assignment #2 Programming component
 * Provides command line access to the AVL tree class
 *
 * This file has been provided to make it easier to test your AVL tree code.
 *
 * DO NOT SUBMIT THIS FILE
 **/

public class AVL{

  public static void main(String[] args) throws IOException{

    int key, value;
    AVLTree tree = new AVLTree();
    System.out.println("Commands: (d)elete; (i)nsert; (p)rint; (q)uit; (s)earch"); 
    
   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
   System.out.print("Command: ");

   String command = in.readLine();
   char c = command.charAt(0);  

   /**
    * The AVL commands are executed based on the user's choice.
    * If a key or value is needed, the user is prompted to enter
    * the additional information.
    * We use try and catch to handle exceptions. 
    **/

   while (! command.equals("q")){
      switch(c){

      //Prints the AVL tree
      case 'p':
      case 'P':
               System.out.println();
        tree.print();
               break;

      //Inserts a new node into the AVL tree        
      case 'i': 
      case 'I':
        System.out.print("Key to insert: ");
         try {
      key = Integer.parseInt(in.readLine());
                    
      tree.insert(key);
                }
  catch(NumberFormatException f) {
                    System.out.println("Invalid number.");
                 }
                break;

      //Searches for a node in the AVL tree, and outputs the node 
     /**case 's':
      case 'S':
  System.out.print("Key to find: ");
  try {
             key = Integer.parseInt(in.readLine());
          System.out.println();
              tree.search(key);
  }
  catch(NoSuchElementException e) {
             System.out.println("Node not found");
          }
  catch(NumberFormatException f) {
      System.out.println("Invalid number.");
                }
          break;*/
   
      //Deletes a node from the AVL tree 
      case 'd':
      case 'D':
  System.out.print("Key to delete: ");
  try {
                    key = Integer.parseInt(in.readLine());
            tree.remove(key);
      }
      catch(NoSuchElementException e) {
         System.out.println("Node not found");
      }
                catch(NumberFormatException f) {
                    System.out.println("Invalid number.");
                }
      break;
      } //switch

      System.out.print("Command: ");
      command = in.readLine();
      c=command.charAt(0);
    } //while
  } // main(String[])

} // AVL 

