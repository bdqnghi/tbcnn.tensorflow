import java.util.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Collections;
import java.util.Random;
import java.util.Date;
import java.io.*;


public class Merge{
  public static void main(String[] args)throws IOException {
    File file = new File("crimeandpunishment/all.txt");
    BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
    String line = null;
    LinkedList words = new LinkedList<Node>();
    int j = 0;
    while( (line = br.readLine())!= null ){
        String [] tokens = line.split("\\s+");
        for(int i = 0; i < tokens.length; i++, j++){
          words.add(tokens[i]);
        }
    }
   

//     String[] words = {"Dostoevsky", "was", "the", "son", "of", "a", "doctor", "His", "parents", "were", "very", "hard-working",
// "and", "deeply", "religious", "people"};

     //System.out.println("before sort: "+words.toString());

      Date start = new Date();

      //merge_sort(words); 

      
      // //System.out.println(toString(words));
      //System.out.println("after sort: "+words.toString());
      // System.out.println("size: "+words.size());
      // Object[] wordsArray = words.toArray();
      Collections.sort(words);
      Date end = new Date();
      System.out.println("after sort: "+words.toString());
      System.out.println("time:" +(end.getTime()-start.getTime()));


      // Date start2 = new Date();

      // mergeSort(words); 

      // Date end2 = new Date();
      // System.out.println("presorted three time:" +(end2.getTime()-start2.getTime()));
        
  }
// final static LinkedList mergeSort(LinkedList l){
//   if (l.next === SENTINEL){
//     return l;
//   } else{
//     LinkedList a = l, b = l.next.next;
//     while (b != SENTINEL){
//       l = l.next;
//       b= b.next.next;
//     }
//     b = l.next;
//     l.next = SENTINEL;
//   }
// }
  
 
 // public Node merge_sort(Node head) {
 //      if(head == null || head.next == null) { return head; }
 //      Node middle = getMiddle(head);      //get the middle of the list
 //      Node sHalf = middle.next; middle.next = null;   //split the list into two halfs

 //      return merge(merge_sort(head),merge_sort(sHalf));  //recurse on that
 //  }

 //  public Node merge(Node a, Node b) {
 //      Node dummyHead, curr; dummyHead = new Node(); curr = dummyHead;
 //      while(a !=null && b!= null) {

 //          if(a.info <= b.info) { 
 //            curr.next = a; a = a.next; 
 //          } else { 
 //            curr.next = b; b = b.next; 
 //          }
 //          curr = curr.next;
 //      }

 //      curr.next = (a == null) ? b : a;
 //      return dummyHead.next;
 //  }


 //  public Node getMiddle(Node head) {
 //      if(head == null) { return head; }

 //      Node slow, fast; 
 //      slow = fast = head;

 //      while(fast.next != null && fast.next.next != null) {
 //          slow = slow.next; fast = fast.next.next;
 //      }
 //      return slow;
 //  }
 
  
  public static void exch(Object[] a, int i, int j){
      Object temp = a[i];
          a[i] = a[j];
          a[j] = temp;
  }

public class Node<T> {
    public T element;
    public Node<T> next = null;
    public Node<T> previous = null;
    public Node(){

    }
    public Node(T element) {
      this.element = element;
    }
    public void reset() {
      this.element = null;
      this.next = null;
      this.previous = null;
    }
  }


  // public static String toString(Comparable[] a){
  //   //StringBuilder sb = new StringBuilder();
  //      // for(int i = 0; i < a.length; i++){
  //   //   sb.append(", "+a[i]);
  //   // }
  //   //sb.deleteCharAt(0);
  //   //return sb.toString();

  //   return Arrays.toString(a);
    
  // }
}