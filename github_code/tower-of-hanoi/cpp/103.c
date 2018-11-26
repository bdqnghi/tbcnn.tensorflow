#include<iostream>
using namespace std;

void towerOfHanoi(int N, char from, char to, char extra) {
    if(N == 1) {
        cout<<"\nTransfer disk 1 from "<<from<<" to "<<to;
        return;
    }
    towerOfHanoi(N-1,from,extra,to);
    cout<<"\nTransfer disk "<<N<<" from "<<from<<" to "<<to;
    towerOfHanoi(N-1,extra,to,from);
}

int main(void) {
    int N;
    cout<<"\nEnter number of disks: ";
    cin>>N;
    
    char peg1 = 'A';
    char peg2 = 'B';
    char peg3 = 'C';
    
    towerOfHanoi(N,peg1,peg3,peg2);
}