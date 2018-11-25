/*************************************************************************
	> File Name: bucketSort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年03月15日 星期二 11时50分11秒
 ************************************************************************/

#include<iostream>
using namespace std;
template<typename Comparable>
vector<Comparable> bucketSort(vector<Comparable> & vec, int maxSize)
{
    vector<Comparable> bucket(maxSize);
    for(int i = 0; i < vec.size(); ++i){
        bucket[vec[i]]  = vec[i];
    }
    return bucket;
}

