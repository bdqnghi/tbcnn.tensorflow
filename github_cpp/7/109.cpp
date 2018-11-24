#include "TowerOfHanoi.hpp"
#include <string>
TowerOfHanoi::TowerOfHanoi(){
	numberOfDisks = 0;
	startPeg = 'A';
	endPeg = 'C';
}

TowerOfHanoi::TowerOfHanoi(const int& n){
	numberOfDisks = n;
	startPeg = 'A';
	endPeg = 'C';
}

TowerOfHanoi::TowerOfHanoi(const int& n, const char& _startPeg, const char& _endPeg){
	numberOfDisks = n;
	startPeg = _startPeg;
	endPeg = _endPeg;
}

std::vector<std::string> TowerOfHanoi::generateSolution()
{
	solve(numberOfDisks,startPeg, endPeg);
	return moves;
}

void TowerOfHanoi::solve(const int& n, const char& currPeg,const char& toPeg){

	if(n<=0){
		return;
	}
	else
	{
		char nextPeg = remove(currPeg, toPeg);
		if(n == 1){
			move(1, toPeg);
			return;
		}
		else
		{
			solve(n-1, currPeg, nextPeg); 
			move(n, toPeg);
			solve(n-1, nextPeg, toPeg);
		}

	}
}

void TowerOfHanoi::move(const int& diskNum, const char& toPeg){
	std::string c = std::to_string(diskNum);
	std::string s = "Move tile " + c + " to peg ";
	s.push_back(toPeg);
	moves.push_back(s);
}

char TowerOfHanoi::remove(const char& peg1, const char& peg2){
	char peg ='\0';
	if ((peg1 == 'A' && peg2 == 'B') || (peg1 == 'B' && peg2 == 'A')) { peg = 'C';}
	else if ((peg1 == 'A' && peg2 == 'C')  || (peg1 == 'C' && peg2 == 'A')) { peg = 'B';}
	else if ((peg1 == 'B' && peg2 == 'C') || (peg1 == 'C' && peg2 == 'B')) { peg = 'A';}
	return peg;
}










