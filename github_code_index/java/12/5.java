package DP;

public class MatrixChainMultiplication {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		MatrixChainMultiplication mc = new MatrixChainMultiplication();
		int[] p = {2,3,6,4,5};
		int[][] cost = new int[p.length][p.length];
		System.out.println(mc.MatrixChain(p, 1, p.length-1));
		System.out.println(mc.MatrxChain(p,cost, 1, p.length));

	}
	
	
	public int MatrxChain(int[] arr,int[][] cost,int start,int end){
		for(int i = 0 ; i < cost.length-1 ; i++)
			cost[i][i] = 0;
		int[][] seq = new int[arr.length][arr.length];
		// Length of matrix. Starts from 2 .. to length. Sort of columns
		for (int L=2 ; L < arr.length; L++){
			// A sort of rows in table
            for (int i=1 ; i < arr.length-L+1; i++) { // Starting point
                int j = i+L-1; // Ending point
                if(j == arr.length) continue;
                cost[i][j] = Integer.MAX_VALUE;
                // Splits at each point
                for (int k=i ; k <= j-1; k++) {
                    int q = cost[i][k] + cost[k+1][j] + arr[i-1]*arr[k]*arr[j];
                    if (q < cost[i][j]) {
                        cost[i][j] = q;
                        seq[i][j] = k;
                    }
                }
            }
        }
		print(seq);
		return cost[1][4];
	}

	public void print(int[][] cost){
		for(int row = 0 ; row < 5 ; row++){
			for(int col = 0 ; col < 5; col++){
				System.out.print(cost[row][col]+"        ");
			}	
			System.out.println();
		}
	}
	
	
	public int MatrixChain(int[] arr,int start,int end){
		if(start == end)
			return 0;
		int cost = Integer.MAX_VALUE;
		int min = 0;
		for(int p = start ; p < end ; p++) {
			min = MatrixChain(arr,start,p)+
					MatrixChain(arr,p+1,end)+
					arr[start-1]*arr[p]*arr[end];
			if(cost > min)
				cost = min;
		}
		return cost;
	}

	
	
}
