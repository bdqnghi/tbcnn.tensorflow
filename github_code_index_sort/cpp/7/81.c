//performs insertion sort on file containing ints. Starts sort based on second line.

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

vector<int>  shellSort(vector<int> vec) {
	cout << "using shellsort.." << endl;
	/*std::vector<int> vec2;
	return vec2;	*/
	int numPasses = 0;
	for (int gap = vec.size() / 2; gap > 0; gap /= 2) {
		++numPasses;
		for (int i = gap; i < vec.size(); i++) {
			int temp = vec[i];
			int j = i;
			for ( ; j >= gap && temp < vec[j - gap ]; j -= gap) {
				vec[j] = vec[j - gap];
			}
			vec[j] = temp;
		}
		/*cout << "After " << numPasses << " passes: "; 
		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;	 */
	}	
	return vec;

}  


/*
int main() {
	std::vector<int> ar;
	int x = 32;
	ar.insert(ar.begin(), x);
	ar.insert(ar.begin() + 1, 18);
	ar.insert(ar.begin() + 2, 6);
	ar.insert(ar.begin() + 3, 22);
	ar.insert(ar.begin() + 4, 28);
	ar.insert(ar.begin() + 5, 2);
	ar.insert(ar.begin() + 6, 14);	
	ar.insert(ar.begin() + 7, 1);	
	for (int i = 0; i < ar.size(); i++) {
		std::cout << ar[i] << " ";
	}
	std::cout << std::endl;
	//std::cout << std::endl;
	ar = shellSort(ar);
	for (int i = 0; i < ar.size(); i++) {
		std::cout << ar[i] << " ";
	}
	std::cout << std::endl;

} */
