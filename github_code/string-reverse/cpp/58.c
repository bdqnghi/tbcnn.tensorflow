/*
OVERVIEW: Given a string, reverse all the words not the string.

E.g.: Input: "i like coding". Output: "coding like i"

INPUTS: A string.

OUTPUT: Modify the string according to the logic.

NOTES: Don't create new string.
*/
#include <Stdio.h>
#include <string.h>

void stringreverse(char* str, int l, int h);

void str_words_in_rev(char *input, int len){
	stringreverse(input, 0, len - 1);
	puts(input);
	printf("\n\n\n");
	int i = 0; int pos1, pos2;
	pos1 = 0; pos2 = 0;
	while (i<(strlen(input) + 1))
	{
		/*if (i == 0 && input[i] == ' ')
		{
		while (input[i] != ' ')
		{
		i++;
		pos1 = i;
		}
		}*/
		printf("i=%d ", i);
		if (input[i] == ' ' || input[i] == '\0')
		{
			pos2 = i - 1;
			printf("inside if condition before swap call pos1= %d pos2= %d\n", pos1, pos2);
			stringreverse(input, pos1, pos2);
			/*while (input[i] != ' ')
			{
			i++;

			pos1 = i;
			printf("inside while loop\t i=%d\n",i);
			continue;
			}*/
			pos1 = i + 1;
			printf("pos1=%d  ", pos1);
		}
		i++;
	}
}
void stringreverse(char* str, int l, int h)
{
	char t;
	
	while (l < h)
	{
		t = str[l];
		str[l] = str[h];
		str[h] = t;
		l++;
		h--;
	}
}