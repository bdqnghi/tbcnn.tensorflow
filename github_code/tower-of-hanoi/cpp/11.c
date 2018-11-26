//Deepak Aggarwal, Coding Blocks
//deepak@codingblocks.com

#include <iostream>
using namespace std;

void towerOfHanoi(int n, char src, char dest, char helper){
    if (n == 0) return;

    //lets shift n-1 disc to helper
    towerOfHanoi(n - 1, src, helper, dest);
    cout << "Move " << n << " th disc " << "from " << src << " to " << dest << endl;
    //lets shift n - 1 disc on helper to dest
    towerOfHanoi(n - 1, helper, dest, src);
}

int main(){
    int nDisc;
    cin >> nDisc;

    towerOfHanoi(nDisc, 'A', 'B', 'C');   
}