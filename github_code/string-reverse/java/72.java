package sample;

import java.util.Arrays;
import java.util.Scanner;

//Stringreverse class
public class JavaStringReverse {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String A = sc.next();
		char[] ch = new char[A.length()];
		int j = 0;
		for (int i = A.length() - 1; i >= 0; i--) {
			ch[j] = A.charAt(i);
			j++;
		}
		String s = Arrays.toString(ch).replace(",", "").replace(" ", "").replace("[", "").replace("]", "");
		System.out.println(s);
		if (Arrays.toString(ch).replace(",", "").replace(" ", "").replace("[", "").replace("]", "").equals(A)) {
			System.out.println("Yes");
		} else {
			System.out.println("No");                    
		}
	}

}
