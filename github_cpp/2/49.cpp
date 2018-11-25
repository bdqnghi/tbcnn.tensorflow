#ifndef __MZDNS_LRU_CACHE_H
#define __MZDNS_LRU_CACHE_H
#include <list>
#include <utility>
#include <boost/unordered_map.hpp>

#include <iostream>

template <typename Key, typename Mapped>
class LRUCache
{
	typedef std::pair<Key, Mapped> 								Pair;
	typedef typename std::list<Pair>  							LRU;
	typedef typename LRU::iterator 								LRU_iterator;
	typedef typename boost::unordered_map<Key, LRU_iterator> 	CacheHashMap;

	public:
	LRUCache(uint32_t n):lru_(LRU()), cache_map_(CacheHashMap(n)), max_(n){}
	~LRUCache(){}

	Mapped* get(const Key& key)
	{
		typename CacheHashMap::iterator it = cache_map_.find(key);
		if(it == cache_map_.end())
			return NULL;
		
		typename CacheHashMap::const_iterator ret_it = _update_item(it);
		return &(ret_it->second->second);
	}

	void put(const Key& key, const Mapped& mapped)
	{
		cleanup();
		typename CacheHashMap::iterator it = cache_map_.find(key);
		if(it != cache_map_.end())
		{
			_update_item(it);
			return;
		}
		else
		{
			if(full())
				_remove_tail();

			_add_item(key, mapped);
		}
	}

	void remove(const Key& key)
	{
		typename CacheHashMap::iterator it = cache_map_.find(key);
		if(it != cache_map_.end())
		{
			_remove_item(it);
		}
	}

	void clear()
	{
		if(! size())
			return;
		cache_map_.clear();
		lru_.clear();
	}
	uint32_t size() const
	{
		return lru_.size();
	}
	void resize(uint32_t s)
	{
		max_ = s;
	}
	bool full()
	{
		return max_ == size();
	}

	
	
	void cleanup()
	{
		typename LRU::iterator lru_it = lru_it.end();
		lru_it --;

		while(size() != 0 && lru_it.invalid())
		{
			typename CacheHashMap::iterator it = cache_map_.find(lru_it->first);
			if(it != cache_map_.end())
			{
				_remove_item(it);
			}
		}
	}

	
	void print()
	{
		typename CacheHashMap::const_iterator it = cache_map_.begin();
		typename LRU::const_iterator lru_it = lru_.begin();
		int i = 0;
		std::cout << "HashMap>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
		for(i = 0;it != cache_map_.end(); ++it, ++i)
		{
			std::cout << "index: " << i << " key: " << it->first << " Mapped: " << it->second->second << std::endl;
		}
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<HashMap" <<std::endl;

		
		std::cout << "LRUList>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;
		for(i = 0;lru_it != lru_.end(); ++lru_it, ++i)
		{
			std::cout << "index: " << i << " " << lru_it->second << std::endl;
		}
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<LRUList" <<std::endl;
	}
	
	private:
	LRU 			lru_;
	CacheHashMap 	cache_map_;	
	uint32_t 		max_;
	

	typename CacheHashMap::iterator _update_item(typename CacheHashMap::iterator it)
	{
		Key key_bak = it->first;
		Mapped item_bak = it->second->second;
		_remove_item(it);
		return  _add_item(key_bak, item_bak);
	}

	void _remove_item(typename CacheHashMap::iterator it)
	{
		lru_.erase(it->second);
		cache_map_.erase(it);
	}
	
	void _remove_tail()
	{
		if(size() == 0)
			return;
		
		LRU_iterator it = lru_.end();	
		it --;
		Key key = it->first;
		lru_.pop_back();
		typename CacheHashMap::iterator rm = cache_map_.find(key);
		if(rm == cache_map_.end())
			return;
		cache_map_.erase(rm);

	}
	typename CacheHashMap::iterator _add_item(const Key& key, const Mapped& mapped)
	{
		lru_.push_front(std::make_pair<Key, Mapped>(key, mapped));
		return cache_map_.insert(cache_map_.begin(), typename CacheHashMap::value_type(key, lru_.begin()));
	}

};


#endif
