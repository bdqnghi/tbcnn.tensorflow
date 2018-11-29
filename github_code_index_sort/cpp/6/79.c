/*Matthew Moy
  Lab 6
  CSE 100
  radix.cpp */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void RadixSort(int array[],int length);
void printresult(int x[], int length);
vector < vector <int> > keys;

//My Main Function
int main(){
	int length = 0;
	cin>>length;
	do{
		int i = 0;
		keys.resize(10);
		int input[length];
		do{
			cin>>input[i];
			i++;
		}while(i < length);
		
		RadixSort(input, length);
		printresult(input, length);
		
		cin>>length;
	}while(length != 0);
}
void RadixSort(int array[],int length){
    int temp;
    int m=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<length;j++){
         temp=(int)((array[j])/pow(10,i))%10;
         keys[temp].push_back((array[j]));
        }
        for(int k=0;k<10;k++){
        	for(int l=0;l<keys[k].size();l++){
            	array[m]=keys[k][l];
            	m++;
         	}
         	keys[k].clear();
        }
		m=0;
    }
    keys.clear();
}
void printresult(int array[], int length){
    for(int i=0;i<length;i++)
        cout<<array[i]<<"\n";
}

