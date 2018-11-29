#include <iostream>  
#include "string.h"
#include <vector>
using namespace std; 


//need to assist space, temp
/*void quickSort(vector<int> &nums, int b, int e, vector<int> &temp)
{
    int m = (b + e) / 2;
    if (m != b) {

        int lb = b, rb = e - 1;

        for (int i = b; i < e; i++) {
            if (i == m)
                continue;
            if (nums[i] < nums[m])
                temp[lb++] = nums[i];
            else
                temp[rb--] = nums[i];
        }

        temp[lb] = nums[m];
        
        for (int i = b; i < e; i++)
            nums[i] = temp[i];
        
        quick_sort(nums, b, lb, temp);
        quick_sort(nums, lb + 1, e, temp);
    }
}*/



//最大时间代价为θ(n²)，最小时间代价为θ(n*logn)，平均时间代价为θ(n*logn)
/*void quickSort(int s[], int l, int r)  
{  
    if (l < r)  
    {        
        int i = l, j = r, x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j]>= x) {   // 从右向左找第一个小于x的数  
                j--;
            }
            if(i < j) {
                s[i++] = s[j];
            }  
                  
            while(i < j && s[i]< x) {     // 从左向右找第一个大于等于x的数
                i++;
            }     
                   
            if(i < j) {
                s[j--] = s[i];  
            }                    
        }  
        s[i] = x;  
        quickSort(s, l, i - 1); // 递归调用  
        quickSort(s, i + 1, r);  
    }  
}
*/

//quick sort
/*void quickSort(int nums[], int b, int e)
{
    if (b < e) {
        int lb = b, rb = e;
        while (lb < rb) {
            while (nums[rb] >= nums[b] && lb < rb) {
                rb--;
            }
            while (nums[lb] <= nums[b] && lb < rb) {
                lb++;
            }
            swap(nums[lb], nums[rb]);
        }
        swap(nums[b], nums[lb]);
        quickSort(nums, b, lb - 1);
        quickSort(nums, lb + 1, e);
    }
}*/

//my quicksort
/*void quickSort(int nums[], int left, int right) {
    int pivot = nums[left];
    if(left < right) {
        //int pivot = nums[left];
        int l = left, r = right;
        while(l < r) {
            //must --r first
            while(l < r && nums[r] <= pivot) {
                --r;
            }
            while(l < r && nums[l] >= pivot) {
                ++l;
            }
            swap(nums[l], nums[r]);
        }
        swap(nums[left], nums[l]);
        quickSort(nums, left, l - 1);
        quickSort(nums, l + 1, right);
    }
}*/

/*************************     There are four kinds of method for sorting, using quick sort    ****************/

//Lei Zhang, this is better, from small to large
//pivot begin from left
/*void quickSort(int nums[], int left, int right ){
    //For here, I can use if(left <= right) 
    if(left < right){
        int pivot = nums[left];
        int l = left + 1, r = right;
        while(l <= r){
            //can change the sequence of r-- and l++           
            while(l <= r && nums[l] <= pivot) {
                l++;
            }
            while(l <= r && nums[r] >= pivot) {
                r--;
            }
            if(l < r) {
                swap(nums[l++], nums[r--]);
            }
        }
        swap(nums[r], nums[left]);
        quickSort(nums, left, r - 1);
        quickSort(nums, r + 1, right);
    }
}


//Lei, from large to small
void quickSort(int nums[], int left, int right ){
    if(left < right){
        int pivot = nums[left];
        int l = left + 1, r = right;
        while(l <= r){
            //can change the sequence of r-- and l++            
            while(l <= r && nums[l] >= pivot) {
                l++;
            }
            while(l <= r && nums[r] <= pivot) {
                r--;
            }
            if(l < r) {
                swap(nums[l++], nums[r--]);
            }
        }
        swap(nums[r], nums[left]);
        quickSort(nums, left, r - 1);
        quickSort(nums, r + 1, right);
    }
}


//Lei, from samll to large
//pivot begin from right
void quickSort(int nums[], int left, int right ){
    if(left < right) {
        //int pivot = nums[left];
        int pivot = nums[right];
        int l = left, r = right - 1;
        while(l <= r){
            //can change the sequence of r-- and l++   
            while(l <= r && nums[l] <= pivot) {
                l++;
            }
            while(l <= r && nums[r] >= pivot) {
                r--;
            }
            if(l < r) {
                swap(nums[l++], nums[r--]);
            }
        }
        swap(nums[l], nums[right]);
        quickSort(nums, left, l - 1);
        quickSort(nums, l + 1, right);
    }
}

//Lei, from large to samll
void quickSort(int nums[], int left, int right ){
    if(left < right) {
        //int pivot = nums[left];
        int pivot = nums[right];
        int l = left, r = right - 1;
        while(l <= r){
            //can change the sequence of r-- and l++            
            while(l <= r && nums[l] >= pivot) {
                l++;
            }
            while(l <= r && nums[r] <= pivot) {
                r--;
            }
            if(l < r) {
                swap(nums[l++], nums[r--]);
            }
        }
        swap(nums[l], nums[right]);
        quickSort(nums, left, l - 1);
        quickSort(nums, l + 1, right);
    }
}*/

/***********************************     End     ***************************************/


//quick sort, 06/22/2016
/*void quickSort(int nums[], int left, int right) {
    if(left < right) {
        int pivot = nums[left];
        int l = left + 1, r = right;
        while(l <= r) {
            while(l <= r && nums[l] <= pivot) {
                ++l;
            }
            while(l <= r && nums[r] >= pivot) {
                --r;
            }
            if(l <= r) {
                swap(nums[l], nums[r]);
                ++l;
                --r;
            }
        }
        swap(nums[r], nums[left]);
        quickSort(nums, left, r - 1);
        quickSort(nums, r + 1, right);
    }    
}*/

//10/04/2016
// void quickSort(int num[], int left, int right) {
//     if(left < right) {
//         int pivot = num[left];
//         int l = left + 1;
//         int r = right;
//         while(l <= r) {
//             while(l <= r && pivot >= num[l]) {
//                 ++l;
//             }
//             while(l <= r && pivot <= num[r]) {
//                 --r;
//             }
//             if(l <= r) {
//                 swap(num[l], num[r]);
//                 ++l;
//                 --r;
//             }       
//         }
//         swap(num[left], num[r]);
//         quickSort(num, left, r - 1);
//         quickSort(num, r + 1, right);
//     }

// }


/*void quickSort(int v[], int begin, int end){
    if(end - begin<=1) return;
    int pivot = v[end-1], less_end = begin;

    for(int i=begin; i<end-1; i++)
        if(v[i]<pivot) swap(v[i], v[less_end++]);

    swap(v[end-1], v[less_end]);
    quickSort(v, begin, less_end);
    quickSort(v, less_end + 1, end);
}*/


int main() {  
    int array[] = {3, 2, 5, 4, 7, 6}, k;  
    int len = sizeof(array)/sizeof(int);  

    cout << "The orginal arrayare:" << endl;  
    for(k = 0;k < len;k++)  
        cout << array[k] << ",";  
    cout << endl;  

    quickSort(array, 0, len - 1);  

    cout << "The sorted arrayare:" << endl;  
    for(k = 0; k < len; k++)  
        cout << array[k] << ",";  
    cout << endl;  
    //system("pause");  

    cout << sizeof(array) << endl;

    char a[] = "abc";
    cout << sizeof(a) << " " << strlen(a)<< endl;
    return 0;  
}
