#include <iostream>
#include <conio.h>
#include "ctimer.hpp"
#include <vector>
#include <fstream>

using namespace std;

class SelectionSortFromFile
{
	public:		
			const char *filepath; 
			ifstream fi; 
			int temp; 
			vector<int> numbers; 
			vector<int>::iterator p; 
			SelectionSortFromFile(const char *); 
			~SelectionSortFromFile();
			bool readFromFile(); 
			void printNumbers(); 
			void selectionSort(); 
			void printFirstTenNumber(); 
			void printLastTenNumber(); 
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

	int n = numbers.size();
	int iMin;
	for (int j = 0; j < n-1; j++) {
		
	 
		
		iMin = j;
		
		for (int i = j+1; i < n; i++) {
			  
			if (numbers[i] < numbers[iMin]) {
				
				iMin = i;
			}
		}
	 
		
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
	
	source = "../../1k.lst";
	SelectionSortFromFile _1k(source);
	timer.Start(); 
	_1k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "1k = " << timeresult << endl;
	timer.Reset();
	
	source = "../../10k.lst";
	SelectionSortFromFile _10k(source);
	timer.Start(); 
	_10k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10k = " << timeresult << endl;	
	timer.Reset();
	
	source = "../../100k.lst";
	SelectionSortFromFile _100k(source);
	timer.Start(); 
	_100k.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "100k = " << timeresult << endl;	
	timer.Reset();	
	
	source = "../../1m.lst";
	SelectionSortFromFile _1m(source);
	timer.Start(); 
	_1m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "1m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../2m.lst";
	SelectionSortFromFile _2m(source);
	timer.Start(); 
	_2m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "2m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../4m.lst";
	SelectionSortFromFile _4m(source);
	timer.Start(); 
	_4m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "4m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../8m.lst";
	SelectionSortFromFile _8m(source);
	timer.Start(); 
	_8m.selectionSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "8m = " << timeresult << endl;	
	timer.Reset();		
	
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





















