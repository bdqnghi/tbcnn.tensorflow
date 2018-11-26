#include <iostream>
using namespace std;

template <typename T>
void printArray(T value[], int count);

template <typename T>
void selectionSort(T value[], int count) {
	int i = 0, j = 0;
	int min = 0, temp = 0;

	// ��ü �ڷ� �������� 1 ���� Ƚ��(count - 1)��ŭ ������ ����.
	// ������ �������� ���� �ڷ�� �ִ� �ڷ��̱� ������ �߰����� ������ �ʿ� ����.
	for (i = 0; i < count - 1; i++) {
		// (���ĵ��� ���� �ڷ�� ��) �ּڰ��� ��ġ(min)�� �ʱ�ȭ ��Ų��.
		min = i;
		for (j = i + 1; j < count; j++) {
			// ���ĵ��� ���� �ڷ���� ������� ���� ���� Ű ���� ã�´�.
			if (value[j] < value[min]) {
				min = j;
			}
		}
		temp = value[i];
		value[i] = value[min];
		value[min] = temp;

		printf("Step-%d, ", i + 1);
		printArray(value, count);
	}
}

int main() {
	int values[] = { 80, 50, 70, 10, 60, 20, 40, 30 };

	printf("Before Sort\n");
	printArray(values, 8);

	selectionSort(values, 8);

	printf("\nAfter Sort\n");
	printArray(values, 8);

	return 0;
}

template <typename T>
void printArray(T value[], int count) {
	int i = 0;
	for (i = 0; i < count; i++) {
		cout << value[i] << " ";
	}
	printf("\n");
}