

struct Node
{
    int key, val;
    Node(int x = 0, int y = 0): key(x), val(y) {}
};

class LRUCache{
public:
    LRUCache(int capacity) {
        size = capacity;
    }
    
    int get(int key) {
        auto p1 = mp.find(key); 
        if (p1 == mp.end()) return -1;
        
        auto p2 = p1->second;  
        l.push_front(Node(p2->key, p2->val)); 
		l.erase(p2);
		mp[key] = l.begin();
        return l.begin()->val;
    }
    
    void set(int key, int val) {
        auto p1 = mp.find(key);
        if (p1 != mp.end())
            l.erase(p1->second);
        else if (mp.size() == size) 
		{
			mp.erase(l.back().key);
            l.pop_back();
		}

        l.push_front(Node(key, val));
        mp[key] = l.begin();
    }

private:
    int size;
    list<Node> l;
    map<int, list<Node>::iterator> mp;
};