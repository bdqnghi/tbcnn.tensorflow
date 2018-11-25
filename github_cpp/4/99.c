
#include <iostream>
using namespace std;

void TowerOfHanoi ( int NumberOfDisc,  char From='A', char To='C',  char Temp='B') {
	
	if (NumberOfDisc == 0) return;
	TowerOfHanoi( NumberOfDisc-1, From, Temp, To);
	cout << "move " << NumberOfDisc << "th from " << From << " to " << To << endl;
	TowerOfHanoi( NumberOfDisc-1, Temp, To, From);
}

void TowerOfHanoiTest() {
		TowerOfHanoi(3);
		
	
		
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
	
	
	
	
	return 0;
}



