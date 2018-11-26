#include <iostream>
using namespace std;


//Array implementation of stack
class Stack
{

	int SIZE;

public:
	int *intarr;
	int TOP = 0;

	Stack();
	Stack(int size);

	void push(int elem);
	int pop();

	int getelem();

};

Stack::Stack()
{
	SIZE = 5;
	intarr = new int[SIZE];
	cout << "\n\n Stack initialized with space of 5 elements!";
}

Stack::Stack(int size)
{
	intarr = new int[SIZE];
	cout << "\n\n Stack initialized with space of " << SIZE << " elements!";
}

void Stack::push(int elem)
{
	//check for overflow
	if (TOP == SIZE)
	{
		cout << "\n\n Stack Overflow, can't push element now!";
		return;
	}
	intarr[TOP] = elem;
	TOP++;
	cout << "\n\n " << elem << " has pushed to stack!";
}

int Stack::pop()
{
	//check for underflow
	if (TOP == 0)
	{
		cout << "\n\n Stack is Empty, can't pop element now!";
		return -1;
	}
	TOP--;
	return intarr[TOP];

}

int Stack::getelem()
{
	//check for underflow
	if (TOP == 0)
	{
		return -1;
	}
	return intarr[TOP-1];
}

/*
 - Tower of Hanoi simulation contains three stacks(pegs) A,B and C
 - At start, Peg A contains N disks
 - The target is to transfer all N disks from Peg A to Peg C with minimum possible moves
*/

class HanoiTowerSimulation
{
	Stack A, B, C;
	int NumOfDisks,Moves;

public:

	HanoiTowerSimulation(); //By default, we consider 3 disks
	HanoiTowerSimulation(int disks); //Dynamic number of disks

	void setupPegs();
	void viewPegs();
	void moveDisks();
	void T(int numOfDisks, Stack Start, Stack Aux, Stack End);
};

HanoiTowerSimulation::HanoiTowerSimulation()
{
	NumOfDisks = 3;
}

HanoiTowerSimulation::HanoiTowerSimulation(int disks)
{
	NumOfDisks = disks;
}

void HanoiTowerSimulation::setupPegs()
{
	for (int i = 0; i < NumOfDisks; i++)
	{
		A.push(i + 1);
	}
}

void HanoiTowerSimulation::viewPegs()
{
	//View of Tower of Hanoi

	system("cls");

	cout << "\n\n\t------------------------------------------------------------------------------";
	cout << "\n\n\n";

	cout << "\t| \t|\t| \t|\t| \t|";
	cout << "\n\t| \t|\t| \t|\t| \t|";
	cout << "\n\t| \t|\t| \t|\t| \t|";
	int m,n,o;
	for (int i = 1; i <= NumOfDisks; i++)
	{
		if (HanoiTowerSimulation::A.TOP == 0) { m = 0; }
		else { m = HanoiTowerSimulation::A.intarr[HanoiTowerSimulation::A.TOP - i]; }
		if (HanoiTowerSimulation::B.TOP == 0) { n = 0; }
		else{ n = HanoiTowerSimulation::B.intarr[HanoiTowerSimulation::B.TOP - i]; }
		if (HanoiTowerSimulation::C.TOP == 0) { o = 0; }
		else { o = HanoiTowerSimulation::C.intarr[HanoiTowerSimulation::C.TOP - i]; }

		cout << "\n\t|" << m << "\t|\t|" << n << "\t|\t|" << o << "\t|";
		cout << "\n\t| \t|\t| \t|\t| \t|";
	}
	cout << "\n      -------------   -------------   -------------";
	cout << "\n      -------------   -------------   -------------";
}

void HanoiTowerSimulation::T(int numOfDisks, Stack Start, Stack Aux, Stack End)
{
	if (numOfDisks == 1)
	{
		cout << endl;
		cout << "\n Press enter for next move... ";
		system("pause");
		End.push(Start.pop());
		system("cls");
		viewPegs();
		return;
	}

	T(numOfDisks - 1, Start, End, Aux);
	T(1, Start, Aux, End);
	T(numOfDisks - 1, Aux, Start, End);
}

void HanoiTowerSimulation::moveDisks()
{
	//algorithm of Tower of Hanoi minimum moves
	T(NumOfDisks, A, B, C);	
}

int main()
{
	HanoiTowerSimulation sim;	//default 3 disks to move from A to C
	sim.setupPegs();
	system("cls");
	sim.viewPegs();
	sim.moveDisks();
}