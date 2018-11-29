package HackeEarth;

import java.util.Scanner;

public class RodCutting {
	public static void main(String hd[]){
		int count=0;
		Scanner in=new Scanner(System.in);
		int t=in.nextInt();
		for(int i=0;i<t;i++){
			 count=0;
			int n=in.nextInt();
			int a[]=new int[n+1];
			a[1]=1;
			for(int j=3;j<=n;j++)
	       	if(eval(j,a)){
	       		count++;
	       		a[j]=1;
	       	}
			System.out.println(count);
		}
	}

	private static boolean eval(int q,int []a) {
		if(a[q]==1)
			return true;
		if(q==1)
			return true;
		if(q%2==0)
			return false;
		return eval(q/2,a);
	}
}
