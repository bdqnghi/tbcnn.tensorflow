//
// Created by bsz on 2018/11/15.
//
/**
 * -------------归并排序---------------
 * -----------------------------------
 * 时间复杂度：o(n)
 * 空间复杂度：o(nlgn)
 * 伪代码：
 * MERGE(A,p,q,r)
 * n1 = q - p + 1 // 数组A[p..q]长度
 * n2 = r - q     // 数组A[q+1..r]长度
 * //let L[1..n1+1] and R[1..n2+1] be new array
 * for i = 1 to n1
 *     L[i] = A[p + i -1]
 * for j = 1 to n2
 *     R[j] = A[q + j]
 * L[n1+1] = ∞
 * R[n2+1] = ∞
 * i = 1
 * j = 1
 * for k = p to r
 *     if L[i] < R[j]
 *         A[k] = L[i]
 *         i = i + 1;
 *     else
 *         A[k] = R[i]
 *         j = j + 1
 *
 * MERGE-SORT(A,p,r)
 * if p < r
 *     q =  「(p+r)/2」 //向下取整，打不出来取整符号用这个代替吧
 *     MERGE-SORT(A,p,q)
 *     MERGE-SORT(A,q+1,r)
 *     MERGE(A,p,q,r)
 *
 */

#include<iostream>
using std::cout;
using std::endl;

void merge(int *,int,int,int);
void merge_sort(int *,int,int);

int main(){
    int A[9] = {5,2,4,7,1,3,2,6,8};
    merge_sort(A,0,8);
    for (int i : A) {
        cout << i << " ";
    }
    cout<<endl;
    return 0;
}

void merge_sort(int *A, int p, int r) {
    if(p < r){//p=r代表序列只剩一个不用归并，p不应该出现大于r的情况
        int q =( p + r ) / 2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;//获取左面序列大小
    int n2 = r - q;//获取右面序列大小
    auto *L = new int [n1+1];//申请临时空间存储左面序列，这里多new一块空间是为了不让后面越界。
    for (int i = 0; i < n1; ++i) {//拷贝左面序列
        L[i] = A[p+i];
    }

    auto *R = new int [n2+1];//申请临时空间存储右面序列，这里多new一块空间是为了不让后面越界。
    for (int j = 0; j < n2; ++j) {//拷贝右面序列
        R[j] = A[q+j+1];
    }

    //设置为无穷，保证一边序列归并完成后，不会内存泄漏
    //设置最后一块空间无穷大，如果是逆序则应设为无穷小
    L[n1] = 65535;
    R[n2] = 65535;

    int i = 0;
    int j = 0;
    for (int k = p; k < r+1; ++k) {
        if(L[i]<R[j]){//取两个序列中较小第一位放入新序列，并右移一位该序列的游标
            A[k] = L[i];
            i++;
        } else{
            A[k] = R[j];
            j++;
        }
    }
    //释放内存
    delete []L;
    delete []R;
}
