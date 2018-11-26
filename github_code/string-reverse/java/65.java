package PROG3_Muppalla_Chandana;
/*We can use concept of recursion
 * call the function for n-1----0
 * the base condition is for string length n=0 return empty string
 * remaining cases read last character  and  concatenate that to a EmptyString and then concat other characters in that sequence 
 *Return the reversed String
 * */
public class Stringreverse {
	static	String  res=new String("");//Since every time we call the function if it is not static variable the concated characters will not restore
	public static String reverseString(int n,String s)
	{
		if(n==0)
		{

			return "";
		}
		res=res+s.substring(n-1,n);// Retrieving single character from back of the String
		reverseString(n-1,s);// calling the function with  n decrement

		return res;
	}

	public static void main(String args[])
	{
		String s="varshika";
		System.out.println(reverseString(s.length(),s));
	}
}
