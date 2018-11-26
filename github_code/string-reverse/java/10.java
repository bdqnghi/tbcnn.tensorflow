
public class Stringreverse {

	public static void main(String arg[])
	{
		
		String str = " ashish is good boy ";
		
		for( int i = 0 ; i < str.length(); i++ )
		{
			if( (str.charAt(i) == ' ') /*|| (i == str.length()-1)*/ )
			{
//				int p = i-1;
				
/*				if(i == str.length()-1 )
				{
					p = i;
				}*/
				
				for( int j = i-1 ; j >=0 ; j-- )
				{
					System.out.print(str.charAt(j));
					
					if( str.charAt(j) == ' ' /*|| j == 0*/ )
					{
	//					System.out.print(" ");
						break;
					}
					
				}
			}
		}
	}
	
}
