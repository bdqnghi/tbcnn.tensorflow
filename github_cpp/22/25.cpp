

#include "BucketSort.h"

using namespace std;

BucketSort::BucketSort()
{
	numOfElements = 10;
	a = new Bucket*[numOfElements];
	for (int i = 0; i < numOfElements; i++) {
		a[i] = new Bucket();
	}
}

void BucketSort::insert(vector<double> v)
{
	for (int i = 0; i < v.size(); i++) {
		int index = v[i] * 10;
		a[index]->insert(v[i]);
	}
}

void BucketSort::print() const
{
	for (int i = 0; i < 10; i++) {
		a[i]->print();
	}
}

BucketSort::~BucketSort()
{
	for (int i = 0; i < 10; i++) {
		a[i]->~Bucket();
	}
	delete[] a;
}
