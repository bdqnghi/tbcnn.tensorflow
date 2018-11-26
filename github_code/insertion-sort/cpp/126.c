#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

template<class T>
void insertionSort(vector<T> &v){
	for(int i = 2; i < v.size(); i++){
		int x = v[i];
		int j = i-1;
		v[0] = x;//sentinela//
		while(x < v[j]){
			v[j+1] = v[j];
			j--;
		}
		int aux = v[j+1];
		v[j+1] = x;
		x = aux;
	}
}
/*
template<class T>
void preenche(vector<T> &v){
	for(int i = 0; i < v.size(); i++){
		(srand(unsigned)time(0));
		v[i] = rand();
	}
}*/

template<class T>
void printVector(vector<T> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

int main(){
	vector<int> v = {90,9,1,4,7,1};
	printVector(v);
	cout << "---------------------\n";
	insertionSort(v);
	printVector(v);
	return 0;
}