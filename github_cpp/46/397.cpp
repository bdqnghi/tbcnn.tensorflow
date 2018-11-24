#include "bits/stdc++.h"
#define MIN(a,b,res) ((a)>(b))? (res)=(b):(res)=(a)
#define printArray(a,l,n) for(int(i)=(l);(i)<int(n);i++) { cout<<(a[i])<<' ';}
#define nl cout<<"\n";
using namespace std;
void createSegmentTree(int input[], int segmentTree[], int low, int high, int pos)
{
	int mid=0;
	if(low==high)
	{
		segmentTree[pos]=input[low];
		return;
	}
	mid=(low+high)/2;
	createSegmentTree(input,segmentTree,low,mid, 2*pos +1);
	createSegmentTree(input,segmentTree,mid+1,high, 2*pos +2);
	MIN(segmentTree[2*pos +1],segmentTree[2*pos +2],segmentTree[pos]);
}
int segmentTreeQuery(int segmentTree[],int qlb, int qub, int lb, int ub, int pos)
{
	if(qlb<=lb && qub >= ub) //total overlap
		return segmentTree[pos];
	else if(qlb> ub || qub < lb) // no overlap
		return INT_MAX;
	else //partial overlap
	{
		int result,mid;
		mid=(lb+ub)/2;
		MIN(segmentTreeQuery(segmentTree,qlb,qub,lb,mid,2*pos +1),segmentTreeQuery(segmentTree,qlb,qub,mid+1,ub,2*pos +2),result);
		return result;
	}
}
int closestPowerOfTwo(int N)
{
	if((N&(N-1))==0) //already a power of 2
	 return N;
	N|= N>>1;
	N|= N>>2;
	N|= N>>4;
	N|= N>>8;
	return (N+1);
}
int main()
{
	cout<<"array is : ";
	int input[]= {-1,-99,4,0,45,23,45,2,7,23,6767,213};
	printArray(input,0,sizeof(input)/sizeof(int));
	cout<<endl;
	int maxSize= closestPowerOfTwo(sizeof(input)/sizeof(int));
	int *segmentTree = new int[maxSize];
	createSegmentTree(input,segmentTree,0,11,0);
	cout<<"segment tree is : ";
	printArray(segmentTree,0,maxSize); nl
	int u,l;
	cout<<"enter range query lower and upper bound"; nl
	cin>>l>>u;
	cout<<"Mininum in range "<<l<<" to "<<u<<" is "<<segmentTreeQuery(segmentTree,l,u,0,11,0);
	return 0;
}