#include <stdio.h>
#include <iostream>
#include <array>
using namespace std;

const size_t arraySize = 80;
void stringReverse  (const array <char, arraySize> &, size_t);

int main()
{
    array <char, arraySize> a = {"Are you crazy??"};
    
    cout << "The values in the array are: " << endl;
    stringReverse  (a, 0);
    cout << endl;
}


void stringReverse  (const array <char, arraySize> &b, size_t current) {
    if (current < b.size()) {
        stringReverse  (b, current + 1);
        cout << b [current] << " ";
    }
}
