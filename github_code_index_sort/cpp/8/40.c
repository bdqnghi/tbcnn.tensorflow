/*************************************************************************
	> File Name: quick.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月28日 星期二 15时03分39秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include<stdio.h>

void quick_sort(int *nums,int left,int right) {
    if(left >= right) return;
    int l = left;
    int r = right;
    while(l < r) {
        while(l < r && nums[r] >= nums[l]) {
            r--;
        }
        swap(nums[l],nums[r]);
        while(l < r && nums[l] <= nums[r]) {
            l++;
        }
        swap(nums[l],nums[r]);
    }
    quick_sort(nums,left,l - 1);
    quick_sort(nums,l + 1,right);
}
int a[15] = {0};
int main()
{
    int n;
    for(int i = 0; i < 10; i++) {
        scanf("%d",&a[i]);
    }
    quick_sort(a,0,9);
    for(int i = 0; i < 10; i++) {
        printf("%d\n",a[i]);
    }
}
