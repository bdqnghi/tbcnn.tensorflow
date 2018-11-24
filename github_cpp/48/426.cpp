#include "Palindrome.h"
#include<iostream>
#include<string>

std::string Palindrome::reverseString(std::string string_1){
    if (string_1.length()==1){
        return string_1;
    }
    else{
        string_reversed=reverseString(string_1.substr(1,string_1.length()))+string_1.at(0);
        return string_reversed;
    }
}

bool Palindrome::isPalindrome(std::string string_2){
    Palindrome str1;
    std::string string_1=str1.reverseString(string_2);
    if (string_1==string_2){
        return 1;
    }
    else {
        return 0;
    }
}


