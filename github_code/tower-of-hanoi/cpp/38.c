//******************************************************************************************************************************
//Filename		:		pp18.cpp
//Author			:		Andrew Lamb
//Version			:		
//Description	:		Implement a recursive function to solve the Towers of Hanoi problem.
//					:		
//					:		
//******************************************************************************************************************************

#include <iostream>

using namespace std;

void tower_of_hanoi (int num_pieces, int left, int middle, int right);
void movedisk (int from, int to);
void writedisk(int disk) ;

int main()
{	
	int pieces;
	int pos1 = 0, pos2 = 1, pos3 = 2;
	
	cout << "=============================================" << endl; 
	cout << "Program Solves the Towers of Hanoi Problem" << endl; 
	cout << "Enter number of pieces:" << endl;
	cin >> pieces;
	
	tower_of_hanoi(pieces, pos1, pos2, pos3);
	
	return 0;	//all ok
}

//******************************************************************************************************************************
//RECURSIVE FUNCTION TO SOLVE THE TOWER-OF-HANOI PROBLEM
void tower_of_hanoi (int num_pieces, int left, int middle, int right)
{
	if (num_pieces >=1)
	{
		tower_of_hanoi(num_pieces - 1, left, right, middle);
		movedisk(left, right);
		tower_of_hanoi(num_pieces -1, middle, left, right);
	}
}
//******************************************************************************************************************************

//******************************************************************************************************************************
void movedisk (int from, int to)
{
	cout << "Move disk from ";
	writedisk(from);
	cout << " to ";
	writedisk(to);
	cout << "." << endl;
}
//******************************************************************************************************************************

//******************************************************************************************************************************
void writedisk(int disk) 
{
	switch (disk)
	{
		case 0:
			cout << "left";
			break;
		case 1:
			cout << "middle";
			break;
		case 2:
			cout << "right";
			break;
	}
}
//******************************************************************************************************************************