#include <iostream>
using namespace std;

void shellsort(int list[], int length){
    int j;
    for (int gap=length/2; gap > 0; gap /= 2){

        for (int i=gap; i < length; i++){
            
            int temp = list[i];
            
            for (j=i; j>=gap && temp < list[j-gap]; j-=gap){

                list[j] = list[j-gap];
            }
            list[j]=temp;
        }
    }
}

int main(){
    int tester[10];
    for(int i=0;i<10;i++){
        tester[i]= 10-i;
        cout << tester[i] << " ";
    }
    cout << endl << endl;
    shellsort(tester,10);
    for(int j=0;j<10;j++){
        cout << tester[j] << " ";
    }
    cout << endl;
    return 0;
}