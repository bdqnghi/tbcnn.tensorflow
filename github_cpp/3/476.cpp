
#include <iostream>
#include <list>
#include <unordered_map>

/**
 * LRU (Least Recently Used
 *
 * Class implements one of the technique to implement LRU
 * Major operations desrired from LRU class are:
 * 1. Fast retrieval of cache items.
 * 2. Low overhead mechanism to maintain ordering of elements.
 * 3. Low insert cost of an element in the cache.
 *
 * Implementation:
 * 1. map/unordered_map needs to hold the mapping key --> value for O(1) or
 *    O(log(N)) lookup.
 * 2. Insertion / eviction needs to be fast; thus value should be maintained
 *    as a double link list providing O(1) time complexity.
 */

// provide user the class to define its own 'map' class
template <
          typename key,
          typename value,
          template <typename ...> class MAP
          >
class LRU
{
    public:
        // maintain the available value as a double linked list
        typedef std::list<value>                                    LIST_;
        // create a map of key --> value pair
        // to facilitate O(1) insertion/deletion create
        // value --> list::iterator mapping as well
        typedef typename std::pair<value, typename LIST_::iterator> VALUE_TRACKER_;
        typedef MAP<key, VALUE_TRACKER_>                            HASH_;

        // ctor
        LRU(value(*f) (const key &k), value c):
            capacity_(c), fn_(f)
            { }

        // dtor
        ~LRU()
            { }

        // lookup function
        value
            operator() (const key &k)
            {
                typename HASH_::iterator itr = hash_.find(k);
                if (itr == hash_.end()) {
                    const value v = fn_(k);
                    insert(k, v);

                    return v;
                } else {
                    // reposition the node to front of the key
                    // end of list reflects least recently used value
                    VALUE_TRACKER_ tracker = itr->second;
                    list_.splice(
                      list_.begin(),
                      list_,
                      tracker.second);
                    return tracker.first;
                }
            }

        // display the key in the hash, mostly for testing
        void
            display_keys()
            {
                // order will be most recently first
                typedef typename LIST_::const_iterator LItr;
                LItr itr (list_.begin());
                LItr end (list_.end());

                for (; itr != end; ++itr) {
                    std::cout << *itr << ",";
                }
                std::cout << std::endl;
            }

    private:
        // if value not found in the list, insert it
        void
            insert(const key &k, const value &v)
            {
                std::cout << "insert key(" << k << "): value(" << v << ")\n";

                if (list_.size() == capacity_) {
                    // boy we ran out of space !
                    evict();
                }

                // update list with the new member
                typedef typename LIST_::iterator LItr;
                LItr itr = list_.begin();

                list_.insert(itr, v);
                // refresh the iterator
                itr = list_.begin();
                // update the hash map with new member key as well
                // value->list::iterator mappings.
                typedef typename std::pair<value, LItr> HASH_ELE;
                HASH_ELE h_element = std::make_pair(v, itr);
                hash_.insert(std::pair<value, HASH_ELE>
                                (v, h_element));
            }

        // remove the element least recently used so far
        void
            evict()
            {
                std::cout << "evict() called\n";

                // last element is least recently used element
                typedef typename LIST_::reverse_iterator rItr;
                rItr itr = list_.rbegin();
                const key k = fn_(*itr);

                // remove key from hash map
                hash_.erase(k);
                // remove the last element from the list
                list_.pop_back();
            }

        // maximum capacity of the LRU
        size_t                  capacity_;
        // function to return key corresponding to a value
        value (*fn_)(const key&);
        // tarck the list iteration
        LIST_                   list_;
        // hash to lookup data
        HASH_                   hash_;
};


int
bucket_fn(const int &value)
{
    // let the std library deal with hashing funciton
    return value;
}

int
main()
{
    LRU<int, int, std::unordered_map> lru(bucket_fn, 10);

    int i = 0;
    for (; i < 5; ++i) {
        lru(i);
    }

    lru.display_keys();
    lru(i);
    lru(++i);

    for (; i < 15; ++i) {
        lru(i);
    }

    std::cout << std::endl;

    lru.display_keys();
    return 0;
}

