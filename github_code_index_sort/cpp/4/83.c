#include <iostream>

using namespace std;

class Kopiec{
private:
	struct element{
		string miejsce;
		int aktywnosc;
		int indeks;
		bool operator < (const element& e)const{
  		if(this->aktywnosc < e.aktywnosc)
  			return true;
  		else if(this->aktywnosc == e.aktywnosc){
  			if(this->indeks < e.indeks)
  				return false;
  			else 
  				return true;
  		}
		else
			return false;
		}
	};
	int n;
	int min;
	element *kopiec;
public:
	Kopiec(){}
	Kopiec(int);
	void push(string, int);
	void pop();
	void wczytaj(int);
	void wypisz(int K);
};
Kopiec::Kopiec(int N){
	n = 0;
	min = 100000;
	kopiec = new element[N];
}
void Kopiec::push(string miejsce, int aktywnosc){
	element z_p;
	int index;	
    kopiec[n].miejsce = miejsce;
    kopiec[n].aktywnosc = aktywnosc;
    kopiec[n].indeks = n;
    n++;
    index = n-1;
	while(kopiec[(index-1)/2] < kopiec[index] && index!=0){  //logn
		z_p = kopiec[index];
		kopiec[index] = kopiec[(index-1)/2];
		kopiec[(index-1)/2] = z_p;
		index = (index-1)/2;
	}
}


void Kopiec::wypisz(int K){
	while(n != 0 && K > 0 && K >= min){
		if(K < kopiec[0].aktywnosc)
			pop();
		else{
			K-=kopiec[0].aktywnosc;
			cout << kopiec[0].miejsce << " ";
			pop();
		}
	}
		
}
void Kopiec::pop(){ //logn 
	element z_p;
	kopiec[0] = kopiec[n-1];
	n--;
	int index = 0;
		while( (index*2+1 < n  && kopiec[index] < kopiec[index*2+1]) || ( index*2+2 < n && kopiec[index] < kopiec[index*2+2])){
			if( index*2+2 < n && kopiec[index*2+1] < kopiec[index*2+2]){
				z_p = kopiec[index*2+2];
				kopiec[index*2+2] = kopiec[index];
				kopiec[index] = z_p;
				index = index*2 + 2;
			}
			else if(index*2+2 < n && kopiec[index*2+2] < kopiec[index*2+1]){
				z_p = kopiec[index*2+1];
				kopiec[index*2+1] = kopiec[index];
				kopiec[index] = z_p;
				index = index*2 + 1;
			}
			else{
				z_p = kopiec[index*2+1];
				kopiec[index*2+1] = kopiec[index];
				kopiec[index] = z_p;
				index = index*2 + 1;
			}
		}
	
}
void Kopiec::wczytaj(int N){
	
	string S;
	int L;
	int K;
	for(int i = 0; i < N; i++){
		cin >> S;
		cin >> L;
		if(L < min)
			min = L;
		push(S, L);
	}
}

int main(){
	//nlogn
	ios_base::sync_with_stdio(false);
	int N;
	int K;
	cin >> N;
	Kopiec k(N);
	k.wczytaj(N);
	cin >> K;
	k.wypisz(K);
	return 0;
}
