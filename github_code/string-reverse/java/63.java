package category.topinterviewquestions.easy;

/**
 * 스트링 문자열을 역으로 변환하라
 *
 */
public class String_ReverseString {
    public static void main(String[] args) {
//        Input: "A man, a plan, a canal: Panama"
//        Output: "amanaP :lanac a ,nalp a ,nam A"

        String s = "A man, a plan, a canal: Panama";
        System.out.println(reverseStringByMe(s));
        System.out.println(reverseStringByAnswer1(s));

    }

    public static String reverseStringByMe(String s) {
        StringBuilder sb = new StringBuilder();
        char[] c = s.toCharArray();
        for (int i = c.length - 1; i >= 0; i--) {
            sb.append(c[i]);
        }
        return sb.toString();
    }

    public static String reverseStringByAnswer1(String s) {
        char[] word = s.toCharArray();
        int i = 0;
        int j = s.length() - 1;
        while (i < j) {
            char temp = word[i];
            word[i] = word[j];
            word[j] = temp;
            i++;
            j--;
        }
        return new String(word);
    }
    public static String reverseStringByAnswer2(String s) {
        return new StringBuilder(s).reverse().toString();
    }
}
