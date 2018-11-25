#include<iostream>
using namespace std;

void towerOfHanoi(int N, char from, char middle, char to) {
    if(N == 1) {
        cout<<"\nTransfer disk 1 from "<<from<<" to "<<middle;
        cout<<"\nTransfer disk 1 from "<<middle<<" to "<<to;
        return;
    }
    towerOfHanoi(N-1,from,middle,to);
    cout<<"\nTransfer disk "<<N<<" from "<<from<<" to "<<middle;
    towerOfHanoi(N-1,to,middle,from);
    cout<<"\nTransfer disk "<<N<<" from "<<middle<<" to "<<to;
    towerOfHanoi(N-1,from,middle,to);
}

int main(void) {
    int N;
    cout<<"\nEnter number of disks: ";
    cin>>N;
    
    char peg1 = 'A';
    char peg2 = 'B';
    char peg3 = 'C';
    
    towerOfHanoi(N,peg1,peg2,peg3);
}