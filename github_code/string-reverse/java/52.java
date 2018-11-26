import java.util.Scanner;

public class Stringreverse {

    public static String reversal(String word) {

        String str;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a String: ");
        str = "";

        str = word;

        int l = str.length();
        String finaloutput = "";

        for ( int i = l - 1; i >= 0; i-- ) {
            System.out.print(str.charAt(i));
            finaloutput= finaloutput + str.charAt(i)+ " ";
        }

        finaloutput=finaloutput.trim();

        return finaloutput;
    }
}