/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package stringreverse;
import java.io.*;
import java.lang.*;
import java.util.*;

/**
 *
 * @author DELL
 */
public class Stringreverse {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String str=new String();
        Scanner read=new Scanner(System.in);
        System.out.println("Enter a string to print it's reverse..");
        str=read.nextLine();
        if(str.length<100000){
        StringBuilder str1=new StringBuilder();
        str1.append(str);
        str1=str1.reverse();
        System.out.println(str1);
        }else{
        System.out.println("Too long..");
        }
      
    }
    
}
