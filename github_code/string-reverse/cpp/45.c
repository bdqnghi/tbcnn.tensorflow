// problem: implement a void reverse(char* str) to reverse a null terminated string

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void reverse(char* str);

int main (int argc, char* argv[]) {
    if (argc < 2 ){
        cerr << "Please enter the string to reverse on command line.\n";
        return 1;
    }

    // read filename and number of lines to read from command line
    string inputStr = argv[1];

    // make a mutable char* copy of the read in string
    char *inputCharStr = new char[inputStr.length() + 1];
    strcpy(inputCharStr, inputStr.c_str());

    reverse(inputCharStr);
    return 0;
}

void reverse(char* str){
    char temp; 
    int start, end;
    start = 0;
    end = strlen(str)-1;

    while (start < end) {
        temp = str[end];
        str[end] = str[start];
        str[start] = temp;
        start++;
        end--;
    }

    int i = 0;
    while(true){
        char inputChr = str[i];

        if(inputChr == '\0'){
            break;
        }

        cout << inputChr;
        i++;
    }

    cout << "\n";
}
