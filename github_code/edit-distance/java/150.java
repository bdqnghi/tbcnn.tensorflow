import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class EditDistance {
    Set<String> _dictionary;

    EditDistance() {
        _dictionary = new HashSet<String>();
        _dictionary.add("levenshtein");
        _dictionary.add("apple");
        _dictionary.add("banana");
        _dictionary.add("check");
        _dictionary.add("cacophonic");
        _dictionary.add("diamond");
        _dictionary.add("evenshtein");
        _dictionary.add("flower");
    }

    private void printMatrix(int[][] matrix) {
        for(int i = 0; i < matrix.length; ++i) {
            for(int j = 0; j < matrix[0].length; ++j) {
                System.out.print(String.format("%3d", matrix[i][j]));
            }
            System.out.println();
        }
    }

    private int getEditDistance(String s, String t) {
        int[][] matrix = new int[s.length() + 1][t.length() + 1];

        for(int i = 0; i <= s.length(); ++i) {
            matrix[i][0] = i;
        }
        for(int i = 0; i <= t.length(); ++i) {
            matrix[0][i] = i;
        }

        for(int i = 1; i <= s.length(); ++i) {
            for(int j = 1; j <= t.length(); ++j) {
                matrix[i][j] = Math.min(matrix[i-1][j] + 1, Math.min(matrix[i][j-1] + 1, matrix[i-1][j-1] + ((s.charAt(i-1) == t.charAt(j-1)) ? 0 : 1)));
            }
        }
        //printMatrix(matrix);
        return matrix[s.length()][t.length()];
    }

    public String getMatchForWord(String input, int threshold) {
        if(_dictionary.contains(input)) {
            System.out.println(input + " => " + input);
            return input;
        }

        Iterator iterator = _dictionary.iterator();
        int currentMinDistance = Integer.MAX_VALUE;
        String closestMatchingWord = "";

        while(iterator.hasNext()) {
            String currentWord = (String)iterator.next();
            int currentEditDistance = getEditDistance(input, currentWord);
            if(currentEditDistance < currentMinDistance) {
                currentMinDistance = currentEditDistance;
                closestMatchingWord = currentWord;
            }
        }

        if(currentMinDistance <= threshold) {
            System.out.println(input + " => " + closestMatchingWord);
            return closestMatchingWord;
        } else {
            System.out.println(input + " => no match");
            return "";
        }
    }

    public static void main(String[] args) {
        EditDistance editDistance = new EditDistance();

        editDistance.getMatchForWord("aple", 3);
        editDistance.getMatchForWord("bannaan", 3);
        editDistance.getMatchForWord("banan", 3);
        editDistance.getMatchForWord("levnsten", 3);
        editDistance.getMatchForWord("evnsten", 3);
        editDistance.getMatchForWord("babon", 3);
        editDistance.getMatchForWord("checkers", 2);

        System.out.println("Edit Distance Between BANDAR and BENS  => " + editDistance.getEditDistance("bandar", "bens"));
        System.out.println("Edit Distance Between DELIS  and DELHI => " + editDistance.getEditDistance("delhi", "delis"));
    }
}
