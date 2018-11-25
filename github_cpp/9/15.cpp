


#include <iostream>
#include <string>
#include <string.h>


using namespace std;

void reverse_words_in_string(string &s);
void reverse_words_in_chararray(char s[]);
void reverse_words_in_carray(char *s);
void reverseC(char *s);
void last_word_in_string(char *s);


int string_to_int(char *str)
{
	int i = 0;
	int number = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9') 
		{

			
			number = number * 10 + str[i] - '0';
		}
		else
		{
			break;

		}
		i++;

	}
	return number;

}


int Anagram(char str1[], char str2[])
{
	int count1[100] = { 0 }, count2[100] = { 0 }, i = 0;

	int num1=0,num2=0;													
	if (strlen(str1) != strlen(str2))
	{
		return 0;
	}

	for (i = 0; i<strlen(str1); i++)
	{
		num1 = num1 + (str1[i] - 'a');
	}
	i = 0;
	for (i = 0; i<strlen(str2); i++)
	{
		num2 = num2 + (str2[i] - 'a');
	}

	if (num1 != num2)
			return 0;
	
	return 1;
}
bool isStringUnique(string str)
{
	if (str.length() > 256) 
	{
		return false;
	}
	bool char_array[256] = {0};
	for (unsigned int i = 0; i < str.length(); i++)
	{
		int value = str.at(i);
		if (char_array[value]!=0)
		{
			return false;
		}
		char_array[value] = true;
	}
	return true;
}
int main()
{
	string s = "my name is a";
		reverse_words_in_string(s);
	
		char a[]= "Hello world\0";

		
		
	
		
		char b[] = "90";
	
		
		
	
		

		bool y = isStringUnique("abc");
		cout << y << endl;
		return(0);
}
	



void reverse_words_in_string(string &s)
{
	
	
	int i = 0;
	
	unsigned int j = 0;

	while (j < s.length())
	{
		
		if (s[j] == ' ' || s[j] == '\0')
		{
			
			reverse(s.begin(), s.end());
			
			i = j + 1;
		}
		j++;
	}
	

}
void last_word_in_string(char *s)
{
	const int len = strlen(s) - 1;
	int i = len;
	while (i >= 0)
	{
		if (s[i] == ' ')
		{
			break;
		}
		i--;
	}
	for (int j = i + 1; j < strlen(s); j++)
	{
		cout << s[j];
	}
	
	
	
}

void reverseC(char* s)
{
	int length = strlen(s);
	int c, i, j;

	for (i = 0, j = length - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
void reverse_words_in_chararray(char s[])
{
	int mid = strlen(s)/2;
	for (int i = 0, j = strlen(s) - 1; i < mid; i++, j--)
	{

		char temp = s[i];
		cout << s[j] << endl;
		s[i] = s[j];
		cout << "Hey" << endl;
		s[j] = temp;

			
	}
}


