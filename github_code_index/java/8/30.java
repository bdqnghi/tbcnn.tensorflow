package ru.gorbunov.test.algorithms.methods;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.AbstractMap;
import java.util.Map;

/**
 * Вычислите расстояние редактирования двух данных непустых строк длины не более 10^2,
 * содержащих строчные буквы латинского алфавита.
 */
public class EditDistance {

    public static void main(String[] args) throws IOException {
        final Map.Entry<String, String> words = getWords();
        final String firstWord = words.getKey();
        final String secondWord = words.getValue();
        final int[][] distanceMatrix = new int[firstWord.length() + 1][secondWord.length() + 1];
        distanceMatrix[0][0] = 0;
        for (int i = 1; i < distanceMatrix.length; i++) {
            distanceMatrix[i][0] = i;
        }
        for (int i = 1; i < distanceMatrix[0].length; i++) {
            distanceMatrix[0][i] = i;
        }

        for (int i = 1; i < distanceMatrix.length; i++) {
            for (int j = 1; j < distanceMatrix[0].length; j++) {
                distanceMatrix[i][j] = getDistanceValue(distanceMatrix[i][j - 1] + 1,
                        distanceMatrix[i - 1][j] + 1, distanceMatrix[i - 1][j - 1]
                                + getSwapValue(firstWord.charAt(i - 1), secondWord.charAt(j - 1)));
            }
        }

        System.out.println(distanceMatrix[distanceMatrix.length - 1][distanceMatrix[0].length - 1]);
//        for (int i = 0; i < distanceMatrix.length; i++) {
//            System.out.println(Arrays.toString(distanceMatrix[i]));
//        }

    }

    private static Map.Entry<String, String> getWords() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        final String firstWord = reader.readLine();
        final String secondWord = reader.readLine();
        return new AbstractMap.SimpleImmutableEntry<>(firstWord, secondWord);

//        return new AbstractMap.SimpleImmutableEntry<>("distance", "editing");
//        return new AbstractMap.SimpleImmutableEntry<>("ab", "ab");
//        return new AbstractMap.SimpleImmutableEntry<>("short", "ports");
    }

    private static int getDistanceValue(int insert, int delete, int swap) {
        return Math.min(Math.min(insert, delete), swap);
    }

    private static int getSwapValue(char first, char second) {
        return first == second ? 0 : 1;
    }
}
