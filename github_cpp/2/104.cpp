

struct CacheEntry
{
    int val;
    int key;
    CacheEntry *prev;
    CacheEntry *next;
    CacheEntry(int v, int k) : key(k), val(v), prev(NULL), next(NULL) {}
};

class LRUCache{
public:
    LRUCache(int capacity) {
	this->capacity = capacity;
	size = 0;
	head = new CacheEntry(0, -1);
	tail = new CacheEntry(0, -1);
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = head;
    }

    ~LRUCache()
        {
	    delete head;
	    delete tail;
	}

    int get(int key) {
	CacheEntry *node = hashmap[key];
	if(node)
	{
	    detach(node);
	    attach(node);
	    return node->val;
	}
	else
	    return -1;
    }

    void set(int key, int value) {
	CacheEntry *node = hashmap[key];
	if(node)
	{
	    node->val = value;
	    detach(node);
	    attach(node);
	}
	else
	{
	    if(size >= capacity) 
	    {
		node = tail->prev;
		node->val = value;
		hashmap.erase(node->key);
		node->key = key;
		detach(node);
	    }
	    else
	    {
		++size;
		node = new CacheEntry(value, key);
	    }
	    attach(node);
	    hashmap[key] = node;
	}
    }

private:
    void detach(CacheEntry *node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
    }

    void attach(CacheEntry *node) {
	node->prev = head;
	head->next->prev = node;
	node->next = head->next;
	head->next = node;
    }

private:
    unordered_map<int, CacheEntry *> hashmap;
    int capacity;
    int size;
    CacheEntry *head;
    CacheEntry *tail;
};
