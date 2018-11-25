#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
using namespace std;

template<typename T> _Task Mergesort{
        int *ori;                         
	int *cp;                          
	int flag;                         
	unsigned int l;                   
	unsigned int h;                   
	unsigned int d;                   
	void main(){
	  
		if(d == 0){
			mergesort(ori, cp, l, h);
			return;
		}

		else{
			
			unsigned int pivot = (l+h)/2;
			
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

			
			{
				Mergesort<T> a(ori, cp, l, pivot, d1);
				Mergesort<T> b(ori, cp, pivot+1, h, d2);
			}
			
			merge(ori, cp, l, pivot, h);
		}	
	}
	public:
	        
		Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth);
		
		~Mergesort(){
		        
			if(flag == 0) {
				delete cp;
			}
		}
	private:
		
		Mergesort(T values[], int *cp, unsigned int low, unsigned int high, unsigned int depth);
		
		void mergesort(int *a, int *b, unsigned int low, unsigned int high);
		
		void merge(int *a, int *b, unsigned int low, unsigned int pivot, unsigned int high);
};


template <typename T>
void Mergesort<T>:: mergesort(int *a, int *b, unsigned int low, unsigned int high){
	int pivot;
	if(low < high){
		pivot = (low + high)/2;
		mergesort(a, b, low, pivot);
		mergesort(a, b, pivot+1, high);
		merge(a, b, low, pivot, high);
	}			
}



template <typename T>
void Mergesort<T>:: merge(int *a, int *b, unsigned int low, unsigned int pivot, unsigned int high){
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


template <typename T>
Mergesort<T>:: Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	
	flag = 0;
	
	cp = new int[high-low+1];
}


template <typename T>
Mergesort<T>:: Mergesort(T values[], int *c, unsigned int low, unsigned int high, unsigned int depth){
	ori = values;
	l = low;
	h = high;
	d = depth;
	cp = c;
	
	flag = 1;
}
