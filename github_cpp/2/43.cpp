
#include <iostream>
#include <list>
#include <unordered_map>




template <
          typename key,
          typename value,
          template <typename ...> class MAP
          >
class LRU
{
    public:
        
        typedef std::list<value>                                    LIST_;
        
        
        
        typedef typename std::pair<value, typename LIST_::iterator> VALUE_TRACKER_;
        typedef MAP<key, VALUE_TRACKER_>                            HASH_;

        
        LRU(value(*f) (const key &k), value c):
            capacity_(c), fn_(f)
            { }

        
        ~LRU()
            { }

        
        value
            operator() (const key &k)
            {
                typename HASH_::iterator itr = hash_.find(k);
                if (itr == hash_.end()) {
                    const value v = fn_(k);
                    insert(k, v);

                    return v;
                } else {
                    
                    
                    VALUE_TRACKER_ tracker = itr->second;
                    list_.splice(
                      list_.begin(),
                      list_,
                      tracker.second);
                    return tracker.first;
                }
            }

        
        void
            display_keys()
            {
                
                typedef typename LIST_::const_iterator LItr;
                LItr itr (list_.begin());
                LItr end (list_.end());

                for (; itr != end; ++itr) {
                    std::cout << *itr << ",";
                }
                std::cout << std::endl;
            }

    private:
        
        void
            insert(const key &k, const value &v)
            {
                std::cout << "insert key(" << k << "): value(" << v << ")\n";

                if (list_.size() == capacity_) {
                    
                    evict();
                }

                
                typedef typename LIST_::iterator LItr;
                LItr itr = list_.begin();

                list_.insert(itr, v);
                
                itr = list_.begin();
                
                
                typedef typename std::pair<value, LItr> HASH_ELE;
                HASH_ELE h_element = std::make_pair(v, itr);
                hash_.insert(std::pair<value, HASH_ELE>
                                (v, h_element));
            }

        
        void
            evict()
            {
                std::cout << "evict() called\n";

                
                typedef typename LIST_::reverse_iterator rItr;
                rItr itr = list_.rbegin();
                const key k = fn_(*itr);

                
                hash_.erase(k);
                
                list_.pop_back();
            }

        
        size_t                  capacity_;
        
        value (*fn_)(const key&);
        
        LIST_                   list_;
        
        HASH_                   hash_;
};


int
bucket_fn(const int &value)
{
    
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

