class Solution {
    // a sorted key-value pair data structure: TreeMap(red-black tree)
    // or, using a heap of key value pairs?
    public List<Integer> topKFrequent(int[] nums, int k) {
        // key value which records the frequency of numbers
        Map<Integer, Integer> count = new HashMap<>();
        
        for(int num : nums){
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        // Use frequency as key, list of numbers that have a given frequency as value
        // Have to tell the compiler that it is a treemap so that we could use its specific methods
        TreeMap<Integer, List<Integer>> myMap = new TreeMap<Integer, List<Integer>>(new Comparator<Integer>(){
            public int compare(Integer i1, Integer i2){
                return i2 - i1;
            }
        });
        
        for(int num : count.keySet()){
            int frequency = count.get(num); // get the frequency
            if(myMap.containsKey(frequency)){
                myMap.get(frequency).add(num);
            }
            else{
                List<Integer> temp = new ArrayList<>();
                temp.add(num);
                myMap.put(frequency, temp);
            }
        }
        
        List<Integer> res = new ArrayList<>();
        while(res.size() < k){
            Map.Entry<Integer, List<Integer>> entry = myMap.pollFirstEntry();
            res.addAll(entry.getValue());
        }
        
        return res;
    }
}

/**
 * There are at least three ways to get the top K frequent elements:
 * (1) bucket approach, as we know the range of frenquency(1 to n)
 * (2) Max Heap approach, store the Map.Entry(a pair), using customized comparator
 * (3) Using treeMap(red-black-tree implementation), with frequency as key
 * 
 * I use the third one here
 */

 // Time Complexity: O(nlogn)
 // O(n) for building the hashmap, and for each key in hashmap, we check its existence 
 // and apply get methods. The average contain check and get is O(logn), so the total running 
 // time is bound by O(nlogn)

 // Space Complexity: O(n), because there are n elements

 // Error-prone points:
 // 1. If we want to use methods specific in a class(like pollFirstEntry in TreeMap), we have 
 // to declare the data structure as TreeMap instead of Map!
 // 2. To get k frequent, we need to use frequency as key instead of each number

 // Syntax:
 // 1. TreeMap Interface: (1) pollFirstEntry (2) pollLastEntry (3)decendingKeySet() (4) keySet()
 // 2. Add collection of elements to the list: addAll(Collection<? extends E> c)