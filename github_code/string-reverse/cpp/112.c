//
//  stringReverse.cpp
//  Algo
//
//  Created by Sudipto Nandi on 9/20/18.
//  Copyright © 2018 Sudipto Nandi. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void reverseWord(string &s)
{
    //Reverse the string
    s = ' '+s;
    reverse(s.begin(), s.end());
    //Loop
    //Find the ' ' and reverse the substring from start to pos (find)
    size_t start = 0;
    size_t finish = 0;
    size_t spaceIdx = 0;
    while((spaceIdx = s.find(' ', start))!= string::npos) {
        finish = spaceIdx;
        reverse(s.begin()+start, s.begin()+finish);
        start = finish+1;
    }
    //Reverse the string
    reverse(s.begin(), s.end());
    s.erase(0,1);
}


int main()
{
    string str{"My name is Sudipto Nandi"};
    
    reverseWord(str);
    
    cout << str << endl;
}

