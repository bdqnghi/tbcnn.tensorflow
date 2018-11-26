// Filename: TowerDemo.cpp
// Date Created: 04/10/2012
// Author: Lance Baker
// Course: SENG6120
// Student Number: c3128034

#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "LinkedList.h"
#include "LStack.h"
#include "Disc.h"
#include "TowerHanoi.h"

using namespace std;
using lance_project::TowerHanoi;
using lance_project::Node;
using lance_project::LinkedList;
using lance_project::Disc;
using lance_project::LStack;

int main() {
	cout << " Hanoi Game" << endl;
	
	int rods = 0; // To hold the rods count
	int discs = 0; // To hold the amount of discs
	do {
		cout << "Enter number of towers and discs: " << endl;
		cin >> rods;
		cin >> discs;
		if (rods < 3) {
			cout << "Error: towers must be more than or equal to 3." << endl;
		}
		if (!(discs >= 3 && discs <= 5)) {
			cout << "Error: discs must be between 3 and 5." << endl;
		}
	} while (!((rods >= 3) && ((discs >= 3) && (discs <= 5))));
	
	TowerHanoi* game = new TowerHanoi(rods, discs);
	game->createTower(0);
	
	int from;
	int to;
	int moves = 0;
	do {
		cout << game->showTowers() << endl;
		cout << "Enter move (from, to): " << endl;
		cin >> from;
		cin >> to;
		if (((from > 0) && (to > 0)) && ((from <= rods) && (to <= rods))) {
			if (!game->move((from-1), (to-1))) {
				cout << "Error, invalid move" << endl;
			} else {
				moves++;
			}
		} else {
			if (from == 0 && to == 0) {
				break;
			} else {
				cout << "Error, outside of range." << endl;
			}
		}
	} while ((((from > 0) && (to > 0)) && ((from <= rods) && (to <= rods))) && (!game->won()));
	
	if (game->won()) {
		cout << game->showTowers() << endl;
		cout << "Winner in " << moves << " moves" << endl;
	}
	return 0;
}
