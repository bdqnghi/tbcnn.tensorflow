package TextSearch;


/**
 * @author Stephan Graf
 * @since 11.05.17
 */
public class Levenshtein {
    /**
     * Determine if two words have a Levenshtein-distance of 1
     * Optimized for speed so the first word has to be one letter shorter than the second
     * Empty words are also permitted
     *
     * @param word1 first word. "" is also permitted
     * @param word2 second word (one letter longer than first
     *
     * @return true if the two words have a levensthein-distance of 1
     */
    public static boolean haveDistanceOne(String word1, String word2) {
        if (word1.length() + 1 != word2.length()) {
            return false;
        }
        int i = 0;
        int distance = 0;
        while (distance <= 1 && i < word1.length()) {
            if (word1.toCharArray()[i] != word2.toCharArray()[i + distance]) {
                distance++;
            } else {
                i++;
            }
        }
        return distance <= 1;
    }
}
