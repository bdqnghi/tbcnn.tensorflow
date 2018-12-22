/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto.algoritmos;

import java.io.*;
import javax.swing.JOptionPane;

/**
 *
 * @author Diego F
 */

class LevenshteinDistance {   
public static int minimo,A,B,C;         
     /**
     * @param args the command line arguments
     */

//A costo de Eliminacion
//B Costo de Insercion
//C Costo de Sustitucion

        public static int minimum(int a, int b, int c) {
        if (a<=b && a<=c)
        {  
          minimo=a;
          A=a;
          return a;
        } 
        else
            if (b<=a && b<=c)
        {
            minimo=b;
            B=b;
            return b;
        }
            else 
            { 
                C=c;
                minimo = c;
                return c;
            }
        
        }
     
    public static int computeLevenshteinDistance(String str1, String str2) {
    
        return computeLevenshteinDistance(str1.toCharArray(),str2.toCharArray());
        
    }
 
    private static int computeLevenshteinDistance(char [] str1, char [] str2) {
        
        int [][]distance = new int[str1.length+1][str2.length+1];
 
        for(int i=0;i<=str1.length;i++)
        {
                distance[i][0]=i;
        }
        for(int j=0;j<=str2.length;j++)
        {
                distance[0][j]=j;
        }
        for(int i=1;i<=str1.length;i++)
        {
            for(int j=1;j<=str2.length;j++)
            { 
              distance[i][j]= minimum(distance[i-1][j]+1,distance[i][j-1]+1,distance[i-1][j-1]+((str1[i-1]==str2[j-1])?0:1));
            }
        }
        
        
        return distance[str1.length][str2.length];
    }
    
  
public static void main(String[] args) {
        // TODO code application logic here
  String Palabra1;
  String Palabra2;
  JOptionPane.showMessageDialog(null, "Algoritmo que permite generar el número mínimo de operaciones\nrequeridas para transformar una cadena de caracteres en otra");
  Palabra1 = JOptionPane.showInputDialog(null,"Ingrese palabra de Referencia: ");
  Palabra2 = JOptionPane.showInputDialog(null,"Ingrese Palabra de Edicion: ");
  LevenshteinDistance.computeLevenshteinDistance(Palabra1, Palabra2);
    
  /*casa → cala (sustitución de 's' por 'l')
    cala → calla (inserción de 'l' entre 'l' y 'a')
    calla → calle (sustitución de 'a' por 'e')*/
 
  if (LevenshteinDistance.A<=LevenshteinDistance.B && LevenshteinDistance.A<=LevenshteinDistance.C)
        {  
            System.out.println("TENDRA UN COSTO DE ELIMINACION POR: "+LevenshteinDistance.A);
        } 
        else
            if (LevenshteinDistance.B<=LevenshteinDistance.A && LevenshteinDistance.B<=LevenshteinDistance.C)
        {
            System.out.println("TENDRA UN COSTO DE INSERCION POR: "+LevenshteinDistance.B);
        }
            else 
            { 
                System.out.println("TENDRA UN COSTO DE SUSTITUCION POR: "+LevenshteinDistance.C);  
            }
         
    System.out.println("EL MINIMO COSTO DE EDICION ES: "+LevenshteinDistance.minimo);

      
    }


}

    

