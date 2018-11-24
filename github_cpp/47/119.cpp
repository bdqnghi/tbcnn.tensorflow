// Sample/test file

/**************************
*   COSC 220
***************************
*
*   binary-search.cpp
*/

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

// Recursive implementation of binary search
int bSearch(int target, Vector<int> & v, int start, int end) {
    if (start > end)
        return -1; // "not found" signal
    int middle = (start + end) / 2;
    if (v[middle] == target)
        return middle;
    if (v[middle] < target)
        return bSearch(target, v, middle + 1, end);
    return bSearch(target, v, start, middle - 1);

}

// Wrapper function; calls recursive function to do real work.
// Returns the index in v at which target is found, or -1 if
// not found.
int bSearch(int target, Vector<int> & v) {
    return bSearch(target, v, 0, v.size() - 1);
}


int main() {
    setConsoleSize(500, 500);
    setConsoleFont("Monospaced-14");
    setConsoleExitProgramOnClose(true);
    setConsolePrintExceptions(true);
    /////////////////////////////////////////////////

    Vector<int> v;
    v += 1, 4, 7, 10, 15, 88, 99; // vector must be in sorted order!
    cout << bSearch(0, v) << endl;      // expect -1
    cout << bSearch(1, v) << endl;      // expect 0
    cout << bSearch(4, v) << endl;      // expect 1
    cout << bSearch(99, v) << endl;     // expect 6
    cout << bSearch(45, v) << endl;     // expect -1
    cout << bSearch(138, v) << endl;    // expect -1

    /////////////////////////////////////////////////
    cout << endl;
    getLine("Press [Enter] to close the window... ");
    //closeConsoleAndExit();
    return 0;
}

