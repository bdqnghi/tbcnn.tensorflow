#include <string>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class heap {

public:

	int *heapArr;
	int heapSize;
	int numElements;

	explicit heap();
	void insert(int val);
	//void deleteItem(int val);
	void maxHeap();
	void minheap();
	void print();
	~heap();

	// helper function
	int rightLeaf(int val);
	int leftLeaf(int val);
	int parent(int val);
	int maxVal(int i, int current, int left, int right);
};

heap::heap(){
	
	heapArr = new int[10];
	for (int i = 0; i < 10 ; i++){
		heapArr[i] = INT_MIN;
	}

	heapSize = 10;

}

heap::~heap(){

}

void heap::print(){

	for (int i = 0 ; i < heapSize ; i++ ){
		if (heapArr[i] == INT_MIN){
			std::cout << "x" << std::endl;
		}else{
			std::cout << heapArr[i] << " ";
	}
}

	std::cout << "\n";
}

int heap::leftLeaf(int val){
	return 2*val + 1;
}

int heap::rightLeaf(int val){
	return 2*val + 2;
}

int heap::parent(int val){
	return (val - 1) / 2;
}

void heap::insert(int val){
	heapArr[numElements] = val;
	numElements++;
}

void heap::maxHeap(){

	for (int i = heapSize/2 ; i > 0 ; i--){
		//std::cout << i << " see me" ;
		int temp = heapArr[i];
		int swapIndex = maxVal(i,heapArr[i],heapArr[leftLeaf(i)],heapArr[rightLeaf(i)]);
		heapArr[i] = heapArr[swapIndex];
		heapArr[swapIndex] = temp;
	}
	print();
}

int heap::maxVal(int index, int current,int left, int right){
	
	if (current > left && current > right){
		return index;
	}else if(left > current && left > right){
		return leftLeaf(index);
	}else{
		return rightLeaf(index);
	}
}

int main(){
	
	heap a;
	a.insert(4);
	a.insert(98);
	a.insert(13);
	a.insert(15);
	a.insert(5);
	a.insert(1);
	a.insert(9);
	a.insert(6);
	a.insert(67);
	a.insert(13);
	a.print();

	a.maxHeap();

	return 0;
}
