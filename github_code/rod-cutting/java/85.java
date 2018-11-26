package rodCutting;

import java.util.ArrayList;
import java.util.Collections;

public class Main {

    // Choice of whether to display debug messages
    static final boolean DEBUG = true;

    // Choices of available rod-cutting functions
    static final int SIMPLE_RECURSIVE = 1;
    static final int DP_MEMOIZED = 2;

    // Function to use
//    static int functionChoice = SIMPLE_RECURSIVE;
    static int functionChoice = DP_MEMOIZED;

    /**
     * Main function, which runs the chosen function to compute
     * the optimal rod cutting positions.
     * @param args
     */
    public static void main(String[] args) {
        // Build an array of canned data, where data[i] gives the value
        // of a rod of length i units
        ArrayList<Integer> data = generateDataset();
        int rodLength = 7;

        // Get the start time
        long startNanos = System.nanoTime();

        // Find the optimal rod cuts
        RodCuttingSolution solution;
        switch (functionChoice) {
            case SIMPLE_RECURSIVE:
                solution = Solver.cutRod(data, rodLength);
                break;
            case DP_MEMOIZED:
                solution = Solver.cutRodMemoized(data, rodLength);
                break;
            default:
                System.out.println("Invalid function specified.");
                solution = new RodCuttingSolution(new ArrayList<Integer>(), 0);
                break;
        }

        // Get the end time and print out the duration
        long endNanos = System.nanoTime();
        long durationNanos = endNanos - startNanos;

        // Print the results
        if (DEBUG) {
            System.out.println("Rod-length values: " + data.toString() + "\n");
        }

        System.out.println("The function took " + String.valueOf(durationNanos / 1000000.0) + " milliseconds.");
        if (DEBUG) {
            System.out.println("Resulting lengths for a rode of length " + rodLength +
                               " (total value = " + solution.value + "): " +
                               solution.lengths.toString() + "\n");
        }
    }

    private static ArrayList<Integer> generateDataset() {
        int size = 11;
        ArrayList<Integer> data = new ArrayList<Integer>(size);

        int[] vals = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
        for (int i = 0; i < size; i++) {
            data.add(i, vals[i]);
        }

        return data;
    }
}
