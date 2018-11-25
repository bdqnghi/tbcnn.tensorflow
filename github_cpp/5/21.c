#include "InsertionSort.h"
#include <iostream>

InsertionSort::InsertionSort() {
    numbers = NULL;
    numbersAmount = 0;
}

InsertionSort::InsertionSort(int *array, int size) {
    numbersAmount = size;
    numbers = new int[size];
    if (numbers == NULL) {
        std::cout << "Allocation failed." << std::endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        numbers[i] = array[i];
    }
}

InsertionSort::~InsertionSort() {
    delete[] numbers;
}

void InsertionSort::SetNumbers(int *array, int size) {
    
    numbersAmount = size;
    numbers = new int[size];
    if (numbers == NULL) {
        std::cout << "Allocation failed." << std::endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        numbers[i] = array[i];
    }
}

void InsertionSort::Print() {
    for (int i = 0; i < numbersAmount; ++i) {
        std::cout << numbers[i] << ", ";
    }
    std::cout << std::endl << std::endl;
}

void InsertionSort::Sort() {
    int j;
    int temp;
    for (int i = 1; i < numbersAmount; ++i) {
        temp = numbers[i];
        j = i-1;

        while (j >= 0 && numbers[j] > temp) {
            numbers[j+1] = numbers[j];
            --j;
        }
        numbers[j+1] = temp;
    }
}
