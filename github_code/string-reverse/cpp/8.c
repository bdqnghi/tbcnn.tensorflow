/* 
7.36: Print a String Backward (with recursion)
Write a recursive function stringReverse that takes a string
and a starting subscript as arguments, prints the string
backward and returns nothing.
The function should stop processing and return when the end of
the string is encountered. Note that, like an array, the square
brackets ([]) operator can be used to iterate through the 
characters in a string.
*/

#include <iostream>
using namespace std;

void stringReverse(string, int);

int main()
{
    string myString;
    int index;
    
    cout << "Enter a string: ";
    getline(cin, myString);

    cout << "Enter a subscript: ";
    cin >> index;

    stringReverse(myString, index);
    cout << endl;
}

void stringReverse(string inString, int index)
{
    if (inString[index+1] == '\0')
        cout << inString[index];
    else
    {
        stringReverse(inString, index + 1);
        cout << inString[index];
    }    
}
