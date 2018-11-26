package dynamicprogramming.rodcutting;

/*
 * Given a rod of length n, 
 * a table of prices pi for i=1,2,...n (ie. pi is the price of rod of length i)
 * determine the max revenue rn, obtainable by cutting up the rod and selling the pieces.
 * NOTE: if the price of pn of rod of length n is large enough, an optimal solution may require no cutting at all.
 * 
 * length i | 1  2  3  4  5   6   7   8   9   10
 * ---------|----------------------------------------------------------------------------------
 * price pi | 1  5  8  9  10  17  17  20  24  30
 * 
 */
public class RodCutting {
	
	int [] prices;
	int n ;
	
	int [] ri;
	
	public RodCutting(){}
	public RodCutting(int[] p, int n){
		this.prices = p;
		this.n = n;
		
		ri = new int[p.length];
	}
	
	/*
	 * Top down approach.
	 * while calculating the top optimum cost, all the bottom optimum are calculated and memoized
	 */
	public int memoizedCutRodAux(int[] p, int n, int[] r){
		int q=0;
		
		if(r[n] >= 0)	return r[n];
		
		if(n==0){
			q = 0;
		}else{
			q = -9999;
			for(int i=1; i<=n; i++){
				q = Math.max(q, p[i] + memoizedCutRodAux(p, n-i, r));
			}
		}
		r[n] = q;
		
		System.out.println("returning revenue for n=" + n + " is " + q);
		return q;
	}
	
	/*
	 * Bottom top approach
	 */
	public int bottomUpRod(int[] p, int n, int[] r){
		int q =-9999;
		
		r[0] = 0;
		for(int i=1; i<=n; i++){
			q = -9999;
			if(i==11){
				q = -9999;
			}
			for(int j=1; j<=i; j++){
				try{
					
					q = Math.max(q, p[j] + r[i-j]);
				}catch(RuntimeException e){
					System.out.println(" i=" + i + ", j=" + j);
					e.printStackTrace();
				}
			}
			r[i] = q;
		}
		return r[n];
	}
	
	
	public static void main(String[] args) {
		int [] pi = {0,1,5,8,9,10,17,17,20,24,30};// prices
		int n = 9;
		int[] r = new int[n+1];
		
		for(int i=0; i<=n; i++) r[i] = -9999;
		
		//to support n > pi.length
		if(n>pi.length){
			int[] pi2 = new int[n+1];
			for(int i=0; i<pi.length; i++) pi2[i] = pi[i];
			for(int i=pi.length; i<n; i++) pi2[i] = pi[pi.length-1];
			pi = pi2;
		}
		
		RodCutting rc = new RodCutting(pi, n);
		int optimumRevenue ;
		//optimumRevenue= rc.memoizedCutRodAux(pi, n, r);
		optimumRevenue = rc.bottomUpRod(pi, n, r);
		
		System.out.println("optimal revenue=" + optimumRevenue);
	}
}

/*
 * top down approach: take a length l, and find an optimal solution for n-l
 * buttom up approach: go building optimal solution from the buttom
 */
