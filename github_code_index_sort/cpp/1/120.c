#include <iostream>
#include <vector>

using namespace std;

int insertionsort_count(vector<int> A, int size) {
	int vergleiche = 0;
	int count = size;
	int einzusortierender_wert;
	int j;
	for (int i = 1; i < count; i++) {
		einzusortierender_wert = A[i];
		j = i;
		if(j>0) vergleiche++;
		else vergleiche++;
		while(j>0 && A[j-1]>einzusortierender_wert) {
			if(j>0) vergleiche++;
			else vergleiche++;
			A[j] = A[j-1];
			j = j-1;
		}
		A[j] = einzusortierender_wert;
	}
	return vergleiche;
}

int selectionsort_count(vector<int> A, int size) {
	int vergleiche = 0;
	int n = size-1;
	int links = 0;
	int min;
	int tmp;
	while(links<n) {
		min = links;
		for(int i = links+1;i<=n;i++) {
			vergleiche++;
			if(A[i] < A[min]) {
				min = i;
			}
		}
		tmp = A[min];
		A[min] = A[links];
		A[links] = tmp;
		links = links+1;
	}
	return vergleiche;
}
int bubblesort_count(vector<int> A, int size) {
	int vergleiche = 0;
	int tmp;
 	for (int n = size; n>1; n--){
		for (int i=0; i<n-1; i=i+1){
			vergleiche++;
			if (A[i] > A[i+1]){
				//vertauschen
				tmp = A[i];
				A[i] = A[i+1];
				A[i+1] = tmp;
				//vertauschen ende
			}
		}
	}
	return vergleiche;
}

int main() {
	cout << "Array erstellen:" << endl;
	vector<int> array(100);
	for(int i = 0; i<3; i++) {
		array[i] = (i/3) + (i%3)*10;
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Insertionsort: " << insertionsort_count(array, 3) << " Vergleiche" << endl;
	cout << "Selectionsort: " << selectionsort_count(array, 3) << " Vergleiche" << endl;
	cout << "   Bubblesort: " << bubblesort_count(array, 3) << " Vergleiche" << endl;

	cout << endl << "Array erweitern:" << endl;
	for(int i = 3; i<6; i++) {
		array[i] = (i/3) + (i%3)*10;
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Insertionsort: " << insertionsort_count(array, 6) << " Vergleiche" << endl;
	cout << "Selectionsort: " << selectionsort_count(array, 6) << " Vergleiche" << endl;
	cout << "   Bubblesort: " << bubblesort_count(array, 6) << " Vergleiche" << endl;

	cout << endl << "Array erweitern:" << endl;
	for(int i = 6; i<9; i++) {
		array[i] = (i/3) + (i%3)*10;
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Insertionsort: " << insertionsort_count(array, 9) << " Vergleiche" << endl;
	cout << "Selectionsort: " << selectionsort_count(array, 9) << " Vergleiche" << endl;
	cout << "   Bubblesort: " << bubblesort_count(array, 9) << " Vergleiche" << endl;

	cout << endl << "Array erweitern:" << endl;
	for(int i = 9; i<12; i++) {
		array[i] = (i/3) + (i%3)*10;
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Insertionsort: " << insertionsort_count(array, 12) << " Vergleiche" << endl;
	cout << "Selectionsort: " << selectionsort_count(array, 12) << " Vergleiche" << endl;
	cout << "   Bubblesort: " << bubblesort_count(array, 12) << " Vergleiche" << endl;

	cout << endl << "Array erweitern:" << endl;
	for(int i = 12; i<15; i++) {
		array[i] = (i/3) + (i%3)*10;
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Insertionsort: " << insertionsort_count(array, 15) << " Vergleiche" << endl;
	cout << "Selectionsort: " << selectionsort_count(array, 15) << " Vergleiche" << endl;
	cout << "   Bubblesort: " << bubblesort_count(array, 15) << " Vergleiche" << endl;

	return 0;
}
