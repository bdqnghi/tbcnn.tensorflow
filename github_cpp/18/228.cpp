#include <iostream>
#include <iomanip>
using namespace std;

int main () {

	char text[] = "hello4";

	for (int i = 0; i < sizeof(text)/2; i ++) {
		char last_char = text[sizeof(text)-i-2];
		
		text[sizeof(text)-i-2] = text[i];
		text[i] = last_char;



		cout << text << endl;

	}

	cout << "######################" << endl;

	char text2[] = "hel4lo";

	int n_chars = sizeof(text2) - 1;

	char *pStart = text2;
	char *pEnd = text2 + n_chars - 1;

	while (pStart < pEnd) {
		char save = *pStart;
		
		*pStart = *pEnd;
		*pEnd = save;

		cout << text2 << endl;
		pStart++;
		pEnd--;
	}


	return 0;
}