#include <iostream>
#include <fstream>

#include "selection-sort.hpp"
#include "selection-sort.cpp"

using namespace std;

int main(int argc, char** argv) {
    char* inputFilename = argv[1];
    int* arr;
    int size;

    ifstream inputFile(inputFilename);

    if(inputFile.is_open()) {
        inputFile >> size;

        arr = new int[size];

        int item;
        int i = 0;
        while(inputFile >> item) {
            arr[i] = item;
            i++;
        }
    }

    cout << endl << "Before Sort: " << endl;
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    SelectionSort::Sort(arr, size);

    cout << endl << "After Sort: " << endl;
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;

    return 0;
}
