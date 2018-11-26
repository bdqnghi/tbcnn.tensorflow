//  ReverseString.cpp

#include <algorithm>
#include "ReverseString.h"

ReverseString::ReverseString() : String() {}

ReverseString::ReverseString(const ReverseString& rs) : String(rs) {}

ReverseString::ReverseString(const char* ch) : String(ch) {}

ReverseString& ReverseString::operator=(const ReverseString& rs)
{
    if (&rs != this) {
        String::operator=(rs);
    }

    return *this;
}

ReverseString ReverseString::operator~()
{
    ReverseString rs(*this);
    ReverseString reverse;
    int count = 0;

    /*for (int i = rs.getLength()-1; i >= 0; i--) {
        reverse.rstring[count] = rs.rstring[i];
        count++;
    }*/

    return reverse;
}
