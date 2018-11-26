#include <iostream>
#include <utility>
#include <list>
#include <map>

class LRUCache
{
public:
	LRUCache(int _capacity) :capacity(_capacity)
    {
        //capacity = capacity;
    }
    
    int get(int key) {
        if(lrucache.find(key) != lrucache.end())
        {
        		auto iter = lrucache[key];
				int value = iter->second;
				seqcache.erase(iter);
				iter = seqcache.insert(seqcache.end(), std::make_pair(key, value));
				lrucache[key] = iter;
        		return value;
        }
        else
        	return -1;
    }
    
    void set(int key, int value)
    {
        if(lrucache.find(key) != lrucache.end())
        {
			auto iter = lrucache.find(key);
			//int key   = iter->second->first;
			//int value = iter->second->second;
			seqcache.erase(iter->second);
			iter->second = seqcache.insert(seqcache.end(), std::make_pair(key, value));
			return;
        }
		if ((int)lrucache.size() >= capacity)
		{
			int key_temp = seqcache.begin()->first;
			seqcache.erase(seqcache.begin());
			lrucache.erase(key_temp);
		}
		auto iter = seqcache.insert(seqcache.end(), std::make_pair(key, value));
        lrucache.insert(std::make_pair(key, iter));
    }

private:
	int capacity;
	std::list<std::pair<int, int> > seqcache;
	std::map<int, std::list<std::pair<int, int> >::iterator > lrucache;
};

int main()
{
	LRUCache cache(2);
	cache.set(2, 1);
	cache.set(2, 2);
	
	std::cout << cache.get(2) << std::endl;
	cache.set(1, 1);
	cache.set(4, 1);
	std::cout << cache.get(2) << std::endl;
	return 0;
}