/**
 * Technique TI Ltd - Brazil
 * HackerRank
 * JavaStringReverse.java
 *
 * @author Ricardo A Harari - ricardo.harari@gmail.com
 * https://www.hackerrank.com/challenges/java-string-reverse
 *
 */

package samples.java;

import java.util.Scanner;

public class JavaStringReverse {
	
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        int i = A.length() / 2;
        String a1 = A.substring(0, i);
        if (i*2 != A.length()) i++;
        String a2 = new StringBuffer(A.substring(i, A.length())).reverse().toString();
        System.out.println(a1.equals(a2) ? "Yes" : "No");
        sc.close();
    }
}
