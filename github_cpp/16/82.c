





#include "ShellSortSuboptimal.h"

ShellSortSuboptimal::ShellSortSuboptimal() : VectorSorter("Shellsort suboptimal") {}
ShellSortSuboptimal::~ShellSortSuboptimal() {
   
}

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
