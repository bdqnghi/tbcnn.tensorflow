// http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/

#include <iostream>
#include <limits>
using namespace std;

int cutRodNaive(int *p, int n);
void cutRodDP(int *p, int n);
void printCutRodSol(int *s, int n, int max_value);
int max(int a, int b);
void printArray(int *arr, int size);

int cutRodNaive(int *p, int n) {
    if (n == 0)
    return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++)
        q = max(q, p[i] + cutRodNaive(p, n-i));
    return q;
}

void cutRodDP(int *p, int n) {
    // array r[j] stores max revenue for total length of rod = j
    // array s[j] stores first optimal cut length for total length of rod = j
    int r[n+1], s[n+1];
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <=j ; i++) {
            if (q < p[i] + r[j-i]) {
                q = p[i] + r[j-i];
                s[j] = i;
            }
            r[j] = q;
        }
    }
    printCutRodSol(s, n, r[n]);
}

void printCutRodSol(int *s, int n, int max_value) {
    cout<<endl<<"max revenue (DP): "<<max_value;
    cout<<endl<<"cuts: ";
    while (n > 0) {
        // print first optimal cut and update remaining length
        cout<<s[n]<<" ";
        n = n - s[n];
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printArray(int *arr, int size) {
    if (size < 1 || arr == NULL)
        return;
    for (int i = 0; i < size; i++)
        cout<<arr[i]<<" ";
}

int main() {
    int arr[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int size = sizeof(arr)/sizeof(int);
    int n = 7;
    cout<<"price array: ";
    printArray(arr, size);
    cout<<endl<<"max revenue (naive): "<<cutRodNaive(arr, n);
    cutRodDP(arr, n);
    cout<<endl<<endl;
}