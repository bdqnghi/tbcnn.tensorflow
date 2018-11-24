#include <algorithm>
#include <iterator>
#include <functional>

#include "hash-table.h"


HashTable::HashTable()
    : m_buckets{new std::forward_list<Pair*> [BUCKET_SIZE]}
    , m_size{0}
{
    for (auto i = 0; i < BUCKET_SIZE; i++) {
        m_buckets[i] = new std::forward_list<Pair*>;
    }
}

HashTable::~HashTable()
{
    for (auto i = 0; i < BUCKET_SIZE; i++) {
        if (m_buckets[i] != nullptr) {
            m_buckets[i]->clear();
            delete m_buckets[i];
        }
    }
}

void HashTable::insert(const std::string key, int value)
{
    int i = std::hash<std::string>{}(key) % BUCKET_SIZE;

    auto it = std::find_if(m_buckets[i]->cbegin(), 
        m_buckets[i]->cend(), [=] (Pair* pair) { return pair->key == key; });

    if (it != m_buckets[i]->cend()) {
        (*it)->value = value;
        return;
    }

    m_buckets[i]->push_front(new Pair(key, value));
    m_size++;
}

int HashTable::value(const std::string key, const int defaultValue) const
{
    int i = std::hash<std::string>{}(key) % BUCKET_SIZE;

    auto it = std::find_if(m_buckets[i]->cbegin(), 
        m_buckets[i]->cend(), [=] (Pair* pair) { return pair->key == key; });

    if (it != m_buckets[i]->cend()) {
        return (*it)->value;
    } else {
        return defaultValue;
    }
}

void HashTable::remove(const std::string key)
{
    int i = std::hash<std::string>{}(key) % BUCKET_SIZE;

    auto it = std::find_if(m_buckets[i]->cbegin(), 
        m_buckets[i]->cend(), [=] (Pair* pair) { return pair->key == key; });

    if (it != m_buckets[i]->cend()) {
        m_buckets[i]->remove(*it);
        m_size--;
    }
}

bool HashTable::contains(const std::string key) const
{
    int i = std::hash<std::string>{}(key) % BUCKET_SIZE;

    auto it = std::find_if(m_buckets[i]->cbegin(), m_buckets[i]->cend(),
        [key] (Pair* p) { return p->key == key; });

    return it != m_buckets[i]->cend();
}

void HashTable::clear()
{
    for (auto i = 0; i < BUCKET_SIZE; i++) {
        if (m_buckets[i] != nullptr) {
            m_buckets[i]->clear();
        }
    }
    m_size = 0;
}