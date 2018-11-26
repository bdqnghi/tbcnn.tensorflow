/* 
 * File:   StringReverse.cpp
 * Author: johnvecchio
 *
 * Created on February 28, 2012, 11:39 AM
 */
#include <iostream>
#include <string>
#include <stack>

using namespace std;

/*
 * 
 */

void reverse(string& x) {
    stack<char> s;
    const int n = x.length();
    
    //Put characters from x onto the stack
    for(int i=0; i<n; ++i){
        s.push(x[i]);
    }
    
    //take characters off of stack and put them back into x
    for(int i=0; !s.empty(); ++i, s.pop()){
        x[i]=s.top();
    }
}

int main() {
    int go =1;
    char c;
    char* s = (char *)malloc(80);
    
    while(go == 1){
        cout << "This program reverses a string using the STL stack" << endl;
        cin.getline(s,81,'\n');
        string word(s);
        reverse(word);
        cout << word << endl;
        
        cout << "Enter another? 1 = continue. Anything else to stop" << endl;
        cin >> go;
        c=getchar();
    }
    
    return 0;
}

	