/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multiple;

/**
 *
 * @author miracle
 */
public class stringreverse 
{
public static void main(String args[]){
        String str = "sivasaikumar";
        char []ch=str.toCharArray();
        int l=str.length();
        for(int i=l-1;i>=0;i--){
            System.out.print(ch[i]);
            
        }
        System.out.println("");
}

}
