//LRU Cache
//Design and implement a data structure for Least Recently Used (LRU) cache. It
//should support the following operations: get and put.
//get(key) - Get the value (will always be positive) of the key if the key
//exists in the cache, otherwise return -1.
//put(key, value) - Set or insert the value if the key is not already present.
//When the cache reached its capacity, it should invalidate the least recently
//used item before inserting a new item.
//Follow up:
//Could you do both operations in O(1) time complexity?
//Example:
//LRUCache cache = new LRUCache( 2 /* capacity */ );
//cache.put(1, 1);
//cache.put(2, 2);
//cache.get(1);       // returns 1
//cache.put(3, 3);    // evicts key 2
//cache.get(2);       // returns -1 (not found)
//cache.put(4, 4);    // evicts key 1
//cache.get(1);       // returns -1 (not found)
//cache.get(3);       // returns 3
//cache.get(4);       // returns 4

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */


//######################################### LinkedHashMap #########################################
public class LRUCache {
	//LinkedHashMap : hashMap with DLL
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
        } else if(cache.size() == cap) cache.remove(cache.entrySet().iterator().next().getKey());  //removes first element
        //} else if(cache.size() == cap) cache.remove(cache.keySet().iterator().next());  //removes first element
       cache.put(key,value);  //append to last
    }
}


//######################################### DLL + HAshTable #########################################
//the "head" node is a pseudo node that marks the head. The double linked list
//can be represented
//as head (pseudo) <--> head <--> ....tail <--> tail (pseudo)
//by adding two pseudo nodes to make the boundaries, we could reduce the
//boundary checking code such as if (head != null), making the code more
//concise and also more efficient.
private Hashtable<Integer, DLinkedNode>
	cache = new Hashtable<Integer, DLinkedNode>();
private int count;
private int capacity;
private DLinkedNode head, tail;

public LRUCache(int capacity) {
	this.count = 0;
	this.capacity = capacity;

	//Add dummy nodes at head and tail
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
		return -1; // should raise exception here.
	}
	// move the accessed node to the head;
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
			// pop the tail
			DLinkedNode tail = this.popTail();
			this.cache.remove(tail.key);
			--count;
		}
	 } else {
		// update the value.
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

/**
 * Always add the new node right after head;
 */
private void addNode(DLinkedNode node){
	node.pre = head;
	node.post = head.post;

	head.post.pre = node;
	head.post = node;
}

/**
 * Remove an existing node from the linked list.
 */
private void removeNode(DLinkedNode node){
	DLinkedNode pre = node.pre;
	DLinkedNode post = node.post;
	pre.post = post;
	post.pre = pre;
}

/**
 * Move certain node in between to the head.
 */
private void moveToHead(DLinkedNode node){
	this.removeNode(node);
	this.addNode(node);
}

// pop the current tail.
private DLinkedNode popTail(){
	DLinkedNode res = tail.pre;
	this.removeNode(res);
	return res;
}


//######################################### HashMap + LL #########################################
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
          moveToEnd(key); //key exists move the page to end
          return mp[key];
        }
        return -1;
    }
    void put(int key, int value) {
        if(mp.count(key)) {
            mp[key] = value; //key exists move the page to end
            moveToEnd(key);
        } else if(mp.size()<capacity) {
            mp[key]=value;
            ageList.push_back(key);
            pos[key] = getLast(ageList);
        } else { //evict page
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
    //Get the end of List
    list<int>::iterator getLast(list<int> &ageList) {
        auto it = ageList.end();
        it--;
        return it;
    }
};
