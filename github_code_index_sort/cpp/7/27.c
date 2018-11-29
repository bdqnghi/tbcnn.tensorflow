#include <iostream>  
#include <iomanip>  
using namespace std;  
class ShellSort {  
public:  
    ShellSort(int);  
    ~ShellSort();  
    void Sort();  
    void ReadData();  
    void Display();  
private:  
    int nums;  
    int *pointer;  
};  
ShellSort::ShellSort(int integer) {  
    nums = integer;  
    pointer = new int[integer];  
}  
ShellSort::~ShellSort() {  
    delete [] pointer;  
}  
void ShellSort::ReadData() {  
    for (int i = 0; i < nums; i++)  
        cin >> pointer[i];  
}  
void ShellSort::Sort() {  
    int gap = nums / 2, temp, i, j;  
  
    while (gap != 0) {  
        for (i = gap; i < nums; i++) {  
            temp = pointer[i];  
            for (j = i; j >= gap; j -= gap) {  
                if (pointer[j - gap] > temp)  
                    pointer[j] = pointer[j - gap];  
                else  
                    break;  
            }  
            pointer[j] = temp;  
        }  
        gap >>= 1;  
    }  
}  
void ShellSort::Display() {  
    for (int i = 0; i < nums ; i++)  
        cout << pointer[i] << " ";  
    cout << endl;  
}  
int main() {  
    int integer;  
    cin >> integer;  
    while (integer != -1) {  
        ShellSort ss(integer);  
  
        ss.ReadData();  
        ss.Sort();  
        ss.Display();  
          
        cin >> integer;  
    }  
    return EXIT_SUCCESS;  
}