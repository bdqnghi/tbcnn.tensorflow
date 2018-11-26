package Java.Strings;

import java.util.Scanner;

public class Java_String_Reverse {
public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        if (isPalindrome(A)) {
			System.out.println("Yes");
		}
		else
			System.out.println("No");
		
	}
        public static boolean isPalindromee(String c)
	{
		
		int aa=0;
		int bb=c.length()-1;
		while (aa<bb) {
			if (c.toLowerCase().charAt(aa++)!=c.toLowerCase().charAt(bb--)) {
				return false;
			}
		}
		return true;
	}
	public static boolean isPalindrome(String c) {
		String chars=c.replaceAll("[^a-zA-Z]", "");
		return isPalindromee(chars);
	}
}
