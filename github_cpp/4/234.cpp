#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

template <class Key, class Val> class HashTable {
private:
    unordered_map<Key, Val> map;
    
public:
    void insert(const pair<Key, Val> &p) {
        map.insert(p);
    }

    Val search(const Key &k) {
        return map[k];
    }

    Val &operator[](const Key &k) {
        return map[k];
    }

    double hash(const string &s) {
        return (map.hash_function())(s);
    }

    void print() {
        cout << "[";
        int count = 0;
        for (auto kv: map) {
            cout << "(" << kv.first << ", " << kv.second << ")";
            if (count++ != map.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

};

int main(int argc, char const *argv[]) {
    HashTable<string, double> ht;
    ht.insert(pair<string, double>("Jeffrey", 123456));
    ht.insert(pair<string, double>("Alan", 789));
    ht.print();
    cout << ht["Jeffrey"] << endl;
    cout.precision(0);
    cout << fixed << ht.hash("Turing") << endl;
    return 0;
}
