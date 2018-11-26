/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prgm;

import java.util.Scanner;

/**
 *
 * @author windows
 */
public class string {
    public static void main(String args[]){
        Scanner s = new Scanner(System.in);
        System.out.println("Enter a string");
        String word = s.nextLine();
        int length = word.length();
       // System.out.println(length);
        char c='0';
       // int count =0,cn=0;
        for(int i = length-1;i>=0;--i){  //System.out.println("letters"+c);
         c = word.charAt(i);
                System.out.println(c);
      
        }
     
    }
}
      
