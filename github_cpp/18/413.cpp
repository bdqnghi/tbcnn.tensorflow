#include <iostream>

using namespace std;

void reverse(string);

int main() {

	string sentence;
	getline(cin, sentence);

	/*
		//For testing
		sentence = "Alice likes cats";

		Sample input:
			Alice likes cats
		Sample output:
			stac sekil ecilA
	*/

	int start = 1;
	int dist = 0;

	for (int i = sentence.length() - 1; i >= 0; i--) {
		dist++;
		if (sentence[i] == ' ') {
			string tmp = sentence.substr(i + 1, dist);
			dist = 0;
			reverse(tmp);
			if (start == 1) { //First
				start = 0;
			} else { //Middle words
				cout << " ";
			}
		}
		else if (i == 0) { //Last
			string tmp = sentence.substr(i, dist);
			reverse(tmp);
		}
	}
}

void reverse(string sent) {
	for (int i = sent.length() - 1; i >= 0; i--) {
		cout << sent[i];
	}
}
