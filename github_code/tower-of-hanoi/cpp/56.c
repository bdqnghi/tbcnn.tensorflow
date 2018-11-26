#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <Windows.h>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

class HanoiTower
{
private:
	vector <int> initialState;
	vector < vector <int> > visitedStates;
	vector <vector<int>> notToVisitStates;
	vector <vector<int>> hillUsed;
	int towersCount;
	int disksCount;
	bool solutionFound = false;
	int maximumNumberOfMoves;
	int minimumNumberOfMoves;
	int algorithmSteps;
	int lastDiskMoved;
	int lastKeyStateIndex;
	int negativeMoves;
	int maxNegativeMoves;
	long duration;
	high_resolution_clock::time_point t0;
	high_resolution_clock::time_point tf;

	int minim(int x, int y)
	{
		return x < y ? x : y;
	}
	void setMaximumNumberOfMoves()
	{
		maximumNumberOfMoves = 1024;
	}
	bool isFinalState(vector<int> state)
	{
		vector<int>::iterator it;
		for (it = state.begin() + 1; it != state.end(); it++)
		{
			if (*it != towersCount)
			{
				return false;
			}
		}
		return true;
	}
	bool canTransit(vector<int> currentState, int disk, int tower)
	{

		int currentTower = currentState[disk];
		//the disk is already on that tower
		if (currentTower == tower)
		{
			return false;
		}
		vector<int>::iterator towerIterator;
		for (int i = 1; i < disk; i++)
		{
			if (currentState[i] == tower || currentState[i] == currentTower)
			{
				return false;
			}
		}
		return true;
	}
	vector<int> getNextState(vector<int> currentState, int disk, int tower)
	{
		currentState[disk] = tower;
		return currentState;
	}
	bool isANewState(vector<int> currentState)
	{
		vector< vector<int> >::iterator it;
		it = find(visitedStates.begin(), visitedStates.end(), currentState);
		return it == visitedStates.end();
	}
	bool diskIsAlreadyPlaced(vector<int> state, int currentDisk)
	{
		int disk = disksCount;
		while (state[disk] == towersCount)
		{
			disk--;
		}
		return disk < currentDisk;
	}
	vector<int> computeInitialState()
	{
		vector<int> initialState(disksCount + 1, 1);
		return initialState;
	}
	bool canMoveDisk(vector<int> state, int disk)
	{
		for (int i = 1; i < disk; i++)
		{
			if (state[i] == state[disk])
			{
				return false;
			}
		}
		return true;
	}
	/*
	If it can move the correct disk to the last tower, then it chooses that disk, otherwise:
	Get a random disk from the set of disks that haven't been placed yet on the last tower (in the correct order)
	For efficency, it ignores the disks that are already placed on the last tower, in the correct order.
	*/
	int getRandomDisk(vector<int> currentState)
	{
		vector<int> availableDisks;
		for (int i = 1; i <= disksCount; i++)
		{
			if (!diskIsAlreadyPlaced(currentState, i) && canMoveDisk(currentState, i))
			{
				availableDisks.push_back(i);
			}
		}
		int randomDiskIndex = rand() % availableDisks.size();
		return availableDisks[randomDiskIndex];
	}
	int getRandomTower()
	{
		return rand() % towersCount + 1;
	}
	int getNumberOfPlacedDisks(vector<int> state)
	{
		int disk = disksCount;
		while (state[disk] == towersCount)
		{
			disk--;
		}
		return disksCount - disk;
	}
	/*
	Returns true if this state has more disks placed on the last tower, in the correct order, than the last key state.
	*/
	bool isAKeyState(vector<int> currentState)
	{
		if (lastKeyStateIndex == 0 && currentState[disksCount] == towersCount) return true; //at least the biggest disk is placed
		int currentStatePlacedDisks = getNumberOfPlacedDisks(currentState);
		int lastKeyStatePlacedDisks = getNumberOfPlacedDisks(visitedStates[lastKeyStateIndex]);
		return currentStatePlacedDisks > lastKeyStatePlacedDisks;
	}
public:
	HanoiTower(int towersCount, int disksCount)
	{
		this->towersCount = towersCount;
		this->disksCount = disksCount;
		initializeProblem();
	}
	vector<int> getInitialState()
	{
		return initialState;
	}
	int getSolution()
	{
		tf = high_resolution_clock::now();
		if (solutionFound) return minimumNumberOfMoves;
		return -1;
	}
	void initializeProblem()
	{
		solutionFound = false;
		srand(time(NULL));
		notToVisitStates.clear();
		visitedStates.clear();
		initialState = computeInitialState();
		visitedStates.push_back(initialState);
		setMaximumNumberOfMoves();
		minimumNumberOfMoves = maximumNumberOfMoves;
		algorithmSteps = 0;
		lastKeyStateIndex = 0;
		lastDiskMoved = 0;
		negativeMoves = 0;
		maxNegativeMoves = disksCount - towersCount + 1;
		t0 = high_resolution_clock::now();
	}
	int getAlgorithmSteps()
	{
		return algorithmSteps;
	}
	int canMoveToLastDisk(vector<int> state)
	{
		int disk = disksCount;
		while (state[disk] == towersCount) disk--;
		for (int i = 1; i < disk; i++)
		{
			if (state[i] == towersCount) return -1;
		}
		if (canMoveDisk(state, disk)) return disk;
		return -1;
	}
	void efficientRandomSolve(vector<int> currentState)
	{
		if (!isFinalState(currentState) && algorithmSteps < maximumNumberOfMoves)
		{
			int disk = getRandomDisk(currentState);
			int tower = getRandomTower();
			if (canMoveToLastDisk(currentState) > 0)
			{
				disk = canMoveToLastDisk(currentState);
				tower = towersCount;
			}
			vector<int> nextState = getNextState(currentState, disk, tower);
			if (canTransit(currentState, disk, tower) && isANewState(nextState))
			{
				visitedStates.push_back(nextState);
				if (isAKeyState(nextState))
				{
					lastKeyStateIndex = visitedStates.size() - 1;
				}
				algorithmSteps++;
				efficientRandomSolve(nextState);
			}
			else
			{

				if (lastKeyStateIndex > 0)
				{
					visitedStates.erase(visitedStates.begin() + lastKeyStateIndex + 1, visitedStates.end());
				}
				algorithmSteps++;
				efficientRandomSolve(visitedStates[visitedStates.size() - 1]);
			}
		}
		else
		{
			if (isFinalState(currentState))
			{
				minimumNumberOfMoves = visitedStates.size();
				solutionFound = true;
			}
		}
	}

	/*
	Find the first solution using an backtracking algorithm
	For "efficiency", if the disk is already placed on the last tower in the correct order,
	then the disk won't be moved anymore.
	Also, for true efficiency, at a step, if it's possible, it moves the correct disk to the last tower.
	*/
	void bktSolve(vector <int> currentState)
	{
		if (!solutionFound)
		{
			for (int disk = 1; disk <= disksCount && !solutionFound && algorithmSteps < maximumNumberOfMoves; disk++)
			{
				if (!diskIsAlreadyPlaced(currentState, disk) && disk != lastDiskMoved && canMoveDisk(currentState, disk)) {
					for (int tower = 1; tower <= towersCount && !solutionFound && algorithmSteps < maximumNumberOfMoves; tower++)
					{
						if (canTransit(currentState, disk, tower))
						{
							if (canMoveToLastDisk(currentState) > 0)
							{
								disk = canMoveToLastDisk(currentState);
								tower = towersCount;
							}
							vector <int> nextState = getNextState(currentState, disk, tower);
							if (isANewState(nextState))
							{
								if (algorithmSteps < maximumNumberOfMoves)
								{
									algorithmSteps++;
									visitedStates.push_back(nextState);
									lastDiskMoved = disk;
									bktSolve(nextState);
									if (algorithmSteps < maximumNumberOfMoves)
										visitedStates.pop_back();
								}
							}
						}
					}
				}
				else if (isFinalState(currentState) && visitedStates.size() < minimumNumberOfMoves)
				{
					minimumNumberOfMoves = visitedStates.size() - 1;
					solutionFound = true;
				}
			}
		}

	}

	bool canMoveDiskToTower(vector<int> state, int disk, int tower)
	{
		for (int i = 1; i < disk; i++)
		{
			if (state[i] == tower)
			{
				return false;
			}
		}
		return true;
	}

	int getRandomAvailableTower(vector<int> state, int disk)
	{
		vector<int> avaiableTowers;
		for (int t = 1; t <= towersCount; t++)
		{
			if (canMoveDiskToTower(state, disk, t))
			{
				avaiableTowers.push_back(t);
			}
		}
		int randomTowerIndex = rand() % avaiableTowers.size();
		return avaiableTowers[randomTowerIndex];
	}

	pair <int, int> getRandomMove(vector<int> currentState)
	{
		vector<pair<int, int>> availableDisks;
		for (int i = 1; i <= disksCount; i++)
		{
			if (!diskIsAlreadyPlaced(currentState, i) && canMoveDisk(currentState, i))
			{
				availableDisks.push_back(make_pair(i, getRandomAvailableTower(currentState, i)));
			}
		}
		int randomDiskIndex = rand() % availableDisks.size();
		return availableDisks[randomDiskIndex];
	}

	int getScore(vector<int> state)
	{
		int score = 0;
		for (int i = 1; i <= disksCount; i++)
		{
			if (diskIsAlreadyPlaced(state, i))
			{
				score += (i * 3);
			}
			else
			{
				if (canMoveDiskToTower(state, i, towersCount))
				{
					score += (i * 2);
				}
				else
				{
					score += state[i];
				}
			}
		}
		return score;
	}

	bool stateIsBetter(vector<int> currentState, vector<int> nextState)
	{
		int currentStateScore = getScore(currentState);
		int nextStateScore = getScore(nextState);
		if (currentStateScore <= nextStateScore)
		{
			negativeMoves = 0;
			return true;
		}
		if (negativeMoves < maxNegativeMoves)
		{
			negativeMoves++;
			return true;
		}
		return false;
	}

	void hillClimbingSolve(vector<int> currentState)
	{
		if (!isFinalState(currentState) && algorithmSteps < maximumNumberOfMoves)
		{
			pair<int, int> randomMove = getRandomMove(currentState);
			int disk = randomMove.first;
			int tower = randomMove.second;
			if (canMoveToLastDisk(currentState) > 0)
			{
				disk = canMoveToLastDisk(currentState);
				tower = towersCount;
			}
			vector<int> nextState = getNextState(currentState, disk, tower);
			if (canTransit(currentState, disk, tower) && isANewState(nextState) && stateIsBetter(currentState, nextState))
			{
				visitedStates.push_back(nextState);
				if (isAKeyState(nextState))
				{
					lastKeyStateIndex = visitedStates.size() - 1;
				}
				algorithmSteps++;
				hillClimbingSolve(nextState);
			}
			else
			{

				if (lastKeyStateIndex > 0)
				{
					visitedStates.erase(visitedStates.begin() + lastKeyStateIndex + 1, visitedStates.end());
				}
				algorithmSteps++;
				hillClimbingSolve(visitedStates[visitedStates.size() - 1]);
			}
		}
		else
		{
			if (isFinalState(currentState))
			{
				minimumNumberOfMoves = visitedStates.size();
				solutionFound = true;
			}
		}
	}
	int aStarSolve(vector<int> currentState){
		visitedStates.push_back(currentState);
		queue <pair<vector<int>, int>> Q;
		algorithmSteps++;
		Q.push(make_pair(currentState, 0));
		while (!Q.empty()){
			pair<vector<int>, int> current_pair = Q.front();
			Q.pop();
			for (int disk = 1; disk <= disksCount; ++disk){
				for (int tower = 1; tower <= towersCount; ++tower){
					if (!diskIsAlreadyPlaced(current_pair.first, disk) && canTransit(current_pair.first, disk, tower)){
						vector <int> newState = getNextState(current_pair.first, disk, tower);
						if (isFinalState(newState)){
							minimumNumberOfMoves = current_pair.second + 1;
							solutionFound = true;
							return current_pair.second + 1;
						}
						if (isANewState(newState)){
							algorithmSteps++;
							visitedStates.push_back(newState);
							Q.push(make_pair(newState, current_pair.second + 1));
						}

					}
				}
			}
		}
	}

	void randomSolve(vector<int> currentState)
	{
		if (!isFinalState(currentState) && algorithmSteps < maximumNumberOfMoves)
		{
			int disk = rand() % disksCount + 1;
			int tower = rand() % towersCount + 1;
			if (canMoveToLastDisk(currentState) > 0)
			{
				disk = canMoveToLastDisk(currentState);
				tower = towersCount;
			}
			vector<int> nextState = getNextState(currentState, disk, tower);
			if (canTransit(currentState, disk, tower))
			{
				visitedStates.push_back(nextState);
				algorithmSteps++;
				randomSolve(nextState);
			}
			else
			{
				int statesToGoBack = rand() % visitedStates.size();
				visitedStates.erase(visitedStates.begin() + statesToGoBack + 1, visitedStates.end());
				algorithmSteps++;
				randomSolve(visitedStates[visitedStates.size() - 1]);
			}
		}
		else
		{
			if (isFinalState(currentState))
			{
				minimumNumberOfMoves = visitedStates.size();
				solutionFound = true;
			}
		}
	}
	long getDuration()
	{
		return duration_cast<microseconds>(tf - t0).count();
	}
};

void createStatistic()
{
	for (int tower = 3; tower <= 10; tower++)
	{
		//cout << tower;
		string fileName = "Statistic/" + to_string(tower) + "towers.txt";
		cout << fileName;
		ofstream g(fileName);
		g << tower << " TOWERS\n";
		g << "-----------------------------------\n";
		for (int disk = tower - 1; disk <= tower + 2; disk++)
		{
			g << disk << " DISKS\n";
			HanoiTower hanoiTower(tower, disk);
			int averagesolutionSteps;
			int averagealgorithmSteps;
			int averagesolutionNotFound;
			long averageduration;

			//BKT
			g << "~~Backtracking~~\n";
			averagesolutionSteps = 0;
			averagealgorithmSteps = 0;
			averagesolutionNotFound = 0;
			averageduration = 0;
			for (int count = 1; count <= 1; count++)
			{
				hanoiTower.initializeProblem();
				hanoiTower.bktSolve(hanoiTower.getInitialState());
				if (hanoiTower.getSolution() > 0)
				{
					averagesolutionSteps += hanoiTower.getSolution();
					averagealgorithmSteps += hanoiTower.getAlgorithmSteps();
					averageduration += hanoiTower.getDuration();
				}
				else
				{
					averagesolutionNotFound++;
				}
			}
			averagealgorithmSteps /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			averageduration /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			averagesolutionSteps /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			g << "Solution not found: " << averagesolutionNotFound << " times\n";
			g << "Average solution steps: " << averagesolutionSteps << "\n";
			g << "Average algorithm steps: " << averagealgorithmSteps << "\n";
			g << "Average duration: " << averageduration << " microseconds\n\n\n";



			////Random
			g << "~~Random~~\n";
			averagesolutionSteps = 0;
			averagealgorithmSteps = 0;
			averagesolutionNotFound = 0;
			averageduration = 0;
			for (int count = 1; count <= 100; count++)
			{
				hanoiTower.initializeProblem();
				hanoiTower.randomSolve(hanoiTower.getInitialState());
				if (hanoiTower.getSolution() > 0)
				{
					averagesolutionSteps += hanoiTower.getSolution();
					averagealgorithmSteps += hanoiTower.getAlgorithmSteps();
					averageduration += hanoiTower.getDuration();
				}
				else
				{
					averagesolutionNotFound++;
				}
			}
			averagealgorithmSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averageduration /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averagesolutionSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			g << "Solution not found: " << averagesolutionNotFound << " times\n";
			g << "Average solution steps: " << averagesolutionSteps << "\n";
			g << "Average algorithm steps: " << averagealgorithmSteps << "\n";
			g << "Average duration: " << averageduration << " microseconds\n\n\n";

			//Efficient random
			g << "~~Efficient Random~~\n";
			averagesolutionSteps = 0;
			averagealgorithmSteps = 0;
			averagesolutionNotFound = 0;
			averageduration = 0;
			for (int count = 1; count <= 100; count++)
			{
				hanoiTower.initializeProblem();
				hanoiTower.efficientRandomSolve(hanoiTower.getInitialState());
				if (hanoiTower.getSolution() > 0)
				{
					averagesolutionSteps += hanoiTower.getSolution();
					averagealgorithmSteps += hanoiTower.getAlgorithmSteps();
					averageduration += hanoiTower.getDuration();
				}
				else
				{
					averagesolutionNotFound++;
				}
			}
			averagealgorithmSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averageduration /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averagesolutionSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			g << "Solution not found: " << averagesolutionNotFound << " times\n";
			g << "Average solution steps: " << averagesolutionSteps << "\n";
			g << "Average algorithm steps: " << averagealgorithmSteps << "\n";
			g << "Average duration: " << averageduration << " microseconds\n\n\n";

			//Hill Climbing
			g << "~~Hill climbing~~\n";
			averagesolutionSteps = 0;
			averagealgorithmSteps = 0;
			averagesolutionNotFound = 0;
			averageduration = 0;
			for (int count = 1; count <= 100; count++)
			{
				hanoiTower.initializeProblem();
				hanoiTower.hillClimbingSolve(hanoiTower.getInitialState());
				if (hanoiTower.getSolution() > 0)
				{
					averagesolutionSteps += hanoiTower.getSolution();
					averagealgorithmSteps += hanoiTower.getAlgorithmSteps();
					averageduration += hanoiTower.getDuration();
				}
				else
				{
					averagesolutionNotFound++;
				}
			}
			averagealgorithmSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averageduration /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			averagesolutionSteps /= (100 - averagesolutionNotFound > 0 ? 100 - averagesolutionNotFound : 1);
			g << "Solution not found: " << averagesolutionNotFound << " times\n";
			g << "Average solution steps: " << averagesolutionSteps << "\n";
			g << "Average algorithm steps: " << averagealgorithmSteps << "\n";
			g << "Average duration: " << averageduration << " microseconds\n\n\n";

			//A STAR

			g << "~~A star*~~\n";
			averagesolutionSteps = 0;
			averagealgorithmSteps = 0;
			averagesolutionNotFound = 0;
			averageduration = 0;
			for (int count = 1; count <= 1; count++)
			{
				cout << "\n" << disk;
				hanoiTower.initializeProblem();
				hanoiTower.aStarSolve(hanoiTower.getInitialState());
				if (hanoiTower.getSolution() > 0)
				{
					averagesolutionSteps += hanoiTower.getSolution();
					averagealgorithmSteps += hanoiTower.getAlgorithmSteps();
					averageduration += hanoiTower.getDuration();
				}
				else
				{
					averagesolutionNotFound++;
				}
			}
			averagealgorithmSteps /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			averageduration /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			averagesolutionSteps /= (1 - averagesolutionNotFound > 0 ? 1 - averagesolutionNotFound : 1);
			g << "Solution not found: " << averagesolutionNotFound << " times\n";
			g << "Average solution steps: " << averagesolutionSteps << "\n";
			g << "Average algorithm steps: " << averagealgorithmSteps << "\n";
			g << "Average duration: " << averageduration << " microseconds\n\n\n";


		}
	}
}
void printSolutionMessage(HanoiTower hanoiTower)
{
	if (hanoiTower.getSolution() == -1)
	{
		cout << "Solution not found in 1024 algorithm steps\n\n";
	}
	else
	{
		cout << hanoiTower.getSolution() << " moves in " << hanoiTower.getAlgorithmSteps() << " algorithm steps\n\n";
	}
}
int main()
{
	
	HanoiTower hanoiTower(4,4);

	cout << "BKT\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	hanoiTower.bktSolve(hanoiTower.getInitialState());
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration/1000 << " ms\n";
	printSolutionMessage(hanoiTower);

	cout << "Random\n";
	hanoiTower.initializeProblem();
	t1 = high_resolution_clock::now();
	hanoiTower.randomSolve(hanoiTower.getInitialState());
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration/1000 << " ms\n";
	printSolutionMessage(hanoiTower);

	cout << "Efficient Random\n";
	hanoiTower.initializeProblem();
	t1 = high_resolution_clock::now();
	hanoiTower.efficientRandomSolve(hanoiTower.getInitialState());
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration/1000 << " ms\n";
	printSolutionMessage(hanoiTower);

	cout << "Hill Climbing\n";
	hanoiTower.initializeProblem();
	t1 = high_resolution_clock::now();
	hanoiTower.hillClimbingSolve(hanoiTower.getInitialState());
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration/1000 << " ms\n";
	printSolutionMessage(hanoiTower);


	cout << "A star\n";
	hanoiTower.initializeProblem();
	t1 = high_resolution_clock::now();
	hanoiTower.aStarSolve(hanoiTower.getInitialState());
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration/1000 << " ms\n";
	printSolutionMessage(hanoiTower);
	int x;
	cin >> x;
	//createStatistic();
}