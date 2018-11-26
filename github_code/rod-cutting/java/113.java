/*
Description��

The rod-cutting problem is the following. 
Given a rod of length n inches and a table of prices pi for i D 1��2������n,
determine the maximum revenue rn obtainable by cutting up the rod and selling the pieces. 
Note that if the price pn for a rod of length n is large enough, an optimal solution may require no cutting at all.

*/
package dynamic_programming;

public class Rod_cutting {
	private int[] price;
	
	Rod_cutting(){
		this.price = new int[11];
		this.setPrice();
	}
	
	public void setPrice() {
		this.price[0] = 0;
		this.price[1] = 1;
		this.price[2] = 5;
		this.price[3] = 8;
		this.price[4] = 9;
		this.price[5] = 10;
		this.price[6] = 17;
		this.price[7] = 17;
		this.price[8] = 20;
		this.price[9] = 24;
		this.price[10] = 30;
	}
	
	public int max(int x,int y) {
		if(x > y ) {
			return x;
		}else {
			return y;
		}
	}
	
	public int getMaxPrice(int x) {
		return this.price[x];
	}
	public int cut_rod(int x) {
		int max_price = 0;
		int middle = 0;
		int j = 0;
		if(x == 0)
			return this.price[x];
		if(x>10)
			j=10;
		else
			j=x;
		for(int i = 1;i <= j;i++) {
			middle = max(middle,this.price[i]+cut_rod(x-i));
		}
		max_price = middle;
		return max_price;
	}
	
	public static void main(String[] args){
		Rod_cutting a = new Rod_cutting();
		System.out.print(a.cut_rod(25));
	}
}
