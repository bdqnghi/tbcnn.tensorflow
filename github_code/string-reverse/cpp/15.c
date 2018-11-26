// StringReverse.cpp : Defines the entry point for the console application.
//

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
	/* Loop till end of string */
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9') //Check if value is between number 0 to 9 
		{

			/*
			* If it is between 0 to 9 then calculate its numeric value.
			* Below value of str[i] is substracted from '0' to get exact numeric value of that numeric character.
			*/
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
/** To check if the two strings are anagrams.**/

int Anagram(char str1[], char str2[])// two input strings str1 and str2
{
	int count1[100] = { 0 }, count2[100] = { 0 }, i = 0;// initialize two arrays count 1 and count 2 to zero to count the characters in the strings

	int num1=0,num2=0;													/* if String size is not equal */
	if (strlen(str1) != strlen(str2))
	{
		return 0;
	}

	for (i = 0; i<strlen(str1); i++)//iterating through the string to calculate the number of characters in string1
	{
		num1 = num1 + (str1[i] - 'a');
	}
	i = 0;
	for (i = 0; i<strlen(str2); i++)//iterating through the string to calculate the number of characters in string2
	{
		num2 = num2 + (str2[i] - 'a');
	}

	if (num1 != num2)// conditio to check if the number of characters are equal in two strings.
			return 0;
	
	return 1;
}
bool isStringUnique(string str)
{
	if (str.length() > 256) // Base case: assuming extended ASCII character set
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
	//	cout << s<<endl;
		char a[]= "Hello world\0";
//reverse_words_in_chararray(a);
		//reverse_str(a);
		//reverse_words_in_carray(a);
	//	last_word_in_string(a);
		/* char haystack[20] = "HelloWorld";
		 char needle[10] = "World";
		char *ret;*/
		char b[] = "90";
	//	ret = strstr(haystack, needle);
		
		//printf("The substring is: %s\n", ret);
	//	int x = Anagram("Yahoo", "Yaho");
		//int x=string_to_int(b);
//		cout << x << endl;
		bool y = isStringUnique("abc");
		cout << y << endl;
		return(0);
}
	//	cout << a << endl;;



void reverse_words_in_string(string &s)
{
	/*
	* 1st step
	* In below while loop , string becomes "erehw ereht si a lliw ereht si a yaw"
	*/
	/* To obtain the start of word to be reversed in a string and its length */
	int i = 0;
	/*To traverse through string */
	unsigned int j = 0;

	while (j < s.length())
	{
		/* Check for word in string. '\0' condition is checked for last word */
		if (s[j] == ' ' || s[j] == '\0')
		{
			/* (s+i) points at the start of word and (j-i) denotes the length */
			reverse(s.begin(), s.end());
			/* "i" will have the index at which next word starts */
			i = j + 1;
		}
		j++;
	}
	/*
	* 2nd Step
	* string "erehw ereht si a lliw ereht si a yaw" is reversed to get "way a is there will a is there where"
	*/
//	reverse(s, s+s.length());
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
	
	/* If last letter of string is blank space then it will be avoided */
	
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


