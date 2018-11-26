// merge.cpp
// compile with... 
// c++ merge.cpp -o merge
// execute with...
// ./merge

#include <iostream>
#include <limits>

void randomDouble (double *a, const int & si){
    for (int j = 0; j < si; j++)
        a[j] = (rand() % 999)/10.0;
}

void randomInts (int *a, const int & si){
    for (int j = 0; j < si; j++)
        a[j] = rand() % 999;
}

template <class Type>
void print (Type *a, const int & si){
    for (int j = 0; j < si; j++)
        std::cout<<a[j]<<", "; 
    std::cout<<std::endl;
}

template <class Type>
void merge(Type *A, const int & p, const int & q, const int & r){

	int n_one = q - p + 1;//1 
	int n_two = r - q; // 1

	int i=0;
	int j=0;
	int k=0;

	Type *L = new Type[n_one+1];
	Type *R = new Type[n_two+1];

	for(i = 0; i < n_one; ++i)
		L[i] = A[p+i];
	L[n_one] = std::numeric_limits<Type>::max();
	i = 0;

	for(j = 0; j < n_two; ++j)
		R[j] = A[q+j+1];
	R[n_two] = std::numeric_limits<Type>::max();
	j = 0;

	for(k = p; k <= r; ++k)
		if (L[i] <= R[j]){
			A[k]=L[i];
			i=i+1;
		}else{
			A[k]=R[j];
			j=j+1;
		}

}

template <class Type>
void mergeSort(Type *A, const int & p, const int & r){

	int q = 0;
	if (p<r){
		q = (p+r)/2;
		mergeSort(A,p,q);
		mergeSort(A,q+1,r);
		merge(A,p,q,r);
	}

}


int main() {
   int * p;
   int n = 10;

   p = new int[n];

   randomInts(p,n);

   print(p,n);

   mergeSort(p,0,9);

   print(p,n);


   delete [] p;
   return 0;
 }
