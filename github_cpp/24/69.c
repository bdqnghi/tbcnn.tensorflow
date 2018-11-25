#include <iostream>
using namespace std;

int main() {

	int a [8], x, k, j, i;
	
	for(int l=1; l <= 8; l++){
		a [l] = l;
	}
	cin >> x;
	i=1;
	j=8;
	k= (i+j)/2;
	
	a [k] = (i+j)/2;
	
	if (k == x){
		cout << "Data Ditemukan" << endl;
		}
			
				
	if (k != x) {
		if (x>k){
			int i=k+1, j=8;
			k = (i + j) / 2;
			if (k == x) {
			cout << "data ditemukan" << endl;
			}
		}
	
		if (x<k){
			int i=1, j=k-1;
			k = (i + j) / 2;
			if (k == x) {
			cout << "data ditemukan" << endl;
			}
		}
		
	}
	
	
	if(x>8 || x<1) {
		cout << "data tidak ditemukan";
	}
	
	
	return 0;	
}

