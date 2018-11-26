#include <iostream>

using namespace std;

template<class T>
void insertionsort(T data[], int n) {
	
	for(int i=1;i<n;i++) {
		
		int j = i;
		
		while( (j>0) && (data[j-1] > data[j]) ) {
			swap(data[j], data[j-1]);
			j--;
		}
	} 
}

template<class T>
void swap(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

template< class T>
void showarray(T data[], int n) {
	for(int i=0;i<n;i++)
		cout << data[i] << " ";
}

main() 
{
    
	char data[] = {'z','a','c','b','f','e','a'};
	int n = sizeof(data)/sizeof(data[0]);
	
	insertionsort(data, n);
	showarray(data, n);
}