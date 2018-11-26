#include<stdio.h>
#include<stdlib.h>
int towers(int,char,char,char);
int main()
{
int n;
printf("Enter the number of disks\n");
scanf("%d",&n);
towers(n,'A','C','B');
printf("\n");
system("pause");
return 0;
}

 int towers(int n , char frompeg, char toppeg, char auxpeg)
{
	if(n==1)
{

	printf("\n%s%c%s%c","Move Disk 1 from peg ",frompeg," to peg ",toppeg);
	return 1;
}
	else
{

	towers(n-1,frompeg,auxpeg,toppeg);
	printf("\n%s%d%s%c%s%c","Move Disk " , n," from peg ",frompeg, " to peg " , toppeg);
	towers(n-1,auxpeg,toppeg,frompeg);
}
}
