package com.tegik.idlinout.module.proc;
import java.lang.String;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.LinkedList;

public class Levenshtein {
	private static int minimum(int a, int b, int c) {
		if (a<=b && a<=c)
		{
			return a;
		} 
		if (b<=a && b<=c)
		{
			return b;
		}
		return c;
	}

	public static int computeLevenshteinDistance(String str1, String str2) {
		return computeLevenshteinDistance(str1.toCharArray(),
				str2.toCharArray());
	}

  public static String execute(String s){
    LinkedList<String> x = new LinkedList<String>();
    x.add("AlCor.");
    x.add("Av.");
    x.add("Bus.");
    x.add("Cep.");
    x.add("Chis.");
    x.add("Flam.Cep.");
    x.add("Hon.");
    x.add("Moon");
    x.add("Nat.");
    x.add("Otro");
    x.add("P.B.");
    x.add("P.M.");
    x.add("Roul.");
    x.add("Rust.");
    x.add("Sndb.");
    x.add("Split");
    x.add("Tomb.");
    x.add("Tomb.Cep.");
    x.add("Sndb.");
    x.add("Tra.");
    return compareList(s,x);
  }
  private static String compareList(String a, LinkedList<String> b){
	  a = a.toUpperCase().replaceAll("[,|.|\\s]", "");
	  String temp2;
	  Integer bI2;
	  String bS = "";
	  Integer bI = Integer.MAX_VALUE;
	  if(b.size() < 1)
		  return "";
	  for (String temp : b) {
		  temp2 = temp.toUpperCase().replaceAll("[,|.|\\s]", "");
		  bI2 = computeLevenshteinDistance(a,temp2);
		  if(bI2 < bI){
			  bS = temp;
			  bI = bI2;
		  }
	  }
	  return bS;
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
			  distance[i][j]= minimum(distance[i-1][j]+1,
					  distance[i][j-1]+1,
					  distance[i-1][j-1]+
					  ((str1[i-1]==str2[j-1])?0:1));
		  }
	  }
	  return distance[str1.length][str2.length];
  }
}
