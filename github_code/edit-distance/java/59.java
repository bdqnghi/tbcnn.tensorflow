
public class EDITDISTANCE {
	static public void main(String Args[])
	{
		String one ="three";
		String two ="wow";
		int distance =EditDistances2(one,two);
		System.out.print(distance);
	}
	
	static int EditDistances2(String one,String two)
	{
		String[] words = one.split("");
		
		String[] words2 = two.split("");
		
		
		int table[][] = new int[words.length][words2.length];
		for(int k = 0; k<words.length;k++)
		{
			table[k][0]=k;
		}
		for(int k = 0; k<words2.length;k++)
		{
			table[k][0]=k;
		}
		for(int i=1;i<words.length;i++)
		{
			for(int j=1;j<words2.length;j++)
			{
				
				if(words[i].equals(words2[j])== true)
					{
						table[i][j] = table[i-1][j-1] ;
						
						
					}
				else if(table[i-1][j]<table[i][j-1]&& table[i-1][j-1]<table[i][j-1])
					{
						table[i][j] = table[i][j-1]+1;
					
					}
				else if(table[i-1][j]>table[i][j-1]&& table[i-1][j]>table[i-1][j-1] )
					{
						table [i][j] = table[i-1][j]+1;
					}
					else
					{
						table [i][j] = table[i-1][j-1]+1;
						
					}
				
				}
		}
		int temp = table[words.length-1][words2.length-1];
		return temp;
	}

	
}
