/* ***********************************************************************

  > File Name: reverse_string.cpp
  > Author: zzy
  > Mail: zzy@taomee.com 
  > Created Time: Sun 19 Nov 2017 05:01:49 PM CST

 ********************************************************************** */
/*
   题目描述
   给定一个句子（只包含字母和空格）， 将句子中的单词位置反转，单词用空格分割, 单词之间只有一个空格，前后没有空格。 
   比如： （1） “hello xiao mi”-> “mi xiao hello”
   输入描述:
   输入数据有多组，每组占一行，包含一个句子(句子长度小于1000个字符)
   输出描述:
   对于每个测试示例，要求输出句子中单词反转后形成的句子
*/
#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>

/*
char * reverse_string_recursion(char* string ,int begin ,int end)
{	
	if (begin < end){
		char tmp = string[begin];
		*(string + begin) = *(string + end);
		*(string + end) = tmp ;
		return reverse_string_recursion(string, begin+1 ,end-1);
	} else{
		return string;
	}
}

char *reverse_string(char * string)
{
	int len = strlen(string) - 1;
	return reverse_string_recursion(string, 0, len);
}
*/

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

