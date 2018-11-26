#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

void reverse(char a[]) {
	char *front = &a[0];
	char *rear = &a[(strlen(a) - 1)];
	int i = 0;
	char temp;
	// This block creates char pointers, a counter integer, and a temporary char variable.

	while (i < (strlen(a) / 2)) {
		temp = *front;
		a[i] = *rear;
		a[((strlen(a) - 1) - i)] = temp;
		i++;
		front = &a[i];
		rear = &a[((strlen(a) - 1) - i)];
	}
	cout << a << endl;
	return;
	/* Using the previously defined variables, this while loop
	   loops until the int counter is less than the length of the string
	   divided by 2. For every value of i, the temp variable and the
	   two pointers swap values until i approaches the middle of the c-string.*/
}

int main() {
	char str[] = "reivaX";
	char str1[] = "zyxwvutsrqponmlkjihgfedcba";
	reverse(str);
	reverse(str1);
	// this block creates c-strings and tests them.

	system("pause");
	return 0;
}