#include <cstdio>
#define MAXSIZE 100
using namespace std;

typedef int DataType;

/*
10
2 4 1 10 3 7 8 9 5 6
10
3 4 6 6 2 4 19 3 12 1
*/

struct sqlist {
    DataType data[MAXSIZE];
    int len;
};

sqlist L;

void merge_process(sqlist &L,int low,int mid,int high) {
    int i=low,j=mid+1,s=high-low+1;
    DataType *tmpArr;
    tmpArr=new int[s];
    int k=0;
    while(i<=mid && j<=high) {
        if(L.data[i]<L.data[j]) tmpArr[k++]=L.data[i++];
        else tmpArr[k++]=L.data[j++];
    }
    while(i<=mid) tmpArr[k++]=L.data[i++];
    while(j<=high) tmpArr[k++]=L.data[j++];
    for(i=0;i<s;i++) L.data[low+i]=tmpArr[i];
    delete []tmpArr;
}

void merge_sort(sqlist &L,int low,int high) {
    if(low<high) {
        int mid=(low+high)/2;
        merge_sort(L,low,mid);
        merge_sort(L,mid+1,high);
        merge_process(L,low,mid,high);
    }
}

int main() {
    int n;
    while(~scanf("%d",&n)) {
        L.len=n;
        for(int i=0;i<n;i++) scanf("%d",&L.data[i]);
        merge_sort(L,0,L.len-1);
        for(int i=0;i<n;i++) printf("%d ",L.data[i]);
        printf("\n");
    }
}
