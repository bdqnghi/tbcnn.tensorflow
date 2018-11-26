// lru.cpp : Defines the entry point for the console application.
//

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
	/*LruCache cache(5);
	cache.set("mohan", "lal");
	cache.set("christian", "bale");
	cache.set("tom", "cruise");
	cache.set("learnado", "dicaprio");
	cache.printCache();
	cout << "christian ? " << cache.get("christian") << endl;
	cout << "tom ? " << cache.get("tom") << endl;
	cout << "learnado ? " << cache.get("learnado") << endl;
	cout << "brad ? " << cache.get("brad") << endl;
	cout << "learnado ? " << cache.get("learnado") << endl;
	cache.printCache();cout << endl;
	cout << "tom ? " << cache.get("tom") << endl;
	cout << "mohan ? " << cache.get("mohan") << endl;
	cout << "learnado ? " << cache.get("learnado") << endl;
	cout << "brad ? " << cache.get("brad") << endl;
	cout << endl;cache.printCache();cout << endl;
	cache.set("kishore", "kumar");cout << endl;
	cout << "learnado ? " << cache.get("learnado") << endl;
	cout << "kishore ? " << cache.get("kishore") << endl;
	cout << "christian ? " << cache.get("christian") << endl;
	cout << "tom ? " << cache.get("tom") << endl;
	cout << "tom ? " << cache.get("tom") << endl;
	cache.printCache();*/
	return 0;
}
