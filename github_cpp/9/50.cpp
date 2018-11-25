// ************************************** rev the string whole and word by word ********************************* //
#include<stdio.h>
#include<string.h>
#include<conio.h>
using namespace std;
main()
{
	int i=0,count=0,noc=0,temp;
	char str1[2000];
	puts("Enter the string");
	scanf("%[^\n]s", &str1); // or gets(str1);
	printf("\n%s",str1);
	printf("\n************REVERE THE STRING ***************\n");
	while(str1[i]!='\0')
	{
		i++;
		noc++;
	}
	printf("\n no of char== %d\n", noc);
	
	while(i--)
	{
		printf("%c",str1[i]);
	}
	
	printf("\n************REVERE THE STRING WORD BY WORD***************\n");
	i=0, temp=0;
	while(i<noc)
	{
	
		while(str1[i]!=' ' && i<noc)
		{
			i++;
		}
		if(str1[i]==' ')
		{
			i--;
			count=i;
			while(count>=temp)
			{
				printf("%c", str1[count]);
				count--;
			}
			printf(" ");
			i=i+2;
			temp=i;
		}
		
		if(i==noc)
		i--;
		
		if(str1[i]==str1[noc-1])
		{
			count=i;
			while(count>=temp)
			{
				printf("%c", str1[count]);
				count--;
			}
			i++;
		}
	}
	
}
