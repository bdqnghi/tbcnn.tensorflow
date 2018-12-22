package dynamicProgramming;

import java.util.Arrays;

public class RodCutting {

	//bottom up
	public void cut(int [] p,int len){
		int [] max = new int[len ];
		int maximum = 0,temp = 0;
		max[0] = p[0];
		for(int j = 1; j < len ; j++){
			
			maximum = p[j];
			for(int i = 1; i < j; i++){
			//	temp = Math.max(max[j-i] + max[i],p[j]);
			//	if(j - i == 0){
			//		temp = p[i];
			//	}else{
				temp = max[j-i] + p[i-1];
			//	}
				if(temp > maximum)maximum = temp;
			}
			max[j] = maximum;
		}
		for(int x: max)System.out.println(x);
	}
	//top down
	public int rodCut(int [] p, int n, int [] maxl){
		if(maxl[n] != 0)return maxl[n];
		int max = p[n-1],temp = 0;
		if(n <= 1){
			maxl[1] = p[0];
			return p[0];
		}
		for(int i = 1; i < n; i++){
			
			temp = p[n - (i +1)] + rodCut(p, i, maxl);
			if(temp > max) max = temp;
		}
		maxl[n] = max;
		return max;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int [] p = {1,5,8,9,10};
		int [] m = new int[6];
		new RodCutting().cut(p,5);
		//System.out.println(new RodCutting().rodCut(p, 5,m));
		//System.out.println(Arrays.toString(m));
		
	}

}
