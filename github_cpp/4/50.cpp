




#include <iostream>
#include "TowerHanoi.h"

using namespace std;

int main() {

	int towerHeight = 0;
	std::cout << "Enter height of tower (1 - 5): ";

	while(!(cin >> towerHeight) || (towerHeight < 1 || towerHeight > 5)) 
	{
		std::cout << "Enter a valid integer number between (1 - 5): ";
		cin.clear();
		cin.ignore (1000, '\n');
	}

	TowerHanoi game(towerHeight); 
	game.generateTower(); 

	int sourceRod = 0;
	int targetRod = 0;

	while(true)
	{
		std::cout << "Select Disk to Move (1 - 3): ";
		while(!(cin >> sourceRod) || !game.validateSelectedTower(sourceRod)) 
		{
			std::cout << "Select correct disk (1 - 3): ";
			cin.clear();
			cin.ignore (1000, '\n');
		}

		std::cout << "Select Disk Target (1 - 3): ";
		while(!(cin >> targetRod) || !game.validateSelectedTower(targetRod)) 
		{
			std::cout << "Select correct disk (1 - 3): ";
			cin.clear();
			cin.ignore (1000, '\n');
		}

		if(sourceRod == 0 && targetRod == 0) 
		{
			std::cout << "Game exited!";
			break;
		}

		bool validMove = game.validateAndMove(sourceRod - 1, targetRod - 1); 
		if(!validMove)
			std::cout << "Invalid Move try again!\n";

		game.generateTower(); 

		if(game.checkWin()) 
		{
			std::cout << "Congratulations you have won the game";
			return false;
		}
	}

	return 0;
}
