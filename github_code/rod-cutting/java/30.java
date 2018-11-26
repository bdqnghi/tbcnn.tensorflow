public class RodCutting{
    protected int[] prices;

    public RodCutting(int[] p){
        this.prices = p;
    }

    public int price(int ind){
        if (ind < 0)
            return 0;
        else if (ind >= this.prices.length)
            return this.prices[this.prices.length - 1];
        else
            return this.prices[ind];
    }

    public int cutRodRec(int n){
        if (n <= 0) return 0;
        int maxVal = Integer.MIN_VALUE;

        // Recursively cut the rod in different pieces and compare different
        // configurations
        for (int i = 0; i < n; i++){
            int subVal = this.price(i) + cutRodRec(n - i - 1);
            if(subVal > maxVal){
                maxVal = subVal;
            }
        }
        return maxVal;
    }

    /* Returns the best obtainable price for a rod of length n and
       price[] as prices of different pieces */
    public int cutRodDyn(int n){
        int[] val = new int[n+1];
        val[0] = 0;
        int i;
        int j;

        // Build the table val[] in bottom up manner and return the last entry
        // from the table
        for (i = 1; i <= n; i++){
            int maxVal = Integer.MIN_VALUE;
            for (j = 0; j < i; j++){
                int subVal = this.price(j) + val[i-j-1];
                if(maxVal < subVal)
                    maxVal = subVal;
            }
            val[i] = maxVal;
        }
        return val[n];
    }

    public static void main(String[] argv){
        int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
        int size = argv.length;
        RodCutting rc = new RodCutting(arr);
        int solution1 = rc.cutRodRec(size);
        int solution2 = rc.cutRodDyn(size);
        System.out.println(solution1 + " == " + solution2);
    }
}
