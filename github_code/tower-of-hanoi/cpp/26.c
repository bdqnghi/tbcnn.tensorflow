#ifndef _TOWERS_OF_HANOI_H_
#define _TOWERS_OF_HANOI_H_

#include "Stack.h"
class TowersOfHanoi {
private:
	// Copy Constructor
	TowersOfHanoi(const TowersOfHanoi &other) { }

	// Assignment operator
	TowersOfHanoi operator=(const TowersOfHanoi &other) { }

	// Stacks for storing discs
	Stack<int> firstTower, secondTower, thirdTower;
	// Internal variables for state conditions and performance
	int numDiscs, lastMoved, stepsTaken;

	enum REFERENCE_IDS {FIRST_TOWER=1,SECOND_TOWER,THIRD_TOWER};
public:
	// Constructor (Default)
	TowersOfHanoi() :numDiscs(0), lastMoved(0), stepsTaken(0) { }
	// Constructor - Initializes the puzzle with input number of discs to move
	TowersOfHanoi(int discCount) : numDiscs(discCount), lastMoved(0), stepsTaken(0) {
		for (int i = discCount; i >= 1; --i) {
			firstTower.InsertFront(i);
		}
		firstTower.SetReferenceID(FIRST_TOWER);
		secondTower.SetReferenceID(SECOND_TOWER);
		thirdTower.SetReferenceID(THIRD_TOWER);
	}
	
	// Destructor
	virtual ~TowersOfHanoi() {
		if (!firstTower.isEmpty()) {
			firstTower.RemoveAll();
		}
		if (!secondTower.isEmpty()) {
			secondTower.RemoveAll();
		}
		if (!thirdTower.isEmpty()) {
			thirdTower.RemoveAll();
		}
		numDiscs = 0;
		lastMoved = 0;
		stepsTaken = 0;
	}

	// CheckAndMove - Verifies that a disc can be moved and moves to the DEST or INTER stack appropriately
	void CheckAndMove(Stack<int> &from, Stack<int> &inter, Stack<int> &dest) {
		if (!from.isEmpty() && lastMoved != from.PeekHead()) {
			if (from.GetNumElems() % 2 == 0) {
				// Move to INTER Tower
				if (inter.isEmpty() || (!inter.isEmpty() && from.PeekHead() < inter.PeekHead())) {
					lastMoved = from.Pop();
					printf("Moving Disc %d from %d to %d\n", lastMoved, from.GetReferenceID(), inter.GetReferenceID());
					stepsTaken++;
					inter.Push(lastMoved);
				}
			}
			else {
				// Move to DEST Tower
				if (dest.isEmpty() || (!dest.isEmpty() && from.PeekHead() < dest.PeekHead())) {
					lastMoved = from.Pop();
					printf("Moving Disc %d from %d to %d\n", lastMoved, from.GetReferenceID(), dest.GetReferenceID());
					stepsTaken++;
					dest.Push(lastMoved);
				}
			}
		} // FROM Tower NOT empty
	}

	// Solve - Main loop for manipulating the Stacks from FirstTower to ThirdTower in proper order
	void Solve() {
		while (thirdTower.GetNumElems() != numDiscs) {
			CheckAndMove(firstTower, secondTower, thirdTower);
			CheckAndMove(secondTower, firstTower, thirdTower);
			CheckAndMove(thirdTower, firstTower, secondTower);
		} // END While Loop
		cout << "Steps: " << stepsTaken << endl;
	}

	// Reset - Resets the Hanoi puzzle back to origin for immediate re-solving
	void Reset() {
		if (!firstTower.isEmpty()) {
			firstTower.RemoveAll();
		}
		if (!secondTower.isEmpty()) {
			secondTower.RemoveAll();
		}
		if (!thirdTower.isEmpty()) {
			thirdTower.RemoveAll();
		}
		for (int i = numDiscs; i > 0; --i) {
			firstTower.InsertFront(i);
		}
		lastMoved = numDiscs = stepsTaken = 0;
	}
};
#endif //_TOWERS_OF_HANOI_H_