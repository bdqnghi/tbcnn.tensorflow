import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Bubble {
    public static void main(String[] args) {
        //  Create a function that takes a list of numbers as parameter
        //  Returns a list where the elements are sorted in ascending numerical order
        //  Make a second boolean parameter, if it's `True` sort that list descending

        //  Example:
        System.out.println(bubble(new int[] {34, 12, 24, 9, 5}));
        //  should print [5, 9, 12, 24, 34]
        System.out.println(advancedBubble(new int[] {34, 12, 24, 9, 5}, true));
        //  should print [34, 24, 12, 9, 5]
    }

    public static String bubble(int[] numbers) {
        Arrays.sort(numbers);
        return Arrays.toString(numbers);
    }

    public static String advancedBubble(int[] numbers, boolean isDescending) {
        if (isDescending = true) {
            Arrays.sort(numbers);
            for (int i = 0; i < numbers.length / 2; i++) {
                int temp = numbers[i];
                numbers[i] = numbers[numbers.length - 1 - i];
                numbers[numbers.length - 1 - i] = temp;
            }
        } else {
            Arrays.sort(numbers);
            }
        return Arrays.toString(numbers);
    }
}
