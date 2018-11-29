//performs insertion sort on file containing ints. Starts sort based on second line.

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

vector<int>  insertionSort(vector<int> vec) {
	cout << "using insertion sort..." << endl;
	/*std::vector<int> vec2;
	return vec2;	*/
	for (int i = 1; i < vec.size(); i++) {
		int temp = (vec[i]);		//std::move(vec[i]);
		int j;
		for (j = i; j > 0 && temp < vec[j - 1]; j--) {
			int temp2 = vec[j - 1];
			vec[j] = temp2;
		}
		vec[j] = temp;
		//cout << "after " << i << " passes: ";
		/*for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << " ";
		}
		cout << std::endl; */
		
	}	
	return vec;

}  



/*int main() {
	std::vector<int> ar;
	int x = 32;
	ar.insert(ar.begin(), x);
	ar.insert(ar.begin() + 1, 18);
	ar.insert(ar.begin() + 2, 6);
	ar.insert(ar.begin() + 3, 22);
	ar.insert(ar.begin() + 4, 28);
	ar.insert(ar.begin() + 5, 2);
	ar.insert(ar.begin() + 6, 14);	
	for (int i = 0; i < ar.size(); i++) {
		std::cout << ar[i] << " ";
	}
	std::cout << std::endl;
	//std::cout << std::endl;
	ar = insertionSort(ar);
	std::cout << std::endl;

} */
