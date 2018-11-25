#include <bits/stdc++.h>
using namespace std;

int binary_search(vector<int> &array, int value,int mode){
	// pre condition array must be sorted
	sort(array.begin(), array.end());
	// end
	int low=0, high=array.size(),mid;
	mid = low + (high-low)/2;
	if(array[mid]==value)
		return mid;
	while(low<high-1){
		if(array[mid]==value)
			return mid;
		else if(array[mid]<value)
			low = mid;
		else if(array[mid]>value)
			high=mid;
		mid = low + (high-low)/2;
	}
	if(mode==0)
		return -1;
	else if(mode==1)
		return low;
	else
		return high;
}


int main(){
	int n,temp,value,mode;
	scanf("%d",&n);
	vector<int> array;
	while(n--){
		scanf("%d",&temp);
		array.push_back(temp);
	}
	scanf("%d",&value);
	printf("select mode [0=search,1=lower_bound,anythng_else=upper_bound] ");
	scanf("%d",&mode);
	int result=binary_search(array,value,mode);
	if(mode==0 && result==-1)
		printf("Value not found\n");
	else
		printf("value = %d at index=%d\n",array[result],result);
	return 0;
}