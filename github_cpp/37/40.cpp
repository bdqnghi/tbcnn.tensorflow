#include <bits/stdc++.h>
using namespace std;


/*
	A basic way:
		r_n = max(p_n, r_1 + r_n-1 , r_2 + r_n-2, ..... , r_n-1 + r1)
		The first argument signifies no cuts, the second a cut of solution for a cut of size 1 and n-1 and so on

	This basic way can be rewritten as : 
		r_n = max(p_i + r_n-i)   for i from 0 to n-1
		This covers all the possible divisions and used only one subproblem
*/
int main(int argc, char const *argv[])
{

	int MAX_SIZE = 10;

	// Prices of cuts ( starting from cut 0)
	vector<int> prices = {0,1,2,2,3,7,3,3,4,5,6};

	// Initialize each optimal value to be 0
	vector<int> optimal(11,0), cutSize(11);


	int max;
	for(int i=1; i <= 10; i++)
	{
		// Let the optimal of cut of size i be price[i] 
		max = prices[i];
		cutSize[i] = 0;
		// Check if a better cut exists using previously calculated optimals
		// NOTE : j is less than i
		for (int j = 1; j < i; ++j)
		{
			if( max < prices[j] + optimal[i-j] )
			{
				max = prices[j] + optimal[i-j];
				cutSize[i] = j;
			}
		}
		// Set optimal for this cut
		optimal[i] = max;
	}


	// Print optimal profit for rod of size i with cuts
	for(int i=0; i <= 10; i++)
	{
		cout << i << " : ";
		int j=i;
		while(cutSize[j]!=0) { cout << cutSize[j] << "+"; j = j - cutSize[j];}
		cout << j;
		cout << "\t\t\t\tProfit:";
		cout << optimal[i];
		cout << endl;			
	}

	return 0;
}



