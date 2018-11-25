

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
    	int n = intervals.size();
    	if (n==1)
    		return {-1};
    	vector<int> ans;
    	map<int,int> TM;
    	for (int i=0; i<n; i++)
    		TM[intervals[i].start] = i;
    	for (auto i:intervals){
    		auto j = TM.lower_bound(i.end);
    		ans.push_back(j==TM.end() ? -1:j->second);
    	}
    	return ans;
    }
};


