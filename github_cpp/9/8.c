

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
