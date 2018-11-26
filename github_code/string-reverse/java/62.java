package Java.Strings.Easy;

import java.util.Scanner;

public class JavaStringReverse {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String word = sc.next();

        int i = 0;
        int j = word.length() - 1;
        boolean isPalindrome = true;
        while (i <= j) {
            if (word.charAt(i) != word.charAt(j)) {
                isPalindrome = false;
                break;
            }
            i++;
            j--;
        }
        System.out.println(isPalindrome ? "Yes" : "No");
    }
}
