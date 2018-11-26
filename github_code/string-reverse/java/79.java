package ds;

/**
 * Created by sunilp on 2/16/18.
 */
public class ReverseString {
	private static String strToReverse="sunil";
	private static StringBuffer s = new StringBuffer();
	private static String tempStr="";

	public static void main(String[] args) {
		String tempStr = reverseWithoutLoop(strToReverse);
		System.out.println("The reversed string is: " + tempStr);
		//reverse(strToReverse);
		//String reversed = reverseString(strToReverse);
		//System.out.println("The reversed string is: " + reversed);
		//reverseUsingIndex(strToReverse);
	}

	private static String reverseWithoutLoop(String strToReverse) {

		if(strToReverse.length() > 0 ) {
			tempStr += strToReverse.substring(strToReverse.length()-1);
			strToReverse = strToReverse.replace(strToReverse.substring(strToReverse.length()-1),"");
			reverseWithoutLoop(strToReverse);
		}
		return tempStr;
	}

	public static String reverseString(String str)
	{
		if (str.isEmpty())
			return str;
		//Calling Function Recursively
		return reverseString(str.substring(1)) + str.charAt(0);
	}

	static void reverse(String str)
	{
		if ((str==null)||(str.length() <= 1))
			System.out.println(str);
		else
		{
			System.out.print(str.charAt(str.length()-1));
			reverse(str.substring(0,str.length()-1));
		}
	}

}
