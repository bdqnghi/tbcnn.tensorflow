#include<iostream>
#include<map>
#include<time.h>

using namespace std;

struct V{
    int val;
    long long seq;
};

class LRUCache{
    private:
	int capacity;
	map<int,V> cache;
	map<long long,int> seq2key;
	long long index;

    public:   
	LRUCache(int _capacity) {
	    capacity = _capacity;
	    index = 0;
	}

	int get(int key) {
	    map<int,V>::iterator it;
	    it = cache.find(key);

	    if(it == cache.end()){
		return -1;
	    }else{
		seq2key.erase(it->second.seq);

		it->second.seq = index++;
		seq2key[it->second.seq] = key;

		return it->second.val;
	    }
	}

	void set(int key, int value) {
	    //first check if the key already exists
	    //get will automatically update access sequence
	    if(get(key) == -1){
		struct V v;
		v.seq = index++;
		v.val = value;

		seq2key[v.seq] = key;

		//check whether need to lru
		if(full()){
		    //lru
		    map<long long,int>::iterator it = seq2key.begin();
		    //erase
		    seq2key.erase(it->first);
		    cache.erase(it->second);
		}
		cache[key] = v;
	    }else{
		cache[key].val = value;
	    }
	    
	}

	bool full(){
	    return cache.size() == capacity;
	}

	void display(){
	    cout<<"*****display("<<cache.size()<<")*******"<<endl;

	    map<long long,int>::iterator it;
	    for(it = seq2key.begin();it!=seq2key.end();it++){
		cout<<cache[it->second].val<<endl;
	    }
	}

	void clear(){
	    cache.clear();
	    seq2key.clear();
	    index = 0;
	}
};

int main(){
    LRUCache lru(2);
    lru.display();

    lru.set(1,1);
    lru.set(2,2);
    lru.set(3,3);
    lru.get(2);
    lru.display();

    lru.set(4,4);
    lru.display();
    lru.set(5,5);
    lru.display();
    lru.set(1,100);
    lru.display();

    lru.clear();
    cout<<lru.get(2)<<endl;
    lru.set(2,6);
    cout<<lru.get(1)<<endl;
    lru.set(1,5);
    lru.set(1,2);
    cout<<lru.get(1)<<endl;
    cout<<lru.get(2)<<endl;

    return 0;
}
