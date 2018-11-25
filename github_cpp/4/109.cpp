

#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<sstream>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;

#define MAX 15
int recursiveCallCount = 0;

string hanoi(int n, char direction, vector<string> &moves)
{
	if (moves[n] == "unknown" && n > 0)
	
	{
		recursiveCallCount++;
		char oppDirection = '+';
		if (direction == '+')
			oppDirection = '-';

		string t = hanoi(n - 1, oppDirection, moves);

		stringstream out;
		out << direction << n;

		string s = hanoi(n - 1, oppDirection, moves);

		moves[n] = t + " " + out.str() + " " + s;
	}
	return moves[n];
}

int main()
{
	srand(time(NULL));

	int n = rand() % MAX + 1;

	vector<string> moves(n + 1); 
	moves[0] = ""; 

	vector<string>::iterator i = moves.begin();
	for (i++; i != moves.end(); i++)
		*i = "unknown";


	cout << "n = " << n << endl;
	cout <<"Moves = " << hanoi(n, '+', moves) << endl;
	cout << "Number of recursive calls = " << recursiveCallCount << endl;

	return 0;
}
