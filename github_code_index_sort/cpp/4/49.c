/**
 *	Author: Caleb A. Payton
 *	
 *	Heapsort algorithm
 *	Program generates a vector of size 20 with random
 *	integers ranging from 1 to 20. Prints unsorted vector,
 *	uses heapsort algorithm to sort integers, then prints
 *	sorted vector.
 */

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;

template<typename Comparable>
void heapsort(vector<Comparable> & a);

template<typename Comparable>
void percDown(vector<Comparable> & a, int i, int n);

void printVector(vector<int> & h);

template<typename Comparable>
void heapsort(vector<Comparable> & a)
{	
	int i;
	int n;
	percDown(a, i, n);
	
	for (int i = a.size() / 2; i >= 0; i--) /* buildHeap */
		percDown(a, i, a.size());
	for (int j = a.size() - 1; j > 0; j--)
	{
		swap(a[0], a[j]); /* deleteMax */
		percDown(a, 0, j);
	}
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
	return 2 * i;
}

/**
 * Internal method for heapsort that is used in deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template<typename Comparable>
void percDown(vector<Comparable> & a, int i, int n)
{
	int child;
	Comparable tmp;

	for (tmp = a[i]; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])
			child++;
		if (tmp < a[child])
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}

void printVector(vector<int> & h)
{
	unsigned int i;
	cout << "Vector:" << endl;
	cout << h[0];
	for (i = 0; i < h.size(); ++i)
	{
		cout << ", " << h[i];
	} // end for
	cout << endl;
}

int main()
{

	vector<int> h(20);

	int i;
	srand(time(NULL));
	for (i = 0; i < h.size(); ++i)
	{
		h[i] = (rand()%20) + 1;
	}
	printVector(h);
	heapsort(h);
	cout << "\nSorted ";
	printVector(h);
	return 0;

}
