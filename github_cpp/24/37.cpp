



#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"

using namespace std;


int bSearch(int target, Vector<int> & v, int start, int end) {
    if (start > end)
        return -1; 
    int middle = (start + end) / 2;
    if (v[middle] == target)
        return middle;
    if (v[middle] < target)
        return bSearch(target, v, middle + 1, end);
    return bSearch(target, v, start, middle - 1);

}




int bSearch(int target, Vector<int> & v) {
    return bSearch(target, v, 0, v.size() - 1);
}


int main() {
    setConsoleSize(500, 500);
    setConsoleFont("Monospaced-14");
    setConsoleExitProgramOnClose(true);
    setConsolePrintExceptions(true);
    

    Vector<int> v;
    v += 1, 4, 7, 10, 15, 88, 99; 
    cout << bSearch(0, v) << endl;      
    cout << bSearch(1, v) << endl;      
    cout << bSearch(4, v) << endl;      
    cout << bSearch(99, v) << endl;     
    cout << bSearch(45, v) << endl;     
    cout << bSearch(138, v) << endl;    

    
    cout << endl;
    getLine("Press [Enter] to close the window... ");
    
    return 0;
}

