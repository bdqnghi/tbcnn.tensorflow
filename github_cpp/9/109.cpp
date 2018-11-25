





#include <iostream>
#include <string.h>

using namespace std;


void stringReverse(char *word)
{
	int len = strlen(word) - 1;
	char c;
	for (int i = 0; i < len; i++)
	{
		
		c = word[i];
		word[i] = word[len];
		word[len--] = c;
	}
}
int main(void)
{
	
	char word[] = "dlrow olleh";
	char word2[] = "!!!!llew ho tub gnipeels eb yllaer dluohs I";
	char word3[] = "++C evoL I";

	cout << word << endl;
	stringReverse(word);
	cout << word << endl << endl;
	
	cout << word2 << endl;
	stringReverse(word2);
	cout << word2 << endl << endl;
	
	cout << word3 << endl;
	stringReverse(word3);
	cout << word3 << endl << endl;

	system("pause");
	return 0;
}
