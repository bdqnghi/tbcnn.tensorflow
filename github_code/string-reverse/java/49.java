/**
 * Created by ovidiu on 06.12.2016.
 */
public class StringReverseExample {

    public static void main(String args[]) {

        //With StringBuffer
        String word = "HelloWorld";
        String reverse = new StringBuffer(word).reverse().toString();
        System.out.printf("Original String: %s, reversed String %s %n", word, reverse);

        //With StringBuilder

        word = "WakeUp";
        reverse = new StringBuilder(word).reverse().toString();
        System.out.printf("Original String: %s, reversed String %s %n", word, reverse);

        word = "Own Implementation";
        reverse = reverse(word);
        System.out.printf("Original String: %s, reversed String %s %n", word, reverse);

    }

    public static String reverse(String source){
        if(source == null || source.isEmpty()){
            return source;
        }
        String reverse = "";
        for(int i = source.length() -1; i>=0; i--){
            reverse = reverse + source.charAt(i);
        }
        return reverse;

    }
}
