package com.zfwhub.algorithm.leetcode.backtracking;
import java.util.*;

// Backtrack template
// https://gist.github.com/rioshen/a92004a6223ca9d1bb36
// https://www.geeksforgeeks.org/backtracking-introduction/
// https://medium.com/@andreaiacono/backtracking-explained-7450d6ef9e1a
public class Backtrack {
    public static List<List<Object>> backtrack(int[] A) {
        // Set up a list of list to hold all possible solutions
        List<List<Object>> result = new LinkedList<List<Object>>();
        if (A == null || A.length == 0) {
            return result;
        }

        // As we need to recursively generate every solution,
        // a variable is needed to store single solution.
        List<Object> solution = new LinkedList<Object>();

        // The process of constructing the solution corresponds exactly to
        // doing a Depth-First-Search of the backtrack tree. Viewing backtracking
        // as a Depth-First-Search on a tree yields a natural recursive implementation
        // of the algorithm.
        dfs(result, solution, A, 0);
        return result;
    }

    private static void dfs(List<List<Object>> result, List<Object> solution, int[] A, int pos) {
        // For recursion, the first thing we need to think about is how to terminate it, i.e., base case.
        // Method isASolution() could be implemented as a private method which returns boolean,
        // or for simple test we can directly use the condition replace it, e.g., generate all subsets
        // we can write the condition: if (A.length == pos)
        if (isASolution(A, pos)) {
            // Because we use the variable - 'solution' to hold partial solution,
            // when this search is terminated, the variable must hold a complete
            // solution.
            // Same like isASolution, processSolution method should print, count or however
            // process the complete solution once it is constructed.
            processSolution(result, solution);
            return;
        }

        for (int i = pos; i < A.length; i++) {
            // Before Depth-First-Search, we should decide whether we need to prune searching
            // which means it's unnecessary to continue search along a wrong partial solution
            if (!isValid(A[i])) continue; // stop searching along this path

            // Add the ith element of the array into the partial solution.
            // Before searching, we need to record the latest element we are using
            // to build the solution tree. Method makeMove should be able to add A[i]
            // to the solution, i.e., solution.add(A[i])
            makeMove(solution, A[i]);

            // Right now, we are searching all possible solutions based on ith element.
            // Warning: remember as we've already added ith element, the last parameter
            // must be `i + 1`.
            dfs(result, solution, A, i + 1);

            // After searching based on ith element, take back the move and search another
            // possible partial solution.
            unmakeMove(solution, A[i]);
        }
    }

    
    
    
    private static void unmakeMove(List<Object> solution, int i) {
        solution.remove(solution.size()-1);
    }

    private static void makeMove(List<Object> solution, int i) {
        solution.add(i);
    }

    private static boolean isValid(int i) {
        return true;
    }

    private static void processSolution(List<List<Object>> result, List<Object> solution) {
        result.add(new ArrayList<>(solution));
    }

    private static boolean isASolution(int[] a, int pos) {
        return pos == a.length;//输出的是最后一个元素必须选择的子集。
    }
    
    public static void main(String[] args) {
        int[] A = new int[] {1,2,3,4};
        System.out.println(backtrack(A));
    }
}
