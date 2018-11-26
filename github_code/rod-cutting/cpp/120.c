#include <iostream>
#include <algorithm>

using namespace std;

void cutRod(int *array, int length) {
    int *value = new int[length+1];
    value[0] = 0;
    int j, k, maxValue;
    for(j = 1; j <= length; ++j){
        maxValue = 0;
        for(k = 0; k < j; ++k){
            maxValue = max(maxValue, (array[k] + value[j-k-1]) );    
        }
        value[j] = maxValue;
    }
    for(j = 1; j <= length; ++j ){
        cout<<j<<":"<<value[j]<<endl;
    }
    cout<<endl;
}

int main(){
    int arr[] = {1,5,8,9,10,17,17,20};
    int length = sizeof(arr)/sizeof(int);

    cutRod(arr, length);

    return 0;
}