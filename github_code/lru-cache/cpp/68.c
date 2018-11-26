#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <utility>

class LRUCache {

private:
    // an entity keeps track of key,value and timestamp
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

    // "cache" does lookup in logarithmic time
    std::map<int, Entity> cache;
    // "pool" maintains timestamp in logarithmic time
    std::set<Entity,Entity::EntityLess> pool;

    // here redundant data are kept:
    // it is possible to share Entity instances
    // in "cache" and "pool"
    // but we choose not to for the sake of simplicity

    // the basic idea to make every "get" and "set" done
    // in logarithmic time is to maintain "cache" and "pool"
    // simultaneously.

    // here I think the biggest problem is to identify the "least recent entity"
    // and remove it when the size exceeds the capacity.

    // for std::set, its first element is guaranteed to be the minimum,
    // so it can be used to remove the oldest content in logarithmic time.
    // see: http://www.cplusplus.com/reference/set/set/begin/

    // Since we are maintaining both "cache" and "pool",
    // at each return point of each method, we must make sure
    // the corresponding manipulations are performed on both structures.

    LRUCache(int _capacity)
        : capacity(_capacity)
        , timestamp(0)
        , cache()
        , pool(){
    }

    int get(int key) {
        tick();

        // O(log(n))
        auto result =
            cache.find(key);

        if (result == cache.end())
            return -1;

        // update the timestamp because we are
        // "using this value"

        Entity e = result->second;
        // we delete the element,
        pool.erase(e);
        // modify the key,
        e.timestamp = timestamp;
        // and insert it again
        // making it an "element update"
        pool.insert(e);

        // and this update runs in
        // O(log(n)) + O(log(n)) = O(log(n)) time

        // "cache" actually doesn't care about this value,
        // but here it's still important to
        // synchorize what we've done in "pool"
        result->second.timestamp = timestamp;
        return e.value;
    }

    void set(int key, int value) {
        tick();
        auto result =
            cache.find(key);

        if (result != cache.end()) {
            // old value are removed here
            // "pool" only cares about the timestamp,
            // the other two values are unnecessary
            pool.erase( Entity(-1,-1,result->second.timestamp) );

            // also remove it from "cache"
            cache.erase( result );
            // runs in:
            // O(log(n)) + O(log(n)) = O(log(n)) time
        }

        Entity e(key,value,timestamp);
        // O(log(n)), insert both in "cache" and in "pool"
        cache.insert( std::pair<int,Entity>(key,e) );
        pool.insert(e);

        // after an insertion, the element size might exceed the capacity,
        // if this is the case, remove the oldest one
        if (cache.size() > capacity)
            removeOldest();
    }

private:
    void tick() {
        // every expose operation bumps
        // the timestamp first.
        // this will ensure the uniqueness of timestamp.

        // since for the "pool" set, we only care about
        // the timestamp, so we need this uniqueness
        // to avoid accidental deletion of other elements
        ++timestamp;
    }

    void removeOldest() {
        // here pool.begin() must point to the
        // minimum (in terms of timestamp) Entity

        // O(log(n))
        auto result =
            cache.find(pool.begin()->key);

        // O(log(n))
        cache.erase(result);

        // O(log(n))
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

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
