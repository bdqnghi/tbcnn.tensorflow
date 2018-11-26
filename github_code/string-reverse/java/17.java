package Java.Strings;

import java.util.Scanner;

/**
 * <p>
 * A palindrome is a word, phrase, number, or other sequence of characters which reads the same
 * backward or forward.(Wikipedia)
 *
 * <p>
 * Given a string <em>A</em> print <em>Yes</em> if it is a palindrome, print <em>No</em> otherwise.
 *
 * <p>
 * <strong>Constraints</strong>
 * <ul><li><em>A</em> will consist at most <em>50</em> lower case english letters.</li></ul>
 *
 * <p>
 * <strong>Sample Input</strong>
 * <div><code>  madam</code></div>
 *
 * <p>
 * <strong>Sample Output</strong>
 * <div><code>  Yes</code></div>
 *
 * @author code36u4r60
 */
public class JavaStringReverse {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String A = sc.next();
        String B = new StringBuilder(A).reverse().toString();
        System.out.println(A.equalsIgnoreCase(B) ? "Yes" : "No");
    }

}
