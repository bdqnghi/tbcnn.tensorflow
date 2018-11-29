/*
	Li, Gellert
	Tang, Paul

	CS A200

	19th September, 2018
	Lab 02
*/

#include "BucketSort.h"
#include <iostream>


void BucketSort::insert(const std::vector<double> &v) {
	for (int i = 0; i < v.size(); i++) {
		int index = int(v[i] * 10);
		bucket[index]->insert(v[i]);
	}
}

BucketSort::BucketSort() {
	numberOfElements = 10;
	bucket = new Bucket*[numberOfElements];
	for (int i = 0; i < 10; i++) {
		bucket[i] = new Bucket();
	};

}

BucketSort::~BucketSort() {
	for (int i = 0; i < numberOfElements; i++) {
		delete bucket[i];
	}
	delete[] bucket;
}

void BucketSort::print() {
	for (int i = 0; i < numberOfElements; i++) {
		bucket[i]->print();
		std::cout << std::endl;
	}
}

void BucketSort::createSortedList(Bucket & bucket) const {
	for (int i = 0; i < numberOfElements; i++) {
		bucket.moveAppend(std::move(*this->bucket[i]));
	}
}
