package practice.problems.strings;

/**
 * Performs string reverse.
 *
 * @author Yashraj R. Sontakke
 */
public class StringReverse {

    /**
     * Iterative approach
     */
    public String reverse(String input) {
        if (input == null || input.length() <= 1) {
            return input;
        }
        String output = "";
        for (int i = input.length() - 1; i >= 0; i--) {
            output = output.concat(Character.toString(input.charAt(i)));
        }
        return output;
    }

    /**
     * Recursive approach
     */
    public String reverseRecursive(String input) {
        if (input.length() <= 1) {
            return input;
        }
        return reverse(input.substring(1)) + input.charAt(0);
    }

    public static void main(String[] args) {
        StringReverse stringReverse = new StringReverse();
        String input = "YASHRAJ";
        System.out.println(String.format("%s reverse is %s", input, stringReverse.reverse(input)));
        System.out.println(String.format("%s reverse is %s", input, stringReverse.reverseRecursive(input)));
    }
}
