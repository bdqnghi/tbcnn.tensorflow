/*
*
* Tag: Data Structure
* Time: O(n)
* Space: O(n)
*/
class LRUCache{
public:
    LRUCache(int capacity) {
        dict.clear();
        cap = capacity;
    }
    
    int get(int key) {
        if(dict.find(key) == dict.end())
            return -1;
        list<pair<int,int>>::iterator it = dict[key];
        cache.push_front(*it);
        cache.erase(it);
        dict[key] = cache.begin();
        return it->second;
    }
    
    void set(int key, int value) {
        if(dict.find(key) == dict.end()){
            while(dict.size() >= cap){
                dict.erase(cache.crbegin()->first);
                cache.pop_back();
            }
        }else{
            cache.erase(dict[key]);
        }
        
        cache.push_front(make_pair(key, value));
        dict[key] = cache.begin();
    }
private:
    unordered_map<int,list<pair<int,int>>::iterator> dict;
    list<pair<int,int>> cache;
    int cap;
};
