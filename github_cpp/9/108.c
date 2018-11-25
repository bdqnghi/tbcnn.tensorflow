///////////////////////////////////////////////////////////////
// ReverseString.cpp      Reverse String Source File         //
// Yueyong Su                                                //
///////////////////////////////////////////////////////////////
#include <string>
#include <algorithm>
#include "ReverseStringClass.h"
using namespace ReverseStringSpace;
using namespace std;

//Reverse String Method
void ReverseStringClass::ReverseString (string &s)
{
	int n=(int)s.size()-1;
	if(n==-1) return;
	int b=0;
	while(b<n)
	{
		char temp=s[b];
		s[b++]=s[n];
		s[n--]=temp;
	}
}

/*
int main(int argc, char* argv[])//a simple test main function
{
	std::cout << "\n  " << "Reverse String Test Result: ";
	string str="This is a string";
	string rev=	str;
	reverse(rev.begin(), rev.end());
	ReverseStringClass rs;
	rs.ReverseString(str);
	if(str.compare(rev)==0)
		std::cout << "Pass! \n";
	else
		std::cout << "Fail! \n";
}*/

