package assignment;
import java.util.Scanner;

public class Stringreverse {
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		String s;
		System.out.println("Please enter a string to reverse it:");
		s=sc.nextLine();
		System.out.println("Entered string is:"+s);
		int length=s.length();
		char[] temp=new char[length];
		for(int i=length-1,j=0;i>=0;i--,j++)
		{
			temp[j]=s.charAt(i);
		}
		String sr=new String(temp);
		System.out.println("Reversed string is:"+sr);
		
	}

}
