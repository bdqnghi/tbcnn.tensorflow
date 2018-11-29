
public class EDITDISTANCE {
	int min(int x, int y, int z)
	{
	   return Math.min(Math.min(x, y), z);
	}
	 
	int editDist(String str1 , String str2 )
	{
	    int m=str1.length();
	    int n=str2.length();
	    int arr[][]=new int[m+1][n+1];
	    for(int i=0;i<=m;i++)
	    {
	    	arr[i][0]=i;
	    }
	    for(int i=1;i<=n;i++)
	    {
	    	arr[0][i]=i;
	    }
	    for(int i=1;i<=m;i++)
	    {
	    	for(int j=1;j<=n;j++)
	    	{
	    		if(str1.charAt(i-1)==str2.charAt(j-1))
	    		{
	    			arr[i][j]=arr[i-1][j-1];
	    		}
	    		else
	    		{
	    			arr[i][j]=Math.min(arr[i-1][j]+1,Math.min(arr[i][j-1]+1,arr[i-1][j-1]+1));
	    		}
	    		
	    	}
	    }
	    
	    return arr[m][n];
	}
	
}
