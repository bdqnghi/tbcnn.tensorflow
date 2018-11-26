// shell.cpp
#include<cstdlib>
#include<cstdio>
#include<deque>
#include<algorithm>
using namespace std;
void shellSortPhase(int a[], int length, int gap) {
    int i;
    for (i = gap; i < length; ++i) {
        int value = a[i];
        int j;
        for (j = i - gap; j >= 0 && a[j] > value; j -= gap) a[j + gap] = a[j];
        a[j + gap] = value;
    }
}
void shellSort(int a[], size_t length) { 
    deque<int> gaps;
    for(size_t z=length/2;z>701;z/=2) gaps.push_front(z);
    static int cuira[] = {701,301,132,57,23,10,4,1};
    for(int z=0;z<sizeof(cuira)/sizeof(int);++z) gaps.push_front(cuira[z]);
    while(gaps.size()) {
        shellSortPhase(a, length, gaps.back());
        gaps.pop_back();
    }
}
const int N = 10000000;
int main() {
    int* arr = new int[N];
    for(int z=0;z<N;++z) arr[z] = rand();    
    shellSort(arr,N);
    for(int z=1;z<N;++z) if(arr[z]<arr[z-1]) printf("!");    
    delete[] arr;
}
