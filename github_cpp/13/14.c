

#include "BubbleSortWrapper.h"


BubbleSortWrapper::BubbleSortWrapper() {}


BubbleSortWrapper::BubbleSortWrapper(int n) {

	
	_sort.setN(n);
	_sortData.setN(n);
}


BubbleSortWrapper::~BubbleSortWrapper() {}




void BubbleSortWrapper::run() {

	
	ofstream outputFile;
	outputFile.open("BSStats.csv");

	
	outputFile << "NSize, OptimalTime, WorstTime, AverageTime, Run1, Run2, Run3, Run4, Run5" << endl;

	
	BubbleSortWrapper _10;
	_10.setData(10);
	outputFile << _10._sortData;
	BubbleSortWrapper _50;
	_50.setData(50);
	outputFile << _50._sortData;
	BubbleSortWrapper _100;
	_100.setData(100);
	outputFile << _100._sortData;
	BubbleSortWrapper _500;
	_500.setData(500);
	outputFile << _500._sortData;
	BubbleSortWrapper _1000;
	_1000.setData(1000);
	outputFile << _1000._sortData;
	BubbleSortWrapper _5000;
	_5000.setData(5000);
	outputFile << _5000._sortData;
	BubbleSortWrapper _10000;
	_10000.setData(10000);
	outputFile << _10000._sortData;

	
	int _n50000 = 50000; 

	BubbleSortWrapper _50000;

	_50000._sort.setN(_n50000); 
	_50000._sortData.setN(_n50000); 

	_50000._sort.generateVectors(OPTIMAL); 
	_50000._sortData.getOptimal().setAvg(_50000._sort.doBubbleSort()); 
	_50000._sort.removeVectorElements(); 

	_50000._sort.generateVectors(AVERAGE); 
	_50000._sortData.getAverage().setAvg(_50000._sort.doBubbleSort()); 
	_50000._sort.removeVectorElements(); 

	_50000._sort.generateVectors(WORST); 
	_50000._sortData.getWorst().setAvg(_50000._sort.doBubbleSort()); 
	_50000._sort.removeVectorElements(); 

	outputFile << _50000._sortData;

	
	

	outputFile.close();
}




void BubbleSortWrapper::setData(int n) {
	setOptimalData(n);
	setAverageData(n);
	setWorstData(n);
}


void BubbleSortWrapper::setOptimalData(int &n) {
	
	_sort.setN(n);
	_sort.generateVectors(OPTIMAL); 
	_sortData.setN(n);
	_sortData.getOptimal().setT1(_sort.doBubbleSort()); 
	_sortData.getOptimal().setT2(_sort.doBubbleSort());
	_sortData.getOptimal().setT3(_sort.doBubbleSort());
	_sortData.getOptimal().setT4(_sort.doBubbleSort());
	_sortData.getOptimal().setT5(_sort.doBubbleSort());
	_sortData.getOptimal().calculateAvg();
	_sort.removeVectorElements();
}


void BubbleSortWrapper::setAverageData(int &n) {
	_sort.generateVectors(AVERAGE); 
	_sortData.getAverage().setT1(_sort.doBubbleSort()); 
	_sort.removeVectorElements();
	_sort.generateVectors(AVERAGE); 
	_sortData.getAverage().setT2(_sort.doBubbleSort());
	_sort.removeVectorElements();
	_sort.generateVectors(AVERAGE); 
	_sortData.getAverage().setT3(_sort.doBubbleSort());
	_sort.removeVectorElements();
	_sort.generateVectors(AVERAGE); 
	_sortData.getAverage().setT4(_sort.doBubbleSort());
	_sort.removeVectorElements();
	_sort.generateVectors(AVERAGE); 
	_sortData.getAverage().setT5(_sort.doBubbleSort());
	_sortData.getAverage().calculateAvg();
	_sort.removeVectorElements();
}


void BubbleSortWrapper::setWorstData(int &n) {
	_sort.generateVectors(WORST); 
	_sortData.getWorst().setT1(_sort.doBubbleSort()); 
	_sortData.getWorst().setT2(_sort.doBubbleSort());
	_sortData.getWorst().setT3(_sort.doBubbleSort());
	_sortData.getWorst().setT4(_sort.doBubbleSort());
	_sortData.getWorst().setT5(_sort.doBubbleSort());
	_sortData.getWorst().calculateAvg();
	_sort.removeVectorElements();
}










