


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
				
				int deletePageIndex = cache.begin()->key;
				page_to_index.erase(deletePageIndex);
				cache.erase(cache.begin());
			}
		}
		else{
			cache.erase(pos->second);
		}
		
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
			
			cin >> index >> value;
			test.set(index, value);
			test.printCache();
		}
		else{
			
			cin >> index;
			cout << test.get(index) << endl;
		}
	}
}
