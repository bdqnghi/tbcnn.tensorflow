/*
bucketSort(arr[], n)
1) Create n empty buckets (Or lists).
2) Do following for every array element arr[i].
.......a) Insert arr[i] into bucket[n*array[i]]
3) Sort individual buckets using insertion sort.
4) Concatenate all sorted buckets.
*/

// Average case O(n+k), k=# buckets


#include<iostream>
#include<iomanip>
using namespace std;
void BucketSort(int arr[],int size){
	const int MAX_SIZE = 101;
	int bucket[MAX_SIZE];
	
	for (int i = 0; i < MAX_SIZE; ++i){
		bucket[i] = 0;
	}
	for (int i = 0; i <size; ++i)
		++bucket[arr[i]];

	for (int i = 0,j = 0; j < MAX_SIZE; ++j)
		for (int k = bucket[j]; k>0; --k)
			arr[i++] = j;
		
}
int main(){
	int arr[10] = { 10, 24, 22, 62, 1, 50, 100, 75, 2, 3 };
	BucketSort(arr, 10);
	for (int i = 0; i <10; ++i){
		cout << arr[i] << endl;
	}
	//return 0;
}


/*
Right now, you are correct that iterating across the input array to distribute the elements into buckets takes time O(n). However, you are slightly off when you say that the total amount of time required to assemble the array is O(k * (average number of elements per bucket)). Note that because there are n elements and k buckets, this would come out to O(k * (n / k)) = O(n), for a total runtime of O(n). To see why the real answer is O(n + k), we need to look more carefully at that big-O term.

For starters, you are absolutely right that the average amount of time that you spend on each bucket is O(n / k). You then say that since there are k buckets, the total runtime is then O(k * (n / k)) = O(n). However, this is incorrect: in particular, it is not true that k * O(n / k) = O(n). The reason for this is that the term O(n / k) is hiding a constant factor. When you visit each bucket and take a look at the elements it contains, it doesn't take exactly n / k time, or even some constant multiple of n / k time. For example, what happens if the bucket is empty? In that case, you're still spending some amount of time looking at the bucket, since you have to determine that you shouldn't iterate over its elements. Thus a more accurate representation of the time required per bucket is something like c0(n / k) + c1, where c0 and c1 are implementation-specific constants. This expression is, of course, O(n / k).

The catch is what happens when you multiply this expression by k to get the total amount of work done. If you compute

k * (c0(n / k) + c1)
You get

c0n + c1k
As you can see, this expression depends directly on k, so the total runtime is O(n + k).

A more direct way to arrive at this result would be to look at the code for the second step of the bucket sort, which looks like this:

For each bucket b:
    For each element x in b:
	Append x to the array.
How much work is done overall? Well, there are k different buckets, so the outermost loop must take at least O(k) time, because we have to look in each bucket. Inside, the inner loop will execute a total of O(n) times overall, because there are a total of n elements distributed across the buckets. From this, we get the O(n + k) total runtime.

The reason that this is important is that it means that if you try doing a bucket sort with a huge number of buckets (say, much greater than n), the runtime might be dominated by the time required to scan over all the buckets looking for the buckets that you actually used, even if most of them are empty. The reason that radix sort is useful is that it uses multiple iterations of bucket sort where there are only two buckets, which runs in time O(n + 2) = O(n). Since you only need to do O(lg U) iterations of this (where U is the maximum value in the array), the runtime is O(n lg U) instead of the O(n + U) you'd get from bucket sort, which is much worse.
*/