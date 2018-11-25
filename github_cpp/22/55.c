#include <iostream>
#include <vector>
using namespace std;


int Med(vector <int> &M, int a, int b, int c){
	if (M[a] >= M[b] && M[b] >= M[c])
		return b;
	if (M[a] >= M[c] && M[c] >= M[b])
		return c;
	if (M[b] >= M[a] && M[a] >= M[c])
		return a;
	if (M[b] >= M[c] && M[c] >= M[a])
		return c;
	if (M[c] >= M[b] && M[b] >= M[a])
		return b;
	if (M[c] >= M[a] && M[a] >= M[b])
		return a;

}

void swap(int&a, int&b){
	int c = a;
	a = b;
	b = c;
}

void InsertSort(vector <int> M, int first, int last){
	for (int i = first; i <= last; i++)
	{
		int temp = M[i];
		int j = i - 1;
		while (j >= 0 && M[j] > temp)
		{
			M[j + 1] = M[j];
			j--;
		}
		M[j + 1] = temp;
	}
}

void quickSort(vector <int> &a, int l, int r)
{
	if (r - l < 4){
		InsertSort(a, l, r);
	}
	else{

		swap(a[l + (r - l) / 2], a[Med(a, l, r, (l + (r - l) / 2))]);
		int x = a[l + (r - l) / 2];
		int i = l;

		int j = r;

		while (i <= j)
		{
			while (a[i] < x) i++;
			while (a[j] > x) j--;
			if (i <= j)
			{
				swap(a[i], a[j]);
				i++;
				j--;
			}
		}
		if (i < r){
			quickSort(a, i, r);
		}
		if (l < j)
			quickSort(a, l, j);
	}
}

int Find_max(int*Arr, int size){ 
	int res=0;
	for (int i = 0; i < size; i++){
		if (res < Arr[i])
			res = Arr[i];
		
	}
	return res;
}

void BucketSort(int*Arr, int size){ 
	int max = Find_max(Arr, size);
	int cou = (max / 10) + 1;
	vector <vector<int>> b(cou);
	for (int i = 0; i < size; i++){
		for (int j = 0; j < cou; j++){
			if ((Arr[i] >= 10 * j) && (Arr[i] <= 10 * j + 9)){
				b[j].push_back(Arr[i]);
			}
		}
	}
	for (int i = 0; i < cou; i++){
		quickSort(b[i], 0, b[i].size() - 1);
	}
	int k = 0;
	for (int i = 0; i < cou; i++)
		for (int j = 0; j < b[i].size(); j++){
			if (b[i].size() != 0){
				Arr[k] = b[i][j];
				k++;
			}
		}
}

int main(){
	int n;
	cin >> n;
	int*Arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> Arr[i];
	BucketSort(Arr, n);
	for (int i = 0; i < n; i++)
		cout << Arr[i] << " ";

	return 0;
}
