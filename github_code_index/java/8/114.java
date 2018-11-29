
public class editdistance {
	public static void main(String[] args){
		int a=minDistance("zoologicoarchaeologist","zoogeologist");
				System.out.println(a);
		/* return number of deletes,replace or insert logic is if == equal to diagonal else minimum(of 3) +1*/
	}
	  public static int minDistance(String word1, String word2) {
	        
	        int m=word1.length();
	        int n=word2.length();
	        if(m==0) return n;
	        if(n==0) return m;

	        int[][] grid=new int[m+1][n+1];
	        for(int i=0;i<grid[0].length;i++){
	            grid[0][i]=i;
	        }
	        for(int i=0;i<grid.length;i++){
	            grid[i][0]=i;
	        }
	        for(int i=1;i<grid.length;i++){
	            for(int j=1;j<grid[0].length;j++){
	                if(word1.charAt(i-1)==word2.charAt(j-1)){
	                    grid[i][j]=grid[i-1][j-1];
	                }else{
	                    grid[i][j]=1+Math.min(grid[i-1][j-1],Math.min(grid[i-1][j],grid[i][j-1]));
	                }
	            }
	        }
	        
	        return grid[m][n];
	    }
}
