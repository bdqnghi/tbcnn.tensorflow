#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    int mySqrt(int x) {
		
		int left=1,right=x;
		
		
		
		
		
		
		while(left<=right){
			
			int mid=left+(right-left)/2;
			
			if(mid== x/mid){
				return mid;
			}else if(mid<x/mid){
				
				left=mid+1;
			}else{
				
				right=mid-1;
			}
		}

		return right;
    }
};

int main(){
    Solution s;
    for(int i=0;i<INT_MAX;i++){
        cout<<s.mySqrt(i)<<endl;
    }
    return 0;
}


class Solution {
public:
    int mySqrt(int x) {
        int left = 1, right = x, ans=x;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mid <= x / mid) {
                left = mid + 1;
                ans = mid;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
};