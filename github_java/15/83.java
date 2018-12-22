package dsalgo;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * https://www.interviewbit.com/problems/rod-cutting/
 */
public class RodCuttingWoodenLog {

    long ans[][];
    int anscut[][];

    public static void main(String[] args) {
        System.out.println(new RodCuttingWoodenLog().rodCut(6, new ArrayList<Integer>(Arrays.asList(1, 2, 5))));
    }

    public ArrayList<Integer> rodCut(int len, ArrayList<Integer> cuts) {
        cuts.add(0);
        cuts.add(len);
        Collections.sort(cuts);
        ans = new long[cuts.size() + 1][cuts.size() + 1];
        anscut = new int[cuts.size() + 1][cuts.size() + 1];

        for (int i = 0; i < cuts.size(); i++)
            for (int j = 0; j < cuts.size(); j++) {
                ans[i][j] = -1;
                anscut[i][j] = -1;
            }

        solve(0, cuts.size() - 1, cuts);
        ArrayList<Integer> orderedCuts = findCuts(0, cuts.size() - 1, cuts);
        return orderedCuts;
    }

    private long solve(int cuti, int cutj, List<Integer> cuts) {
        //no cuts
        if (cutj - cuti <= 1)
            return ans[cuti][cutj] = 0;

        if (ans[cuti][cutj] != -1)
            return ans[cuti][cutj];

        long minCost = Long.MAX_VALUE;
        for (int i = cuti + 1; i <= cutj - 1; i++) {

            long cutCost = cuts.get(cutj) - cuts.get(cuti);

            long leftCost = solve(cuti, i, cuts);

            long rightCost = solve(i, cutj, cuts);

            long totalCost = cutCost + leftCost + rightCost;

            if (minCost > totalCost) {
                minCost = totalCost;
                anscut[cuti][cutj] = i;
            }
        }
        return ans[cuti][cutj] = minCost;
    }

    private ArrayList<Integer> findCuts(int i, int j, List<Integer> cuts) {
        if (anscut[i][j] == -1)
            return new ArrayList<Integer>();
        int k = anscut[i][j];
        ArrayList<Integer> toReturn = new ArrayList<>();
        toReturn.add(cuts.get(k));

        toReturn.addAll(findCuts(i, k, cuts));
        toReturn.addAll(findCuts(k, j, cuts));
        return toReturn;
    }

}
