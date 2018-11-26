#include <iostream>
using namespace std;

class BubbleSort {
public:
	BubbleSort();
	BubbleSort(int boyut, int dizi[]);
	void sirala();
	void yazdir();
	~BubbleSort();

private:
	int *arr;
	int takip;
	int min_i;
	int boyut;
};
BubbleSort::BubbleSort() {
	arr = NULL;
	takip = 0;
}
BubbleSort::BubbleSort(int boyut, int dizi[]) {
	this->boyut = boyut;
	arr = new int[boyut];
	if (arr == NULL) std::cout << 0;
	takip = 0;
	for (int i = 0; i < boyut; i++){
		arr[takip] = dizi[i];
		takip++;
	}
}
void BubbleSort::sirala() {
	int i, j, temp;
	for (i = 0; i < takip - 1; i++) {
		for (j = 0; j < takip - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void BubbleSort::yazdir() {
	cout << "Dizi: {";
	for (int i = 0; i < takip; i++){
		cout << " " << arr[i];
		i != takip - 1 && cout << ",";
	}
	cout << " }"<<endl;
}
BubbleSort::~BubbleSort() {
	delete[]arr;
}
void main() {
	int dizi[] = { 400, -900, 900, 450, 390, 100, 320, -9000, 230 };
	BubbleSort ob(9, dizi), *p=&ob;
	p->sirala();
	p->yazdir();
}
