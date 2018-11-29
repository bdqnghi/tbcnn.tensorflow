/*
            CSCI 3200
Authour:    Ashley Fraley
Assignment: 6
File:       EditDistance.java
Tab stop:   3  

Description: Using a two-dimensional array of integers it finds the edit distance between two strings.
*/

import java.util.*;
import java.lang.Math.*;

public class EditDistance
{
   public static void main(String[] args)
   {
      Scanner k = new Scanner(System.in);
      String s = k.nextLine().trim();
      String t = k.nextLine().trim();
      int m = s.length(); 
      int n = t.length();
      int[][] distance = new int[m + 1][n + 1];
      
      System.out.println("The edit distance between " + '"' + s + '"' + " and " + '"' + t + '"' + " is " + d(distance,s,t) + ".");
   }
   
//initArray:
//
   public static void initArray(int m, int n, int [][] distance)
   {
      for(int i = 0; i <= m; i++)
      {
         distance[i][0] = i;
      }
      for(int j = 0; j <= n; j++)
      {
         distance[0][j] = j;
      }
   }


//minNum:
//Allows you to find the minimum integer between
//three different integers instead of only two   
   public static int minNum(int x, int y, int z)
   {
      return Math.min(Math.min(x,y),z);
   }
   
//d:
//Returns the edit distance between two strings   
   public static int d(int [][] distance, String s, String t)
   {
      int length = 0;
      int m = s.length();
      int n = t.length();
      while(length != distance.length)
      {
         if(s.charAt(m) == t.charAt(n))
	      {
	         distance[m-1][n-1] = distance[m][n];
	         m = m - 1;
	         n = n - 1;
	         length = length + 1;
	      }
	      else
	      {
	         int replace = distance[m][n] + 1;
	         int insert = distance[m][n-1] + 1;
	         int delete = distance[m-1][n] + 1;
	         
	         int min = minNum( replace,insert,delete);
	         distance[m-1][n-1] = min;
	         m = m - 1;
	         n = n - 1;
	         length = length + 1;
	      }   
      }
      return distance[m][n];
   }
 }
	
