class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int max_elem = INT_MIN, min_elem = INT_MAX, l = nums.size(), res = 0;
        if (l < 2) return res;
        for (int n : nums) {
            max_elem = max(max_elem, n);
            min_elem = min(min_elem, n);
        }
        if (max_elem == min_elem) return res;
        int bucket_size = (max_elem - min_elem) / l + 1;
        vector<vector<int>> gaps(l + 1, vector<int>(0));
        for (int n : nums) {
            int bucket_index = (n - min_elem) / bucket_size;
            if (gaps[bucket_index].size() == 0) {
                gaps[bucket_index].push_back(n);
                gaps[bucket_index].push_back(n);
            } else {
                gaps[bucket_index][0] = min(n, gaps[bucket_index][0]);
                gaps[bucket_index][1] = max(n, gaps[bucket_index][1]);
            }
        }
        int pre = 0;
        for (int i = 1; i < l + 1; i++) {
            if (gaps[i].size() == 0) continue;
            res = max(res, gaps[i][0] - gaps[pre][1]);
            pre = i;
        }
        return res;
    }
};