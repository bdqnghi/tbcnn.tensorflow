







#include <iostream>
using namespace std;

int main() {
	char text[] = "hello";
    int nChars = sizeof(text)-1;
    cout << "len: " << nChars << endl;
	char *pStart = text;
	char *pEnd = text + nChars - 1;

	cout << "*pStart: " << *pStart << endl;
	cout << "*pEnd: " << *pEnd << endl;

	while (pStart < pEnd) {
		char save = *pStart;
		*pStart = *pEnd;
		*pEnd = save;

		pStart++;
		pEnd--;
	}
	cout << text << endl;
	return 0;
}
