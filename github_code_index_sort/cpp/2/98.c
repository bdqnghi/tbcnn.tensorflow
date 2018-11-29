#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
using namespace std;

template<typename T> _Task Mergesort{
    T *ori;                         //use to store the original array
	T *cp;                          //use to sort
	int flag;                         //conditional flag, use to clear array
	unsigned int l;                   //start point of array
	unsigned int h;                   //end of the array
	unsigned int d;                   //depth
	void main(){
	  //check depth, if depth is zero call the mergesort ans return
		if(d == 0){
			mergesort(ori, cp, l, h);
			return;
		}

		else{
			//caculate the pivot
			unsigned int pivot = (l+h)/2;
			//caculate the next depth
			unsigned int d1=d;
			if(l >= pivot){
				d1 = 0;
			}
			else{
				d1 = d1-1;			
			}
			unsigned int d2=d;
			if(pivot >= h){
				d2 = 0;
			}
			else{
				d2 = d2-1;			
			}

			//make two new mergesort tasks
			{
				Mergesort<T> a(ori, cp, l, pivot, d1);
				Mergesort<T> b(ori, cp, pivot+1, h, d2);
			}
			//merge two sorted array
			merge(ori, cp, l, pivot, h);
		}	
	}
	public:
	        //constructor
		Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth);
		//destructor
		~Mergesort(){
		        //delete the cp when finish the first task
			if(flag == 0) {
				delete cp;
			}
		}
	private:
		//private constructor. pass array pointer to the child task
		Mergesort(T values[], T *cp, unsigned int low, unsigned int high, unsigned int depth);
		//mergesort. sort the array by recursion
		void mergesort(T *a, T *b, unsigned int low, unsigned int high);
		//merge two sorted array. called after mergesort
		void merge(T *a, T *b, unsigned int low, unsigned int pivot, unsigned int high);
};

//mergesort
template <typename T>
void Mergesort<T>:: mergesort(T *a, T *b, unsigned int low, unsigned int high){
	int pivot;
	if(low < high){
		pivot = (low + high)/2;
		mergesort(a, b, low, pivot);
		mergesort(a, b, pivot+1, high);
		merge(a, b, low, pivot, high);
	}			
}

//helper func to the mergesort
//merge two sorted array
template <typename T>
void Mergesort<T>:: merge(T *a, T *b, unsigned int low, unsigned int pivot, unsigned int high){
	unsigned int h,i,j,k;
	h = low;
	i = low;
	j = pivot+1;

	while((h<=pivot)&&(j<=high)){
		if(a[h]<=a[j]){
			b[i] = a[h];
			h++;
		}
		else{
			b[i] = a[j];
			j++;
		}
		i++;
	}
	if(h>pivot){
		for(k = j; i<=high; k++){
			b[i] = a[k];
			i++;
		}
	}
	else{
		for(k=h; k<=pivot; k++){
			b[i] = a[k];
			i++;
		}
	}

	for(unsigned int i = low; i <= high; i++){
		a[i] = b[i];
	}
}

//public constructor
template <typename T>
Mergesort<T>:: Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	//set the flag
	flag = 0;
	//create a array. use to sort array 
	cp = new T[high-low+1];
}

//private constructor
template <typename T>
Mergesort<T>:: Mergesort(T values[], T *c, unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	cp = c;
	//set the flag
	flag = 1;
}
