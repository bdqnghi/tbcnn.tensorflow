/**
 * Given a rod of n inches and a table of prices. Write an algorithm to find maximum revenue
 * by cutting rod and selling pieces.
 *
 * Example:
 *
 * Length: 1  2  3  4  5  6  7  8  9  10
 * Price:  1  5  8  9  10 17 17 20 24 30
 *
 * For rod of length 4
 *
 * Ways to sell:
 *
 * Cut into 2,2 pieces - Price: 10
 * Cut into 1, 1, 1, 1 pieces - Price: 4
 * Cut into 3, 1 pieces - Price: 9
 * Cut into 2, 1, 1 pieces - Price: 7
 * 4 - Price: 9
 *
 * Naive Approach: Recursion
 *
 * 1) There can be n - 1 cuts made on the rod of length n.
 * 2) There are 2^n - 1 ways to cut rod
 * 3) For every length we have 2 options whether to cut the rod or not.
 *
 * Time Complexity: 2^n-1
 * But this complexity is very high since we are solving many subproblems repeatedly.
 *
 * resources/RodCuttingProblemOverlappingSubproblems.png
 *
 * Dynamic Programming:
 *
 * Bottoms up
 *
 * 1) Instead of solving problem again and again we can store the result in the array and use it.
 *
 */
public class RodCuttingProblem_DP {

    private static int rodCuttingProblemMaximumRevenue_UsingRecursion(int[] price, int rodLength) {

        if (rodLength <= 0) {
            return 0;
        }

        int max = -1;
        //Either we will cut the rod or not
        for (int i = 0; i < rodLength; i++) {

            max = Math.max(max, price[i] + rodCuttingProblemMaximumRevenue_UsingRecursion(price, rodLength - (i + 1)));
        }
        return max;
    }

    private static int rodCuttingProblemMaximumRevenue_DP(int[] price, int rodLength) {

        int[] solution = new int[rodLength + 1];
        solution[0] = 0;

        for (int i = 1; i <= rodLength; i++) {
            int max = -1;
            for (int j = 0; j < i; j++) {

                max = Math.max(max, price[j] + solution[i - (j + 1)]);
            }
            solution[i] = max;
        }

        return solution[rodLength];
    }

    public static void main(String[] args) {
        int[] value = { 2, 3, 7, 8, 9 };
        int len = 5;
        System.out.println("Max profit for length is " + len + ":"
                + rodCuttingProblemMaximumRevenue_UsingRecursion(value, len));

        System.out.println("Max profit for length is " + len + ":"
                + rodCuttingProblemMaximumRevenue_DP(value, len));
    }
}
