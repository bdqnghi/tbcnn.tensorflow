public class Solution {
    public int minDistance(String word1, String word2) {
        // Start typing your Java solution below
        // DO NOT write main() function
        int l1=word1.length(),l2=word2.length();
        if(l1==0) return l2;
        if(l2==0) return l1;
        int[][] d=new int[l1+1][l2+1];
        for(int i=0;i<=l2;i++)
            d[0][i]=i;
        for(int i=0;i<=l1;i++)
            d[i][0]=i;
        for(int i=1;i<=l1;i++) {
            for(int j=1;j<=l2;j++) {
                int m=Math.min(d[i-1][j]+1,d[i][j-1]+1);
                m=Math.min(m,d[i-1][j-1]+(word1.charAt(i-1)==word2.charAt(j-1)?0:1));
                d[i][j]=m;
            }
        }
        return d[l1][l2];
    }
}
