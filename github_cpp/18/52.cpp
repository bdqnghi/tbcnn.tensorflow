
#include <iostream>
#include "../../cpplib/cpputils.h"
using namespace std;




int findCuttingRecNonOptimal(int* prices, const int& priceLength, int rodSize, int* cuts)
{
	cout << "findCuttingRecNonOptimal called with : rodSize = " << rodSize << endl; 
	if( 0 == rodSize )
		return 0;
	
	int price = -1;
	
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





int findCuttingRecOptimal(int* prices, const int& priceLength, int rodSize, int* cuts, int* optimalPrices)
{
	cout << "findCuttingRecOptimal called with : rodSize = " << rodSize << endl; 
	if( 0 == rodSize )
		return 0;
	
	int price = optimalPrices[rodSize]; 
	if( price != -1 )
		return price ;
	
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
	optimalPrices[rodSize] = price; 
	return price;
}


int findCuttingIterOptimal(int* prices, const int& priceLength, int rodSize, int* cuts, int* optimalPrices)
{
	optimalPrices[0] = 0 ;
	optimalPrices[1] = prices[1]; 
	for(int i = 1 ; i <= rodSize; i++ ) 
	{
		int maxPrice = -1;
		for( int j = 1 ; j <= i ; j++ ) 
		{
			int price = prices[j] + optimalPrices[i-j];
			if( maxPrice < price )
			{
				cuts[i] = j ;
				maxPrice = price;
			}
		}
		optimalPrices[i] = maxPrice; 
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
	int* cuts ; 
	int* optimalPrices; 
	createAndInitArray(cuts,rodSize+1,0);
	createAndInitArray(optimalPrices,rodSize+1,-1);	

	
	
	finalPrice = findCuttingIterOptimal(prices,size,rodSize,cuts,optimalPrices);

	print1DArray("The optimal cuts are : ", cuts, rodSize+1);
	cout << "And the Optimal Price is : " << finalPrice << endl;

	delete cuts;
	delete prices;

}