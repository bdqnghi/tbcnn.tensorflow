package dp_2;

/**
 * Created by polarbear on 6/13/17.
 */
public class EditDistance_Jul02 {
    public static void main(String[] a) {//
        EditDistance_Jul02 mySolution = new EditDistance_Jul02();
        System.out.println(mySolution.editDistance("abbcc", "dbbcc"));

        System.out.println(mySolution.editDistance("abcabc", "dabacd"));
        System.out.println(mySolution.editDistance("abbcc", "dbbabc"));


    }
    public int editDistance(String one, String two) {
        if (one == null || two == null) {
            return 0;
        }

        if (one.length() == 0) {
            return two.length();
        }
        if (two.length() == 0) {
            return one.length();
        }

        int[][] editDistance = new int[one.length() + 1][two.length() + 1];
        for (int i = 0; i < editDistance.length; i++) {
            for (int j = 0; j < editDistance[0].length; j++) {
                if (i == 0 || j == 0) {
                    editDistance[i][j] = Math.max(i, j);
                } else {
                    if (one.charAt(i - 1) == two.charAt(j - 1)) {
                        editDistance[i][j] = editDistance[i - 1][j - 1];
                    } else {
                        int replace = 1 + editDistance[i - 1][j - 1];
                        int insert = 1 + editDistance[i][j - 1];
                        int delete = 1 + editDistance[i - 1][j];
                        editDistance[i][j] = Math.min(Math.min(replace, delete), insert);
                    }
                }

            }

        }
        return editDistance[editDistance.length - 1][editDistance[0].length - 1];

    }



}
