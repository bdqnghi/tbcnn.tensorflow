/* File: mergesort.cc
 * Author: Dan McFalls (dmcfalls@stanford.edu)
 *
 * Single-threaded and multithreaded implementations of MergeSort.
 */

#include "mergesort.h"
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_CHILD_THREADS 1
#define MAX_MT_DEPTH 8

using namespace std;

void *mergesortRoutine(void *thread_arg);
void mergesortST_helper(float arr[], index_t left, index_t right, float scratch[]);
void mergesortMT_helper(float arr[], index_t left, index_t right, float scratch[], index_t depth);

typedef struct thread_data {
	float *arr;
	index_t left;
	index_t right;
	float *scratch;
	size_t depth;
} thread_data;

void merge(float arr[], index_t left, index_t mid, index_t right, float scratch[]) {
	for (index_t i = left; i < mid; i++) {
	  scratch[i] = arr[i];
	}
	for (index_t j = mid; j < right; j++) {
    scratch[j] = arr[j];
	}

	index_t left_ptr = left, right_ptr = mid, merge_ptr = left;

	while (left_ptr < mid && right_ptr < right) {
		if (scratch[left_ptr] < scratch[right_ptr]) {
		  arr[merge_ptr] = scratch[left_ptr];
		  left_ptr++;
		} else {
			arr[merge_ptr] = scratch[right_ptr];
			right_ptr++;
		}
		merge_ptr++;
	}

	while(left_ptr < mid) {
		arr[merge_ptr] = scratch[left_ptr];
		left_ptr++;
		merge_ptr++;
	}
	while(right_ptr < right) {
		arr[merge_ptr] = scratch[right_ptr];
		right_ptr++;
		merge_ptr++;
	}
}

void mergesortST_helper(float arr[], index_t left, index_t right, float scratch[]) {
	if (right - left > 1) {
		index_t mid = (left + right) / 2;

		mergesortST_helper(arr, left, mid, scratch);
		mergesortST_helper(arr, mid, right, scratch);

		merge(arr, left, mid, right, scratch);
	}
}

/* Function: mergesortST
 * Single-threaded implementation of mergeSort on an array of floats
 * @param left : beginning index of arr, inclusive
 * @param right : end index off arr, exclusive (if left is 0, this is the # of elements)
 */
void mergesortST(float arr[], index_t left, index_t right) {
	index_t size = right - left;
	float *scratch = new float[size];
	mergesortST_helper(arr, left, right, scratch);
	delete[] scratch;
}

void *mergesortRoutine(void *thread_arg) {
	thread_data *args;
	args = (thread_data *) thread_arg;
	if (args->depth < MAX_MT_DEPTH) {
		mergesortMT_helper(args->arr, args->left, args->right, args->scratch, args->depth);
	} else {
		mergesortST_helper(args->arr, args->left, args->right, args->scratch);
	}
	pthread_exit(NULL);
}

void mergesortMT_helper(float arr[], index_t left, index_t right, float scratch[], index_t depth) {
	if (right - left > 1) {
		index_t mid = (left + right) / 2;
		pthread_t threads[NUM_CHILD_THREADS];
		size_t new_depth = depth + 1;

		thread_data left_data = {arr, left, mid, scratch, new_depth};
		pthread_create(&threads[0], NULL, mergesortRoutine, &left_data);
		if(new_depth < MAX_MT_DEPTH) {
			mergesortMT_helper(arr, mid, right, scratch, new_depth);
		} else {
			mergesortST_helper(arr, mid, right, scratch);
		}
		void *status;
		pthread_join(threads[0], &status);

		merge(arr, left, mid, right, scratch);
	}
}

/* Function: mergesortMT
 * Multithreaded implementation of mergeSort on an array of floats
 * @param left : beginning index of arr, inclusive
 * @param right : end index off arr, exclusive (if left is 0, this is the # of elements)
 */
void mergesortMT(float arr[], index_t left, index_t right) {
	index_t size = right - left;
	float *scratch = new float[size];
	mergesortMT_helper(arr, left, right, scratch, 0);
	delete[] scratch;
}
