#include <vector>
#include <string>
#include <list>
#include <cassert>
#include <iostream>
using namespace std;

void bucketsort(vector<string> &v){
  //takes unsorted vector and returns sorted vector 
	//inserts into 26 buckets, each of which starts with a letter of the alphabet
	vector< vector<string> > buckets(26);

	int letter = 0;
	for(int i=0; i<v.size(); i++){
		if(v[i] != ""){
			assert(v[i][0] >= 'a' && v[i][0] <= 'z');
			letter = v[i][0] - 'a';
			buckets[letter].push_back(v[i]);
		}
	}

	//inner sorts 
	v.clear();
	for(int i=0; i<buckets.size(); i++){
		sort(buckets[i].begin(), buckets[i].end());
		for(int j = 0; j<buckets[i].size(); j++){
			v.push_back(buckets[i][j]);
		}
	}
}

int main(){

	vector<string> a = {"kiwi", "apple", "banana", "bananas", "grape", "apricot" };

	bucketsort(a);

	for (auto s: a){
		cout << s << endl;
	}
}
