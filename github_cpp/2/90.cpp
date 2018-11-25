

#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

class LRUcache
{
private:
   int _capacity;
   typedef list<int> USED;
   USED used;
   typedef pair<int, USED::iterator> pairData;
   typedef unordered_map<int, pairData> cacheS;
   
   cacheS cache;
   void touch(cacheS::iterator it) {
      used.erase(it->second.second);
      int key = it->first;
      used.push_front(key);
      it->second.second = used.begin();
   } 
public:
   LRUcache(int capacity):_capacity(capacity) {}

   int get(int key) {
      auto it = cache.find(key);
      if (it == cache.end())
         return -1;
      touch(it);
      return it->second.first;
      
   }

   void set(int key, int value) {
      auto it = cache.find(key);
      if (it == cache.end()) {
         if (used.size() == _capacity) {
            cache.erase(used.back());
            used.pop_back();
         } else {

         }
         used.push_front(key);
      } else {
         touch(it);
      }
      cache[key] = {value,used.begin()};
   }
};

int main() {
   LRUcache *lru = new LRUcache(3);
   lru->set(1,2);
   lru->set(2,2);
   lru->set(3,2);
   lru->set(4,4);
   lru->set(5,5);
   lru->set(6,6);
   lru->set(6,7);
   cout << lru->get(1) << endl;
   cout << lru->get(2) << endl;
   cout << lru->get(3) << endl;
   cout << lru->get(4) << endl;
   cout << lru->get(5) << endl;
   cout << lru->get(6) << endl;
   return 0;
}
