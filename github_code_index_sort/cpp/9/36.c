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
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void select_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void bubble_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void shell_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
//单工法
Type adjustArray(Type *Array, Type start, Type end);

Type quick_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void binsert_sort(Type *Array, Type len);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void insert_sort(char *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
//start -- end为元素区间，min -- max为元素值得范围
Type count_sort(Type *Array, Type start, Type end, Type min, Type max);

/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void radix_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void merge(Type *Array, Type start, Type mid, Type end);

void merge_sort(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void bigRootHeapAdjust(Type *Array, Type start, Type end);
/*
 *Function：
 *		selection-sort
 *Parameter：
 *		Array:	
 *		start
 *		end
 */
void heap_sort(Type *Array, Type start, Type end);

#endif	//ECHO_SORT