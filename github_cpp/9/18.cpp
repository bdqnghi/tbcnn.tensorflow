//(Print a String Backward) Write a recursive function stringReverse that takes a string and a starting subscript as arguments, prints the string backward and returns nothing. The function should stop processing and return when the end of the string is encountered. Note that like an array the square brackets ( [] ) operator can be used to iterate through the characters in a string .
#include <iostream>
using namespace std;
void stringReverse(const char string[])
{
	if(string[0]=='\0')
		return;
	stringReverse(&string[1]);
	cout<<string[0];
}

int main()
{
	const int size = 50;
	char string[size]="MY name is Jone.";
	for(int i=0; i<size;++i)
		cout<<string[i];
	cout<<'\n';
	stringReverse(string);
	cout<<endl;
	return 0;
}
