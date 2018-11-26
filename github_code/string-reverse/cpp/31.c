#include <vector>, <string>
#include <iostream>
using namespace std;


void reverseString(const string& someString){
	vector<char> chars;
	for (char x : someString){
		chars.push_back(x);
	}
	size_t tempSize = chars.size()-1;
	while (!(tempSize <0)){
		cout << chars[tempSize];
		if (tempSize == 0) break;
		--tempSize;
		//(tempSize == 0) ? (tempSize = -1) : (--tempSize);
		//(condition) ? (if_true) : (if_false)
		//--tempSize;
	}
	cout << endl;
}

int main(){
	reverseString("I LIKE TO POOP IN MY PANTS");
	system("pause");
}