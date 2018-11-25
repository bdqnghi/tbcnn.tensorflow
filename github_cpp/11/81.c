

#include<iostream>
#include<fstream>
using namespace std;

class HeapSort{
public:
	HeapSort();
	int* myHeap;
	int size, index = 0;
	void heapAry();
	void buildHeap(ifstream&, ofstream&);
	void deleteHeap();
	void insertOneDataItem(int);
	void deleteRoot(ofstream&, ofstream&);
	void bubbleUp(int);
	void bubbleDown(int);
	bool isHeapEmpty();
	bool isHeapFull();
	void printHeap(ofstream&);
	~HeapSort();
};


HeapSort::HeapSort(){
	myHeap = NULL;
	size = 0;
}

void HeapSort::heapAry(){
	myHeap = new int[size];
	myHeap[0] = 0;
}

void HeapSort::buildHeap(ifstream& infile, ofstream& outfile){
	int value;
	while (infile >> value){
		insertOneDataItem(value);
		printHeap(outfile);
	}
}

void HeapSort::deleteHeap(){
	delete[] myHeap;
}

void HeapSort::insertOneDataItem(int data){
	index++;
	if (isHeapFull()) return;
	else{
		myHeap[index] = data;
		myHeap[0]++;
		bubbleUp(myHeap[0]);
	}
}

void HeapSort::deleteRoot(ofstream& outputFile1, ofstream& outputFile2){	
	if (isHeapEmpty()){
		outputFile1 << "The heap is empty.\n";
		return;
	} else{
		while(!isHeapEmpty()){
			outputFile2 << myHeap[1] << " ";
			myHeap[1] = myHeap[myHeap[0]];
			myHeap[0]--;
			if (myHeap[0] > 0){
				bubbleDown(1);
			}
			printHeap(outputFile1);
			
		}
	}
}

void HeapSort::bubbleUp(int index){
	int parentIndex, temp;
	if (index != 0){
		parentIndex = index / 2;
		if (myHeap[parentIndex] > myHeap[index]){
			temp = myHeap[parentIndex];
			myHeap[parentIndex] = myHeap[index];
			myHeap[index] = temp;
			bubbleUp(parentIndex);
		}
	}
}

void HeapSort::bubbleDown(int root){
	int leftChild, rightChild, minIndex, temp;
	leftChild = 2 * root;
	rightChild = 2 * root + 1;
	if (rightChild >= myHeap[0]){
		if (leftChild >= myHeap[0]){
			return;
		}
		else{
			minIndex = leftChild;
		}
	} else {
		if (myHeap[leftChild] <= myHeap[rightChild]){
			minIndex = leftChild;
		}
		else{
			minIndex = rightChild;
		}
	}
	if (myHeap[root] > myHeap[minIndex]){
		temp = myHeap[minIndex];
		myHeap[minIndex] = myHeap[root];
		myHeap[root] = temp;
		bubbleDown(minIndex);
	}
}

bool HeapSort::isHeapEmpty(){
	return myHeap[0] == 0;
}

bool HeapSort::isHeapFull(){
	return myHeap[0] == (size - 1);
}

void HeapSort::printHeap(ofstream& outfile){
	for (int i = 0; i <=  myHeap[0]; i++){
		outfile << myHeap[i] << " ";
	}
	outfile << endl;
}

HeapSort::~HeapSort(){
	deleteHeap();
}


int main(int argc, char* argv[])
{
	int count = 0, data;
	HeapSort* heapSort = new HeapSort();
	ifstream infile1;
	infile1.open(argv[1]);
	ofstream outfile1;
	outfile1.open(argv[2]);
	ofstream outfile2;
	outfile2.open(argv[3]);

	while (infile1 >> data){
		count++;
	}
	heapSort->size = (count + 1);
	heapSort->heapAry();
	infile1.close();

	ifstream infile2;
	infile2.open(argv[1]);
	heapSort->buildHeap(infile2, outfile1);
	infile2.close();
	heapSort->deleteRoot(outfile1, outfile2);
	system("pause");
	return 0;
}

