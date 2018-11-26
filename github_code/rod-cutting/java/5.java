public class rodCutting{
	

	static void revenue(int price[], int n, int cost){
	/* r_n = max { p_i + r_n-i } for i from 1 to n*/
		int r[] = new int[n+1]; int s[] = new int[n+1];
		s[0] = 0;//cannot cut if there is no rod; 
		s[1] = 1;//cut a rod with length 1 at the length 1, meaning no cut;
		r[0] = 0; //just 0; revenue for a length 0 rod is just $0
		r[1] = price[1]; //revenue of length 1 is always the price for length 1	
		System.out.print("r[i]: "); 
			
		for(int j = 1; j <= n; j++){ // O(n)
			int max = price[j];//price for not cutting at all	
			s[j] = j;	 //cut rod of length j at length j -> no cut
			for(	int k = 1; k<= j-1; k++) //O(n);
				if( max < price[k] + r[j-k] - cost){
					max = price[k] + r[j-k] - cost;
					s[j] = k;	
				}
			r[j] = max;			
			System.out.print(r[j] + " ");	//max revenue for rod of length i
		}//O(n^2);
		
		/* print out the best cuts for each size of rod	*/
		System.out.print("\ns[i]: ");
		for(int i = 1 ; i < s.length; i++){
			System.out.print(s[i] + " " );
		}
		System.out.println();
	}
}


	
