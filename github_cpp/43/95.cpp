#include <assert.h>
#include <limits.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>

class Node {
public:
	int value;
	Node *next = NULL;
};

void bucket_sort(int array[], int sorted[], int len)
{
	const int BUCKET_NUM = 10;
	Node *bucket = new Node[BUCKET_NUM];
	// 1. determain number range for every bucket.
	int max = INT_MIN;
	for (int i = 0; i < len; i ++) {
		if (array[i] > max) {
			max = array[i];
		}
	}

	// 2. insert every input number into the right bucket and the right place of the number serial chain.
	const int BUCKET_SIZE = max / BUCKET_NUM;
	for (int i = 0; i < len; i ++) {
		int bucket_index = array[i] / BUCKET_SIZE;
		if (bucket_index >= BUCKET_NUM) {
			bucket_index = BUCKET_NUM - 1;
		}
		Node *new_node = new Node();
		new_node->value = array[i];
		Node *insert_pos = bucket + bucket_index;
		while (insert_pos->next != NULL && insert_pos->next->value < array[i]) {
			insert_pos = insert_pos->next;
		}
		Node *next = insert_pos->next;
		insert_pos->next = new_node;
		new_node->next = next;
	}

	// 3. draw out the result iteratally into the 'sorted' array.
	int cursor = 0;
	for (int i = 0; i < BUCKET_NUM; i ++) {
		Node *node = bucket + i;
		while (node->next != NULL) {
			sorted[cursor] = node->next->value;
			cursor ++;
			node = node->next;
		}
	}
}

int main()
{
	srand(time(NULL));
	const int ARRAY_LEN = 1000;
	const int INT_RANGE = 100000;
	int *array = new int[ARRAY_LEN];
	int *sorted = new int[ARRAY_LEN];
	for (int i = 0; i < ARRAY_LEN; i ++) {
		array[i] = rand() % INT_RANGE;
	}

	// Sort in standard way
	std::vector<int> v(array, array + ARRAY_LEN);
	std::sort(v.begin(), v.end());

	// Sort in our way
	bucket_sort(array, sorted, ARRAY_LEN);

	// Compare them
	for (int i = 0; i < ARRAY_LEN; i ++)
	{
		//	std::cout << array[i] << ", ";
		assert(v[i] == sorted[i]);
	}
}
