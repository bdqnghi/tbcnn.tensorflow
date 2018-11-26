//============================================================================
// Name        : TowerDemo.cpp
// Author      : Glen Bray
//============================================================================

#include <iostream>
#include "TowerHanoi.h"

using namespace std;

int main() {

	int towerHeight = 0;
	std::cout << "Enter height of tower (1 - 5): ";

	while(!(cin >> towerHeight) || (towerHeight < 1 || towerHeight > 5)) // Get tower height from user
	{
		std::cout << "Enter a valid integer number between (1 - 5): ";
		cin.clear();
		cin.ignore (1000, '\n');
	}

	TowerHanoi game(towerHeight); // Create tower with size player inputed
	game.generateTower(); // Generate initial tower to console

	int sourceRod = 0;
	int targetRod = 0;

	while(true)
	{
		std::cout << "Select Disk to Move (1 - 3): ";
		while(!(cin >> sourceRod) || !game.validateSelectedTower(sourceRod)) // Get source rod input from user
		{
			std::cout << "Select correct disk (1 - 3): ";
			cin.clear();
			cin.ignore (1000, '\n');
		}

		std::cout << "Select Disk Target (1 - 3): ";
		while(!(cin >> targetRod) || !game.validateSelectedTower(targetRod)) // Get target rod input from user
		{
			std::cout << "Select correct disk (1 - 3): ";
			cin.clear();
			cin.ignore (1000, '\n');
		}

		if(sourceRod == 0 && targetRod == 0) // Check if user selected 0 0 to exit game
		{
			std::cout << "Game exited!";
			break;
		}

		bool validMove = game.validateAndMove(sourceRod - 1, targetRod - 1); // Check if valid move if so then move
		if(!validMove)
			std::cout << "Invalid Move try again!\n";

		game.generateTower(); // Print new tower to console

		if(game.checkWin()) // Check if player has won
		{
			std::cout << "Congratulations you have won the game";
			return false;
		}
	}

	return 0;
}
