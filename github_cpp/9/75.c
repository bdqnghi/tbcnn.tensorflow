







#include <iostream>
#include <string>

using namespace std;

int main( int argc, const char *argv[] )
{
    
    string delims(" ");
    string line("i ma wyz");
    
    string::size_type begin, end;
    
    begin = line.find_first_not_of(delims);
    
    while(begin != string::npos)
    {
        end = line.find_first_of(delims, begin);
        if(end == string::npos)
        {
            end = line.size();
        }

        for(int i = static_cast<int>(end) - 1; i >= static_cast<int>(begin); i--)
        {
            cout << line.at(i);
        }
        cout << delims;
        begin = line.find_first_not_of(delims, end);
    }
    
    return 0;
}
