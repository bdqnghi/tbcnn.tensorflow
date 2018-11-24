//
//  main.cpp
//  tower-of-hanoi
//
//  Created by Phanindra Saggurthi on 16/06/18.
//  Copyright © 2018 Phanindra Saggurthi. All rights reserved.
//

#include <iostream>
#include <array>
#include <stack>
using namespace std;
const int kNumPegs=3;

void computeTowerOfHanoi(int num_rings,array<stack<int>,kNumPegs>& pegs,int from_peg,int to_peg,int use_peg){
    if(num_rings){
        computeTowerOfHanoi(num_rings-1, pegs,from_peg,use_peg,to_peg);
        pegs[to_peg].push(pegs[from_peg].top());
        pegs[from_peg].pop();
        cout<<" From peg : "<<from_peg+1<<" to peg : "<<to_peg+1<<endl;
        computeTowerOfHanoi(num_rings-1, pegs,use_peg,to_peg,from_peg);
    }
}
void computeTowerOfHanoi(int num_pegs){
    array<stack<int>,kNumPegs> pegs;
    for(int ring_num=num_pegs;ring_num>=1;--ring_num){
        pegs[0].push(ring_num);
    }
    computeTowerOfHanoi(num_pegs,pegs,0,1,2);
    cout<<"---------\n";
}

int main(int argc, const char * argv[]) {
    int num_rings;
    cin>>num_rings;
    computeTowerOfHanoi(num_rings);
    return 0;
}
