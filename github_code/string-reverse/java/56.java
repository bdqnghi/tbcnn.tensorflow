import java.util.Scanner;

public class StringReverse {
	public  char tempArr[];
	public char reversedArray[];
//	public String reversedString;
	
	public void reverse(String in)
	{ 
		String input = in;
		int length = input.length();
		//copy the contents from the string to array
		tempArr = new char[length];
		reversedArray = new char[length];
		
		for(int i=0;i<length;i++)
		{
			tempArr[i] = input.charAt(i);
	
		}
		//logic to reverse the string
		for(int i=0;i<length;i++)
		{
			reversedArray[i]=tempArr[length-i-1];
		}
	String reversedString =  new String(reversedArray);
		System.out.println("The final reversed string is"+" "+reversedString);
		
		
	}
public static void main(String args[])
{
	Scanner sc = new Scanner(System.in)	;
System.out.println("enter the string to reverse");
String in = sc.nextLine();
StringReverse obj = new StringReverse();
obj.reverse(in);

}
} 
