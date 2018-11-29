//This question is similar to string interleave problem.
//increae the length of word2 from 0 to word2.length();
//then try to find the min steps with each length of word1 (1--n)
//line 24: if the last two characters match, use the result of subproblems
//line 27: if the last two characters do not match, use the minimum of 3 operations (delete, insert, replace)

public class Solution {
    public int minDistance(String word1, String word2) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(word1 == null && word2 == null) return 0;
        if(word1 == null) return word2.length();
        if(word2 == null) return word1.length();
        int l1 = word1.length(), l2 = word2.length();
        int[][] steps = new int[l1+1][l2+1]; //how many steps to move word1 of length i to word 2 of length j
        for(int i = 0; i <= word1.length(); i++){
            steps[i][0] = i;
        }
        for(int j = 0; j <= word2.length(); j++){
            steps[0][j] = j;
        }
        for(int j = 1; j <= word2.length(); j++){//length of word2
            for(int i = 1; i <= word1.length(); i++){
                if(word1.charAt(i-1) == word2.charAt(j-1)){
                    steps[i][j] = steps[i-1][j-1];
                }
                else{
                    steps[i][j] = Math.min(Math.min(steps[i-1][j] + 1, steps[i][j-1] + 1), steps[i-1][j-1]+1);//delete, insert, or replace
                }
            }
        }
        return steps[l1][l2];
    }
    

}



//http://n00tc0d3r.blogspot.com/2013/03/edit-distance.html
//The size of the table can be reduced to two rows.


