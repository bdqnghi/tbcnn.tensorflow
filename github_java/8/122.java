package spell.trellis;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;
import java.util.regex.*;

import spell.util.Utils;

public class Levenshtein {
	
	public enum PruningType { MAX_DISTANCE, BEAM_WIDTH };
	public class Pruning
	{ 
		
		PruningType type;
		
		double value;
		
		Pruning( PruningType p, double x)
		{
			this.type = p;
			this.value = x;
		}
		
	}
	
	
	public int insertionCost=1;
	public int deletionCost=1;
	public int matchingCost=0;
	public int substitutionCost=1;
	
	
	public int prunedCost(int[][] trellis, int y, int x, boolean match)
	{	//compute minimum only over nodes that are valid
		
		return Utils.min( 
				trellis[y][x-1]+insertionCost, 
				trellis[y+1][x-1]+((match)? matchingCost : substitutionCost), 
				trellis[y+1][x] + deletionCost
				);
		
	}
	
	
	public int LevenshteinDistance(char[] x, char[] y)
	{
		int ylen = y.length;
		int xlen = x.length;
		int[][] trellis = new int[ylen][xlen];
		
		//INITIALIZING THE TRELLIS - FIRST COLUMN, FIRST ROW (COMPARISON WITH DUMMY CHAR)
		
		trellis[ylen-1][0]=0;	//empty char compared with empty char
		for(int i=1; i< ylen; i++)
			trellis[ylen-1-i][0]= trellis[ylen-1-i+1][0] + Utils.min(deletionCost, insertionCost);;
		for(int i=1; i< xlen; i++)
			trellis[ylen-1][i]= trellis[ylen-1][i-1] + Utils.min(deletionCost, insertionCost);;
		
		
		//CALCULATING THE REST OF THE TRELLIS
		
		for(int i=1; i< xlen; i++)	//for 2nd column onwards
		{
			for(int j=1; j<ylen; j++)	//from 2nd row onwards
			{
				trellis[ylen-1-j][i] = prunedCost(trellis, ylen-1-j, i, x[i]==y[j]);
			}
		}
		
		
		Utils.displayTrellis(trellis, x, y);
		
		return trellis[0][xlen-1];	//the farthest cell on the diagonal contains the total cost
		
	}
	
	public int distance(String A, String B)
	{
		//add dummy character in beginning to bootstrap distance trellis
		A = " " + A;
		B = " " + B;
		
		char[] a = A.toCharArray();
		char[] b = B.toCharArray();
		
		return LevenshteinDistance(a,b);
		
	}
	
	
	private static int minimum(int a, int b, int c) 
	{
	        return Math.min(Math.min(a, b), c);
	}
	
	public static int computeLevenshteinDistance(String str1,String str2) 
	{
	        int[][] distance = new int[str1.length() + 1][str2.length() + 1];
	
	        for (int i = 0; i <= str1.length(); i++)
	                distance[i][0] = i;
	        for (int j = 1; j <= str2.length(); j++)
	                distance[0][j] = j;
	
	        for (int i = 1; i <= str1.length(); i++)
	                for (int j = 1; j <= str2.length(); j++)
	                        distance[i][j] = minimum(
	                                        distance[i - 1][j] + 1,
	                                        distance[i][j - 1] + 1,
	                                        distance[i - 1][j - 1]
	                                                        + ((str1.charAt(i - 1) == str2.charAt(j - 1)) ? 0 : 1));
	        
	        Utils.displayTrellis(distance, (" "+str2).toCharArray(), (" "+str1).toCharArray());
	        return distance[str1.length()][str2.length()];
	}
	

	
	public static void main(String args[])
	{
		String a = "testing";
		String b = "tastesaing";
		Levenshtein l = new Levenshtein();
		int distanceAB = l.distance(a,b);
//		System.out.println(distanceAB);
		
		b = "abcxyz";
		a = "abcdefg";
		distanceAB = l.distance(b,a);
//		System.out.println(distanceAB);
		
		b = "geafad";
		a = "asdasf";
		distanceAB = l.distance(b,a);
//		System.out.println(distanceAB);
		
	}

}
