import java.util.HashMap;

/*
Various Implementations of the Rod-Cutting problem.
The Rod-Cutting problem can be stated as,
"Given a rod of length n inches and a table of prices p(i) for i = 1,2,...n,
determine the maximum revenue r(n) obtainable by cutting up the rod and selling the pieces."
 */
public class RodCut {
    public static void main(String args[]){
        HashMap<Integer, Integer> prices = new HashMap<Integer, Integer>();
        prices.put(1,1);
        prices.put(2,5);
        prices.put(3,8);
        prices.put(4,9);
        prices.put(5,10);
        prices.put(6,17);
        prices.put(7,17);
        prices.put(8,20);
        prices.put(9,24);
        prices.put(10,30);

        // correctness & timing examples
        System.out.println("Max. Revenue for n = 8 using Memoization: "+Utilities.time(() -> rodCutMemo(prices, 8)));
        System.out.println("Max. Revenue for n = 8 using Recursion: "+Utilities.time(() -> rodCutRecursive(prices, 8)));
        System.out.println("Max. Revenue for n = 8 using DP: "+Utilities.time(() -> rodCutDP(prices, 8)));
    }

    /*
    A General Recursive solution, which is not efficient with larger values of rodLength.

    Pseudocode:
        CUT-ROD(p, n)
            if n == 0
                return 0
            q = -INFINITY
            for i = 1 to n
                q = max(q, p[i] + CUT-ROD(p, n - i))
            return q
     */

    /*
    Given: the table of prices and the length of the rod.
    Returns: the maximum revenue that can be obtained from cutting/not cutting the rod.
     */
    public static int rodCutRecursive(HashMap<Integer, Integer> prices, int rodLength){
        // base case when rodLength is 0, revenue is 0.
        if( rodLength == 0){
            return 0;
        }
        // start with revenue to be -INFINITY
        int revenue = Integer.MIN_VALUE;
        // loop runs from 1 to given rodLength
        for(int i = 1; i <= rodLength; i++){
            // rod is cut into 2 parts,  one of length i and the rest
            // the revenue for both parts is calculated, added and compared with the max revenue so far,
            // this is done recursively for each rod length.
            revenue = Math.max(revenue, prices.get(i) + rodCutRecursive(prices, rodLength - i));
        }
        return revenue;
    }

    /*
    A Memoized solution, which is very efficient with larger values of rodLength.

    Pseudocode:
        MEMOIZED-CUT-ROD(p, n)
            let r[0..n] be a new array
            for i = 0 to n
                r[i] = -INFINITY
            return MEMOIZED-CUT-ROD-AUX(p, n, r)

        MEMOIZED-CUT-ROD-AUX(p, n, r)
            if r[n] >= 0
                return r[n]
            if n == 0
                q = 0
            else q = -INFINITY
                for i = 1 to n
                    q = max(q, p[i] + MEMOIZED-CUT-ROD-AUX(p, n - i, r))
            r[n] = q
            return q
     */

    /*
    Given: the table of prices and the length of the rod.
    Returns: the maximum revenue that can be obtained from cutting/not cutting the rod.
     */
    public static int rodCutMemo(HashMap<Integer, Integer> prices, int rodLength){
        // initialise an array of length rodLength + 1
        int[] memo = new int[rodLength + 1];
        for(int i = 0; i < memo.length; i++){
            // let each initial value be set as -INFINITY
            memo[i] = Integer.MIN_VALUE;
        }
        return rodCutMemo(prices, rodLength, memo);
    }

    /*
    Given: the table of prices, the length of the rod and an int array which stores previous computations.
    Returns: the maximum revenue that can be obtained from cutting/not cutting the rod.
     */
    public static int rodCutMemo(HashMap<Integer, Integer> prices, int rodlength, int[] memo){
        // start with revenue to be -INFINITY
        int revenue = Integer.MIN_VALUE;

        // if memo contains result for corresponding length
        // further computations are not required and result in array at index rodLength is returned.
        if(memo[rodlength] >= 0){
            return memo[rodlength];
        }
        // base case when rodLength is 0, revenue is 0.
        else if(rodlength == 0){
            return 0;
        }
        // if result has not been computed before, compute result
        else{
            // loop runs from 1 to given rodLength
            for(int i = 1; i <= rodlength; i++){
                // rod is cut into 2 parts,  one of length i and the rest
                // the revenue for both parts is calculated, added and compared with the max revenue so far,
                // this is done recursively for each rod length.
                revenue = Math.max(revenue, prices.get(i) + rodCutMemo(prices, rodlength - i, memo));
            }
        }
        // store the result in the memo array at index rodLength
        memo[rodlength] = revenue;
        return revenue;
    }

    /*
    A Dynamic Programming solution, which is very efficient with larger values of rodLength.

    Pseudocode:
        EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
            let r[0..n] and s[0..n] be new arrays
            r[0] = 0
            for j = 1 to n
                q = -INFINITY
                for i = 1 to j
                    if q < p[i] + r[j - i]
                        q = p[i] + r[j - i]
                        s[j] = i
                r[j] = q
            return r and s
     */

    /*
    Given: the table of prices and the length of the rod.
    Returns: the maximum revenue that can be obtained from cutting/not cutting the rod.
     */
    public static int rodCutDP(HashMap<Integer, Integer> prices, int rodLength){
        // table that stores the max revenue for an equivalent length.
        HashMap<Integer, Integer> revenues = new HashMap<Integer, Integer>();
        // array to store the solution pieces for the max revenue
        int[] solution = new int[rodLength];
        // base case when rodLength is 0, revenue is 0.
        revenues.put(0,0);
        // outer loop runs from 1 upto given rodLength
        for(int i = 1; i <= rodLength; i++){
            int revenue = Integer.MIN_VALUE;
            // inner loop runs upto the length under consideration
            // this ensures, that the max revenue for a length has been calculated
            // before it is accessed for higher lengths.
            for(int j  = 1; j <= i; j++){
                // add price to the result computed for the other half.
                // since both loops are in ascending order, we wont come across a length that
                // hasn't been calculated or the base case.
                if(revenue < prices.get(j) + revenues.get(i - j)) {
                    revenue = prices.get(j) + revenues.get(i - j);
                    // store the length of the piece with max. revenue in the solution array
                    solution[i - 1] = j;
                }
            }
            // store the result in the memo array at index rodLength
            revenues.put(i, revenue);
        }
        // prints the solution of pieces to the maximum revenue
        printSolution(solution, rodLength);
        return revenues.get(rodLength);
    }

    /*
    Pseudocode:
        PRINT-CUT-ROD-SOLUTION(p, n)
            (r, s) = EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
            while n > 0
        print s[n]
        n = n - s[n]
    */

    /*
    Given: the solution of pieces and the length of the rod.
    Effect: prints the solution to the screen.
     */
    public static void printSolution(int[] sol, int n){
        System.out.print("The Solution for length "+ n +" is: ");
        while(n > 0){
            System.out.print(sol[n - 1]+"\t");
            n = n - sol[n - 1];
        }
        System.out.println();
    }
}
