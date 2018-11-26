/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package stringreverse;

/**
 *
 * @author student
 */
import java.util.*;
public class Stringreverse {

    public static void main(String[] args) {
Scanner s=new Scanner(System.in);
        System.out.println("Enter the String to be reversed");
String a=s.nextLine();
StringBuffer b=new StringBuffer(a);
        System.out.println("the reversed string is   "+b.reverse());
    }
    
}
