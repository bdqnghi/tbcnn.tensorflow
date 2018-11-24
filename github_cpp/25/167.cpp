//The beginning
#include <iostream>
#include<stdio.h>
#include<string.h>
//#include<oxymoron.h>

using namespace std;
int l;
void swap (char*str, int lower,int upper)
{
	
	char temp;
	temp = *(str+lower);
	*(str + lower)= *(str + upper);
	*(str + upper)= temp;
	return;
}

void permute(char *str, int lower, int length)
{
	
	if (length==1)
	{	cout<<str-l+1<<endl;
		return;
	}
	//cout<<str<<" "<<length<<" "<<lower<<endl;
	for (int i=lower;i<length;++i)
	{	
		//cout<<str<<" "<<i<<" "<<length<<endl;
		//swap(str,0,lower);
		
		swap(str,0,i);
		permute(str+1,0,strlen(str+1));
		swap(str,0,i);
		
	}
}


int main()
{
	char str[100];
	int length;
	cout<<"Enter the string to be permuted\n";
	cin.getline(str,100);
	cout<<"\n\n\n";
	l=strlen(str);
	length=strlen(str);
	permute(str,0,length);

return 0;
}


