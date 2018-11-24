class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> m;
        for (int n : nums) m[n]++;
        int n = nums.size();
        map<int, vector<int>> freq;
        for (auto p : m) {
            if (freq.find(p.second) == freq.end()) freq[p.second] = vector<int>(1, p.first);
            else freq[p.second].push_back(p.first);
        }
        vector<int> res;
        for (int i = n; i > 0 && res.size() < k; i--) {
            if (freq.find(i) != freq.end() && freq[i].size() > 0) {
                for (int j = 0; j < freq[i].size() && res.size() < k; j++) res.push_back(freq[i][j]);
            }
        }
        return res;
    }
};
