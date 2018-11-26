//
//  main.cpp
//  Rod_Cutting
//
//  Created by Lois on 10/9/17.
//  Copyright © 2017 Yang Hu. All rights reserved.
//  Dynamic programming: rod cutting problem
//  Dynamic programming thus uses additional memory to save computation time

#include <iostream>
#include <vector>
#include <map>
using namespace std;

//Recursive top-down implementation: O(2^n)
int RodCutting(map<int,int> &price, int n) {
    int value = 0;
    if(n>=0) {
        for(int i=1;i<=n;i++)
            value = max(price[i]+RodCutting(price,n-i),value);
    }
    
    return value;
}

// top-down with memoization


// bottom-up with memoization O(n^2)
int BottonUpRodCut(map<int,int> &price, int n) {
    int value = 0;
    vector<int> r(n+1);
    r[0]=0;
    for(int j = 1;j<=n;j++) {
        value = -1;
        for(int i=1;i<=j;i++) {
            value = max(value,price[i]+r[j-i]);
        }
        r[j]=value;
    }
    return r[n];
}


// establish a class to store a solution
class Solution {
private:
    vector<int> r; // revenue
    vector<int> s; // cut length
    int size;  // length
public:
    // constructors
    Solution(int n): r(n+1), s(n+1), size(n) {};
    Solution();
    
    // modify
    void modifyr(int i, int key) {r[i]=key;};
    void modifys(int i, int key) {s[i]=key;};
    
    // get values
    int getr(int i) const {return r[i];};
    int gets(int i) const {return s[i];};
    int getn() {return size;};
};


// return the total return as well as the first piece to cut
Solution ExtendedRodCut(map<int,int> &price, int n) {
    Solution plan(n);
    int value;
    plan.modifyr(0, 0);
    for(int j=0;j<=n;j++) {
        value = -1;
        for(int i=0;i<=j;i++) {
            if(value < (price[i]+plan.getr(j-i)) ) {
                value = price[i]+plan.getr(j-i);
                plan.modifys(j, i);
            }
        }
        plan.modifyr(j,value);
    }
    return plan;
}

// funtion to print out the cutting plan
void PrintSolution(Solution plan) {
    int n = plan.getn();
    while(n>0) {
        cout << plan.gets(n) << ' ';
        n = n - plan.gets(n);
    }
    cout << endl;
    return;
}


int main(int argc, const char * argv[]) {
    // price table
    map<int, int> price({{1,1},{2,5},{3,8},{4,9},{5,10},{6,17},{7,17},{8,20},{9,24},{10,30}});
    
    //Recursive top-down implementation
    for(int i=1; i <=10;i++)
        cout << BottonUpRodCut(price, i) << endl;
    
    // return the total return as well as the first piece to cut
    Solution s1 = ExtendedRodCut(price, 7);
    cout << "Revenue: " << s1.getr(s1.getn()) << endl;
    PrintSolution(s1);
    return 0;
}
