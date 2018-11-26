#include <iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
#include "heap.h"

void SortArray(int *input, int n);
void printArray(int *array, int n);

void SortArray (int *input, int n) {
  Heap heap(n);
  int  i;

  i = 0;
  heap.createHeap();
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@Do not edit above @@@@@@@@@@@@@@@@@@@@@@@@@*/

/*Complete the  function to use the Heap ADT defined above to 
sort the array of n elements. The elements should be stored back in the array
called input*/
  for(i = 0;i<n;i++){
 	heap.insertHeap(input[i]);
  }
  for(i=0;i<n;i++){

  	input[i] = heap.deleteMin();
  }
  
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@Do not edit below @@@@@@@@@@@@@@@@@@@@@@@@@*/
void printArray(int *array, int n, std::ofstream &fp1)
{
	int i;
	fp1 << "Array : ";
	if (n <= 0) return;

	for(i=0;i<n-1;i++){
		fp1 << array[i] << " ";
	}
	fp1<<array[i]<<endl;
}

int main(int argc, char **argv)
{
	int n;
	int i;
	int *array;

	if(argc != 3){
		cout << "Pass <input file> <outputfile> as arguments when you run the executable" << endl;
		std::exit(-1);
	}
		

	std::ifstream fp;
	std::ofstream fp1;
	fp.open(argv[1]);
	fp1.open(argv[2]);

	if(!fp){
		cout << "Input file " << argv[1] << " not present" << endl;
		exit(1);
	}


	fp >> n;
	if(n > 0){
		array = new int[n];
		for (i = 0; i < n; i++)
		    fp >> array[i];
		SortArray(array, n);
	}
        printArray(array,n,fp1);
	fp.close();
	fp1.close();
	return 0;
}
