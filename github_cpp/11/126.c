#ifndef HEAPSORT_H_
#define HEAPSORT_H_



#include <stdint.h>
#include <vector>

#include "IPv6_addr.h"
#include "cflow.h"

void heapSort(int * a, int count);
void heapSort(uint64_t * a, int count);
void heapSort(long * a, int count);
void heapSort(long * a, int * b, int count);
void heapSort(double * a, int count);
void heapSort(double * a, int * b, int count);
void heapSort(int * a, int * b, int count);
void heapSort(std::vector<IPv6_addr> & a, std::vector<int> & b);
void heapSort(uint32_t * a, int * b, int count);
void heapSort(uint64_t * a, uint32_t * refs, int count);
void heapSort3Level(uint64_t * index1, uint64_t * index2, uint32_t * refs, uint32_t count);
void heapSort(int * a, int * b, int * c, int count);

#endif 

