
import java.util.Arrays;

public class RadixSort {

    private static int max(int[] nums) {

        int mx = Integer.MIN_VALUE;

        for (int n : nums) {
            mx = Math.max(mx, n);
        }

        return mx;

    }

    private static void sortCount(int[] nums, int mask) {

        int[] counts = new int[10];
        int[] out = new int[nums.length];

        for (int i = 0; i < nums.length; i++) {
            counts[(nums[i] / mask) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            counts[i] += counts[i - 1];
        }

        for (int i = nums.length - 1; i >= 0; i--) {
            out[counts[(nums[i] / mask) % 10] - 1] = nums[i];
            counts[(nums[i] / mask) % 10]--;
        }

        System.arraycopy(out, 0, nums, 0, nums.length);

    }

    public static void radixSort(int[] nums) {

        int m = max(nums);

        for (int mask = 1; m / mask > 0; mask *= 10) {

            sortCount(nums, mask);

        }

    }

    public static void main(String[] args) {

        int[] nums = new int[]{1, 52, 2, 25, 6, 10, 25, 200, 15, 12, 8, 2};

        System.out.println(Arrays.toString(nums));

        radixSort(nums);

        System.out.println(Arrays.toString(nums));

    }

}
