#include <iostream>
#include <cstring>
using namespace std;

int stringreverse(char* begin,char* end)
{
	if(NULL==begin||NULL==end) return;
	while(begin<end)
	{

		char temp;
		temp = *begin;
		*begin = *end;
		*end = temp;
		begin++;
		end--;
	}
}

int wordreverse(char* p,int len)
{
	if(NULL==p)
		return;
	len = strlen(p);
	stringreverse(p,p+len-1);

	for (int i = 0; i < len; ++i)
	{
		cout<<p[i];
			/* code */
	}
	cout<<endl;
	char* begin =p;
	for (int i = 0; i < len; ++i)
	{
		if(' '==*(p+i))
		{
			stringreverse(begin,p+i-1);
			begin = p+i+1;
		}

	}
}

int main()
{
	char a[]="I am a student.";
	wordreverse(a);
	for (int i = 0; i < strlen(a); ++i)
	{
		cout<<a[i];
	}
	
}