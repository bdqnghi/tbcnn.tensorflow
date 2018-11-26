/*
Consider a modification of the rod-cutting problem in which, in addition to a price pi for each rod, each cut incurs a fixed cost of c. The revenue associated with a solution is now the sum of the prices of the pieces minus the costs of making the cuts. Give a dynamic-programming algorithm to solve this modified problem.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int rodCutting(int priceTable[], int rodLength, int cost)
{
	if (rodLength == 0)
	{
		return 0;
	}

	int* table = new int[rodLength + 1];

	table[0] = 0;

	for (int currentLenght = 1; currentLenght <= rodLength; currentLenght++)
	{
		cout << "our current Length is " << currentLenght << endl;

		int maxPrice = -1;
		int costDeducted;

		// checks over our subproblems to find the current highest for this length
		// this loop traverses our price table but only until the current length 
		for (int x = 1; x <= currentLenght; x++)
		{
			cout << "\t\tNote current price when length is " << x << " is " << priceTable[x] << endl;
			cout << "\t\t\t We like to reuse the subproblem " << currentLenght - x << " which its result was " << table[currentLenght - x] << endl;
			cout << "\t\t\t\t\tWe will do " << priceTable[x] << "+" << table[currentLenght - x] << endl;
			cout << "\t\t\t\t\t\t\tHi there what is max here " << max(maxPrice, priceTable[x] + table[currentLenght - x]) << endl;


			// condition to check if cuts were made
			if (currentLenght - x != 0)
			{
				costDeducted = cost;
				cout << "\t--------------------------We had to make a cut here so we should get " << priceTable[x] + table[currentLenght - x] - costDeducted << endl;
			}
			else
			{
				costDeducted = 0;
			}

			maxPrice = max(maxPrice, priceTable[x] + table[currentLenght - x] - costDeducted);
		}

		cout << "the maximum price with the length of " << currentLenght << " is " << maxPrice << endl << endl;
		table[currentLenght] = maxPrice;
	}

	return table[rodLength];
}

int main()
{
	int pricetable[] = { 0,1,5,8,9,10,17,17, 20, 24, 30 };
	int n = 7;

	cout << "The maximum possible price for a rod of length " << n << " is " << rodCutting(pricetable, n,2) << endl;

	return 0;

}