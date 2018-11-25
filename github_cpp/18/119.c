







#include "rod_cutting.hpp"
class Solution{
    
public:
    int rodCut(int length, vector<pair<int, int>> prices);
};

int Solution::rodCut(int length, vector<pair<int, int>> prices){
    if (length == 0 or prices.empty()) {
        return 0;
    }
    vector<int> _states(length+1, -1);  _states[0] = 0;
    
    
    for (pair<int, int>& p : prices) {
        for (int i = 0; i < _states.size(); i++) {
            if (_states[i] >= 0 and i+p.first <= length) {
                _states[i+p.first] = max(_states[i+p.first], _states[i] + p.second);
            }
        }
    }
    return _states[length];
}
struct Test{
    vector<pair<int, int>> prices;
    int length;
};

const vector<Test> _testcases = {
    {
        
        
        {{1,1}, {2, 5}, {3, 8}, {4,9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}},
        10,
    },
    {
        
        
        {{1,1}, {2, 5}, {3, 8}, {4,9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}},
        4,
    },
    {
        
        
        {{1,1}, {2, 5}, {3, 8}, {4,15}, {5, 10}, {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}},
        16,
    },
};
int main(){
    Solution solve;
    
    for (auto test : _testcases) {
        cout << solve.rodCut(test.length, test.prices) << "\n";
    }
    return 0;
}