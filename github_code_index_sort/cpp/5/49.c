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

class BubbleSortFromFile
{
	public:		
			const char *filepath; // Dosyanin dizini
			ifstream fi; // Datalarin okunacagi dosyanin streami			
			int temp; // Dosyadan okunan degeler gecici olarak burada tutulacak.
			vector<int> numbers; // Dosyadan gelen datalarin tutuldugu vector
			vector<int>::iterator p; // vektor uzerinde iterasyon yapabilmek gerekli pointer
			BubbleSortFromFile(const char *); // Kurucu fonksiyon
			~BubbleSortFromFile();
			bool readFromFile(); // Dosyadan deger okuyup vector'e add yapan function
			void printNumbers(); // Vectorde ki sayilari ekrana yazan function
			void bubbleSort(); // Bubble sort algoritmasini vector uzerinde kostur!
			void printFirstTenNumber(); // ilk 10 sayiyi yazdir
			void printLastTenNumber(); // Son 10 sayiyi yazdir			
};
BubbleSortFromFile::BubbleSortFromFile(const char *file)
{
	filepath=file;
	this->readFromFile();
}
bool BubbleSortFromFile::readFromFile(){		
	fi.open(filepath);
	if(!fi.is_open()) return 0;
	while(fi >> temp)
	{
		numbers.push_back(temp);
	}
	return 1;
}
void BubbleSortFromFile::printNumbers()
{	
	p=numbers.begin();
	while(p!=numbers.end())
	{
		cout<<*p<<" ";
		p++;
	}
	cout << endl;
}

void BubbleSortFromFile::bubbleSort()
{
	for(int i=0; i < numbers.size();i++)
		for(int j=i+1; j < numbers.size();j++)
			{
			if (numbers[i] > numbers[j])
				{
					int temp;
					temp = numbers[i];
					numbers[i]=numbers[j];
					numbers[j]=temp;
				}
			}		
}
void BubbleSortFromFile::printFirstTenNumber()
{
	cout << "Frist 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[i] << " ";
	cout << endl;
}
void BubbleSortFromFile::printLastTenNumber()
{
	cout << "Last 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[numbers.size()-1-i] << " ";
	cout << endl;
}
BubbleSortFromFile::~BubbleSortFromFile()
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
	BubbleSortFromFile _1k(source);
	timer.Start(); 
	_1k.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "1k = " << timeresult << endl;
	timer.Reset();
	// 10k number
	source = "../../10k.lst";
	BubbleSortFromFile _10k(source);
	timer.Start(); 
	_10k.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10k = " << timeresult << endl;	
	timer.Reset();
	// 100k number
	source = "../../100k.lst";
	BubbleSortFromFile _100k(source);
	timer.Start(); 
	_100k.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "100k = " << timeresult << endl;	
	timer.Reset();	
	// 1M number
	source = "../../1m.lst";
	BubbleSortFromFile _1m(source);
	timer.Start(); 
	_1m.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "1m = " << timeresult << endl;	
	timer.Reset();		
	// 2M number
	source = "../../2m.lst";
	BubbleSortFromFile _2m(source);
	timer.Start(); 
	_2m.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "2m = " << timeresult << endl;	
	timer.Reset();		
	// 4M number
	source = "../../4m.lst";
	BubbleSortFromFile _4m(source);
	timer.Start(); 
	_4m.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "4m = " << timeresult << endl;	
	timer.Reset();		
	// 8M number
	source = "../../8m.lst";
	BubbleSortFromFile _8m(source);
	timer.Start(); 
	_8m.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "8m = " << timeresult << endl;	
	timer.Reset();		
	// 10M number
	source = "../../10m.lst";
	BubbleSortFromFile _10m(source);
	timer.Start(); 
	_10m.bubbleSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10m = " << timeresult << endl;	
	timer.Reset();		
	return 0;	
}





















