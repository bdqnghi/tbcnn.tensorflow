
import java.io.*;
import java.util.*;

public class AVL{
  public static void main(String[] args) throws IOException{
    int key, value;

    AvlTree tree = new AvlTree();
    System.out.println("Commands: (d)elete; (i)nsert; (p)rint; (q)uit; (s)earch"); 
    
   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
   System.out.print("Command: ");

   String command = in.readLine();
   char c = command.charAt(0);  

  

   while (! command.equals("q")){
      switch(c){

      
      case 'p':
      case 'P':
               System.out.println();
       tree.inorder(tree.root);
               break;

        
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
      } 

      System.out.print("Command: ");
      command = in.readLine();
      c=command.charAt(0);
    } 
  } 
} 

