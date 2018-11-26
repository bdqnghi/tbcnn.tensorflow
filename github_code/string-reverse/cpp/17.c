#include <iostream>
using namespace std;

void reverse(char *str)
{
    int start , end, len =0;
    char temp;
    while(str[len] != '\0')
    {
        len++;
    }
    cout<< len<<endl;
    end = len -1;
    for(int i =0; i<len/2;i++)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    cout<< str;
}

int main() {
	// your code goes here
	char str[] ="geeksfor geeks";
	reverse(str);
	return 0;
}
