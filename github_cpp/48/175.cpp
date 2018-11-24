//PALINDROME

#include<iostream>
using namespace std;

int palin(char str[],int len);

int const size=100;

void main()
{

    char str[size];
	int len=0,flag,i;

	cout<<"\n Enter the string =";
	cin>>str;

	for(i=0;str[i]!='\0';i++)
		len++;

	flag=palin(str,len);

	if(flag)
		cout<<"\n Given string is a palindrome";
	else
		cout<<"\n Given string is not a palindrome";
	cout<<endl;
}

int palin(char str[],int len)
{

	int i,j;

	for(i=0,j=len-1;i<len/2;i++,j--)
	{
		if(str[i]==str[j])
		   continue;
		else
			return 0;
	}

	return(1);
}

