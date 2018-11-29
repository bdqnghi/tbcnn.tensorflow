//Author:Vagdevi Challa
//SJSU Id:012524707
//Assignment no:12
//File name:ShellSortSuboptimal.cpp
//Description:Sorting algorithms comparision

#include "ShellSortSuboptimal.h"

ShellSortSuboptimal::ShellSortSuboptimal() : VectorSorter("Shellsort suboptimal") {}
ShellSortSuboptimal::~ShellSortSuboptimal() {
   
}
//https://github.com/ysmiles/cpp_test/blob/master/SortTest/ShellSortSuboptimal.cpp
void ShellSortSuboptimal::run_sort_algorithm()
{
    int h = size / 2;
    while (h > 0) {
        for (int i = h; i != size; ++i) {
            int j = i - h;
            while (j >= 0  && data[j + h] < data[j]) {
            	++compare_count;
                swap(j, j + h);
                j -= h;
            }
        }
        h /= 2;
    }
}
