#include <bits/stdc++.h>
#include <math.h>

using namespace std;

typedef struct buck {
	double key;
	buck *next;
}buck;

buck *insert_node(double k) {
	buck *temp = new buck;
	temp -> key = k;
	temp -> next = NULL;
	return temp;
}


buck *buck_insert(double k, buck *bucket) {
	buck *temp = bucket;
	buck *tt;
	if (temp == NULL) {
		bucket = insert_node(k);
		return bucket;
	}
	if (bucket -> key > k) {
		buck *tem = insert_node(k);
		tem->next = bucket;
		return tem;
	}

	while ((temp -> next != NULL) && (temp-> next-> key < k)) {
		temp = temp->next;
	}
	tt = temp -> next;
	temp->next = insert_node(k);
	temp = temp -> next;
	temp -> next = tt;
	
	return bucket;
}

void bucketsort(double a[], int n) {
	buck *bucket[n];
	int i;
	for (i = 0; i < n; i++) {
		bucket[i] = NULL;
	}	

	for (i = 0; i < n; i++) {
		bucket[(int)(n * a[i])] = buck_insert(a[i], bucket[(int)(n * a[i])]);
	}	
	
	int k = 0;
	for (i = 0; i < n ; i++) {
		while (bucket[i] != NULL) {
			a[k++] = bucket[i] -> key;
			bucket[i] = bucket[i] -> next;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int i;
	double a[n];
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}

	bucketsort(a, n);
	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}
