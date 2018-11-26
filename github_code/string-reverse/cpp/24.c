//
//  StringReverse.cpp
//  LeetCodeSolutions
//
//  Created by Himangshu Ranjan Borah on 6/11/16.
//  Copyright © 2016 NC State University. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "AllSolutions.h"

using namespace std;

StringReverse::StringReverse(string str){
    _str = str;
}


string StringReverse::GetReversedString(){
    string result = _str;
    if(result.length() == 0)
        return "";
    unsigned long i = 0;
    unsigned long j = result.length() - 1;
    while(i < j){
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
        i++;
        j--;
    }
    return result;
}
