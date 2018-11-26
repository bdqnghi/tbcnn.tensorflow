/* The classic quick-sort is done in 5 stages:
    1. find a 'pivot value'
    2. move all values less than or equal to the pivot value to the left
    3. move all values larger than the pivot to the right
    4. quick-sort the values less than or equal
    5. quick-sort the values larger than
*/
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_N 101

int N;
int A[MAX_N];

void printArr() {
    for (int i = 0; i < N; i++) cout << A[i] << " ";
    cout << endl;
    //cout << sizeof(A) / sizeof(A[0]) << endl;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* The trick here is to swap the pivot value to the front of the sequence,
    partition the rest of the values, and then swap the pivot value back to where it belongs
*/
int partitioning(int left, int right) {
    int mid = left + (right - left) / 2;
    int pivot = A[mid];

    swap(&A[mid], &A[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while (i <= j && A[i] <= pivot) {
            i++;
        }
        while (i <= j && A[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[left], &A[i - 1]);
    return i - 1;
}

void quicksort(int left, int right) {
    if (left >= right) {
        return;
    }
    int part = partitioning(left, right);
    printArr();

    quicksort(left, part - 1);
    quicksort(part + 1, right);
}

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];

    cout << N << endl;
    printArr();

    quicksort(0, N - 1);
    printArr();

    fclose(stdin);
    //fclose(stdout);

    return 0;
}
