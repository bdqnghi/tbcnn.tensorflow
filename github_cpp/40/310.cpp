#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	void sortIntegers2(vector<int> & A) {
		quick_sort(A);
	}
private:
	void quick_sort(vector<int> & A) {
		partial_sort(A, 0, A.size());
	}
	void partial_sort(vector<int> & A, int begin, int end) {
		if (end - begin <= 1) {
			return;
		}
		int partition = quick_select(A, begin, end);
		partial_sort(A, begin, partition);
		partial_sort(A, partition + 1, end);
	}
	int quick_select(vector<int> & A, int begin, int end) {
		int pivot = A[begin];
		int i = begin + 1;
		int j = end - 1;
		while (i <= j) {
			if (A[i] <= pivot) {
				++i;
			}
			else if (pivot <= A[j]) {
				--j;
			}
			else {
				swap(A[i], A[j]);
			}
		}
		--i;
		swap(A[begin], A[i]);
		return i;
	}
};

int main(void) {
    Solution solution;
    vector<int> A;

    A = {3, 2, 1, 4, 5};
    solution.sortIntegers2(A);
    for (const auto & i : A) {
        cout << i << '\t';
    }
    cout << '\n';

    return 0;
}