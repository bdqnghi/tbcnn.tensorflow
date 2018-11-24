#include <iostream>

using namespace std;

typedef unsigned int uint;

template <class T>
struct CNode{
	T* values;
	T** links;
	uint n;
	CNode(uint n){
		this->n = n;
		values = new T[n];
		links = new T*[n+1];
		uint i;
		for(i = 0; i < n; i++){
			links[i] = values[i] = 0;
		}
		links[i] = 0;
	}
	bool findVal(T val, uint pos){
		uint i;
		for(i = 0; i < n && values[i] < val; i++){
			;
		}
		pos = i;
		return val == values[i];
	}
};

template <class T>
class CBTree{
	CNode<T>* root;
	uint N;
	bool findIorD(T val, CNode<T>**& p);
public:
	CBTree(uint n);
	bool find(T val);
};

template <class T>
CBTree<T>::CBTree(uint n){
	this->N = n;
	root = new CNode<T>(N);
}

template <class T>
bool CBTree<T>::find(T val){
	CNode<T>* temp = root;
	uint p;
	while (temp && !temp->findVal(val, p)){
		if (p == N-1 || ! (temp->values[p+1]) ){ //p es el ultimo valor o la siguiente casilla esta vacia
			if (val > temp->values[p]) temp = temp->links[p+1]; 
		} else temp = temp->links[p];
	}
	return temp && temp->findVal(val, p);
}

int main(int argc, char *argv[]) {
	
	return 0;
}

