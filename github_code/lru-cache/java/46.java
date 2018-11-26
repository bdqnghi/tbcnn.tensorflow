import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
class LRU {

    public static int getNumberOfMisses(int[] a, int maxCacheSize) {

        int cacheMiss = 0;
        Map<Integer, Integer> cacheMap = new LinkedHashMap();
        int i = 0;
        List<Integer> list = new ArrayList<>();
        for (int k = 0; k < a.length; k++) {
            list.add(new Integer(a[k]));
        }
        while (list.size() > 0) {
            Integer value = list.remove(0);
            if (cacheMap.get(value) != null) {
                // If it contains no miss. Move the element to first
                cacheMap.remove(value);
                // So this will be the younger value
                cacheMap.put(value, value);
            }

            if (cacheMap.get(value) == null) {
                cacheMiss++;
                // If its null check if any value needs to be removed based on
                // cachesize.
                if (cacheMap.size() == maxCacheSize) {
                    // Then a cache is full. Remove the oldest entry.
                    Iterator cacheIterator = cacheMap.entrySet(). ();
                    Map.Entry<Integer, Integer> toRemove = (Entry<Integer, Integer>) cacheIterator.next();
                    cacheMap.remove(toRemove.getKey());
                    // Now add the new data
                    cacheMap.put(value, value);
                } else {
                    // Cache is not full but there is no data
                    // So load the data in cache
                    cacheMap.put(value, value);
                }

            }

        }

        return cacheMiss;
    }

    public static void main(String[] arr) {
        int[] a = { 2, 3, 1, 3, 2, 1, 4, 3, 2 };
        int result = getNumberOfMisses(a, 2);
        System.out.println("Cachce Miss" + result);
    }
}