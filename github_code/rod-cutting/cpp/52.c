/*
The rod-cutting problem is the following. Given a rod of length n inches and a
table of prices p i for i D 1; 2; : : : ; n, determine the maximum revenue r n obtain-
able by cutting up the rod and selling the pieces. Note that if the price p n for a rod
of length n is large enough, an optimal solution may require no cutting at all.
*/
#include <iostream>
#include "../../cpplib/cpputils.h"
using namespace std;

// O(exponential) // return the optimal price recursively, assumed prices[0] = 0 
// in this method cuts are used just to create the final answer of optimal cuts.
// algorithm does not require or uses cuts array
int findCuttingRecNonOptimal(int* prices, const int& priceLength, int rodSize, int* cuts)
{
	cout << "findCuttingRecNonOptimal called with : rodSize = " << rodSize << endl; 
	if( 0 == rodSize )
		return 0;
	
	int price = -1;
	// find the first cut and recurse on rest of the rodLength
	for( int i = 1 ; i <= rodSize ; i++ )
	{
		cout << "trying for the rod cut size of : " << i << endl;
		int nextPrice = prices[i] + findCuttingRecNonOptimal(prices, priceLength,rodSize-i,cuts);
		if( price < nextPrice )
		{
			cuts[rodSize] = i ; 
			price = nextPrice;
		}
	}
	cout << "returning final price for rodSize = " << rodSize << ", price " << price << endl;
	return price;
}

// O(n2) // return the optimal price recursively, assumed prices[0] = 0
// This method is top to bottom dynamic programming approach.
// in this method cuts are used just to create the final answer of optimal cuts.
// algorithm does not require or uses cuts array
int findCuttingRecOptimal(int* prices, const int& priceLength, int rodSize, int* cuts, int* optimalPrices)
{
	cout << "findCuttingRecOptimal called with : rodSize = " << rodSize << endl; 
	if( 0 == rodSize )
		return 0;
	
	int price = optimalPrices[rodSize]; // quick lookup if the price is already present.
	if( price != -1 )
		return price ;
	// find the first cut and recurse on rest of the rodLength
	for( int i = 1 ; i <= rodSize ; i++ )
	{
		cout << "trying for the rod cut size of : " << i << endl;
		int nextPrice = prices[i] + findCuttingRecOptimal(prices, priceLength,rodSize-i,cuts,optimalPrices);
		if( price < nextPrice )
		{
			cuts[rodSize] = i ; 
			price = nextPrice;
		}
	}
	cout << "returning final price for rodSize = " << rodSize << ", price " << price << endl;
	optimalPrices[rodSize] = price; // set the optimal price of the rodSize's cutting for quick lookup.
	return price;
}

/*
O(n2)
this is bottom up dynamic programming approach
*/
int findCuttingIterOptimal(int* prices, const int& priceLength, int rodSize, int* cuts, int* optimalPrices)
{
	optimalPrices[0] = 0 ;
	optimalPrices[1] = prices[1]; // optimal cut size of rod of length 1 is the price of rodSize = 1
	for(int i = 1 ; i <= rodSize; i++ ) // finding optimal price for rodSize = i
	{
		int maxPrice = -1;
		for( int j = 1 ; j <= i ; j++ ) // finding optimal first cut at j for rodSize = i 
		{
			int price = prices[j] + optimalPrices[i-j];
			if( maxPrice < price )
			{
				cuts[i] = j ;
				maxPrice = price;
			}
		}
		optimalPrices[i] = maxPrice; // set the optimal price of this rodSize for future use.
	}

	return optimalPrices[rodSize];
}

int main()
{
	int size = 0 ; 
	cout << "Input number of prices : " ;
	cin >> size;
	int* prices;
	cout << "Input the prices : " ;
	inputAndCreateArray(prices,size);

	print1DArray("The prices you entered : ", prices, size);

	cout << "Enter the size of the rod : ";
	int rodSize;
	cin >> rodSize;

	int finalPrice;
	int* cuts ; // what is optimal first cut for the rodSize == index of the array
	int* optimalPrices; // it stores the optimal prices for the different rodSizes for optimal algos
	createAndInitArray(cuts,rodSize+1,0);
	createAndInitArray(optimalPrices,rodSize+1,-1);	

	// finalPrice = findCuttingRecNonOptimal(prices, size, rodSize,cuts);
	// finalPrice = findCuttingRecOptimal(prices,size,rodSize,cuts,optimalPrices);
	finalPrice = findCuttingIterOptimal(prices,size,rodSize,cuts,optimalPrices);

	print1DArray("The optimal cuts are : ", cuts, rodSize+1);
	cout << "And the Optimal Price is : " << finalPrice << endl;

	delete cuts;
	delete prices;

}