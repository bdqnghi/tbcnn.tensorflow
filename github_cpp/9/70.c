#include <iostream>
#include <string>
using namespace std;

void C_ReverseString(char *str)
{
	int len = strlen(str);
	
	for(int i=0; i<len/2; i++)
	{
		char tmp = *(str + i);
		*(str + i) = *(str + (len-1) -i );
		*(str + (len-1-i) ) = tmp;
	}
	cout << str << endl;
}

void CPP_ReverseString(string &str)
{

	int len = str.length();

	for(int i=0; i<len/2; i++)
	{
		char tmp = str[i];
		str[i] = str[(len-1)-i];
		str[(len-1)-i] = tmp;
	}
	cout << str << endl;
}

void main()
{
	string str = "shahadathossain";
	CPP_ReverseString(str);

	char cstr[] = "abc";
	C_ReverseString(cstr);
}