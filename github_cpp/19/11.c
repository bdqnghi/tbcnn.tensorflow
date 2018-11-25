
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_N 101

int N;
int A[MAX_N];

void printArr() {
    for (int i = 0; i < N; i++) cout << A[i] << " ";
    cout << endl;
    
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


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
    

    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];

    cout << N << endl;
    printArr();

    quicksort(0, N - 1);
    printArr();

    fclose(stdin);
    

    return 0;
}
