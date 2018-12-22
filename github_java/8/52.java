/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package editdistance;

import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author Harshita V
 */
public class Editdistance {

    /**
     * @param args the command line arguments
     */
    public static int minDistance(String word1, String word2) {
	int len1 = word1.length();
	int len2 = word2.length();
 
	// len1+1, len2+1, because finally return dp[len1][len2]
	int[][] dp = new int[len1 + 1][len2 + 1];
 
	for (int i = 0; i <= len1; i++) {
		dp[i][0] = i;
	}
 
	for (int j = 0; j <= len2; j++) {
		dp[0][j] = j;
	}
 
	//iterate though, and check last char
	for (int i = 0; i < len1; i++) {
		char c1 = word1.charAt(i);
		for (int j = 0; j < len2; j++) {
			char c2 = word2.charAt(j);
 
			//if last two chars equal
			if (c1 == c2) {
				//update dp value for +1 length
				dp[i + 1][j + 1] = dp[i][j];
			} else {
				int replace = dp[i][j] + 1;
				int insert = dp[i][j + 1] + 1;
				int delete = dp[i + 1][j] + 1;
 
				int min = replace > insert ? insert : replace;
				min = delete > min ? min : delete;
				dp[i + 1][j + 1] = min;
			}
		}
	}
 
	return dp[len1][len2];
}
    public static void main(String[] args) {
        // TODO code application logic here
        ArrayList<String> al=new ArrayList<>();
        al.add("pied");
        al.add("pile");
        al.add("pier");
        al.add("pides");
        String s="pide";
        ArrayList possible=new ArrayList();
        for(int i=0;i<al.size();i++){
        
        if(minDistance((String)al.get(i),s)<2){
            System.out.println((String)al.get(i));
        System.out.println("yo");
         possible.add((String)al.get(i));
        }
        
        String x=(String)al.get(i);
        char[] charArr=x.toCharArray();
        Arrays.sort(charArr);
       
        
        
        char[] charArr2=s.toCharArray();
        Arrays.sort(charArr2);
        
        if(charArr.toString().equals(charArr2.toString())){ possible.add((String)al.get(i));}
        
        }
        System.out.println(possible);
    }
    
}
