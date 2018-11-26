/*Radix-sort first sorts the integers by their least significant d bits, then their next significant d bits, and 
so on until, in the last pass, the integers are sorted by their most significant d bits.*/
#include <iostream>
#include <vector>

using namespace std;

void radixSort(vector<int> &a){
  int d = 8, w = 32;
  for (int p=0; p<w/d; p++){
    vector<int> c(1<<d);
    vector<int> b(a.size());
    for(int i=0; i<a.size(); i++)
      c[(a[i]>>d*p)&((1<<d)-1)]++;
    for(int i=0; i<1<<d; i++)
      c[i] += c[i-1];
    for (int i=a.size()-1; i>=0; i--)
      b[--c[(a[i]>>d*p)&((1<<d)-1)]] = a[i];
    a = b;
  }
}

int main(){
  vector<int> arrayToBeSorted = {13,8,5,2,4,0,6,9,7,3,12,1,10,11}; 
  radixSort(arrayToBeSorted);
  for(int element:arrayToBeSorted){
    cout<<element<<" ";
  }
  return 0;
}
