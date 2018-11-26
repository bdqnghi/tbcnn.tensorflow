/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
/*
map:red-black-tree, O(nlogn)
since no same start point =>map : start - id
find lower_bound j, j.start as the smallest >=i.end
*/
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
    		auto j = TM.lower_bound(i.end);//std::_Rb_tree_iterator<std::pair<const int, int> >
    		ans.push_back(j==TM.end() ? -1:j->second);
    	}
    	return ans;
    }
};
//92
/*
76
Find smallest start i,largest start j
store
	map[intervals[i].start - start] = i;
for every interval, find j
			int j = intervals[i].end - start;
            while (j < map.size() && map[j] == -1) {
                j++;
            }

*/
