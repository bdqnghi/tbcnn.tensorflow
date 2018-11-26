package com.etnos.algorithms;

/**
 * This java program reverses a string.
 * <p>
 * String "abc" -> "cba"
 */
public class ReverseString {
    public static void main(String[] args) {
        ReverseString reverseString = new ReverseString();
        String testString = "abc";
        String result = reverseString.reverseStringByStringBuilder(testString);
        System.out.println("reverseStringByStringBuilder " + testString + " result: " + result);

        result = reverseString.reverseStringByCharArrayAndStringBuilder(testString);
        System.out.println("reverseStringByCharArrayAndStringBuilder " + testString + " result: " + result);

        result = reverseString.reverseStringByCharArray(testString);
        System.out.println("reverseStringByCharArray " + testString + " result: " + result);

        result = reverseString.reverseStringRecursively(testString);
        System.out.println("reverseStringRecursively " + testString + " result: " + result);
    }

    /**
     * Reverse string using {@link StringBuilder#reverse()}
     * <p>
     * Complexity: O(n)
     *
     * @param str string to reverse. Can be null or empty
     * @return reversed string or empty string
     */
    protected String reverseStringByStringBuilder(String str) {
        if (str != null && str.length() > 0) {
            StringBuilder stringBuilder = new StringBuilder(str.length());
            return stringBuilder.append(str).reverse().toString();
        } else {
            return "";
        }
    }

    /**
     * Reverse string using custom logic. Use StringBuilder as a placeholder
     * <p>
     * Complexity: O(n)
     *
     * @param str string to reverse. Can be null or empty
     * @return reversed string or empty string
     */
    protected String reverseStringByCharArrayAndStringBuilder(String str) {
        if (str != null && str.length() > 0) {
            char[] defaultChars = str.toCharArray();
            StringBuilder stringBuilder = new StringBuilder(str.length());
            for (int i = defaultChars.length - 1; i >= 0; i--) {
                stringBuilder.append(defaultChars[i]);
            }
            return stringBuilder.toString();
        } else {
            return "";
        }
    }

    /**
     * Reverse string using custom logic. Use char[] as a placeholder
     * <p>
     * Complexity: O(n)
     *
     * @param str string to reverse. Can be null or empty
     * @return reversed string or empty string
     */
    protected String reverseStringByCharArray(String str) {
        if (str != null && str.length() > 0) {
            char[] defaultChars = str.toCharArray();
            int length = defaultChars.length;
            char[] reverseChars = new char[length];
            for (int i = length - 1, j = 0; i >= 0; i--, j++) {
                reverseChars[j] = defaultChars[i];
            }
            return String.valueOf(reverseChars);
        } else {
            return "";
        }
    }

    /**
     * Reverse string using recursion. See {@link String#charAt(int)} and {@link String#substring(int, int)}
     * <p>
     * Complexity: O(n)
     *
     * @param str string to reverse. Can be null or empty
     * @return reversed string or empty string
     */
    protected String reverseStringRecursively(String str) {
        if (str != null && str.length() > 0) {
            return str.charAt(str.length() - 1) + reverseStringByCharArray(str.substring(0, str.length() - 1));
        } else {
            return "";
        }
    }

}
