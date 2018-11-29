#include <iostream>
using namespace std;

void counting_sort(int *arr, int n, int e) {
  int C[10] = {};
  int sorted_arr[n];

  for (int j = 0; j < n; j++)
    C[(arr[j] / e) % 10]++;

  for (int i = 1; i < 10; i++)
    C[i] += C[i - 1];

  for (int j = n - 1; j >= 0; j--) {
    sorted_arr[C[(arr[j] / e) % 10] - 1] = arr[j];
    C[(arr[j] / e) % 10]--;
  }

  for (int i = 0; i < n; i++)
    arr[i] = sorted_arr[i];
}

int getMax(int *arr, int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max) max = arr[i];
  return max;
}

void radix_sort(int *arr, int n) {
  int max = getMax(arr, n);
  for (int e = 1; (max / e) > 0; e *= 10)
    counting_sort(arr, n, e);
}

int main() {
  int n = 10; // numer of elements
  int arr[n];
  srand(time(nullptr));

  for (int i = 0; i < n; i++)
    arr[i] = rand() % 201;

  cout << "Array before radix sort: ";

  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";

  cout << endl;
  radix_sort(arr, n);
  cout << "Array after radix sort: ";

  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";

  cout << endl;
}
