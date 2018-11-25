/*

 * cutRod.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: user

#include <iostream>
#include<string>
#include<limits.h>
using namespace std;


void cutRod(int price[],int n){
int table[n+1];
table[0]=0;
for(int i=1;i<=n;i++){
	int maxval=INT_MIN;
	for(int j=0;j<i;j++){
		maxval=max(price[j]+table[i-j-1],maxval);
	table[i]=maxval;
	}
}

cout<<"Max val is "<<table[n]<<endl;
}

void cuttingRod(int price[],int n){
	int table[n+1];
	table[0]=0;
	for(int i=1;i<=n;i++){
		int maxval=INT_MIN;
		for(int j=0;j<i;j++){
			maxval=max(maxval,table[i-j-1]+price[j]);
		}
		table[i]=maxval;
	}
}
int main(){
	int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
	    int size = sizeof(arr)/sizeof(arr[0]);
	    cutRod(arr,size);
}
*/
