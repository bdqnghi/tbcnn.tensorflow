package com.codingparadox.spellchecker;

import com.codingparadox.utilities.Math;

/**
 * This is the class to calculate Levenshtein Distance
 * between two input strings
 * 
 * @author paradox
 *
 */
public class LevenshteinDistance {
	
	private int[][] distance;
	
	private String string1;
	private String string2;
	
	/**
	 * This function initializes our distance matrix
	 * with the boundary/initial condition
	 */
	private void initMatrix(){
		int m = this.string1.length()+1;
		int n = this.string2.length()+1;
		distance = new int[m][n];
		for(int i=1; i<m; ++i){
			distance[i][0] = i;
		}
		for(int i=1; i<n; ++i){
			distance[0][i] = i;
		}
	}
	
	public int[][] getMatrix(){
		return this.distance;
	}
	
	/**
	 * This is the actual function to calculate 
	 * LevenshteinDistance distance
	 * 
	 * @param s1 It is the first input string
	 * @param s2 It is the next input string
	 * @return int It is the total cost of similarity between two string
	 */
	public int calculateDistance(String s1, String s2){
		this.string1 = s1;
		this.string2 = s2;
		int m = s1.length();
		int n = s2.length();
		
		this.initMatrix();
		
		for(int j=1; j<n+1; ++j){
			for(int i=1; i<m+1; ++i){
				char a = s1.charAt(i-1);
				char b = s2.charAt(j-1);
				int del = this.distance[i-1][j] + 1;
				int ins = this.distance[i][j-1] + 1;
				int sub = this.distance[i-1][j-1] + (a==b ? 0 : 1);
				this.distance[i][j] = Math.min(del, ins, sub);
			}
		}
		return distance[m-1][n-1];
	}
	
	public void display(){
		int m = this.string1.length()+1;
		int n = this.string2.length()+1;
		for(int j=0; j<n; ++j){
			for(int i=0; i<m; ++i){
				//System.out.println(distance[0][1]);
				System.out.print(this.distance[i][j]);
			}
			System.out.println("");
		}
	}
}
