


#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include "lrustl.cpp"
#include "lruraw.cpp"

using namespace std;

char randCharacters() {
	const char charSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const size_t max_index = (sizeof(charSet) - 1);
	return charSet[rand() % max_index];
}

string randomString(size_t len) {
	string ret(len, 0);
	generate_n(ret.begin(), len, randCharacters );
	return ret;
}

int main(int argc, char** argv)
{
	StlLRU<int, string> cache(2);
	cache.put(2, "hello");
	cout << cache.get(2) << endl;
	try{
		cout << cache.get(1) << endl;
	} catch(exception err) {
		cout << err.what() << endl;
	}

	cache.put(1, "world");
	cache.put(1, "universe");
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;

	cache.put(8, "apples");
	try{
		cout << cache.get(1) << endl;
	} catch(exception err) {
		cout << err.what() << endl;
	}
	cout << cache.get(8) << endl;
	
	return 0;
}
