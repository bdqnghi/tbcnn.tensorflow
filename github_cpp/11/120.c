#include <iostream>
#include "ctimer.hpp"
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class HeapSortFromFile
{
	public:		
			const char *filepath; 
			ifstream fi; 
			int temp; 
			vector<int> numbers; 
			vector<int>::iterator p; 
			HeapSortFromFile(const char *); 
			~HeapSortFromFile();
			bool readFromFile(); 
			void printNumbers(); 
			void heapSort(); 
			void printFirstTenNumber(); 
			void printLastTenNumber(); 
};
HeapSortFromFile::HeapSortFromFile(const char *file)
{
	filepath=file;
	this->readFromFile();
}
bool HeapSortFromFile::readFromFile(){		
	fi.open(filepath);
	if(!fi.is_open()) return 0;
	while(fi >> temp)
	{
		numbers.push_back(temp);
	}
	return 1;
}
void HeapSortFromFile::printNumbers()
{	
	p=numbers.begin();
	while(p!=numbers.end())
	{
		cout<<*p<<" ";
		p++;
	}
	cout << endl;
}

void HeapSortFromFile::heapSort()
{
	make_heap (numbers.begin(),numbers.end());
	push_heap (numbers.begin(),numbers.end());
	sort_heap (numbers.begin(),numbers.end());
}
void HeapSortFromFile::printFirstTenNumber()
{
	cout << "Frist 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[i] << " ";
	cout << endl;
}
void HeapSortFromFile::printLastTenNumber()
{
	cout << "Last 10 Number : ";
	for(int i=0; i < 10;i++)
		cout << numbers[numbers.size()-1-i] << " ";
	cout << endl;
}
HeapSortFromFile::~HeapSortFromFile()
{
	numbers.erase(numbers.begin(), numbers.end());
}
int main(int argc, char **argv)
{
	CTimer timer; double timeresult;const char * source;
	ofstream of("results.txt",ios::app);
	timer.Reset();
	
	source = "../../1k.lst";
	HeapSortFromFile _1k(source);
	timer.Start(); 
	_1k.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();	
	of << "1k = " << timeresult << endl;
	timer.Reset();
	
	source = "../../10k.lst";
	HeapSortFromFile _10k(source);
	timer.Start(); 
	_10k.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10k = " << timeresult << endl;	
	timer.Reset();
	
	source = "../../100k.lst";
	HeapSortFromFile _100k(source);
	timer.Start(); 
	_100k.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "100k = " << timeresult << endl;	
	timer.Reset();	
	
	source = "../../1m.lst";
	HeapSortFromFile _1m(source);
	timer.Start(); 
	_1m.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "1m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../2m.lst";
	HeapSortFromFile _2m(source);
	timer.Start(); 
	_2m.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "2m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../4m.lst";
	HeapSortFromFile _4m(source);
	timer.Start(); 
	_4m.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "4m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../8m.lst";
	HeapSortFromFile _8m(source);
	timer.Start(); 
	_8m.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "8m = " << timeresult << endl;	
	timer.Reset();		
	
	source = "../../10m.lst";
	HeapSortFromFile _10m(source);
	timer.Start(); 
	_10m.heapSort();
	timer.Stop(); 
	timeresult = timer.ElapsedTime();
	of << "10m = " << timeresult << endl;	
	timer.Reset();		
	return 0;	
}





















