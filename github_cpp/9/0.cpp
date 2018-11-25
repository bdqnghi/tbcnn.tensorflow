#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

void swap(int &a, int &b) {
     int c = a;
         b = c;
         a = b;
}

int main() {
    int i, j, S;
    string s;
    getline(cin, s);
    S = s.size();
    cout << string(80, '\n');
    sleep(1);
    for (i=0; i<S/2; i++) {
        cout << string(80, '\n');
	swap(s[i], s[S-i-1]);
	cout << s << endl;
	for (j=0; j<S; j++) {
		if (j == i || j == S-i-1) cout << '^';
		else                      cout << ' ';
	}
	cout << endl << std::flush;
	usleep(500000);
    }
}
