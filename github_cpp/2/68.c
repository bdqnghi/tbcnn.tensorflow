#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <utility>

class LRUCache {

private:
    
    struct Entity
    {
        int key, value;
        unsigned int timestamp;
        Entity(int k, int v, int ts)
            : key(k)
            , value(v)
            , timestamp(ts) {
        }

        struct EntityLess {
            bool operator() (const Entity& a, const Entity& b) const
            { return a.timestamp < b.timestamp; }
        };
    };

public:

    unsigned int capacity;
    unsigned int timestamp;

    
    std::map<int, Entity> cache;
    
    std::set<Entity,Entity::EntityLess> pool;

    
    
    
    

    
    
    

    
    

    
    
    

    
    
    

    LRUCache(int _capacity)
        : capacity(_capacity)
        , timestamp(0)
        , cache()
        , pool(){
    }

    int get(int key) {
        tick();

        
        auto result =
            cache.find(key);

        if (result == cache.end())
            return -1;

        
        

        Entity e = result->second;
        
        pool.erase(e);
        
        e.timestamp = timestamp;
        
        
        pool.insert(e);

        
        

        
        
        
        result->second.timestamp = timestamp;
        return e.value;
    }

    void set(int key, int value) {
        tick();
        auto result =
            cache.find(key);

        if (result != cache.end()) {
            
            
            
            pool.erase( Entity(-1,-1,result->second.timestamp) );

            
            cache.erase( result );
            
            
        }

        Entity e(key,value,timestamp);
        
        cache.insert( std::pair<int,Entity>(key,e) );
        pool.insert(e);

        
        
        if (cache.size() > capacity)
            removeOldest();
    }

private:
    void tick() {
        
        
        

        
        
        
        ++timestamp;
    }

    void removeOldest() {
        
        

        
        auto result =
            cache.find(pool.begin()->key);

        
        cache.erase(result);

        
        pool.erase( pool.begin() );
    }
};

#include <gtest/gtest.h>

namespace {

#define GET(ADDR,EXPECT) {                      \
        EXPECT_EQ(EXPECT,lru.get(ADDR));        \
    }                                           \

#define SET(ADDR,VALUE) {                       \
        lru.set(ADDR,VALUE);                    \
    }

#define MY_TEST(TN,T,C,...) TEST(TN,T) {                                \
        LRUCache lru(C);                                                \
        __VA_ARGS__;                                                    \
    }

    MY_TEST(LRUCache,Simple,10,
            SET(1,123);
            SET(2,456);
            GET(1,123);
            GET(2,456);)

    MY_TEST(LRUCache,Overwrite,10,
            SET(1,123);
            SET(1,456);
            GET(2,-1);
            GET(1,456);)

    MY_TEST(LRUCache,Expire,2,
            SET(1,123);
            SET(2,456);
            SET(3,789);
            GET(1,-1);
            GET(2,456);
            GET(3,789);)

    MY_TEST(LRUCache,TouchOld,2,
            SET(1,123);
            SET(2,456);
            GET(1,123);
            SET(3,789);
            GET(1,123);
            GET(2,-1);
            GET(3,789);)

#undef GET
#undef SET
#undef MY_TEST

}  

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
