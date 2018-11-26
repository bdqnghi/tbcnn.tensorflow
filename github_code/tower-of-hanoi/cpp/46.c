#include "../headers.hpp"
using namespace std;

void towerOfHanoi(int n, char source, char auxillary, char destination)
{

    // if only one peg was sent
    if (n == 1)
    {
        cout << "Peg " << n << " has been transferred from " << source << " to " << destination << endl;
    }

    // move n-1 pegs from source to auxillary
    towerOfHanoi(n - 1, source, destination, auxillary);

    // move nth peg from source to destination
    cout << "Peg " << n << " has been transferred from " << source << " to " << destination << endl;

    // move n-1 pegs from auxillary to destination
    towerOfHanoi(n - 1, auxillary, source, destination);
}

int main()
{
    //system("clear");

    int n = 0;
    cout << "Enter number of pegs to move: ";
    cin >> n;

    towerOfHanoi(n, 'A', 'B', 'C');

    return 0;
}
