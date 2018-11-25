


#include <iostream>
#include<cmath>
using namespace std;

void printHanoiSteps(int n, string src, string dest, string helper) {
    if (n == 0) return;

    printHanoiSteps(n - 1, src, helper, dest);
    cout <<"Move " <<n<<"th disc from "<< src << " to " << dest << endl;
    printHanoiSteps(n - 1, helper, dest, src);
}

int main() {
    string h1 = "T1";
    string h2 = "T2";
    string h3 = "T3";
    int n;
    cin >> n;
    printHanoiSteps(n, h1, h2 , h3);
    cout<<pow(2,n)-1;
}
