/**
 * 
 */
package org.maras.framework.edit;

import java.util.Scanner;

/**
 * @author Andrew Schade, Shun Cheung (Assoc Professor @ Emory College)
 * 
 *         Edit-Distance based off the Java algorithm located at:
 *         <a>http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/DynProg/edit-distance.html</a>
 */
public class DistanceMeasure {

	private int min = Integer.MAX_VALUE;
	private String ans = "";
	
	private double T(String x, String y, int i, int j, int n, String s) {
		double sol1, sol2, sol3;

		/*
		 * --------------------------- Base cases ---------------------------
		 */
		if (i == 0) {
			if (n + j <= min) {
				min = n + j;

				if (j > 0)
					ans = s + j + " ins()";
				else
					ans = s;
			}

			return (j);
		}

		if (j == 0) {
			if (n + i <= min) {
				min = n + i;

				if (i > 0)
					ans = s + i + " del()";
				else
					ans = s;
			}

			return (i);
		}

		if (x.charAt(i - 1) == y.charAt(j - 1)) {
			sol1 = T(x, y, i - 1, j - 1, n, s);

			return (sol1);
		} else {
			/*
			 * ------------------------ Divide step ------------------------
			 */
			sol1 = T(x, y, i - 1, j, n + 1, s + "del(" + (i - 1) + ");");
			// Try delete step as last
			sol2 = T(x, y, i, j - 1, n + 1, s + "ins(" + y.charAt(j - 1) + "," + (i - 1) + ");");
			// Try insert step as last
			sol3 = T(x, y, i - 1, j - 1, n + 1,
					s + "sub(" + x.charAt(i - 1) + "->" + y.charAt(j - 1) + "," + (i - 1) + ");");
			// Try replace step as last

			/*
			 * ---------------------------------------
			 * Conquer: solve original problem using
			 * solution from smaller problems 
			 * ---------------------------------------
			 */
			sol1 = sol1 + 1;
			sol2 = sol2 + 1;
			sol3 = sol3 + 2;

			if (sol1 <= sol2 && sol1 <= sol3)
				return (sol1);

			if (sol2 <= sol1 && sol2 <= sol3)
				return (sol2);

			if (sol3 <= sol1 && sol3 <= sol2)
				return (sol3);
		}

		return (0); // To please the stupid Java compiler
	}
	
	private static int numOccur(String src, String pattern)
	{
		int lastIndex = 0;
		int count = 0;

		while(lastIndex != -1){

		    lastIndex = src.indexOf(pattern,lastIndex);

		    if(lastIndex != -1){
		        count ++;
		        lastIndex += pattern.length();
		    }
		}
		return count;
	}
	
	public double getEditDistance(String from, String to)
	{
		min=Integer.MAX_VALUE;
		ans = "";
		double distance_r = T(from, to, from.length(), to.length(),0,"");
		
		return distance_r;
		
	}

	public static void main(String[] args) {

		// String x = "man";
		// String y = "moon";

		String x = "theophylline";
		String y = "ibuprofen500mg";
		DistanceMeasure dm = new DistanceMeasure();
		double r;

		r = dm.getEditDistance(x, y);

		System.out.println("x = " + x);
		System.out.println("y = " + y);
		System.out.println();
		System.out.println("Min. Edit Distance = " + r);
		System.out.println();
		System.out.println("Sequence of edit operations:");
		System.out.println("   " + dm.ans);
	}

}
