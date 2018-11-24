/* 
Segment Tree | Set 1 (Sum of given range)

Let us consider the following problem to understand Segment Trees.

We have an array arr[0 . . . n-1]. We should be able to
1 Find the sum of elements from index l to r where 0 <= l <= r <= n-1

2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.

Problem statement link https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/ 

*/

#include<iostream>
#include<climits>

using namespace std;

void makeTree(int arr[], int start, int end, int tree[], int index){

	if(start == end){
		tree[index] = arr[start];
		return;
	}

	int mid = (start+end)/2;

	makeTree(arr, start, mid, tree, 2*index+1);
	makeTree(arr, mid+1, end, tree, 2*index+2);

	tree[index] =  tree[2*index +1] + tree[2*index+2];

	return ;
}

int getSum(int tree[], int start, int end, int l, int r, int index){

	if(l <= start && r >= end)
		return tree[index];

	if(end < l || start >r)
		return 0;

	if(start != end){

	int mid = (start+end)/2;

	return getSum(tree, start, mid, l, r, 2*index+1) + getSum(tree, mid+1, end, l, r, 2*index+2);
	}
}

void updateTree(int tree[], int arr[], int start, int end, int i, int val, int index){

	if(i < start || i > end)
		return;

	tree[index] += val;

	if(start!=end){
		int mid = (start+end)/2;
		updateTree(tree, arr, start, mid, i, val, 2*index+1);
		updateTree(tree, arr, mid+1, end, i, val, 2*index+2);
	}
}

int main(){

	int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    int tree[2*n -1];
    makeTree(arr, 0, n-1, tree, 0);
    cout<<"Sum of values in given range 1 3 "<<getSum(tree, 0, n-1, 1, 3, 0)<<endl;

    //Update: set arr[1] = 10 and update corresponding segment tree nodes
    int diff = 10 - arr[1];
    arr[1] = 10;
    updateTree(tree, arr, 0, n-1, 1, diff, 0);

    cout<<"Sum of values in given range 1 3 "<<getSum(tree, 0, n-1, 1, 3, 0)<<endl;

	return 0;
}