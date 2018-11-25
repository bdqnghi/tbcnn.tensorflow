

std::map's implementation is red-black-tree, lower_bound finds the first key in the BST that is no less 
    than the given key. We first store all the indexes of
    intervals using starting point as key into the BST, then search it using end points of each interval. 
    Time complexity O(nlgn).

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> hash;
        vector<int> res;
        int n = intervals.size();
        for (int i = 0; i < n; ++i)
            hash[intervals[i].start] = i;
        for (auto in : intervals) {
            auto itr = hash.lower_bound(in.end);
            if (itr == hash.end()) res.push_back(-1);
            else res.push_back(itr->second);
        }
        return res;
    }
};
