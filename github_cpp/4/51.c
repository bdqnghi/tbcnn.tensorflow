







#include <iostream>
using namespace std;


void move(int, char, char, char);


int main(int argc, const char * argv[]) {
    
    int n;
    cout << "Enter the number of disk: ";
    cin >> n;
    cout << "Following is the sequence of moves given A (source), C(Target), B(Auxillary) " << endl << endl;
    cout << "Disk" << "\t" << "From" << "\t" << "To" << endl;
    move(n, 'A', 'C', 'B');
    
    return 0;
}


void move(int n, char fromPeg, char toPeg, char auxPeg) {
    
    if(n == 1) {
        cout << "1" << "\t\t" << fromPeg << "\t\t" << toPeg << endl;
        return;
    }
    
    move(n-1, fromPeg, auxPeg, toPeg);
    cout << n << "\t\t" << fromPeg << "\t\t" << toPeg << endl;
    move(n-1, auxPeg, toPeg, fromPeg);
    
}

