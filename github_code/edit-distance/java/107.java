import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * User: Dmitriy Bandurin
 * Date: 12.12.11
 * Time: 17:07
 */
public class LevenshteinDistance {
    public static void main(String[] args) throws IOException {
        final InputStreamReader in = new InputStreamReader(System.in);
        final BufferedReader bufferedReader = new BufferedReader(in);
        final String firstString = bufferedReader.readLine().trim();
        final String secondString = bufferedReader.readLine().trim();
        int[][] mass = new int[firstString.length() + 1][secondString.length() + 1];
        mass[0][0] = 0;

        for(int str = 1; str <= firstString.length(); str++){
            mass[str][0] = mass[str - 1][0] + 1;
        }

        for(int col = 1; col <= secondString.length(); col++){
            mass[0][col] = mass[0][col - 1] + 1;
        }

        for(int i = 1; i <= firstString.length(); i++){
            final char firstChar = firstString.charAt(i - 1);
            for(int j = 1; j <= secondString.length(); j++) {
                final char secondChar = secondString.charAt(j - 1);
                mass[i][j] = Math.min(Math.min(mass[i - 1][j - 1] + (firstChar == secondChar ? 0 : 1), mass[i - 1][j] + 1), mass[i][j - 1] + 1);
            }
        }
        System.out.println(mass[firstString.length()][secondString.length()]);
    }
}
