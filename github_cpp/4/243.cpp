
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class THashtable {
private:
	static const size_t MinCapacity = 7;

	size_t Capacity;
	size_t Size;
	vector<vector<pair<string,int> > > Buckets;

	size_t Hash(const string& str) const {
		const size_t N = 127;
		size_t res = 0;
		for (size_t i = 0; i < str.size(); ++i) {
			res = (res*N + str[i]) % Capacity;
		}
		return res;
	}

	void RehashAll() {
		vector<vector<pair<string,int> > > newBuckets(Capacity);
		for (size_t i = 0; i < Buckets.size(); ++i) {
			for (size_t j = 0; j < Buckets[i].size(); ++j) {
				size_t bucketInd = Hash(Buckets[i][j].first);
				newBuckets[bucketInd].push_back(Buckets[i][j]);
			}
		}
		Buckets = newBuckets;
	}

public:
	THashtable()
		: Capacity(MinCapacity)
		, Size(0)
		, Buckets(Capacity)
	{}

	const int* Get(const string& key) const {
		size_t bucketInd = Hash(key);
		const vector<pair<string,int> >& bucket = Buckets[bucketInd];
		for (size_t i = 0; i < bucket.size(); ++i) {
			if (bucket[i].first == key) {
				return &bucket[i].second;
			}
		}
		return NULL;
	}

	void Set(const string& key, int value) {
		if ((double)Size / Capacity > 0.5) {
			Capacity *= 2;
			RehashAll();
		}
		size_t bucketInd = Hash(key);
		vector<pair<string,int> >& bucket = Buckets[bucketInd];
		for (size_t i = 0; i < bucket.size(); ++i) {
			if (bucket[i].first == key) {
				bucket[i].second = value;
				return;
			}
		}
		bucket.push_back(make_pair(key, value));
		++Size;
	}

	void Remove(const string& key) {
		if ((double)Size / Capacity < 1.0/8 && Capacity > 2*MinCapacity) {
			Capacity = ::max(MinCapacity, Capacity/4);
			RehashAll();
		}
		size_t bucketInd = Hash(key);
		vector<pair<string,int> >& bucket = Buckets[bucketInd];
		for (size_t i = 0; i < bucket.size(); ++i) {
			if (bucket[i].first == key) {
				bucket.erase(bucket.begin() + i);
				--Size;
				return;
			}
		}
	}
};

int main() {
	THashtable hash;

	hash.Set("", 0);
	hash.Set("zero", 5);
	hash.Set("zero", 0);
	hash.Set("one", 1);
	cout << "zero: " << *hash.Get("zero") << endl;

	hash.Set("two", 2);
	hash.Set("three", 3);
	cout << "three: " << *hash.Get("three") << endl;

	hash.Set("four", 4);
	hash.Set("five", 5);
	hash.Set("six", 6);
	hash.Set("seven", 7);
	hash.Set("eight", 8);
	hash.Set("nine", 9);
	hash.Set("ten", 10);
	hash.Set("eleven", 11);

	cout << "five: " << *hash.Get("five") << endl;
	cout << "ten: " << *hash.Get("ten") << endl;
	cout << "seven: " << *hash.Get("seven") << endl;
	cout << "eleven: " << *hash.Get("eleven") << endl;
	cout << "<empty>: " << *hash.Get("") << endl;

	return 0;
}
