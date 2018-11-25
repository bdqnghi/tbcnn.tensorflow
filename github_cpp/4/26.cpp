#ifndef _TOWERS_OF_HANOI_H_
#define _TOWERS_OF_HANOI_H_

#include "Stack.h"
class TowersOfHanoi {
private:
	
	TowersOfHanoi(const TowersOfHanoi &other) { }

	
	TowersOfHanoi operator=(const TowersOfHanoi &other) { }

	
	Stack<int> firstTower, secondTower, thirdTower;
	
	int numDiscs, lastMoved, stepsTaken;

	enum REFERENCE_IDS {FIRST_TOWER=1,SECOND_TOWER,THIRD_TOWER};
public:
	
	TowersOfHanoi() :numDiscs(0), lastMoved(0), stepsTaken(0) { }
	
	TowersOfHanoi(int discCount) : numDiscs(discCount), lastMoved(0), stepsTaken(0) {
		for (int i = discCount; i >= 1; --i) {
			firstTower.InsertFront(i);
		}
		firstTower.SetReferenceID(FIRST_TOWER);
		secondTower.SetReferenceID(SECOND_TOWER);
		thirdTower.SetReferenceID(THIRD_TOWER);
	}
	
	
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

	
	void CheckAndMove(Stack<int> &from, Stack<int> &inter, Stack<int> &dest) {
		if (!from.isEmpty() && lastMoved != from.PeekHead()) {
			if (from.GetNumElems() % 2 == 0) {
				
				if (inter.isEmpty() || (!inter.isEmpty() && from.PeekHead() < inter.PeekHead())) {
					lastMoved = from.Pop();
					printf("Moving Disc %d from %d to %d\n", lastMoved, from.GetReferenceID(), inter.GetReferenceID());
					stepsTaken++;
					inter.Push(lastMoved);
				}
			}
			else {
				
				if (dest.isEmpty() || (!dest.isEmpty() && from.PeekHead() < dest.PeekHead())) {
					lastMoved = from.Pop();
					printf("Moving Disc %d from %d to %d\n", lastMoved, from.GetReferenceID(), dest.GetReferenceID());
					stepsTaken++;
					dest.Push(lastMoved);
				}
			}
		} 
	}

	
	void Solve() {
		while (thirdTower.GetNumElems() != numDiscs) {
			CheckAndMove(firstTower, secondTower, thirdTower);
			CheckAndMove(secondTower, firstTower, thirdTower);
			CheckAndMove(thirdTower, firstTower, secondTower);
		} 
		cout << "Steps: " << stepsTaken << endl;
	}

	
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
#endif 