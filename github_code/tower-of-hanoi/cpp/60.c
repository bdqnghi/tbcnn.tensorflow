#include <iostream>
using namespace std;

void towerofHanoi(int Size, int source, int dest, int temp)
{

  if(Size == 1)
	{
		cout << "Move disk " << Size << " from rod " << source << " to rod " << dest << endl;
	}
	else
	{
		towerofHanoi(Size - 1, source, temp, dest);
		cout << "Move disk "  << Size << " from rod " << source << " to rod " << dest << endl;
		towerofHanoi(Size - 1, temp, dest, source);
	}
}

int main()
{	
	int disk;
	cout << "Enter the number of Disks " << endl;
	cin >> disk;
	towerofHanoi(disk, 1, 3, 2);
	return 0;
}