#include "HeapSort.h"
#include <iostream>

HeapSort::HeapSort(int max) {
	maxItems = max;
	length = 0;
	items = new ItemType[maxItems];
}

HeapSort::HeapSort(int max, ItemType *items, int l) {
	maxItems = max;
	length = 0;
	this->items = new ItemType[maxItems];
	for (int i = 0; i < l; i++) {
		this->enqueue(items[i]);
	}
}

HeapSort::~HeapSort() {
	delete items;
}

bool HeapSort::isEmpty() const {
	return (length == 0);
}

bool HeapSort::isFull() const {
	return (length == maxItems);
}

void HeapSort::enqueue(ItemType newItem) {
	if(isEmpty()) {
		items[length] = newItem;
		length++;
	} else if (!isFull()) {
		items[length] = newItem;
		length++;
		subida(0, length - 1);
	}

}

ItemType HeapSort::dequeue() {
	if(!isEmpty()) {
		ItemType removedPos = items[0];
		if (length == 1) {
			length--;
			return removedPos;
		}
		for (int i = 0; i < length - 1; i++) {
			items[i] = items[i + 1];
		}
		length--;

		return removedPos;
	}
}


void HeapSort::subida(int root, int index) {
	int pai = (index - 1)/2;
	while (items[index] > items[pai]) {
		ItemType aux = items[index];
		items[index] = items[pai];
		items[pai] = aux;
		index = pai;
		pai = (pai - 1)/2;
		if (index == 0)
			break;
	}
}

void HeapSort::descida(int index, int bottom) {
	int filho1 = 2*index + 1;
	int filho2 = 2*index + 2;
	int son = (items[filho1] > items[filho2]) ? filho1 : filho2;

	if(son > bottom) {
		return;
	} else {
		if (items[index] < items[son]) {
			ItemType aux = items[index];
			items[index] = items[son];
			items[son] = aux;
			index = son;
			descida(index, bottom);
		} else {
			return;
		}
	}
}



void HeapSort::sort() {
	int bottom = length - 1;
	do {
		ItemType aux = items[0];
		ItemType aux2 = items[bottom];
		items[0] = aux2;
		items[bottom] = aux;
		bottom--;
		
		descida(0, bottom);
	} while (bottom > 0 && !(bottom == 1 && items[0] < items[1]));
}


