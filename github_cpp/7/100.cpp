#include<iostream>
using namespace std;
void towerOfHanoi(int n, char from, char to, char aux){
  if(n==1) {
    cout<<"Disk "<<n<<" is moved from "<<from<<" to "<<to<<endl;
    return;
  }
  towerOfHanoi(n-1, from, aux, to);                                  //n-1 disks are first moved from 'A' to 'C'
  cout<<"Disk "<<n<<" is moved from "<<from<<" to "<<to<<endl;      //moving n th disk to 'B'
  towerOfHanoi(n-1, aux, to, from);                                  //n-1 disks are then moved from 'C' to 'B'
}
int main(){
  int n = 3;
  towerOfHanoi(n, 'A', 'B', 'C');
  
  return 0;
}
