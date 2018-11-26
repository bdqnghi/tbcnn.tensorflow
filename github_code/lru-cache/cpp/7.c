/*
	Suppose we have several pages of memory that work as the cache. 
	We should maintain the cache with LRU algorithm which means we 
	should always keep the pages in cache in order. Getting page
	value and setting page value are two frequent manipulations so
	we have to find an ideal data struture to store the pages.

	Therefore, I got linked list to store the pages(
	easy to move the page according to theirs used order) 
	and map to tell where a particular page is in that list.

	Suppose we have the cache like this:

	1(2) --> 3(3) --> 5(6) --> 2(1)

	and the capacity of cache is 4.(The value between a pair of 
	pathesises is the value of that page.)

	And the map situation is:
	page 1: 0 
	page 2: 3
	page 3: 1
	page 5: 4

	On one hand, getting the value of a page is as easy as finding index in
	the map and locate the index(I represent it as a pointer) in the list.

	On the other one, setting the value of a page is a little more complex.
	First of all, find that page. Then set the value. When it comes that the
	cache is full, remove the least recently used page(the first one of the list).
	Otherwise, insert the new page into the list.

	Both the manipulations are done by putting the latest manipulated page
	from its orginal position to the tail of the list because this will prove
	the page is the most recently used one.
*/


#include<iostream>
#include<map>
#include<list>
using namespace std;

struct Page{
	int key;
	int value;
	Page(int k = 0, int v = 0): key(k), value(v){}
};

class LRUCache{
public:
	LRUCache(int capacity){
		size = capacity;
	}

	int get(int key){
		map<int, list<Page>::iterator >::iterator pos = page_to_index.find(key);
		if(pos == page_to_index.end())
			return -1;
		else{
			// getting means using.
			Page page = *(pos->second);
			cache.erase(pos->second);
			cache.push_back(page);
			list<Page>::iterator it = cache.end();
			it--;
			page_to_index[key] = it; 
			return page.value;
		}
	}

	void set(int key, int value){
		map<int, list<Page>::iterator >::iterator pos = page_to_index.find(key);
		Page newPage(key, value);
		if(pos == page_to_index.end()){
			if(cache.size() == size){
				// cache is full;
				int deletePageIndex = cache.begin()->key;
				page_to_index.erase(deletePageIndex);
				cache.erase(cache.begin());
			}
		}
		else{
			cache.erase(pos->second);
		}
		//setting means using
		cache.push_back(newPage);
		list<Page>::iterator it = cache.end();
		it--;
		page_to_index[key] = it; 
	}

	void printCache(){
		cout << "The cache is:" << endl;
		list<Page>:: iterator it;
		for(it = cache.begin(); it != cache.end(); it++){
			cout << it->key << ": " << it->value << endl;
		}
	}

	~LRUCache(){
		cache.clear();
		page_to_index.clear(); 
	}

private:
	list<Page> cache; 
	map<int, list<Page>::iterator > page_to_index;
	int size;
};

int main(){
	LRUCache test(5);
	int command;
	int index;
	int value;

	while(cin >> command){
		if(command == 0){
			// set
			cin >> index >> value;
			test.set(index, value);
			test.printCache();
		}
		else{
			// get
			cin >> index;
			cout << test.get(index) << endl;
		}
	}
}
