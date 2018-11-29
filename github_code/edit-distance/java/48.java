package stringex;


public class Editdistance {

    public static void main(String a[]){
       String C = "kitten";
        String D = "sitting";
        System.out.printf("len"+findDistance(C.toCharArray(),C.length(),D.toCharArray(),D.length()));

    }
     public static int findDistance(char[] X,int m,char[] Y,int n){
         int[][] T = new int[m][n];
         for (int i = 1; i < m; i++)
             T[i][0] = i;
         for (int j = 1; j < n; j++)
             T[0][j] = j;

         int cost =0;
            for (int i=1;i<m;i++){
                for (int j=1;j<n;j++){
                    if(X[i-1]==Y[j-1]){
                        cost=0;
                    } else {
                        cost=1;

                    }

                 T[i][j]=Math.min(Math.min(T[i - 1][j] + 1,        // deletion
                            T[i][j - 1] + 1),        // insertion
                            T[i - 1][j - 1] + cost);
                }

            }

         return T[m-1][n-1];
     }


}
