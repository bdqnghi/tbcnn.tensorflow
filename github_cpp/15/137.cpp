#include "Heap.h"

/**
 *�������ʾ��
 */
Heap::Heap(int *initArray, int initLength) {
	this->length = initLength;
	this->array = new int[length];
	for (int i = 0; i < length; i++) {
		this->array[i] = initArray[i];
	}
}
/**
 *����ڴ�
 */
Heap::~Heap() {
	delete[]this->array;
	this->length = 0;
}

/**
 *��ȡ���ڵ�
 */
int Heap::getParent(int index) {
	if (index < 1) {
		cout << "THE INDEX IS ROOT, NO PARENT!" << endl;
		return NULL;
	}
	else
	{
		return (index - 1) / 2;
		/*
		if (index % 2 == 0) {
			return index / 2 - 1;
		}
		else {
			return index / 2;
		}*/
	}
}
/**
 *��ȡ������
 */
int Heap::getLeftChild(int index) {
	return 2 * index + 1;
}
/**
 *��ȡ������
 */
int Heap::getRightChild(int index) {
	return 2 * index + 2;
}

/**
 *���ö�
 */
void Heap::setArray(int *initArray) {
	this->array = initArray;
}
/**
 *��ȡ��
 */
int* Heap::getArray() {
	return this->array;
}
/**
 *���öѵĳ���
 */
void Heap::setLength(int initLength) {
	this->length = initLength;
}
/**
 *��ȡ�ѵĳ���
 */
int Heap::getLength() {
	return this->length;
}
/**
*��ӡ��
*/
void Heap::showHeap() {
	for (int i = 0; i < this->getLength(); i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

/**
 *ʹ��������ֵ����ѵĶ���
 *�ٶ������������������������ѵĶ���
 *�����½�������������ֵ����ѵ�����
 */
void Heap::maxHeapify(int index) {
	int left = this->getLeftChild(index);
	int right = this->getRightChild(index);
	int largest;
	if (left < this->getLength() && right < this->getLength()) {
		if (this->array[left] > this->array[right]) {
			largest = left;
		}
		else {
			largest = right;
		}
	}
	else if (left < this->getLength() && right >= this->getLength()) {
		largest = left;
	}
	else if (left >= this->getLength()) {
		largest = index;
	}
	if (this->array[index] < this->array[largest]) {
		int temp = this->array[index];
		this->array[index] = this->array[largest];
		this->array[largest] = temp;

		maxHeapify(largest);
	}
}
/**
 *��������
 *ֻ���һ���Ԫ�ؽ���maxHeapify
 *��벿�־�Ϊ��Ҷ���ɿ��ɶ����Ķ�
 *��ǰ�벿�ֿ�ʼ���Զѽ��е���
 */
void Heap::buildMaxHeap() {
	for (int i = (this->getLength()) / 2; i >= 0; i--) {
		maxHeapify(i);
	}
}
/**
 *���ж�����
 *�Ƚ�������
 *����Ԫ����ѵ����һ��Ԫ�ؽ��л���
 *�Ի������ĵ�һ��Ԫ�ؽ��ж����ʵ�ά��
 */
void Heap::heapSort() {
	this->buildMaxHeap();
	int initLength = this->getLength();
	int index = this->getLength() - 1;
	for (; index > 0; index--) {
		int temp = this->array[0];
		this->array[0] = this->array[index];
		this->array[index] = temp;

		this->setLength(index);
		maxHeapify(0);
	}
	this->setLength(initLength);
}
/**
 *��ȡ���е����Ԫ�ز�ά���ѵ�����
 */
int Heap::heapExtractMax() {
	if (this->getLength() < 1) {
		cout << "HEAP UNDERFLOW" << endl;
		return NULL;
	}
	int max = this->array[0];
	this->array[0] = this->array[this->getLength() - 1];
	this->setLength(this->getLength() - 1);
	maxHeapify(0);
	return max;
}
/**
 *����������ֵ�滻��ά���ѵ�����
 */
void Heap::heapIncreaseKey(int index, int key) {
	if (key < this->array[index]) {
		cout << "NEW KEY IS SMALLER THAN CURRENT KEY!" << endl;
	}
	else {
		this->array[index] = key;
		while (index > 0 && this->array[this->getParent(index)] < this->array[index]) {
			int temp = this->array[this->getParent(index)];
			this->array[this->getParent(index)] = this->array[index];
			this->array[index] = temp;
			index = this->getParent(index);
		}
	}
}
/**
 *�Զ����һ��Ԫ�ز�ά���ѵ�����
 */
void Heap::maxHeapInsert(int key) {
	int _length = this->getLength();
	int newLength = this->getLength() + 1;
	int *temp = new int[newLength];
	for (int i = 0; i < _length; i++) {
		temp[i] = this->array[i];
	}
	delete[]this->array;
	this->setArray(temp);
	this->setLength(newLength);
	this->heapIncreaseKey(newLength - 1, key);
}
/*
 *ɾ��ָ��Ԫ��
 *��Ҫɾ����Ԫ������е����һ��Ԫ�ػ���
 *�����һ��ɾ���Ի������Ԫ�ؽ���heapify
 */
void Heap::heapDelete(int index) {
	int temp1 = this->array[this->getLength() - 1];
	this->array[this->getLength() - 1] = this->array[index];
	this->array[index] = temp1;

	int key = this->array[index];
	int _length = this->getLength();
	int newLength = this->getLength() - 1;
	this->setLength(newLength);

	if (key <= this->array[this->getParent(index)]) {
		this->maxHeapify(index);
	}
	else {
		while (index >= 0 && this->array[this->getParent(index)] < this->array[index]) {
			int temp = this->array[this->getParent(index)];
			this->array[this->getParent(index)] = this->array[index];
			this->array[index] = temp;
			index = this->getParent(index);
		}
	}
}