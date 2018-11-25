#ifndef ECHO_SORT
#define ECHO_SORT

#include <iostream>
#include <cstring>
#include <math.h>
template<typename Type>
void swap(Type &a, Type &b){
	Type temp = a;
	a = b;
	b = temp;
}

Type rand(Type start, Type end){
	Type size = end - start + 1;
	return (start + rand() % size);
}

void select_sort(Type *Array, Type start, Type end);

void bubble_sort(Type *Array, Type start, Type end);

void shell_sort(Type *Array, Type start, Type end);


Type adjustArray(Type *Array, Type start, Type end);

Type quick_sort(Type *Array, Type start, Type end);

void binsert_sort(Type *Array, Type len);

void insert_sort(char *Array, Type start, Type end);


Type count_sort(Type *Array, Type start, Type end, Type min, Type max);


void radix_sort(Type *Array, Type start, Type end);

void merge(Type *Array, Type start, Type mid, Type end);

void merge_sort(Type *Array, Type start, Type end);

void bigRootHeapAdjust(Type *Array, Type start, Type end);

void heap_sort(Type *Array, Type start, Type end);

#endif	