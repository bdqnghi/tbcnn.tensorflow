







#include <iostream>
using namespace std;

void InsertSort(int * a, int n){
    for(int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 and a[j] > key){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}


class listTode{
public:
    void insert(int a){
        
    }
};
void BucketSort(int * a, int n){
    listTode *b = new listTode[n];
    for(int i = 0; i < n; i++){
        b[n * a[i]].insert(a[i]);
    }
    for(int i = 0; i < n; i++){
        
    }
    int j = 0;
    for(int i = 0; i < n; i++){
        
    }
}

void BucketSort1(int * a, int n){
    listTode *b = new listTode[n];
    for(int i = 0; i < n; i++){
        b[n * a[i]].insert(a[i]);
    }
    for(int i = 0; i < n; i++){
        
    }
    int j = 0;
    for(int i = 0; i < n; i++){
        
    }
}



int main(int argc, const char * argv[]) {
    
    return 0;
}
