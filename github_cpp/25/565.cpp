#include "bits_stdc.h"

void permutationUtil(vector<int> &in, int index, vector<vector<int>> &out) {
	
	if (index == in.size() - 1)
		out.push_back(in);

	else {
		for (int i = index; i < in.size(); i++) {
			swap(in[i], in[index]);
			permutationUtil(in, index + 1, out);
			swap(in[i], in[index]);
		}
	}
}

vector<vector<int>> permutation(vector<int>& in) {
	vector<vector<int>> out;
	permutationUtil(in, 0, out);
	return out;
}

void print2dVector(vector<vector<int>> in) {
	for (auto vec : in) {
		for (auto n : vec) {
			cout << n << " ";
		}
		cout << "\n";
	}
}

/*int main() {

	vector<int> input = { 1,2,3 };
	print2dVector(permutation(input));
	return 0;
}*/