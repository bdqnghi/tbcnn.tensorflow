/**
 * @author David Han & Keith Davis
 */
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Set;

/*
 * Least recently used cache algorithm
 * 
 * This algorithm replaces the data in the cache 
 * with the oldest last request.
 */


public class LRU extends CacheScheme {
	
	public int numCollisions(int cacheSize, String word){
		int collisionNum = 0;
		LinkedHashMap<Character, Data> cKeys = new LinkedHashMap<Character, Data>();
		char[] requests = word.toCharArray();
		for (int i = 0; i < word.length(); i++) {
			char currentKey = requests[i];
			if (cKeys.containsKey(requests[i])) {
				// character is already there
				char special = requests[i];
				cKeys.get(special).frequency++;
				Data newSpecial = new Data(special);
				newSpecial = cKeys.get(special);
				cKeys.remove(special);
				cKeys.put(special,newSpecial);
			} else {
				// character is not there
				if (cKeys.size() < cacheSize) {
					// cache is not full
					cKeys.put(requests[i], new Data(requests[i]));
				} else {
					// cache is full and character is not there
					Iterator iter = cKeys.keySet().iterator();
					cKeys.remove(iter.next());
					cKeys.put(requests[i],new Data(requests[i]));
					collisionNum++;
				}
			}
		}
		//System.out.println("LRU cache is " + cKeys.keySet());
		//System.out.println(collisionNum);
		return collisionNum;
	}
}

