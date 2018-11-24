// palindrome.cpp : Defines the entry point for the console application.
//
// 17th.palindromeofgivenstring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<malloc.h>
#include<string.h>
struct test{
	char input[20];
	bool valuereturn;// return type is bool
}teststub[24]={
				{NULL,false}, // null case
				{"m",true}, // single character(odd length)
				{"1",true}, //single digit (odd length)
				{"mo",false},  //even length return false case of length=2
				{"121",true}, //odd length return True case of length=3(digits)
				{"mom",true}, // odd length return true case length=3(characters)
				{"amma",true}, //even length return true case of length=4
				{"abca", false},//even length return false case of length=4
				{"madam",true}, // odd length return true case length=5(characters)
				{"mommy",false}, // odd length return false case length=5(characters)
				{"abcabc",false}, // length =6
				{"abcdcba",true}, //length=7
				{"aaaAAaaa",true}, //all are similar characters upper and lowercases
				{"abcdefghij",false}, // all are different characters
				{"!@#@!",true},// special charcters of length=5
				{"()" ,false}, // open and closed braces
				{"())(",true}, // sepcial charactersof even length=4
				{"m  o    m",false}, // adding spaces of length=3 returns false space is not counted
				{"    ", true}, // only spaces
				{"a              a",true}, // single charcter wid spaces
				{"1234567890987654321",true},// length=19 in digits
				{"1.001",false}, // floating point values
				{"AbCcBa",false}, // upper n lower case of even length
				{"AaaaA",true}
};
bool checkPalindrome(char *s)
{
	int i=0,j=0,index;bool flag=false;
	int l=strlen(s)-1;
	index=l;
	while(s[j]!=0)
	{
		for(i=0;i<=index/2;i++)
		{
			if(s[i]==s[l-i])
				flag=true;
			else
			{
				flag=false;
				break;
			}
		}
		j++;
	}
	return flag;
}

void testCase()
{
	for(int index=0; index<24; index++)
	{
		bool returnpalin=checkPalindrome(teststub[index].input);
		if(returnpalin==teststub[index].valuereturn) printf("Passed\n"); else printf("Failed\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	testCase();
	return 0;
}


