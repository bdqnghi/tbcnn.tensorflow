#include "stdafx.h" //добавление библиотеки
#include <iostream> //добавление библиотеки
using namespace std; //обявление пространства имён std
 
int main(int argc, char* argv[]) //начало программы
{
    const int size_array = 10; //объявлена переменная константа, которой присвоено значение 10
    int array_[size_array] = {-8, -7, -6, -6, -4, 2, 6, 7, 8, 15 }; // объявление одномерного массива
    cout << "array[" << size_array << "] = { ";
    for (int counter = 0; counter < size_array; counter++) // начало цила for
    {
     cout << array_[counter] << " "; // печать элементов одномерного массива array1
    }
    cout << " }"; // конец оформление вывода массива
    int average_index = 0, // переменная для индекса среднего элемента массива
        first_index   = 0, // индекс первого элемента в массиве
        last_index    = size_array -1, // индекс последнего элемента в массиве
        search_value  = 15; // искомое значение
    if (last_index == -1) cout << "\narray is empty" << endl; // если индекс последнего элемента равен -1 то, тогда массив пуст
 
    while (first_index < last_index)// начало цикла while
    {
        average_index = first_index + (last_index - first_index) / 2; // средний элемент = первый + (последний - первый)
        search_value <= array_[average_index] ? last_index = average_index : first_index = average_index + 1;    // найден ключевой элемент или нет и присвоение найденому значению last_index
    }
    if ( array_[last_index] == search_value) // начало цикла if else
        cout << "\nvalue is found" << "\nindex = " << last_index << endl;
    else
        cout << "\nvalue is not found" << endl;
    return 0; // возвращение значения 0
}