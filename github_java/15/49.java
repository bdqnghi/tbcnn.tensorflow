package blog.dp.rodcutting;

/**
 * Rod Cutting Problem using Bottom Up Approach(DP)
 * @author Prateek
 */
public class RodCutting {

	private int[] aux;
	private int[] cost;
	int sol[];

	public void solve(int[] cost , int len){
		this.aux = new int[len+1];
		this.sol = new int[len+1];
		this.cost= cost;
		
		int maxCost=bottomUp(cost, len );
		System.out.println("Maximum Revenue:  "+maxCost);
		System.out.print("Rod cut of sizes :  ");
		printSol(len);
	}
	
	/**
	 * Bottom up Approach
	 * @param cost
	 * @param len
	 * @return
	 */
	public int bottomUp(int cost[],int len){
		aux[0] = 0;  //auxillay array
		int maxCost = 0;
		
		for(int i=1;i<=len;i++){
			 maxCost=Integer.MIN_VALUE;

			for(int j=0;j<i;j++)
				if(maxCost <  cost[j] + aux[(i-1)-j]){
					maxCost = cost[j] + aux[(i-1)-j];
					sol[i] = j+1;
				}

			aux[i]=maxCost;
		}
		return maxCost;
	}

	private void printSol(int len){
		while(len > 0){
			System.out.print(sol[len] + "\t");
			len=len - sol[len];
		}
	}
	
	public static void main(String[] args) {
		int[] cost = {1, 5 , 7, 9 , 10	, 16 , 18 , 20 , 22 };
		//int[] cost = { 1 , 5, 8  , 9,  10 , 17 , 17, 20 , 24 ,30 };
		int len= 8 ;
		RodCutting obj=new RodCutting();
		obj.solve(cost, len);
	}
}
