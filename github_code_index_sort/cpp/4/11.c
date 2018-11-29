/********HEAPS*************/
#include <algorithm>
#include <vector>
int a[]={1,2,3,4};
vector<int> v(a,a+sizeof(a)/sizeof(a[0]);
make_heap(v.begin(),v.end(),greater<int>());    //make min_heap out of elements
make_heap(v.begin(),v.end(),less<int>());       //make max_heap out of elements
v.push_back(6);
push_heap(v.begin(),v.end(),cmp);    //max-heapify positioning last element of vector with comparator function if any
pop_heap(v.begin(),v.end(),cmp);     //move max_element of heap to last position of array
v.pop_back();                    //remove max_element of heap
sort_heap(v.begin(),v.end(),cmp);    //heap-sort
