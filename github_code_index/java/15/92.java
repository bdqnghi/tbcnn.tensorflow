package Dynamic_Programming;

public class CuttingRodProblem {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int sizesAvailabletoCut[]={1,2,3,4};
		int values[]={2,5,7,8};
		int totalLengthDesired=5;// answer (2,5,5}  or (5,7};
		int mat[][]=new int[sizesAvailabletoCut.length+1][totalLengthDesired+1];
		
		maximizeCutRod(sizesAvailabletoCut,values,mat,totalLengthDesired);
		
	}

	
	public static void maximizeCutRod(int sizesAvailabletoCut[],int values[],int mat[][],int totalLengthDesired )
	{
		
		for(int i=0;i<totalLengthDesired+1;i++)
			mat[0][i]=0;
		
		for(int i=0;i<sizesAvailabletoCut.length+1;i++)
			mat[i][0]=0;

		
		for(int i=1;i<sizesAvailabletoCut.length+1;i++)
		{
			for(int j=1;j<totalLengthDesired+1;j++)
			{
		if(i>j)
		{
			mat[i][j]=mat[i-1][j];
		}
		else
		{
				mat[i][j]=Math.max(mat[i-1][j],values[i-1]+mat[i][j-i]);
				
		}
			}
		}
		
		
		for(int i=0;i<sizesAvailabletoCut.length+1;i++)
		{
			for(int j=0;j<totalLengthDesired+1;j++)
			{
				System.out.print(mat[i][j]+" ");
				
			}
			System.out.println();
		}
		
		System.out.println("Values participated to make maximum profit of length 5 and maximum value="+mat[sizesAvailabletoCut.length][totalLengthDesired]);

		int j=totalLengthDesired;
		for(int i=sizesAvailabletoCut.length;i>=0;)
		{
			if(i>0 && j>0 && mat[i][j]!=mat[i-1][j])
			{
				System.out.println(values[i-1]);
				
				j=j-i;
			}
			else
				i--;
			
			
		}
		}
		
		
	
}
