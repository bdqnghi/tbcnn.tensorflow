/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package njassignments;
import java.io.*;
import java.util.*;

/**
 *
 * @author ADMIN
 */
public class towerofhanoi {
     public static void main(String[] args) {
       towerofhanoi toh = new towerofhanoi();
       System.out.print("Enter number of discs: ");
       Scanner scan = new Scanner(System.in);
       int discs = scan.nextInt();
       toh.solve(discs, "A", "B", "C");
   }
     
     void solve(int n, String start, String auxiliary, String end) {
       if (n == 1) {
           System.out.println(start + " -> " + end);
       }
       else {
           solve(n - 1, start, end, auxiliary);
           System.out.println(start + " -> " + end);
           solve(n - 1, auxiliary, start, end);
       }
   }
}
    

