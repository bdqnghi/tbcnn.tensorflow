// string_reverse_recursion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<malloc.h>

char * reverse(char *s,int n,int i)
{
	char p;
	if(i>n/2)
	{
		p=s[n-i];
		s[n-i]=s[i];
		s[i]=p;
		return reverse(s,n,--i);
	}
	else
		return s;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	char *s;
	printf("enter length of string\n");
	scanf("%d",&n);
	s=(char *)malloc(n*sizeof(char));
	printf("enter string\n");
	fflush(stdin);
	scanf("%s",s);
	s=reverse(s,n-1,n-1);
	printf("%s",s);

	return 0;
}

