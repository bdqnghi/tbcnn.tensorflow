#include <map>
#include <iostream>

#define DEBUG

#ifdef DEBUG
int newCount = 0;
int deleteCount = 0;

void *operator new(size_t size)
{
    newCount++;
    return malloc(size);
}

void operator delete(void *data)
{
    deleteCount++;
    free(data);
    return ;
}

#endif

class LRUNode
{
public:
    LRUNode(int key, int value)
        : m_key(key), m_value(value), m_last(nullptr), m_next(nullptr)
    {}

    int m_key, m_value;
    LRUNode *m_last, *m_next;
};

class LRUCache
{
public:
    LRUCache(int capacity)
        : m_size(0), m_max(capacity), m_head(new LRUNode(-1, -1)), m_end(new LRUNode(-1, -1))
    {
        m_head->m_next = m_end;
        m_end->m_last = m_head;
        m_end->m_next = nullptr;
    }

    ~LRUCache()
    {
        auto temp = m_head;
        while(temp)
        {
            auto temp2 = temp;
            temp = temp->m_next;
            delete temp2;
        }
    }

    int get(int key)
    {
        auto it = m_map.find(key);
        if(it != m_map.end())
        {
            auto temp =it->second;
            temp->m_last->m_next = temp->m_next;
            temp->m_next->m_last = temp->m_last;

            temp->m_next = m_head->m_next;
            temp->m_next->m_last = temp;
            m_head->m_next = temp;
            temp->m_last = m_head;

            return temp->m_value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        auto it = m_map.find(key);
        if(it != m_map.end())
        {
            it->second->m_last->m_next = it->second->m_next;
            it->second->m_next->m_last = it->second->m_last;

            auto temp = it->second;
            temp->m_next = m_head->m_next;
            temp->m_next->m_last = temp;
            m_head->m_next = temp;
            temp->m_last = m_head;
            temp->m_value = value;

            return ;
        }

        if(m_size == m_max)
        {
            auto temp = m_end->m_last;
            temp->m_last->m_next = temp->m_next;
            temp->m_next->m_last = temp->m_last;

            m_map.erase(m_map.find(temp->m_key));

            delete temp;
            m_size --;
        }

        auto temp = new LRUNode(key, value);
        m_map[key] = temp;

        temp->m_next = m_head->m_next;
        temp->m_next->m_last = temp;
        m_head->m_next = temp;
        temp->m_last = m_head;

        m_size ++;

        return ;
    }

    std::map<int, LRUNode *> m_map;
    LRUNode *m_head, *m_end;
    int m_size;
    int m_max;
};

int main()
{
    LRUCache *cache = new LRUCache(2);

    cache->put(1, 1);
    cache->put(2, 2);
    std::cout << cache->get(1) << std::endl;       
    cache->put(3, 3);                              
    std::cout << cache->get(2) << std::endl;       
    cache->put(4, 4);                              
    std::cout << cache->get(1) << std::endl;       
    std::cout << cache->get(3) << std::endl;       
    std::cout << cache->get(4) << std::endl;       

    delete cache;

#ifdef DEBUG
    std::cout << (newCount == deleteCount) << std::endl;
#endif

    return 0;
}