#include<iostream>
#include<vector>
using namespace std;

//Comparison fucntion
template <class T>
int ascendingOrder(T a,T b){
	if(a==b)
		return 0;
:q	return(a<b?-1:1);
}

//Comparison Function
template <class T>
int descendingOrder(T a,T b){
        if(a==b)
                return 0;
        return(a>b?-1:1);
}

//Display the elements
template <class T>
void display(vector<T> &v){
	for(int i=0;i<v.size();i++){
		cout << v[i] << "\t";
	}
}

//HeapSort - Finding left child
int leftChild(int i){
	return i*2+1;
}

//HeapSort - Finding right child
int rightChild(int i){
	return i*2+2;
}

//HeapSort - Finding parent
int parent(int i){
	return (i-1)/2;
}

//HeapSort - Swap two template elements
template <class T>
void swap(vector<T> &v,int firstIndex,int secondIndex){
	T temp;
	temp = v[firstIndex];
	v[firstIndex] = v[secondIndex];
	v[secondIndex] = temp;
}

//HeapSort - To maintain the heap property
template <class T>
void heapify(vector<T> &v,int i,int heapSize,int (cmpFn)(T a, T b)){
	int l = leftChild(i);
	int r = rightChild(i);
	int largest;
	if(l<=heapSize && (cmpFn(v[i],v[l])<0))
		largest = l;
	else
		largest = i;
	if(r<=heapSize && (cmpFn(v[largest],v[r])<0))
		largest = r;
	if(largest!=i){
		swap(v,largest,i);
		heapify(v,largest,heapSize,cmpFn);
	}
}

//HeapSort - Builds a heap from the array by calling Heapify
template <class T>
void buildHeap(vector<T> &v,int (cmpFn)(T a,T b)){
	int heapSize = v.size()-1;
	for(int i=(v.size()-2)/2;i>=0;i--)
	{
		heapify(v,i,heapSize,cmpFn);
	}
}

//HeapSort - performs sorting of template elements based on comparision function
template <class T>
void heapSort(vector<T> &v,int (cmpFn)(T a, T b) = ascendingOrder){
	buildHeap(v,cmpFn);
	int heapSize=v.size()-1,temp;
	for(int i=v.size()-1;i>=0;i--){	
		swap(v,heapSize,0);
		heapSize--;
		heapify(v,0,heapSize,cmpFn);
	}
}

//Heap Sort Reference - http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap07.htm

//main fucntion - creation and sorting of vectors with integer,float and character elements
int main(){
	vector<int> v;
	v.push_back(6);
	v.push_back(5);
	v.push_back(3);
	v.push_back(1);
	v.push_back(8);
	v.push_back(7);
	v.push_back(2);
	v.push_back(4);
	cout << "\nSet of Integer Values\t";
	display(v);
	cout << "\ndefault:\t\t";
	heapSort(v);
	display(v);
	cout << "\ndescendingOrder:\t";
        heapSort(v,descendingOrder);
        display(v);
	cout << "\nascendingOrder:\t\t";
        heapSort(v,ascendingOrder);
        display(v);

	vector<float> v1;
        v1.push_back(2.0);
        v1.push_back(3.6);
        v1.push_back(1.9);
	v1.push_back(4.0);
	v1.push_back(0.9);
	v1.push_back(4.2);
	v1.push_back(8.9);
	v1.push_back(1.9);
        cout << "\n\nSet of Float Values\t";
        display(v1);
        cout << "\ndefault:\t\t";
        heapSort(v1);
        display(v1);
        cout << "\ndescendingOrder:\t";
        heapSort(v1,descendingOrder);
        display(v1);
        cout << "\nascendingOrder:\t\t";
        heapSort(v1,ascendingOrder);
        display(v1);

        vector<char> v2;
        v2.push_back('g');
        v2.push_back('o');
        v2.push_back('w');
	v2.push_back('t');
	v2.push_back('h');
	v2.push_back('a');
	v2.push_back('m');
	v2.push_back('R');
        cout << "\n\nSet of Characters\t";
        display(v2);
        cout << "\ndefault:\t\t";
        heapSort(v2);
        display(v2);
        cout << "\ndescendingOrder\t\t";
        heapSort(v2,descendingOrder);
        display(v2);
        cout << "\nascendingOrder\t\t";
        heapSort(v2,ascendingOrder);
        display(v2);

}
