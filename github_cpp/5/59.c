

#include<iostream>
#include<vector>
using namespace std;

int insertion_sort(vector<int> &v){
	int length = v.size();
	int key = 0;
	int i = 0;
	for (int j = 1; j < length; j++){
		key = v[j];
		i = j - 1;
		while ((i >= 0) && (v[i] > key)){   
			v[i + 1] = v[i];
			v[i] = key;
			i = i - 1;
		}
	}
	return 0;
}
int main(int argc, const char * argv[]){
	vector<int> v = { 20, 25, 5, 12, 17, 35, 29 };

	cout << "test v : ";
	for (auto i : v) cout << i << " ";
	cout << endl;

	cout << "insertion-sort v: ";
	insertion_sort(v);
	for (auto i : v) cout << i << " ";
	cout << endl;

	return 0;
}