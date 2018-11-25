






#include <iostream>

using namespace std;

const int MAX=5;

int main() {
    int A[MAX];
    int temp;
    int k;
    
    
    
    cout << "Enter " << MAX << " numbers to sort, one per line." << endl;
    
    
    
    for (k = 0; k < MAX; ++k) {
        cin >> A[k];
    }
    
    cout << endl << "Original: ";
    for (k = 0; k < MAX; ++k) {
        cout << A[k] << " ";
    }
    
    
    
    for (int i = 0; i < MAX; ++i) {
        for (int j = MAX-1; j > i; --j) {
            if (A[j] < A[j-1]) {
                
                temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
            }
        }
        
        
        cout << endl << "After Pass "<< i << "  ";
        for (k = 0; k < MAX; ++k) {
            cout << A[k] << " ";
        }
    }
    
    
    
    cout << endl << "Sorted: ";
    for (k = 0; k < MAX; ++k) {
        cout << A[k] << " ";
    }
    cout << endl;
}
