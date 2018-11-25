

























public class LRUCache {
	
    LinkedHashMap<Integer,Integer> cache=new LinkedHashMap<>();
    int cap=0;

    public LRUCache(int capacity) {
        cap=capacity;
    }

    public int get(int key) {
        if(cache.containsKey(key)) {
            int value = cache.get(key);
            cache.remove(key);
            cache.put(key,value);
            return value;
        }
        return -1;
    }

    public void put(int key, int value) {
        if(cache.containsKey(key)) {
          cache.remove(key);
          cache.put(key,value);
        } else if(cache.size() == cap) cache.remove(cache.entrySet().iterator().next().getKey());  
        
       cache.put(key,value);  
    }
}









private Hashtable<Integer, DLinkedNode>
	cache = new Hashtable<Integer, DLinkedNode>();
private int count;
private int capacity;
private DLinkedNode head, tail;

public LRUCache(int capacity) {
	this.count = 0;
	this.capacity = capacity;

	
	head = new DLinkedNode();
	head.pre = null;

	tail = new DLinkedNode();
	tail.post = null;

	head.post = tail;
	tail.pre = head;
}

public int get(int key) {
	DLinkedNode node = cache.get(key);
	if(node == null){
		return -1; 
	}
	
	this.moveToHead(node);
	return node.value;
}

public void put(int key, int value) {
	DLinkedNode node = cache.get(key);
	if(node == null){
		DLinkedNode newNode = new DLinkedNode();
		newNode.key = key;
		newNode.value = value;

		this.cache.put(key, newNode);
		this.addNode(newNode);

		++count;

		if(count > capacity){
			
			DLinkedNode tail = this.popTail();
			this.cache.remove(tail.key);
			--count;
		}
	 } else {
		
		node.value = value;
		this.moveToHead(node);
	}
}


class DLinkedNode {
	int key;
	int value;
	DLinkedNode pre;
	DLinkedNode post;
}


private void addNode(DLinkedNode node){
	node.pre = head;
	node.post = head.post;

	head.post.pre = node;
	head.post = node;
}


private void removeNode(DLinkedNode node){
	DLinkedNode pre = node.pre;
	DLinkedNode post = node.post;
	pre.post = post;
	post.pre = pre;
}


private void moveToHead(DLinkedNode node){
	this.removeNode(node);
	this.addNode(node);
}


private DLinkedNode popTail(){
	DLinkedNode res = tail.pre;
	this.removeNode(res);
	return res;
}



class LRUCache{

private:
    map<int,int> mp;
    map<int,list<int>::iterator> pos;
    list<int> ageList;
    int capacity;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    int get(int key) {
        if(mp.count(key)) {
          moveToEnd(key); 
          return mp[key];
        }
        return -1;
    }
    void put(int key, int value) {
        if(mp.count(key)) {
            mp[key] = value; 
            moveToEnd(key);
        } else if(mp.size()<capacity) {
            mp[key]=value;
            ageList.push_back(key);
            pos[key] = getLast(ageList);
        } else { 
            mp.erase(ageList.front());
            ageList.pop_front();
            mp[key]=value;
            ageList.push_back(key);
            pos[key] = getLast(ageList);
        }

    }
    void moveToEnd(int key) {
        ageList.erase(pos[key]);
        ageList.push_back(key);
        pos[key]= getLast(ageList);
    }
    
    list<int>::iterator getLast(list<int> &ageList) {
        auto it = ageList.end();
        it--;
        return it;
    }
};
