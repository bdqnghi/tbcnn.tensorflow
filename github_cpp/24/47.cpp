#include<bits/stdc++.h>
def REP(i,a,b) for (int (i) = (a); i < (b); i++)

using namespace std;

string keys[10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
int visitpos[10]
map<string, int> mapstr;
int binary-search(string A, int low, int high, char key[], int pos, int keysize){
	if (low <= high){
		int mid = (low+high/2);
		if (A[mid] == key[pos]){
			if (mapstr[key[pos]] == '\0')
				mapstr[key[pos]] = pos;
			else if (mapstr[key[pos]] <= mid){
				pos++;
				if (pos == keysize) return 1;
				else binary-search(A, low, high, key, pos, keysize);
		}
		else if (A, low, mid-1, )


	}
}

int func(string encr, int size){
	int res;
	sort(encr.begin(), encr.end());
	REP(i,0,10)
		res = binary-search(encr, 0, size, keys[i], 0, keys[i].size());

}

int main(){
	int T;
	string encr;
	cin >> T;
	REP(i,0,T){
		cin >> encr;
		func(encr, encr.size());


	}


}