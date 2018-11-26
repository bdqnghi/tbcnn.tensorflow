class LRUCache {

    private LinkedHashMap<Integer, Integer> map;
	private int capacity = 0;

	public LRUCache(int capacity) {
		this.capacity = capacity;
		map = new LinkedHashMap<>(capacity, 0.75f, true);
	}

	public int get(int key) {
		Integer val = map.get(key);
		if(val == null){
			return -1;
		}
		return val;
	}

	public void put(int key, int value) {
		map.put(key, value);

		while (map.size() > capacity) {
			Iterator<Map.Entry<Integer, Integer>> i = map.entrySet().iterator();
			if (i.hasNext()){
				Map.Entry<Integer, Integer> toEvict = i.next();
				map.remove(toEvict.getKey());
			}
		}
	}
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */