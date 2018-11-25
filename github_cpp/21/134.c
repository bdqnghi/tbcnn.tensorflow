#include <iostream>
using namespace std;

class SelectionSort {
public:
	SelectionSort();
	SelectionSort(int boyut, double dizi[]);
	void sirala();
	void yazdir();
	~SelectionSort();

private:
	double *arr;
	int takip;
	int min_i;
	int boyut;
};
SelectionSort::SelectionSort() {
	arr = NULL;
	takip = 0;
}
SelectionSort::SelectionSort(int boyut, double dizi[]) {
	this->boyut = boyut;
	arr = new double[boyut];
	if (arr == NULL) std::cout << 0;
	takip = 0;
	for (int i = 0; i < boyut; i++){
		arr[takip] = dizi[i];
		takip++;
	}
}
void SelectionSort::sirala() {
	double temp;
	for (int i = 0; i < takip - 1; i++) {
		min_i = i;
		for (int j = i + 1; j < takip; j++) {
			if (arr[j] < arr[min_i])
				min_i = j;
		}
		if (min_i != i) {
			temp = arr[i];
			arr[i] = arr[min_i];
			arr[min_i] = temp;
		}
	}
}
void SelectionSort::yazdir() {
	cout << "Dizi: {";
	for (int i = 0; i < takip; i++){
		cout << " " << arr[i];
		i != takip - 1 && cout << ",";
	}
	cout << " }"<<endl;
}
SelectionSort::~SelectionSort() {
	delete[]arr;
}
void main() {
	double dizi[] = { 3.45, -9.34, 1.12, 55.34, -9.34, 3.34, 9.44, 3.32, 10.75 };
	SelectionSort ob(9, dizi), *p=&ob;
	p->sirala();
	p->yazdir();
}
