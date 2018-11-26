//
//  main.cpp
//  Ntpu_Algorithm1
//
//  Created by Keng on 13/12/2016.
//  Copyright © 2016 Keng. All rights reserved.
//

#include <iostream>

using namespace std;


int *price;
int *max_price;
int *s;
//use bottom up to build the max_price
int cut_rod(int n){
    
    int q;
    max_price[0]=0;

    for(int j=1;j<=n;j++){
        q=-1;
        for(int i=1;i<=j;i++){
            //compare maximum value verus new case value
            if(q<price[i]+max_price[j-i]){
                q=price[i]+max_price[j-i];
                s[j]=i;//store the best rod cutting case
            }
        }
        max_price[j]=q;//store the max_price for j
    }
    return max_price[n];
}
int get_count(int array[],int k){
    int n=0;
    while(k>0){
        k=k-s[k];
        n++;
    }
    return n;
}
int main() {
    
    int k,i=1;
    int count=0;
    //input there are how many price in the rod
    cin>>k;
    
    //create array for k space
    max_price=new int[k+1];
    price=new int[k+1];
    s=new int[k+1];
    //set each length max price value
    for(int i=0;i<=k;i++){
        max_price[i]=-1;
    }
    
    //input each price
    while(i<=k){
        cin>>price[i];
        i++;
    }
    //calculate optimization answer
    int output=cut_rod(k);
    cout<<output<<endl;
    
    count=get_count(s,k);
    //print how many count here
    cout<<count<<endl;
    //print_each_solution
    while(k>0){
        cout<<s[k]<<" ";
        k=k-s[k];
    }
        
    
    return 0;
}
