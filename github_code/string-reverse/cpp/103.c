// stringreverse.cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "malloc.h"
void string_reverse(char *s1)
{
	int i=0,j=0;char *s2;
	while(s1[i]!='\0')
	{
		i++;
	}i--;
s2=(char *)malloc((i+1)*sizeof(char));
while(i>=0)
{

s2[j]=s1[i];
	i--;j++;
}s2[j]='\0';
printf("the reverse of the string is");
puts(s2);
}

int _tmain(int argc, _TCHAR* argv[])
{ char *s1;int n;
printf("Enter the range of the string");
scanf("%d",&n);
s1=(char *)malloc(n*sizeof(char));
gets(s1);
gets(s1);
string_reverse(s1);

return 0;
}

