// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

bool isAnagram(string a, string b) {
    std::vector<int> res(26);
    for(auto& character : a) {
        int index = character - 'a';
        res[index]++;
    }

    for(auto& character : b) {
        int index = character - 'a';
        res[index]--;
    }
    
    for(auto& value : res) {
        if(value != 0) return false;
    }
    return true;
}

struct Bucket {
    Bucket(string& a) {
        insert(a);
    }
    
    bool doesThisBelong(string& a) {
        if(values.empty()) return true;
        return isAnagram(*values.begin(), a);
    }
    
    void insert(string& a) {
        values.push_back(a);
    }
    
    void output() {
        for(auto& value : values) {
            cout << value << ' ';
        }
    }
    
    private:
        vector<string> values;
};

void sort(vector<string>& strings, vector<Bucket>& buckets) {
    for(auto value : strings) {
        bool inserted = false;
        for(auto& bucket : buckets) {
            if(bucket.doesThisBelong(value)) {
                bucket.insert(value);
                inserted = true;
            }
        }
        if(!inserted) {
            buckets.push_back(Bucket(value));
        }
    }
}

int main()
{
    vector<Bucket> res;
    vector<string> v = {"oliverqueen"s, "noliverquee"s, "barryallen"s, "allenbarry"s, "cat"s, "tac"s, "butthole", "holebutt"s, "fog"s, "gof"s, "bat"s, "tab"s };

    sort(v, res);
    
    for(auto& bucket : res) {
        bucket.output();
        cout << "\n\n";
    }
}
