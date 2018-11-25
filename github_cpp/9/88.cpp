#include <iostream>
#include <fstream>

using namespace std;

void string_reverse1(char*); 
char *string_reverse2(const char *string);

int main()
{
	char test[] = "testNumberTwo"; 
	string_reverse1(test); 
	cout << test << endl; 
	char* test2 = string_reverse2("testString"); 
	cout << test2 << endl; 
}


void string_reverse1(char *string)
{
	
	char temp;
	int end = 0, beginning = 0;
	while (string[end] != NULL)
	{
		end++;
	}
	end--; 
	while (beginning < end)
	{
		temp = string[end];
		string[end] = string[beginning];
		string[beginning] = temp;
		beginning++;
		end--;
	}



}

char *string_reverse2(const char *string)
{
	int end = 0, beginning = 0; 
	while (string[end] != NULL)
	{
		end++;
	}
	char *newString = new char[end]; 
	for (int i = 0; i < end; i++)
	{
		newString[i] = ' '; 
	}
	newString[end] = '\0'; 
	end--; 
	char temp; 
	while (beginning < end)
	{
		temp = string[beginning]; 
		newString[beginning] = string[end]; 
		newString[end] = temp; 
		beginning++;
		end--; 
	}
	
	return newString; 

}
