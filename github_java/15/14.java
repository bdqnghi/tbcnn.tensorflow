
public class RodCutting {

	public RodCutting() {
	}
	
	public void cutRod(int[] p, int n) {
		int[] r = new int[p.length], s = new int[p.length];
		
		for(int i = 1; i <= n; i++) {
			int q = p[i];
			s[i] = i;
			for(int j = 1; j <= i-1; j++) {
				if(p[j] + r[i-j] > q) {
					q = p[j] + r[i-j];
					s[i] = j;
				}
			}
			r[i] = q;
		}
		
		printSolution(p, r, s, n);
	}
	
	public void printSolution(int[] p, int[] r, int[] s, int n) {
		n = 9;
		int i = n;
		System.out.println();
		System.out.print("Total Revenue: "+r[n]+" [");
		while(i > 0) {
			System.out.print(s[i]+",");
			i = i - s[i];
		}
		System.out.println("]");

		for(int j = 0; j < p.length; j++) {
			System.out.print(j+",\t");
		}
		System.out.println("");
		for(int j = 0; j < p.length; j++) {
			System.out.print(p[j]+",\t");
		}
		System.out.println("");
		for(int j = 0; j < r.length; j++) {
			System.out.print(r[j]+",\t");
		}
		System.out.println("");
		for(int j = 0; j < s.length; j++) {
			System.out.print(s[j]+",\t");
		}
	}

	public static void main(String[] args) {
		RodCutting c = new RodCutting();
		int[] p = {0,1,5,8,10,13,17,17,20,24,30};
		int n = 10;
		c.cutRod(p, n);
	}

}

