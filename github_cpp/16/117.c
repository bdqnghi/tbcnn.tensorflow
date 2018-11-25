
#include "ShellSortSuboptimal.h"


ShellSortSuboptimal::ShellSortSuboptimal() {}


ShellSortSuboptimal::~ShellSortSuboptimal() {}


string ShellSortSuboptimal::name() const { return "Shellsort suboptimal"; }


void ShellSortSuboptimal::run_sort_algorithm() throw (string)
{
    
	
	int g = size / 2;
while (g > 0) {
for (int i = 0; i < size - g; i++) { 
int j = i + g;
int tmp = array[j];
while (j >= g && tmp > array[j - g]) {
array[j] = array[j - g];
j -= g;
}
array[j] = tmp;
}
if (g == 2) { 

g = 1;

} else {

g =g/2;

}

}
return array;
}
}
