


#include <iostream>
using namespace std;

void towerOfHanoi(int n, char src, char dest, char helper){
    if (n == 0) return;

    
    towerOfHanoi(n - 1, src, helper, dest);
    cout << "Move " << n << " th disc " << "from " << src << " to " << dest << endl;
    
    towerOfHanoi(n - 1, helper, dest, src);
}

int main(){
    int nDisc;
    cin >> nDisc;

    towerOfHanoi(nDisc, 'A', 'B', 'C');   
}