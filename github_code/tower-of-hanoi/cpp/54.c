#include <iostream>
#include "Algorithm/TowerOfHanoi.h"
using namespace std;

TowerOfHanoi::TowerOfHanoi(){
}
TowerOfHanoi::~TowerOfHanoi(){
}

void TowerOfHanoi::tower(int n, char BEG, char AUX, char END){
        //here disk 1<2<3....
        if(n==1){
            cout<<"Move disk "<<n<<" from "<<BEG<<" to "<<END<<"\n";
            return;
        }
        tower(n-1, BEG, END, AUX);
        cout<<"Move disk "<<n<<" from "<<BEG<<" to "<<END<<"\n";
        tower(n-1, AUX, BEG, END);
        return;
}
