/**
 * Created by austinzhang on 12/7/16.
 */
public class LevenshteinDistance {

    //Implementation of Levenshtein Distance algorithm which is used to measure
    //the similarity between two strings
    //Information for implementing the algorithm was found here:
    //https://people.cs.pitt.edu/~kirk/cs1501/Pruhs/Fall2006/Assignments/editdistance/Levenshtein%20Distance.htm
    public static int levenshteinDistance(CharSequence firstSentence, CharSequence secondSentence) {
        int length1 = firstSentence.length() + 1;
        int length2 = secondSentence.length() + 1;

        // the array of distances
        int[] cost = new int[length1];
        int[] newcost = new int[length1];

        // initial cost of skipping prefix in String s0
        for (int i = 0; i < length1; i++) cost[i] = i;

        // dynamically computing the array of distances

        // transformation cost for each letter in s1
        for (int j = 1; j < length2; j++) {
            // initial cost of skipping prefix in String s1
            newcost[0] = j;

            // transformation cost for each letter in s0
            for (int i = 1; i < length1; i++) {
                // matching current letters in both strings
                int match = (firstSentence.charAt(i - 1) == secondSentence.charAt(j - 1)) ? 0 : 1;

                // computing cost for each transformation
                int cost_replace = cost[i - 1] + match;
                int cost_insert = cost[i] + 1;
                int cost_delete = newcost[i - 1] + 1;

                // keep minimum cost
                newcost[i] = Math.min(Math.min(cost_insert, cost_delete), cost_replace);
            }

            // swap cost/newcost arrays
            int[] swap = cost;
            cost = newcost;
            newcost = swap;
        }

        // the distance is the cost for transforming all letters in both strings
        return cost[length1 - 1];
    }
}