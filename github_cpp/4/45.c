#include<iostream>
using namespace std;
void towerOfHanoi(int n, char from, char to, char aux){
  if(n==1) {
    cout<<"Disk "<<n<<" is moved from "<<from<<" to "<<to<<endl;
    return;
  }
  towerOfHanoi(n-1, from, aux, to);                                  
  cout<<"Disk "<<n<<" is moved from "<<from<<" to "<<to<<endl;      
  towerOfHanoi(n-1, aux, to, from);                                  
}
int main(){
  int n = 3;
  towerOfHanoi(n, 'A', 'B', 'C');
  
  return 0;
}
