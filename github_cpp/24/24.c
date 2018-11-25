

#include <bits/stdc++.h>

#define ll long long 

#define tr(container, it) \ 
	for(typeof(container.begin()) it = container.begin();it != container.end(); it++)


using namespace std;

bool myfunction (int i,int j) { return (i<j); }





int bsearch_0(vector<int>& A,int target)
{
	int lo = 0;
	int hi = A.size()-1;
	int mid;

	while(lo <= hi)
	{
		mid = lo + (hi-lo)/2;
		if(A[mid]==target)
			return mid;
		else if (A[mid]>target)
		{
			hi = mid-1;
		}
		else 
		{
			lo = mid+1;
		}
	}	
	return -1;
}



int lowerbound(vector<int>& A,int target)
{
	int lo = 0;
	int hi = A.size()-1;
	int mid;

	while(lo < hi)
	{
		mid = lo + (hi-lo)/2;
		if (A[mid]>=target)
		{
			hi = mid;
		}
		else 
		{
			lo = mid+1;
		}
	}	

	if(A[lo] >= target)
		return lo;
	else
		return -1;
}


int upperbound(vector<int>& A,int target)
{
	int lo = 0;
	int hi = A.size()-1;
	int mid;

	while(lo < hi)
	{
		mid = lo + (hi-lo+1)/2;
		if (A[mid]<=target)
		{
			lo = mid;
		}
		else 
		{
			hi = mid-1;
		}
	}

	if(A[lo] <= target)
		return lo;
	else
		return -1;
}

int main () 
{
	int A[] = {0,5,13,19,22,41,55,68,72,81,98};
	std::vector<int> V(A,A+(sizeof(A)/sizeof(A[0])));
	cout<<V.size()<<endl;

	int search  = bsearch_0(V,98);
	cout << search << endl;
 	int lsearch = lowerbound(V,100);
 	int usearch = upperbound(V,68);

	cout << lsearch << endl;
 	cout << usearch << endl;

 	
 	vector<int>::iterator low,up;
 	low = lower_bound(V.begin(),V.end(),100);
 	up = upper_bound(V.begin(),V.end(),68);

 	
 	
 	
 	cout << "Using STL for lower : " << (low - V.begin())   << '\n';
	cout << "Using STL for upper : " << (up - V.begin()) -1 << '\n';

	int B[] = {32,71,12,45,26,80,53,33};
	vector<int> W(B,B+(sizeof(B)/sizeof(B[0])));

	sort(W.begin(),W.end(),myfunction);
	tr(W,it)
		cout<<*it<<endl;

	return 0;
}
