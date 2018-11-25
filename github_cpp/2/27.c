
#include <list>
#include <iostream>
#include <string>
#include <unordered_map>


struct item
{
    item(const std::string& val) : m_value(val) {};
    std::string m_value;
};

class cache
{
protected:
    int max_entries = 2;
    int entries = 0;

    typedef std::pair<std::string, item> item_pair_t;
    typedef std::list<item_pair_t> cache_list_t; 
    typedef std::unordered_map<std::string, cache_list_t::iterator> cache_map_t; 

    cache_list_t m_cache_list;
    cache_map_t m_cache_map;
    
public:
    void insert(const std::string& key, const std::string& value)
    {
        item local_item(value);
        m_cache_list.push_front(std::make_pair(key, local_item));
        m_cache_map[key] = m_cache_list.begin();
        entries++;

        if ( entries > max_entries )
        {
            m_cache_map.erase(m_cache_list.back().first);
            m_cache_list.pop_back();
            entries--;
        }
    }

    item get(const std::string& key)
    {
        return m_cache_map[key]->second;
    }

    void printr()
    {
        for ( auto&& i : m_cache_map )
        {
            std::cout << i.first << " , " ;
        }
        std::cout << "\n";
    }
};


int main()
{
cache* lru = new cache();

lru->insert("key-1", "value-1");
lru->insert("key-2", "value-2");
lru->printr();
lru->insert("key-3", "value-3");
lru->insert("key-4", "value-4");
lru->printr();
lru->insert("key-5", "value-5");
lru->printr();


return 0;
}
