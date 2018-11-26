package DynamicProgramming.SequenceDP.Others;

/**
 * Created by yizhao on 5/18/15.
 */
public class RodCutting {
    public static void main(String args[]) {
        int[] price = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
        System. out.println(rodCutting(price, 1)); // 1
        System. out.println(rodCutting(price, 2)); // 5
        System. out.println(rodCutting(price, 3)); // 8
        System. out.println(rodCutting(price, 4)); // 10
        System. out.println(rodCutting(price, 5)); // 13
        System. out.println(rodCutting(price, 6)); // 17
        System. out.println(rodCutting(price, 7)); // 18
    }

    public static int rodCutting(int[] price, int RodLength) {
        // state:
        int f[] = new int[RodLength + 1];
        for (int i = 1; i <= RodLength; i++) {
            for (int j = 0; j < price.length; j++) {
                if (j < i) {
                    f[i] = Math. max(f[i], f[j] + price[i - 1 - j]);
                }
            }
        }
        return f[RodLength];
    }
}
