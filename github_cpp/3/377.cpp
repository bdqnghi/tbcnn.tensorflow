#include <iostream>
#include <list>
#include <map>
using namespace std;

class LRUCache{
public:
	int cap;
	list<int> ls;
	map<int, pair<int, list<int>::iterator> > mp;
	LRUCache(int capacity) {
		cap = capacity;
	}
	int get(int key) {
		map<int, pair<int, list<int>::iterator> >::iterator p = mp.find(key);
		if (p != mp.end()) {
			ls.erase(p->second.second);
			ls.push_front(key);
			p->second.second = ls.begin();
			return p->second.first;
		}
		return -1;
	}
	void set(int key, int value) {
		map<int, pair<int, list<int>::iterator> >::iterator p = mp.find(key);
		if (p != mp.end()) {
			ls.erase(p->second.second);
			ls.push_front(key);
			p->second.first = value;
			p->second.second = ls.begin();
		}
		else {
			if (ls.size() == cap) {
				int u = ls.back();
				mp.erase(u);
				ls.pop_back();
			}
			ls.push_front(key);
			mp.insert(make_pair(key, make_pair(value, ls.begin())));
		}
	}
};

int main() {
	LRUCache lru(2);
	lru.set(2, 1);
	lru.set(1, 1);
	cout << lru.get(2) << endl;
	lru.set(4, 1);
	cout << lru.get(1) << endl;
	cout << lru.get(2) << endl;
	return 0;
}
