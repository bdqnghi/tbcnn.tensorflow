










#include "string_functions.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <utility>

char * cppStringToCString(std::string cpp_string) {
    char * c_string = (char*)malloc(sizeof(char) * (cpp_string.size() + 1));
    std::copy(cpp_string.begin(), cpp_string.end(), c_string);
    c_string[cpp_string.size()] = '\0';
    return c_string;
}


void freeCString(char * p) {
    free(p);
}


std::vector<std::string> splitString(char * inString, char delimiter) {
    return splitString(std::string(inString), delimiter);
}


std::vector<std::string> splitString(std::string inString, char delimiter) {
    std::vector<std::string> result;
    if (inString.length() == 0)
        return result;
    std::stringstream ss(inString);
    while(ss.good())
    {
        std::string substr;
        getline(ss, substr, delimiter);
        result.push_back(substr);
    }
    return result;
}


std::string getReverseComplement(std::string sequence) {
    std::string reverseComplement;
    reverseComplement.reserve(sequence.length());
    for (int i = sequence.length() - 1; i >= 0; --i) {
        char letter = sequence[i];
        switch (letter) {
        case 'A': reverseComplement.push_back('T'); break;
        case 'T': reverseComplement.push_back('A'); break;
        case 'G': reverseComplement.push_back('C'); break;
        case 'C': reverseComplement.push_back('G'); break;
        case 'R': reverseComplement.push_back('Y'); break;
        case 'Y': reverseComplement.push_back('R'); break;
        case 'S': reverseComplement.push_back('S'); break;
        case 'W': reverseComplement.push_back('W'); break;
        case 'K': reverseComplement.push_back('M'); break;
        case 'M': reverseComplement.push_back('K'); break;
        case 'B': reverseComplement.push_back('V'); break;
        case 'D': reverseComplement.push_back('H'); break;
        case 'H': reverseComplement.push_back('D'); break;
        case 'V': reverseComplement.push_back('B'); break;
        case 'N': reverseComplement.push_back('N'); break;
        case '.': reverseComplement.push_back('.'); break;
        case '-': reverseComplement.push_back('-'); break;
        case '?': reverseComplement.push_back('?'); break;
        case '*': reverseComplement.push_back('*'); break;
        }
    }
    return reverseComplement;
}
