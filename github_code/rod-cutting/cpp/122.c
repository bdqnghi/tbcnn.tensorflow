//
//  RodCutting.cpp
//  DynamicProgramming
//
//  Created by PRO on 2018-02-25.
//  Copyright © 2018 AIR. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int Rod_Cutting(int length,int price[]);
void PrintCut(int length,int track[],int price[]);

int main(int argc, const char * argv[]) {
    
    int price[10] = {1,5,8,9,10,17,17,20,24,30};
    int length = sizeof(price)/sizeof(price[0]);
    
    int profit = Rod_Cutting(length, price);
    
    cout<<"Maximum Total profit is: " <<profit<<endl;
    cout<<endl;
    
    return 0;
}

int Rod_Cutting(int length,int price[]){
    
    int r[length + 1];
    r[0] = 0;
    int track[length + 1];
    
    for(int i = 1; i <= length; i ++){
        for(int j = 0;j < length;j ++){
            if(i - j - 1 >= 0){
                int temp = price[j] + r[i - j - 1];
                if(r[i] < temp){
                    r[i] = temp;
                    track[i] = j + 1;
                }
            }
        }
    }
    
    PrintCut(length, track, price);
    
    
    return r[length];
}

void PrintCut(int length,int track[],int price[]){
    
    while(length > 0){
        cout<<"Rod Length: "<< track[length]<<" "<<"Price: "<<price[length - 1]<<endl;
        length -= track[length];
    }
    cout << endl;
}
