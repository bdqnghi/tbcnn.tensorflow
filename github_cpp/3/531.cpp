/**
 * It uses an unordered map to store key-value pairs together with a reference
 * to linked list node. Linked list reference points to log entry. Logs are
 * stored in a linked list to ensure constant time insert/delete ops (assuming
 * that node references are available). Head of the list points to the least
 * recently used element (to its key, in fact) in cache.
 */

typedef int Key;
typedef list<int> LogList;
typedef list<int>::iterator Log;
typedef pair<int, Log> CachedItem;
typedef unordered_map<Key, CachedItem> Cache;

class LRUCache {
public:
    LRUCache(int capacity) {
        c = capacity;
    }

    int get(int key) {
        auto it = cache.find(key);

        if (it == cache.end())
            return -1;

        use(it);
        return it->second.first;
    }

    void set(int key, int value) {
        auto it = cache.find(key);

        if (it == cache.end()) {
            if (cache.size() == c)
                invalidate();

            turns.push_back(key);
        }
        else
            use(it);

        cache[key] = { value, --turns.end() };
    }
private:
    Cache cache;
    LogList turns;
    int c;

    void use(Cache::iterator it) {
        Key k = it->first;
        CachedItem v = it->second;

        turns.erase(v.second);
        turns.push_back(k);
        cache[k] = { v.first, --turns.end() };
    }

    void invalidate() {
        Key lru = turns.front();
        cache.erase(lru);
        turns.pop_front();
    }
};
