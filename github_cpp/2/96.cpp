
#include "webproxy.h"
#include "cache.h"

using namespace  ::Rpc;

using namespace std;
struct hash_value{
	uint32_t lru_cnt;
	webpage cached_pg;
};

struct lru_metadata{
	string url;
	uint32_t pg_size;
};
typedef std::map<std::string, hash_value> url_map;
typedef std::map<uint32_t, lru_metadata> lru_map;
#define  DEBUG

url_map web_cache;
lru_map lru_table;

int32_t cache_sz_total;
int32_t cache_sz_remaining;

uint64_t glru_count;

void set_cache_size(uint32_t size){
	cache_sz_total = cache_sz_remaining = size;

}
void add_to_cache(std::string url, webpage& current_page){

	hash_value pg_data;
	lru_metadata lru_min;
	lru_map::iterator itr;

	if (cache_sz_total < current_page.webpage_len)
	{
		
		cout<<"Cache too small for url "<<url<<"\n";
		return;
	}
	else if (current_page.webpage_len == 0)
	{
		cout<<"Page data is null \n";
		return;
	}

	
	while (cache_sz_remaining < current_page.webpage_len)
	{
		uint32_t min_size = current_page.webpage_len;
		uint32_t pg_found = 0;
		while (!pg_found && min_size)
		{
			for ( itr = lru_table.begin(); itr != lru_table.end(); ++itr)
			{
					if (itr->second.pg_size >= min_size)
					{
						cache_sz_remaining += web_cache[itr->second.url].cached_pg.webpage_len;

#ifdef DEBUG

						cout<<"\tEvicting URL "<<itr->second.url<<" of size: "<<itr->second.pg_size<<"\n";
#endif
						web_cache.erase(itr->second.url);
						lru_table.erase(itr);
						pg_found = 1;
						break;
					}
			}
			min_size = min_size/2;
		}
	}

	
	pg_data.cached_pg = current_page;
	pg_data.lru_cnt = glru_count++;
	lru_min.pg_size = current_page.webpage_len;
	lru_min.url = url;

	cache_sz_remaining -= current_page.webpage_len;
#ifdef DEBUG_EXTRA
	cout<<"Caching Page data for Url "<<url<<" Length "<<current_page.webpage_len<<":\n"<< current_page.webpage_data<<"\n";
	cout<<"Cache size remaining after new addition"<<cache_sz_remaining<<"\n";
#endif

	web_cache[url] = pg_data;

	lru_table[pg_data.lru_cnt] = lru_min;
	return;
}

int32_t get_cached_page(std::string url, webpage& returned_page)
{
	uint32_t prev_lru, curr_lru;
	lru_metadata lru_min;

	if (web_cache.find(url) == web_cache.end())
	{
		cout<<" URL "<<url<<" not found in cache \n";
		return -1;
	}

	prev_lru = web_cache[url].lru_cnt;
	lru_min = lru_table[prev_lru];

	lru_table.erase(prev_lru);

	curr_lru = glru_count;
	lru_table[curr_lru] = lru_min;

	web_cache[url].lru_cnt = glru_count++; 
	returned_page = web_cache[url].cached_pg;

#ifdef DEBUG_EXTRA
	cout<<"Cached Page data for Url "<<url<<" Length "<<returned_page.webpage_len<<":\n"<< returned_page.webpage_data<<"\n";
#endif
	return 0;
}


