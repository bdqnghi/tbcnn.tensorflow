#include "../headers.hpp"
using namespace std;

void towerOfHanoi(int n, char source, char auxillary, char destination)
{

    
    if (n == 1)
    {
        cout << "Peg " << n << " has been transferred from " << source << " to " << destination << endl;
    }

    
    towerOfHanoi(n - 1, source, destination, auxillary);

    
    cout << "Peg " << n << " has been transferred from " << source << " to " << destination << endl;

    
    towerOfHanoi(n - 1, auxillary, source, destination);
}

int main()
{
    

    int n = 0;
    cout << "Enter number of pegs to move: ";
    cin >> n;

    towerOfHanoi(n, 'A', 'B', 'C');

    return 0;
}
