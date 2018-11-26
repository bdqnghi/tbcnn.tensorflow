
#include <vector>
//#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <iostream>

#include "timer.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////
//
template <class T>
void print(vector<T>& v, ostream& out = std::cout){
	
	if (v.empty()) {
		out << "[]";
		return;
	}

	out << "[";
	for (size_t i =0; i < v.size() - 1; i++){
		out << v[i] << ", ";
	}
	out << *v.rbegin();
	out << "]";
}

////////////////////////////////////////////////////////////////////////////
//
template <class T>
bool checkResult(vector<T>& v){
	float last = *v.begin();
	vector<int>::iterator it;
	for (it = v.begin()+1; it != v.end(); it ++){
		if (last > *it)
			return false;
		last = *it;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////
//
template  <class T>
void bubleSort(vector<T>& v){

	bool swapped;
	do{
		swapped = false;
		for (long long i =1; i < v.size(); i++){
			if (v[i-1] > v[i]){

				T aux = v[i];
				v[i] = v[i-1];
				v[i-1] = aux;
				
				swapped = true;
			}
		}
	}while (swapped);
}

////////////////////////////////////////////////////////////////////////////
//
template <class T>
void bucketSort (vector<T>& v, unsigned classes = 1000){
	vector<vector<T> > buckets(classes);
	
	for (size_t i=0; i< v.size(); i++){
		unsigned index = v[i];
		buckets[index].push_back(v[i]);
	}

	v.clear();
	for (int i=0; i< classes; i++){
		if (buckets[i].empty())
			continue;
		bubleSort(buckets[i]);
		v.insert( v.end(), buckets[i].begin(), buckets[i].end());
	}
}

////////////////////////////////////////////////////////////////////////////
//
template <unsigned byte>
void radix (vector<int>& in, vector<int>& out){
	unsigned count[256];
	unsigned index[256];
	memset(count, 0x0, sizeof(unsigned) * 256);
	
	for (size_t i=0; i< in.size(); i++)
		count[ ((in[i]) >> (byte*8)) & 0xff] ++;
	
	index[0] =0;	
	for (size_t i=1; i< 256; i++)
		index[i] = index[i-1] + count[i-1];

	for (size_t i=0; i< in.size(); i++)
		out[index[((in[i]) >> (byte*8)) &0xff]++] = in[i];
}

void radixSort (vector<int>& v){

	vector<int> temp(v.size());
	radix<0> (v, temp);
	radix<1> (temp, v);
	radix<2> (v, temp);
	radix<3> (temp, v);
}

////////////////////////////////////////////////////////////////////////////
//
template <class T>
void insertionSort(vector<T>&v){

	for(size_t i=1; i< v.size()-1; i++){
		T    item = v[i];
		size_t hole = i;
		
		while ((hole > 0) && (v[hole-1] > item)){
			v[hole] = v[hole-1];
			hole = hole-1;
		}
		v[hole] = item;
	}
}

////////////////////////////////////////////////////////////////////////////
//

template <class T>
void testAlgorithms (vector<T>& buffer){

	{
		ayuso::Timer time;

		vector<T> data(buffer);
		time.start();
		bubleSort(data);
		double t = time.stop();
	
		bool ok = checkResult(data);
		//cout << "BubbleSort took " << t << "sec - result: " << (ok?"OK":"WRONG") << "\n";
		cout << "BubbleSort " << (ok?"OK":"WRONG") << "\n";
	}

	{
		ayuso::Timer time;

		vector<T> data(buffer);
		time.start();
		bucketSort(data);
		double t = time.stop();
	
		bool ok = checkResult(data);
		//cout << "BucketSort took " << t << "sec - result: " << (ok?"OK":"WRONG") << "\n";
		cout << "BucketSort " << (ok?"OK":"WRONG") << "\n";
	}

//	runTest(bubleSort<T>, "BubbleSort", buffer);
//	runTest(bucketSort<T>, "BucketSort", buffer);
//	runTest(radixSort, "RadixSort", buffer);

}

////////////////////////////////////////////////////////////////////////////
//
int main (int argc, char **argv){

	vector<size_t> sizes;
	sizes.push_back(5);
	sizes.push_back(20);
	sizes.push_back(512);
	sizes.push_back(1024);
	sizes.push_back(1024*16);
/*
	sizes.push_back(1024*128);
	sizes.push_back(1024*1024);
	sizes.push_back(1024*1024*16);
*/
	for (size_t i = 0; i < sizes.size(); i++){

		cout << "Running Test for size " << sizes[i] << "\n";

		// generate speudo random (same data every run)
		srand(1234);
		vector<int> vData(sizes[i]);
		for (size_t j=0; j < sizes[i]; j++) {
			//	vData[j] = rand()%1000;
			vData.insert(vData.end(), rand()%1000);
		}

		testAlgorithms(vData);
	}

	return 0;
}
