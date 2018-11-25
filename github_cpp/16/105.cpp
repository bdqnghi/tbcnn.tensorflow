
#include "ShellSortOptimal.h"


ShellSortOptimal::ShellSortOptimal() {}


ShellSortOptimal::~ShellSortOptimal() {}


string ShellSortOptimal::name() const { return "Shellsort optimal"; }


void ShellSortOptimal::run_sort_algorithm() throw (string)
{
    
	
	int g = size / 2;
while (g > 0) {
for (int i = 0; i < size - g; i++) { 
int j = i + g;
int tmp = data[j];
while (j >= g && tmp > data[j - g]) {
data[j] = data[j - g];
j -= g;
}
data[j] = tmp;
}
if (g == 2) { 

g = 1;

} else {

g /= 2.2;

}

}
return data;
}
}
