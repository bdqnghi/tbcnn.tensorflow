/* Unlike Divide-and-Conquer, Dynamic Programming(DP) applies when the subproblems overlap - that is subproblems share subproblems.
  In this context, DP solves each subproblems just once and saves its answer in a table, thereby avoiding the work for recomputing the answer
  every time it solves each subproblem. DP is especially useful for optimization problems, which is to find the best solution among many possible
  solutions. 
  
  -     When developing a dynamic-programming algorithm, we follow a sqeuence of four steps:

        1) Characterize the stucture of an optimal solution.
        2) Recursively define the value of an optimal solution.
        3) Compute the value of an optimal solution, typically in a bottom-up fashion.
        4) Construct an optimal solution from computed information.

  -     Rod Cutting  

        The rod-cutting problem is the following. Given a rod of length n inches and a
        table of prices pi for i = 1,2...,n, determine the maximum revenue rn obtain-
        able by cutting up the rod and selling the pieces.

        If an optimal solution cuts the rod into k pieces, for some 1 <= k <= n, then an optimal decomposition
        
        n = i1 + i2 + ... + ik

        of the rod into pieces of length i1, i2, ..., ik provides maximum corresponding revenue

        rn = pi1 + pi2 + ... + pik

        (note: again, rn is the maximum corresponding revenue, not just the revenue)

        originally, we consider cutting the rod into two pieces(the first cut):

        rn = max(pn, r1+rn-1, r2+rn-2,...,rn-1 + r1)

        
        pn:                              corresponds to making no cuts at all and selling the rod of length n as is.
        r1+rn-1, r2+rn-2,...,rn-1+r1:    the other n-1 arguments to max correspond to the maximum revenue obtained
                                         an initial cut of the rod into two pieces of size i and n-i for each i = 1, 2, ..., n-1
                                         and then optimally cutting up those pieces further.

        Once we make the first cut, we may consider the two pieces as independent instances of the rod-cutting problem. So now, two related
        subproblems are exposure to us and we need the revenue from each of those two pieces.

        In a related, but slightly simpler, we view a decomposition as consisting of a first piece of length i cut off and left-hand end remainder
        of length n-i. Only the remainder, and not the first piece, maybe further divided:

        rn = max(pi + rn-i)   (15.2)
            1<=i<=n

        In this formulation, an optimal solution embodies the solution to only one related subproblem - the remainder - rather than two.

        -   Recursive top-down implementation

            The following procedure implements the computation implicit in equation (15.2)

            CUT-ROD(p,n)
            1   if n == 0
            2       return 0
            3   q = -inf
            4   for i = 1 to n
            5       q = max(q, p[i] + CUT-ROD(p, n-i))
            6   return q

            The O(CUT-ROD(p,n)) is 2.^n, which is exponential in n. (?? How to prove it)

        -   Using dynamic programming for optimal rod cutting

            The dynamic-programming method works as follows: Having observed that a naive recursive solution is inefficient because it
            solves the same sub-problems repeatedly, we arrange for each subproblem to be solved only once, saving its solution. If we
            need to refer to this subproblem's solution again later, we can just look it up, rather than recompute it. It serves an
            example of a time-memory trade-off. It transfers a exponential solution into a polynomial time when the number of distinct
            subproblems involved is polynomial in the input size and we can solve each subproblem in polynomal time.

            There are usually two equivalent ways to implement a dynamic-programming approach:

            1) top-down with memorization
        
            step 1: checks to see whether it has previously solved this subproblem. It so, it returns the saved value in the usual manner. 
            step 2: if not, the procedure computes the value in the usual manner.

            The reason why we called "memorization" is because it "remembers" what results it has computed previously.

            MEMORIZED-CUT-ROD(p,n)
            1   let r[0...n] be a new array
            2   for i=0 to n
            3       r[i] = -inf
            4   return MEMORIZED-CUT-ROD-AUX(p,n,r)

            MEMORIZED-CUT-ROD-AUX(p,n,r)
            1   if r[n]>=0
            2       return r[n] //return the result right away as it has been computed before
            3   if n == 0
            4        q = 0
            5   else q = -inf
            6       for i = 1 to n
            7           q = max(q, p[i] + MEMORIZED-CUT-ROD-AUX(p,n-i,r))
            8   r[n] = q
            9   return q
            

            2) bottom-up method

            we sort the particular subproblem by size and solve them in size order, smallest first. When solving a particular subproblem, 
            we have already solved all of the smaller subproblems its solution depends upon, and we have saved their solutions. We solve 
            each sub-problem only once, and when we first see it, we have already solved all of its prerequisite subproblems.

            Comparing to MEMORIZED method, the bottom-up version is even simpler

            BOTTOM-UP-CUT-ROD(p, n)
            1   let r[0..r] be a new array
            2   r[0] = 0
            3   for j = 1 to n
            4       q = -inf
            5       for i = 1 to j
            6           q = max(q, p[i] + r[j-i])
            7       r[j] = q
            8   return r[n]
            
        
*/ 

import java.util.*;
import java.lang.Integer;
import java.lang.Math;

public class dynamic {


    public static int memorized_cut_rod(int[] p, int n) {
        //Create a new array r[0..n]. It initializes a new auxilary array r[0..n] with value -inf
        int[] r = new int[n+1];
        for (int i = 0; i <= n; i++) {
            r[i] = Integer.MIN_VALUE;
        }

        int q = memorized_cut_rod_aux(p, n, r);

        for (int j : r) {
            System.out.println("j = " + j);
        }
        
        return q;
    }

    /*
    *
    *   parameter:  p:  the price array for different lengths of rod
    *               n:  the length of the rod
    *               r:  the auxiliary array. Each element stores the maximum revenue of selling a piece with the length of i
    */

    public static int memorized_cut_rod_aux(int p[], int n, int[] r) {

        //checks to see whether it has previously solved this subproblem. It so, it returns the saved value in the usual manner. 
        if (r[n] >= 0) {
            System.out.println("A previously solved subproblem is found. n = " + n);
            return r[n];
        }

        int q;

        //check if the length is 0. If so, there is nothing to sell. The price is 0 of course
        if (n == 0) {
            q = 0;
        } else {
            q = Integer.MIN_VALUE;
            for (int i = 1; i <= n; i++) {
                //In a related, but slightly simpler, we view a decomposition as consisting of a first piece of length i cut off 
                //and left-hand end remainder of length n-i. Only the remainder, and not the first piece, maybe further divided:
                q = Math.max(q, p[i] + memorized_cut_rod_aux(p, n-i, r));
            }

            r[n] = q;
        }

        return q;
    }

    public static int bottom_up_cut_rod(int p[], int n) {
        //Let r[0..n] be a new array
        int[] r = new int[n+1];
        r[0] = 0;
        
        int q;
        for (int j = 1; j <= n; j++) {
            q = Integer.MIN_VALUE;
            for (int i = 1; i <= j; i++) {
                q = Math.max(q, p[i] + r[j-i]);
            }
            r[j] = q;
        }

        return r[n];
    }

    public static void main(String[] args) {

        /*
        *
        *   length i    |0|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10|
        *   price pi    |0|  1|  5|  8|  9| 10| 17| 17| 20| 24| 30|
        */
        //The length is 11
        int[] p = new int[]{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
        
        //int q = memorized_cut_rod(p, 3);
        int q = bottom_up_cut_rod(p, 3);

        System.out.println("q = " + q);
    }
}
