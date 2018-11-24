#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

void reverseStr(string &str)
{
	int i = 0, j = str.length()-1;
	while(i < j)
	{
		char temp;
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int main()
{
	string input;
	cout << "enter the strings you want to reverse..use empty line to finish" << endl;
	
	do {
         getline(std::cin,input);
	     
		 reverseStr(input);
		 cout << "The reverse string is " << input << endl;

	}while(!input.empty());

	return 0;
}