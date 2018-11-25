

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

    

    return reverse;
}
