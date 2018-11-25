#include <bits/stdc++.h>
using namespace std;



int main(int argc, char const *argv[])
{

	int MAX_SIZE = 10;

	
	vector<int> prices = {0,1,2,2,3,7,3,3,4,5,6};

	
	vector<int> optimal(11,0), cutSize(11);


	int max;
	for(int i=1; i <= 10; i++)
	{
		
		max = prices[i];
		cutSize[i] = 0;
		
		
		for (int j = 1; j < i; ++j)
		{
			if( max < prices[j] + optimal[i-j] )
			{
				max = prices[j] + optimal[i-j];
				cutSize[i] = j;
			}
		}
		
		optimal[i] = max;
	}


	
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



