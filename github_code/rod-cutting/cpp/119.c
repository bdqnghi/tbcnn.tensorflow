//
//  rod_cutting.cpp
//  leetcode2016
//
//  Created by Shihao Zhang on 9/16/16.
//  Copyright © 2016 David Zhang. All rights reserved.
//

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
    
    /// prices = <length, price>
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
        //1	 2	3	4	5	6	7	8	9	10
        //1	 5	8	9	10	17	17	20	24	30
        {{1,1}, {2, 5}, {3, 8}, {4,9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}},
        10,
    },
    {
        //1	 2	3	4	5	6	7	8	9	10
        //1	 5	8	9	10	17	17	20	24	30
        {{1,1}, {2, 5}, {3, 8}, {4,9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}},
        4,
    },
    {
        //1	 2	3	4	5	6	7	8	9	10
        //1	 5	8	9	10	17	17	20	24	30
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