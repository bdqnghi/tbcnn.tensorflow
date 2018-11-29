#include <iostream>

/*
	The priority queue build on the heap-sort mechanics in that
	it effectively maintains a heap-sort on the array. It uses
	the same binary tree mechanism that a heap-sort uses.

	The only difference is that it supports the extract and insert
	methods which take data out and add data to the array.

	A class was created to facilitate easier handling of the
	data structure since it needs some additional members to
	operate safely. These members are the maximum number of items
	the array can have before needing to be reallocated and the
	current number of items.
*/

#define PARENT(x) ((x) / 2)
#define LEFT(x) ((x) * 2)
#define RIGHT(x) ((x) * 2 + 1)

template <typename T> class PriorityQueue {
	int max_items;
	T   *ary;
	int size;
public:
	PriorityQueue (int max_items) {
		this->max_items = max_items;
		this->ary = new T[max_items];
		this->size = 0;
	}

	int count() {
		return this->size;
	}

	int max_heapify(int i) {
		int left = LEFT(i);
		int right = RIGHT(i);

		int largest;

		if (left < this->size && this->ary[left] > this->ary[i]) {
			largest = left;
		} else {
			largest = i;
		}

		if (right < this->size && this->ary[right] > this->ary[largest]) {
			largest = right;
		}

		if (largest != i) {
			int tmp = this->ary[largest];

			this->ary[largest] = this->ary[i];
			this->ary[i] = tmp;

			this->max_heapify(largest);
		}

		return 1;
	}

	int insert(T t) {
		if (this->size + 1 >= this->max_items) {
			return 0;
		}

		int i = this->size;

		this->ary[this->size++] = t;

		while(i > -1 && this->ary[PARENT(i)] < this->ary[i]) {
			T tmp = this->ary[i];
			this->ary[i] = this->ary[PARENT(i)];
			this->ary[PARENT(i)] = tmp;

			i = PARENT(i);
		}

		return 1;
	}

	int extract_max(T &t) {
		if (size < 1) {
			return 0;
		}

		t = this->ary[0];

		ary[0] = this->ary[this->size - 1];

		this->size--;

		this->max_heapify(0);

		return 1;
	}


	int maximum(T &t) {
		if (this->size < 1) {
			return 0;
		}

		t = ary[0];

		return 1;
	}
};

int main(int argc, char *argv[]) {
	using namespace std;

	PriorityQueue<int> *pq = new PriorityQueue<int>(128);

	pq->insert(4);
	pq->insert(5);
	pq->insert(2);
	pq->insert(3);
	pq->insert(-10);
	pq->insert(9);
	pq->insert(2);

	int out;

	pq->maximum(out);

	cout << "maximum=" << out << endl;

	cout << "dump of priority queue" << endl;

	while (pq->count() > 0) {
		pq->extract_max(out);
		cout << out << " ";
	}

	cout << endl;
}