/**
 * Class that calculates the edit distance between two strings, given by counting the minimum number of operations
 * needed to transform one string into the other, where an operation is defined as an insertion, deletion, or
 * substitution of a single character, or a transposition of two adjacent characters.
 *
 * @author Bart Bussmann
 * @since 3-3-2017
 */
public class EditDistance implements StringDistance {

    //class variables
    private String string1;
    private String string2 ;

    //constructor
    public EditDistance(String str1, String str2){
        string1 = str1;
        string2 = str2;
    }

    /**
     * method that calculates the edit distance between two strings.
     * @return edit distance between string1 and string2.
     */
    public double distance() {

        //initialize the distance matrix, where dist_matrix[i][j] will contain the edit-distance between
        //string1[0..i-1] and string2[0..j-1].
        int[][] dist_matrix = new int[string1.length() + 1][string2.length() + 1];

        //if string1 is empty, the distance is the length of the string2.
        if (string1.length() == 0) {
            return string2.length();
        }
        //if string2 is empty, the distance is the length of the string1.
        else if (string2.length() == 0) {
            return string1.length();
        }
        //if both strings are the same, the distance is 0.
        else if (string1 == string2) {
            return 0;
        }
        else {
            //the edit-distance between an empty string and string1[0..i-1] is i (i * insertions)
            for (int i = 0; i < string1.length() + 1; i++) {
                dist_matrix[i][0] = i;
            }

            //the edit-distance between an empty string and string2[0..j-1] is j (j * insertions)
            for (int j = 0; j < string2.length() + 1; j++) {
                dist_matrix[0][j] = j;
            }
            //the rest of the distance matrix is filled dynamically
            for (int i = 1; i < string1.length() +1; i++) {
                for (int j = 1; j < string2.length() +1; j++) {

                    //for every necessary edit, we add 1 to the total distance
                    int cost = 1;
                    //but if the characters are the same, substitution and transposition edits are not counted.
                    if (string1.charAt(i-1) == string2.charAt(j-1)) {
                        cost = 0;
                    }
                    //the total distance for insertion, deletion, and substitution are calculated.
                    int insertion_dist = dist_matrix[i][j - 1] + 1;
                    int deletion_dist = dist_matrix[i - 1][j] + 1;
                    int substitution_dist = dist_matrix[i - 1][j - 1] + cost;

                    //we insert the minimum value of the three edits in the distance matrix.
                    dist_matrix[i][j] = Math.min(Math.min(insertion_dist, deletion_dist), substitution_dist);

                    //but it is also possible to do a transposition edit when two adjacent characters are the same
                    if (i > 1 && j > 1 && (string1.charAt(i-1) == string2.charAt(j - 2)
                            && string1.charAt(i - 2) == string2.charAt(j - 1))) {
                        int transpos_dist = dist_matrix[i - 2][j - 2] + cost;
                        //this value is inserted in the distance matrix if it is smaller than the current matrix.
                        if (transpos_dist < dist_matrix[i][j]) {
                            dist_matrix[i][j] = transpos_dist;
                        }
                    }
                }
            }
        }
        //the value of the distance matrix where i is the length of string1 and j is the length of string2 is returned.
        return dist_matrix[string1.length()][string2.length()];
    }
}