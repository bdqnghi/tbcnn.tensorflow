#include <iostream>
using namespace std;

void TowerOfHanoi(int n, char A, char B, char C) {
	if (n <= 0) return;
	TowerOfHanoi(n - 1, A, C, B);
	cout << "Move " << n << "th disc from T" << A << " to T" << B << endl;
	TowerOfHanoi(n - 1, C, B, A);
}

int CountTowerOfHanoi(int n, char A, char B, char C) {
	if (n <= 1) return 1;
	int count1 = CountTowerOfHanoi(n - 1, A, C, B);
	//cout << "Move " << n << "th disc from T" << A << " to T" << B << endl;
	int count2 = CountTowerOfHanoi(n - 1, C, B, A);
	return count1+count2+1;
}

int main() {
	int n;
	cin >> n;
	TowerOfHanoi(n, '1', '2', '3');
	cout << CountTowerOfHanoi(n, '1', '2', '3');
}