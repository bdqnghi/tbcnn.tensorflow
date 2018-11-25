#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int max(const int& a, const int& b) {
  return (a > b) ? a : b;
}

int rodcut(const int* val, const int& size, const int& rodlength) {
  int sol[rodlength+1];
  for(int i=0;i<=rodlength;i++)
    sol[i] = 0;

  for(int i=0; i<=rodlength; i++) {
    for(int j=1; j<size; j++) {
    if( j <= i)
      sol[i] = max(sol[i], val[j] + sol[i-j]);
    }
  }

  cout<<"Printing array: "<<endl<<"[ ";
  for(int i=0;i<rodlength;i++) {
    cout<<sol[i]<<" ";
  }
  cout<<sol[rodlength]<<" ]"<<endl;
  return sol[rodlength];
}

int main() {
  int val[] = {-1,1,3,4,5};
  int size = sizeof(val)/sizeof(val[0]);
  int rodlength = 9;
  int ans = rodcut(val, size, rodlength);
  cout<<"The max value is: "<<ans<<endl;
  return 0;
}
