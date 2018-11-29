package rodCutting;

import java.util.ArrayList;

public class Solver {

    /**
     * Cuts the rod using the simple recursive solution.
     * @param valueByLength - a list of values for each rod length
     * @param rodLength - the total length of the rod to be cut
     */
    static RodCuttingSolution cutRod(ArrayList<Integer> valueByLength, int rodLength) {
        // Note: for problem 2a, you only need to return the correct value,
        // not the list of lengths, so you can still return new ArrayList<Integer>()
        // until you start 2c
    	if(rodLength == 0){
    		return new RodCuttingSolution(new ArrayList<Integer>(),0);
    	}
    	int best = Integer.MIN_VALUE;
    	ArrayList<Integer> cuts = new ArrayList<Integer>();
    	for(int i = 1; i <= rodLength; i++){
    		RodCuttingSolution sln = cutRod(valueByLength, rodLength - i);
    		if(valueByLength.get(i)+ sln.value > best){
    			cuts = sln.lengths;
    			cuts.add(i);
    		}
    		best = Math.max(best, valueByLength.get(i)+ sln.value);	
    	}
        return new RodCuttingSolution(cuts, best);
    }

    /**
     * Cuts the rod using the simple recursive solution.
     * @param valueByLength - a list of values for each rod length
     * @param rodLength - the total length of the rod to be cut
     */
    static RodCuttingSolution cutRodMemoized(ArrayList<Integer> valueByLength, int rodLength) {
        // Note: for problem 2b, you only need to return the correct value,
        // not the list of lengths, so you can still return new ArrayList<Integer>()
        // until you start 2c
    	RodCuttingSolution[] res = new RodCuttingSolution[rodLength + 1];
    	for(int i = 0; i <= rodLength; i++){
    		res[i] = new RodCuttingSolution(new ArrayList<Integer>(), Integer.MIN_VALUE);
    	}
        return cutRodMemoized(valueByLength, rodLength, res);
    }
    static RodCuttingSolution cutRodMemoized(ArrayList<Integer> valueByLength, int rodLength, RodCuttingSolution[] res){
    	if(res[rodLength].value >= 0){
			return res[rodLength];
		}
    	int q = Integer.MIN_VALUE;
		if(rodLength == 0){
			q = 0;
		}
		ArrayList<Integer> cuts = new ArrayList<Integer>();
		for(int i = 1; i <= rodLength; i++){
			RodCuttingSolution sln = cutRodMemoized(valueByLength, rodLength - i, res);
    		if(valueByLength.get(i)+ sln.value > q){
    			cuts = sln.lengths;
    			cuts.add(i);
    		}
			q = Math.max(q, valueByLength.get(i)+ sln.value);
		}
		res[rodLength] = new RodCuttingSolution(cuts, q);
		return res[rodLength];
    }
}
