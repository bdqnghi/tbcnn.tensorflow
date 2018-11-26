/*
 * Top K Frequent Elements
 * Tag: Hash Table
 * Tag: Heap
 */
import java.util.*;

public class TopKFrequentElements {
    public List<Integer> topKFrequent(int[] nums, int k) {
    	// Bucket-sort method
        Map<Integer, Integer> cnts = new HashMap<Integer, Integer>();
        Map<Integer, List<Integer>> cntLists = new HashMap<Integer, List<Integer>>();
        // Sort based on occurrence count, use bucket sort
        for(int num : nums) {
            int oriCnt = cnts.getOrDefault(num, 0);
            cnts.put(num, oriCnt + 1);
        }
        
        for(int num : cnts.keySet()) {
            int cnt = cnts.get(num);
            if(cntLists.get(cnt) == null) cntLists.put(cnt, new ArrayList<Integer>());
            cntLists.get(cnt).add(num);
        }
        
        List<Integer> res = new ArrayList<Integer>();
        for(int cnt = nums.length; cnt >= 0 && res.size() < k; cnt --)
            // NOTE: type: addAll cannot involve null
            if(cntLists.containsKey(cnt)) res.addAll(cntLists.get(cnt));
        
        return res;
        // TODO: heap-based method
    }
}
