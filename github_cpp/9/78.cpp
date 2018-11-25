

#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>



int main(int argc, const char* argv[])
{   
    std::string tmp;
    std::vector< std::vector<std::string>  > input_info;
    while ( getline(std::cin, tmp) )
    {
        std::vector<std::string> input_tmp;
        std::istringstream istring(tmp);
        std::string  s;
        while (istring >> s){
            input_tmp.push_back(s);
        }
        input_info.push_back(input_tmp);
        tmp="";
    }
    auto itr = input_info.begin();
    while (itr != input_info.end()) {
        auto itr_line = (*itr).rbegin();
        while( itr_line != (*itr).rend() ) {
            if (itr_line == (*itr).rbegin())
                printf("%s", (*itr_line).c_str());
            else 
                printf(" %s", (*itr_line).c_str());
            itr_line ++;
        }
        printf("\n");
        itr ++;
    }
    return 0;
}

