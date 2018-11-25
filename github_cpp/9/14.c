#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

void reverse(char a[]) {
	char *front = &a[0];
	char *rear = &a[(strlen(a) - 1)];
	int i = 0;
	char temp;
	

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
	
}

int main() {
	char str[] = "reivaX";
	char str1[] = "zyxwvutsrqponmlkjihgfedcba";
	reverse(str);
	reverse(str1);
	

	system("pause");
	return 0;
}