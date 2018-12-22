package codemonk.sorting.tle;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * @author Saurabh Dutta
 * @problemLink https://www.hackerearth.com/practice/algorithms/sorting/radix-sort/practice-problems/algorithm/monk-and-sorting-algorithm/
 */
public class MonkAndSortingAlgorithm {

    private static int maxLen;
    private static int chunkIndex;
    private static Map<String, String> actualInputMap;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());
        String[] input = br.readLine().split(" ");
        actualInputMap = new HashMap<>();
        maxLen = Integer.MIN_VALUE;
        for (int i = 0; i < N; i++) {
            maxLen = Math.max(maxLen, input[i].length());
        }
        char[] suffix = new char[maxLen];
        Arrays.fill(suffix, '0');
        String leftPad = new String(suffix);
        for (int i = 0; i < N; i++) {
            String number = leftPad.substring(input[i].length()) + input[i];
            actualInputMap.put(number, input[i]);
            input[i] = number;
        }
        chunkIndex = 1;
        StringBuilder output = new StringBuilder();
        while (5 * (chunkIndex - 1) < maxLen) {
            Arrays.sort(input, (o1, o2) -> {
                int start = Math.max(0, maxLen - 5 * chunkIndex);
                int end = Math.max(0, maxLen - 5 * (chunkIndex - 1));
                String sub1 = o1.substring(start, end);
                String sub2 = o2.substring(start, end);
                return Integer.compare(Integer.parseInt(sub1), Integer.parseInt(sub2));
            });
            chunkIndex++;
            output.append(printArray(input));
            output.append("\n");
        }
        System.out.println(output);

    }

    private static String printArray(String[] arr) {
        StringBuilder result = new StringBuilder();
        for (String item : arr) {
            result.append(actualInputMap.get(item) + " ");
        }
        return result.toString().trim();
    }

}
