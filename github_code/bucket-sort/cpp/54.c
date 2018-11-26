#include "SequenceBucketSort.h"
/*
Init some value
*/
SequenceBucketSort::SequenceBucketSort(string fileName, unsigned long numBuc, int max, int min):fileInput(fileName),
numBucket(numBuc), maxVal(max), minVal(min)
{
		offset = ceil((maxVal - minVal)/(numBucket + 0.0));
}
/*
Find name of bucket, then put value to its bucket file
*/
void SequenceBucketSort::PutToCorrectBucket(int value,
		unsigned long indexBuck) {
	listBucket[indexBuck].push_back(value);
}
/*
Open file input to get data
Then, put each number to correct bucket
*/
bool SequenceBucketSort::GenerateBucket(int minValue, int maxValue,
		unsigned long numBuck, string inputFile) {
	int tmpVal;
	ifstream input(inputFile.c_str());

	if (!input.is_open()) {
		cerr << "Error when open input files\n";
		return false;
	}
	while (input >> tmpVal) {
		PutToCorrectBucket(tmpVal,tmpVal/offset);
	}
	return true;
}
/*
Write list number has shorted to output file
*/
void SequenceBucketSort::writeResultToFile(deque<int> list, ofstream& out){
	while(!list.empty()){
		int val = list.front();
		out<<val<<" ";
		list.pop_front();
	}
}
/*
Sort all instances of Bucket, we just use the stl sort (introsort) with Big-O = O(nlogn) in worst case
Then, call function to write output
*/
void SequenceBucketSort::sortCurrentBucket(unsigned long indexBuck,
		ofstream& out) {
	sort(listBucket[indexBuck].begin(), listBucket[indexBuck].end());
	writeResultToFile(listBucket[indexBuck],out);
}
/*
Call function to generate all bucket from array saved in file
Sort and gather all bucket ordered, then write to output file
*/
void SequenceBucketSort::Run() {
	GenerateBucket(minVal, maxVal, numBucket, fileInput.c_str());
	ofstream out("output.txt");
	for(size_t i = 0; i<=numBucket; ++i){
		sortCurrentBucket(i,out);
	}
}
