//cannot pass the test, as the remove takes time.
//see http://oj.leetcode.com/discuss/397/does-anyone-solve-it-by-using-java-got-tle


public class LRUCache {
    public class Entry{
        int key;
        int value;
        public Entry(int key, int value){
            this.key = key;
            this.value = value;
        }
    }
    
    LinkedList<Entry> queue;
    int curNum, maxCap;
    HashMap<Integer, Entry> map;
    
    public LRUCache(int capacity) {
        curNum = 0;
        maxCap = capacity;
        queue = new LinkedList<Entry>();
        map = new HashMap<Integer, Entry>();
    }
    
    public int get(int key) {
        if(map.containsKey(key)){
            //return map.get(key).value;
            Entry ent = map.get(key);
            queue.remove(ent);
            queue.addFirst(ent);
            return ent.value;
        }
        else{
            return -1;
        }
    }
    
    public void set(int key, int value) {
        if(map.containsKey(key)){
            Entry ent = map.get(key);
            ent.value = value;
            queue.remove(ent);
            queue.addFirst(ent);//replace ent at the first place
        }
        else{
            if(curNum < maxCap){//insert a new entry
                Entry ent = new Entry(key, value);
                map.put(key, ent);
                queue.addFirst(ent);
                ++curNum;
            }
            else{
                Entry ent = new Entry(key, value);
                Entry oldEnt = queue.removeLast();
                map.remove(oldEnt.key);
                map.put(key, ent);
                queue.addFirst(ent);
            }
        }
    }

}
