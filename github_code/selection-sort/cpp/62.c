#include <iostream>
#include <conio.h>
#include "ctimer.hpp"
#include <vector>
#include <fstream>
/*
# Mehmet Dursun INCE 26.03.2013 
#
# Using bubble sort algorithm in huge data stack.
*/
using namespace std;

class SelectionSortFromFile
{
	public:		
			const char *filepath; // Dosyanin dizini
			ifstream fi; // Datalarin okunacagi dosyanin streami			
			int temp; // Dosyadan okunan degeler gecici olarak burada tutulacak.
			vector<int> numbers; // Dosyadan gelen datalarin tutuldugu vector
			vector<int>::iterator p; // vektor uzerinde iterasyon yapabilmek gerekli pointer
			SelectionSortFromFile(const char *); // Kurucu fonksiyon
			~SelectionSortFromFile();
			bool readFromFile(); // Dosyadan deger okuyup vector'e add yapan function
			void printNumbers(); // Vectorde ki sayilari ekrana yazan function
			void selectionSort(); // Bubble sort algoritmasini vector uzerinde kostur!
			void printFirstTenNumber(); // ilk 10 sayiyi yazdir
			void printLastTenNumber(); // Son 10 sayiyi yazdir			
};
SelectionSortFromFile::SelectionSortFromFile(const char *file)
{
	filepath=file;
	this->readFromFile();
}
bool SelectionSortFromFile::readFromFile(){		
	fi.open(filepath);
	if(!fi.is_open()) return 0;
	while(fi >> temp)
	{
		numbers.push_back(temp);
	}
	return 1;
}
void SelectionSortFromFile::printNumbers()
{	
	p=numbers.begin();
	while(p!=numbers.end())
	{
		cout<<*p<<" ";
		p++;
	}
	cout << endl;
}

void SelectionSortFromFile::selectionSort()
{
/*
From http://en.wikipedia.org/wiki/Selection_sort
*/
	int n = numbers.size();
	int iMin;
	for (int j = 0; j < n-1; j++) {
		/* find the min element in the unsorted a[j .. n-1] */
	 
		/* assume the min is the first element */
		iMin = j;
		/* test against elements after j to find the smallest */
		for (int i = j+1; i < n; i++) {
			/* if this element is less, then it is the new minimum */  
			if (numbers[i] < numbers[iMin]) {
				/* found new minimum; remember its index */
				iMin = i;
			}
		}
	 
		/* iMin is the index of the minimum element. Swap it with the current position */
		if ( iMin != j ) {
			swap(numbers[j], numbers[iMin]);
		}
	}	
}
void SelectionSortFromFile::printFirstTenNumber()
{
	cout << "Frist 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[i] << " ";
	cout << endl;
}
void SelectionSortFromFile::printLastTenNumber()
{
	cout << "Last 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[numbers.size()-1-i] << " ";
	cout << endl;
}
SelectionSortFromFile::~SelectionSortFromFile()
{
	numbers.erase(numbers.begin(), numbers.end());
}
int main(int argc, char **argv)
{
	CTimer timer; double timeresult;const char * source;
	ofstream of("results.txt",ios::app);
	timer.Reset();
	// 1k number
	source = "../../1k.lst";
	SelectionSortFromFile _1k(source);
	timer.Start(); 
	_1k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "1k = " << timeresult << endl;
	timer.Reset();
	// 10k number
	source = "../../10k.lst";
	SelectionSortFromFile _10k(source);
	timer.Start(); 
	_10k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10k = " << timeresult << endl;	
	timer.Reset();
	// 100k number
	source = "../../100k.lst";
	SelectionSortFromFile _100k(source);
	timer.Start(); 
	_100k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "100k = " << timeresult << endl;	
	timer.Reset();	
	// 1M number
	source = "../../1m.lst";
	SelectionSortFromFile _1m(source);
	timer.Start(); 
	_1m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "1m = " << timeresult << endl;	
	timer.Reset();		
	// 2M number
	source = "../../2m.lst";
	SelectionSortFromFile _2m(source);
	timer.Start(); 
	_2m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "2m = " << timeresult << endl;	
	timer.Reset();		
	// 4M number
	source = "../../4m.lst";
	SelectionSortFromFile _4m(source);
	timer.Start(); 
	_4m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "4m = " << timeresult << endl;	
	timer.Reset();		
	// 8M number
	source = "../../8m.lst";
	SelectionSortFromFile _8m(source);
	timer.Start(); 
	_8m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "8m = " << timeresult << endl;	
	timer.Reset();		
	// 10M number
	source = "../../10m.lst";
	SelectionSortFromFile _10m(source);
	timer.Start(); 
	_10m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10m = " << timeresult << endl;	
	timer.Reset();	
			
	return 0;	
}





















