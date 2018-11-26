#include <iostream>
#include <conio.h>
#include "ctimer.hpp"
#include <vector>
#include <fstream>
/*
# Mehmet Dursun INCE 26.03.2013 
#
# Using quick sort algorithm in huge data stack.
*/
using namespace std;

class QuickSortFromFile
{
	private:		
		const char * filepath; // Dosyanin dizini
		ifstream fi; // Datalarin okunacagi dosyanin streami
		int temp; // Dosyadan okunan degerleri gecici olarka burada tutulacaktir.
		vector <int> numbers; // Sayilar bu vektorde tutulacaktir.
		vector <int>::iterator p; // Vektor uzerinde ki sayilara bu pointer ile ulasilacaktir.
	public:
		QuickSortFromFile(const char *);
		~QuickSortFromFile();
		bool readFromFile(); // Dosyadan deger okuyup vector'e add yapan function
		void printNumbers(); // Vectorde ki sayilari ekrana yazan function
		void printFirstTenNumber(); // ilk 10 sayiyi yazdir
		void printLastTenNumber(); // Son 10 sayiyi yazdir
		void quickSort(int, int); // quickSort islemi ile siralamayi yapacak function		
		void quickSortStart();
		int partition(int , int);
};
QuickSortFromFile::QuickSortFromFile(const char *file)
{
	filepath = file;
	this->readFromFile();
}
QuickSortFromFile::~QuickSortFromFile()
{
	numbers.erase(numbers.begin(), numbers.end());
}
bool QuickSortFromFile::readFromFile()
{
	fi.open(filepath);
	if(!fi.is_open()) return 0;
	while(fi >> temp)
	{
		numbers.push_back(temp);
	}
	return 1;
}
void QuickSortFromFile::printNumbers()
{
	p = numbers.begin();
	while(p!=numbers.end())
	{
		cout << *p << " "; p++;
	}
	cout << endl;
}
void QuickSortFromFile::printFirstTenNumber()
{
	cout << "Frist 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[i] << " ";
	cout << endl;
}
void QuickSortFromFile::printLastTenNumber()
{
	cout << "Last 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[numbers.size()-1-i] << " ";
	cout << endl;
}
int QuickSortFromFile::partition(int p, int r)
{
    int pivot = numbers[r];

    while ( p < r )
    {
        while ( numbers[p] < pivot )
            p++;

        while ( numbers[r] > pivot )
            r--;

        if ( numbers[p] == numbers[r] )
            p++;
        else if ( p < r )
        {
            int tmp = numbers[p];
            numbers[p] = numbers[r];
            numbers[r] = tmp;
        }
    }

    return r;
}
void QuickSortFromFile::quickSortStart()
{
	quickSort(0,numbers.size());
}
// The quicksort recursive function

void QuickSortFromFile::quickSort( int p, int r)
{
    if ( p < r )
    {
        int j = partition( p, r);        
        quickSort( p, j-1);
        quickSort( j+1, r);
    }
}

int main(int argc, char **argv)
int main(int argc, char **argv)
{
	CTimer timer; double timeresult;const char * source;
	ofstream of("results.txt",ios::app);
	timer.Reset();
	// 1k number
	source = "../../1k.lst";
	QuickSortFromFile _1k(source);
	timer.Start(); 
	_1k.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "1k = " << timeresult << endl;
	timer.Reset();
	// 10k number
	source = "../../10k.lst";
	QuickSortFromFile _10k(source);
	timer.Start(); 
	_10k.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "10k = " << timeresult << endl;
	timer.Reset();

	
	// 100k number
	source = "../../100k.lst";
	QuickSortFromFile _100k(source);
	timer.Start(); 
	_100k.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "100k = " << timeresult << endl;	
	timer.Reset();	
	// 1M number
	source = "../../1m.lst";
	QuickSortFromFile _1m(source);
	timer.Start(); 
	_1m.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "1m = " << timeresult << endl;	
	timer.Reset();		
	// 2M number
	source = "../../2m.lst";
	QuickSortFromFile _2m(source);
	timer.Start(); 
	_2m.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "2m = " << timeresult << endl;	
	timer.Reset();		
	// 4M number
	source = "../../4m.lst";
	QuickSortFromFile _4m(source);
	timer.Start(); 
	_4m.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "4m = " << timeresult << endl;	
	timer.Reset();		
	// 8M number
	source = "../../8m.lst";
	QuickSortFromFile _8m(source);
	timer.Start(); 
	_8m.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "8m = " << timeresult << endl;	
	timer.Reset();		
	// 10M number
	source = "../../10m.lst";
	QuickSortFromFile _10m(source);
	timer.Start(); 
	_10m.quickSortStart();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10m = " << timeresult << endl;	
	timer.Reset();	
	of.close();	
	return 0;	
}





















