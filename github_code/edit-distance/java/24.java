import java.util.*;
import java.io.*;

public class Edit{

 	String s1=""; 
 	String s2 ="";
        int distance = 0;	
 	public static void main(String[] args) throws IOException{
		 Edit e = new Edit();
		 e.getStrings();
		 e.findDistance();
		System.out.println("The edit distance between " + e.s1 + " and " + e.s2 + " is " + e.distance);
      	}

	public void findDistance(){
		int s1Length = s1.length();
		int s2Length = s2.length();
		int [][] dyn = new int [s1Length + 1][s2Length + 1];

		//trivial steps of filling out the table
		for (int c = 0; c < s1Length + 1; c++){
			dyn[c][0]=c;	
		}
		for(int k = 0; k < s2Length + 1; k++){
			dyn[0][k] = k;
		}
		//Slighy different implementation of the algorythm. I didn't see we were given it. Pretty similar, some
		//vars have different name.
		for (int a = 0; a < s1Length; a++) {
			char c1 = s1.charAt(a);
		for (int b = 0; b < len2; b++) {
			char c2 = s2.charAt(b);
 
			//if last two chars equal
			if (c1 == c2) {
				dp[a + 1][b + 1] = dp[a][b];
			} else {
				int rep = dp[a][b] + 1;
				int ins = dp[a][b + 1] + 1;
				int del = dp[a + 1][b] + 1;
 				//Finds the MIN between REP, INS, DEL
				int min = rep > ins ? ins : rep;
				min = delete > min ? min : delete;
				//INSERTS MIN TO BOTTOM RIGHT CORNER>>>ANSWER ONCE DONE Iterating
				dp[a + 1][b + 1] = min;
				distance = min
			}
		}
	}


	

		//distance = 4;
	}
 	 public void getStrings() throws IOException, FileNotFoundException{
		BufferedReader reader = new BufferedReader(new FileReader("myStrings.txt"));
		s1= reader.readLine();
		s2= reader.readLine();
  	}	

}
