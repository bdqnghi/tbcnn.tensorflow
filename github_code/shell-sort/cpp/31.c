//Author:Vagdevi Challa
//SJSU Id:012524707
//Assignment no:12
//File name:ShellSortOptimal.cpp
//Description:Sorting algorithms comparision

#include "ShellSortOptimal.h"

ShellSortOptimal::ShellSortOptimal() :VectorSorter("Shellsort optimal") {}
ShellSortOptimal::~ShellSortOptimal() {
   
}
void ShellSortOptimal::run_sort_algorithm()
{
	int j = 1;
	for ( j = 1; j <= data.size() / 3; j = 3*j + 1);
    int h = (j - 1) / 3;
    while (h > 0) {
        for (int i = h; i != size; ++i) {
            int j = i - h;
            while (j >= 0 && data[j + h] < data[j]) {

            	 compare_count++;
                swap(j, j + h);
                j =j- h;
            }
        }
        h = (h - 1) / 3;
    }
}
