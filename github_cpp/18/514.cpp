#include <iostream>
#include <string>
#include <stack>
using namespace std;

//Function Prototypes
void Reverse(string &);

int main() {

	string user_string;
	cout << "Enter a string: ";
	getline(cin, user_string);
	Reverse(user_string);
	cout << "\n" << user_string << "\n";

	return 0;
}

void Reverse(string &my_string) {

	// Create a stack of characters
	stack<char> S;

	// For each character in my_string... 
	for (char &c : my_string)
		S.push(c); // Push into stack

	// For each character in my_string...
	for (char &i : my_string) {
		i = S.top(); // Overwrite i
		S.pop();     // And perform pop
	}
}
