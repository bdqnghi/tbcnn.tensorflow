#include<iostream>
#include<string.h>

using namespace std;

void StringReverse(char * str)
{
    if(NULL == str) return;

    int n = strlen(str);

    if (1 == n) return;

    char ct = 0;

    //int a = 1; int b =2;
    //a ^= b ^= a ^= b;
    //cout << "a: " << a << " b: " << b << endl;

    int halflen = (0 == n % 2) ? n/2: (n+1)/2;
    for(int i = n - 1; i >= halflen; --i)
    {
        ct = *(str + n - i -1);
        *(str + n - i -1) = *(str + i);
        *(str + i) = ct;
    } 
}

int main()
{
    char streven[] = "abcdef";
    char strodd[] = "abcdefg";
    cout << "streven: " << streven << endl;
    cout << "strodd: " << strodd << endl;
    cout << endl << "After reversing:" << endl;
    StringReverse(streven);
    cout << "streven: " << streven << endl;
    StringReverse(strodd);
    cout << "strodd: " << strodd << endl;
    return 0;
}


