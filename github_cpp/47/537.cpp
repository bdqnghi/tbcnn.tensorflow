https://leetcode.com/problems/search-for-a-range/description

int result(auto v, int start , int end , int target){

    //cout<<start<<"  "<<end<<endl;

    if(start == end){
        if(v[start] == target) return start;
        else return -1;
    }
    if(start > end || start < 0 || end > v.size()-1) return -1;

    int mid = start + (end - start) / 2;
    //cout<<"mid "<<mid << endl;

    if(v[mid] == target) return mid;
    else if(v[mid] < target) return result(v, mid+1 , end , target); //remember mid + 1 hoga idhar if not there the testcase that fails is [5,7,7,8,8,10] to find is 6
    else if(v[mid] > target) return result(v, start , mid-1 , target); //remember mid - 1 hoga idhar

}



class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int min = 0;
        int max = 0;

        vector <int > v;

        int value = result(nums , 0 ,nums.size()-1 , target);

        if(value == -1){
            v.push_back(-1);v.push_back(-1);
            return v;
        }
        else{
            for(int i = value ; i>=0 ; i--) if(nums[i] == target) min = i;
            for(int i = value ; i<nums.size() ; i++) if(nums[i] == target) max = i;
        }

        v.push_back(min);
        v.push_back(max);

        return v;


    }
};
