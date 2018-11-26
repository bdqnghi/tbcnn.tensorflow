// demonstrates AVL tree
import java.io.*;                 // for I/O
import java.lang.Integer;         // for parseInt()
public class avl
   {
   public static void main(String[] args) throws IOException
      {

      Tree theTree = new Tree();

      theTree.insert(50);
      theTree.insert(25);
      theTree.insert(75);
      theTree.insert(12);
      theTree.insert(37);
      theTree.insert(43);
      theTree.insert(30);

      theTree.insert(33);
      theTree.insert(87);
      theTree.insert(93);
      theTree.insert(97);


      theTree.find(97, theTree.getRoot());

      }  // end main()

// -------------------------------------------------------------
   public static void putText(String s)
      {
      System.out.print(s);
      System.out.flush();
      }
// -------------------------------------------------------------
   public static String getString() throws IOException
      {
      InputStreamReader isr = new InputStreamReader(System.in);
      BufferedReader br = new BufferedReader(isr);
      String s = br.readLine();
      return s;
      }
// -------------------------------------------------------------
   public static char getChar() throws IOException
      {
      String s = getString();
      return s.charAt(0);
      }

//-------------------------------------------------------------
   public static int getInt() throws IOException
      {
      String s = getString();
      return Integer.parseInt(s);
      }
// -------------------------------------------------------------
   }  // end class TreeApp
