/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RodCuttingProgram;

/**
 *
 * @author Vinayak
 */
public class RodCuttingProgram {
    public static void main(String[]args) throws Exception{


	       int[] x = {0,1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
               int n = 0;
	for(int i=1;i<10;i++)
		 n=i;
	System.out.println("\tPricing table");
        System.out.println("lenght i | 1    2   3   4   5   6   7   8   9   10");
        System.out.println("---------|-----------------------------------------");
        System.out.println("price pi | 1    5   8   9   10  17  17  20  24  30\n");
        System.out.println("Maximum value obtained is:"+cutRod(x,n)+"\n");
        
	        System.out.println("Length   Rev CR     Num Calls CR     RevMCR   Num calls MCR     Cut Pieces");
	         int num = 0;
	        for(int i=1;i<=10;i++)
	        {
	 num=i;
	         
	        RodCuttingProgram r_d = new RodCuttingProgram();
	         int y = r_d.Rod_Cut(x, num);
	       
	         RodCuttingProgram r_d1 = new RodCuttingProgram();
	         int d = r_d1.Memoized_Cut_Rod(x, num);
	          RodCuttingProgram rod = new RodCuttingProgram();
	         
	         System.out.print( "  "+ num+"\t  "+y+ "\t \t "+ct+"\t       "+d+"\t    "+a +"\t\t");   rod.PrintCutRodSolution(x, num);
	         System.out.print("\n");
	         
	         ct=0; 
	         a=0;
	       }
	   }
    int[] p = {1,5,8,9,10,17,17,20,24,30};
    public static int cutRod(int[]p, int n){	
		int q=0;		
		if(n<=0)
			return 0;	
		for(int i = 1; i <= n; i++)
		{

			q = Math.max(q,p[i]+cutRod(p,n-i));
		
			}
		
		return q;
		}
    
    
	   public static int ct=0,a=0;  

	   public int Rod_Cut(int x[], int num) throws Exception{
	      
	        ct++;
	        if(num >= x.length ){
	           
	            throw new Exception("rod of length can not grater than the price array length");        
	        }
	        if (num == 0) {
	            return 0;
	        }
	        int y = Integer.MIN_VALUE;
	        for (int p = 1; p <= num; p++) {
	            
	            y = Math.max(y, (x[p] + Rod_Cut(x, num - p)));
	        }
	         
	        return y;
	      
	    }
	   public int Memoized_Cut_Rod_Aux(int x[], int num, int z[]) throws Exception{
	       a++;
	       if(num >= x.length){
	          throw new Exception("rod of length can not grater than the price array length");        
	      }
	      int y;
	      if (z[num] >= 0) {
	          return z[num];
	      }
	      if (num == 0) {
	          y = 0;
	      } else {
	          y = Integer.MIN_VALUE;
	          for (int j = 1; j <= num; j++) {
	              y = Math.max(y, (x[j] + Memoized_Cut_Rod_Aux(x, num - j, z)));
	          }
	      }
	      z[num] = y;
	      return y;
	  }
	    public int Memoized_Cut_Rod(int x[], int num) throws Exception{       
	        if(num >= x.length){
	            throw new Exception("rod of length can not grater than the price array length");        
	        }
	        int z[] = new int[num + 1];
	        for (int p = 0; p <= num; p++) {
	            z[p] = Integer.MIN_VALUE;            
	        }     
	        return Memoized_Cut_Rod_Aux(x, num, z);
	    }
	    
	    public void PrintCutRodSolution(int[] x, int num)
	    {
	       BottomUpCutRod(x,num);
	        while (num > 0) {
	            System.out.print("  " +t[num]);
	            num = num - t[num];
	        }
	    }
	    public static int []z,t;
	    public void BottomUpCutRod(int[] x, int num)
	    {
	         z = new int[num+1];
	         t = new int[num+1];
	        for(int i=0;i<=num;i++){
	            z[i]=i;
	            z[i]=i;
	        }
	        for (int j = 1; j <= num; j++)
	        {
	            int result = 0;
	            for (int i = 1; i <= j; i++)
	            {
	                if (result < x[i] + z[j - i]) {
	                    result = x[i] + z[j - i];
	                    t[j] = i;
	                }
	            }
	            z[j] = result;
	        }
	    }
    }

