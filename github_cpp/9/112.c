







#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void reverseWord(string &s)
{
    
    s = ' '+s;
    reverse(s.begin(), s.end());
    
    
    size_t start = 0;
    size_t finish = 0;
    size_t spaceIdx = 0;
    while((spaceIdx = s.find(' ', start))!= string::npos) {
        finish = spaceIdx;
        reverse(s.begin()+start, s.begin()+finish);
        start = finish+1;
    }
    
    reverse(s.begin(), s.end());
    s.erase(0,1);
}


int main()
{
    string str{"My name is Sudipto Nandi"};
    
    reverseWord(str);
    
    cout << str << endl;
}

