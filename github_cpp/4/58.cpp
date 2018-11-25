#define _CRT_SECURE_NO_WARNINGS
#include "hanoi.h"






void hanoi(int n, TowerOfHanoi &x, TowerOfHanoi &y, TowerOfHanoi &z) {

	if (n == 0) return; 

	hanoi(n - 1, x, z, y); 

	move(x, y); 

	print_all(x, y, z); 

	hanoi(n - 1, z, y, x); 

}


int main(void) {

	TowerOfHanoi a('X'), b('Y'), c('Z');

	for (int i = 6; i > 0; i--) a.push(i);
	print_all(a, b, c);

	hanoi(a.size(), a, b, c);

	print_all(a, b, c);
	assert(a.empty());
	assert(b.CheckDisk()); 
	assert(c.empty());

	printf("Passed all tests.\n");

	return 0;
}

void move(TowerOfHanoi &x, TowerOfHanoi &y) {

	assert(!x.empty());
	if (!y.empty()) assert(x.top() < y.top());

	y.push(x.top());
	x.pop();
}

bool empty(const TowerOfHanoi &x) {

	return x.empty();
}

bool size(const TowerOfHanoi &x) {

	return x.size();
}

void print(TowerOfHanoi x) {

	TowerOfHanoi temp('T');

	printf("%c:", x._name);

	while (!x.empty()) {
		assert(!x.empty());
		temp.push(x.top());
		x.pop();
	}

	while (!temp.empty()) {
		printf("%d-", temp.top());
		temp.pop();
	}
	printf("\n");
}

void print_all(const TowerOfHanoi x, const TowerOfHanoi y, const TowerOfHanoi z) {
	char name = 'X';

	while (true) {
		if (name == x._name) {
			print(x);
			name++;
		}
		else if (name == y._name) {
			print(y);
			name++;
		}
		else if (name == z._name) {
			print(z);
			name++;
		}
		else break;
	}

	printf("--------------------\n");
}

bool TowerOfHanoi::CheckDisk() {
	int temp = 0;

	while (this->size() > 1) {
		temp = this->top();

		this->pop();


		if (temp > this->top()) return false;
	}

	return true;
}
