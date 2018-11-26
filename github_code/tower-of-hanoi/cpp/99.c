/*
 * towerOfHanoi.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: franksjsu
 */
#include <iostream>
using namespace std;

void TowerOfHanoi ( int NumberOfDisc,  char From='A', char To='C',  char Temp='B') {
	//cout << "ToH from " << From << " to " << To << " using " << Temp << endl;
	if (NumberOfDisc == 0) return;
	TowerOfHanoi( NumberOfDisc-1, From, Temp, To);
	cout << "move " << NumberOfDisc << "th from " << From << " to " << To << endl;
	TowerOfHanoi( NumberOfDisc-1, Temp, To, From);
}

void TowerOfHanoiTest() {
		TowerOfHanoi(3);
		//TowerOfHanoi(10);
	//	TowerOfHanoi(50);
		//TowerOfHanoi(4, 'A','C','B');
}
void hello(int a=10,int b=2)
{
	cout<<a<<" "<<b;
}
int main()
{
	char ac[2]={'1'};
	char b[5];
	cout<<ac[0]<<" "<<b;
	
	//hello(5);
	//cout<<sizeof('\n');
	//TowerOfHanoiTest();
	return 0;
}

/*
if(!in_stream.eof());// To determine we are not at the end of file
fin.putback();

If a function should not change a value of parameter then use "const" so it will be read only parameter 
*/

