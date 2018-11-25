

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "timer.h"

const unsigned MAX_LENGTH = 1000;

using namespace std;


Timer t;


void selectionSort(vector<int> &a){
    for(unsigned i = 0; i < a.size() - 1; i++){
        
        unsigned smallest_i = i;
        int smallest_value = a[i];
        for(unsigned j = i + 1; j < a.size(); j++){
            if( smallest_value > a[j]){
                smallest_i = j;
                smallest_value = a[j];
            }
        }
        
        int temp = a[i];
        a[i] = a[smallest_i];
        a[smallest_i] = temp;
        t.incrementA(); 
    }
}


int main(){
    
    srand(time(0));
    
    vector<int> a;
    
    
    for(unsigned length = 1; length < MAX_LENGTH; length++){
        
        a.clear();
    
        
        for(unsigned i = 0; i < length; i++){
            a.push_back(rand() % 10000);
        }
        
        
        t.setN(length);
        t.tic();
        
        selectionSort(a);
        t.toc();
        
        
        for(unsigned i = 0; i < length-1; i++){
            if(a.at(i) > a.at(i+1)){
                cout << "Error!" << endl;
            }
        }
    }
    t.saveResults("times.csv");
}