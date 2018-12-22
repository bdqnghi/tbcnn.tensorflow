package RodCutting;

import java.util.Scanner;

/*modification of the rod-cutting problem in which, in addition to a
price pi for each rod, each cut incurs a fixed cost of c. The revenue associated with
a solution is now the sum of the prices of the pieces minus the costs of making the
cuts. Give a dynamic-programming algorithm to solve this modified problem.*/

public class Modification1 {
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.println("Enter the number of rods");
		int n = in.nextInt();
		int[] p = Main.getInputPrices(n);
		int[] c = Main.getInputCosts(n);
		double[] r = new double[n+1];
		int[] s = new int[n+1];
		r[0]=0;
		System.out.println("Dynamic programming - Bottom up approach with memoization plus modification of fixed costs");
		System.out.println("Enter the value rod length for which the value is to be calculated");
		int rod = in.nextInt();
		System.out.println(bottomUp(p,rod,r,s,c));
		System.out.println("Rods that comprises "+n);
		while(n >0) {
			System.out.println(s[n]);
			n = n-s[n];
		}
		in.close();
	}
	
	public static double bottomUp(int[] p,int n,double[]r,int[] s,int[] c) {
		
		for(int j=1;j<=n;j++) {
			double q=Double.NEGATIVE_INFINITY;
			for(int i=1;i<=j;i++) {
				if(q < p[i]-c[i]+r[j-i]) {
					q= p[i]-c[i]+r[j-i];
					s[j]=i;
				}
			}
			r[j]=q;
		}		
		return r[n];
	}

}
