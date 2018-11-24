#include <iostream>
#include <string>
#include <iterator>

using std::string;      using std::cin;
using std::cout;        using std::endl;
using std::iterator;

void reverseString(string &);
template <typename T> void value_swap(T & a, T & b);

int main()
{
    string str = "words";
    string str2 = "wowzers";
    cout << str << endl;
    cout << str2 << endl;
    reverseString(str2);
    cout << str2 << endl;

    auto e = str.size() - 1;

    for(auto i = 0; i < e; ++i)
    {
        char temp;

        temp = str.at(i);
        str.at(i) = str.at(e);
        str.at(e) = temp;
        --e;
    }

    cout << str << endl;

    for(string::const_iterator iter = str.end() - 1; iter != str.begin() - 1; --iter)
    {
        cout << *iter;
    }
    cout << endl;
    return 0;
}


void reverseString(string &str)
{
    string::iterator start = str.begin();
    string::iterator last = str.end() - 1;

    while (start != last)
    {
        value_swap(*start, *last);
        ++start;
        --last;
    }
}

template <class T> void value_swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}

