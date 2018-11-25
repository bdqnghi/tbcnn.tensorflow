#include "RodCutting.h"
#include <iostream>

RodCutting::RodCutting(void)
{
}


RodCutting::~RodCutting(void)
{
}









void RodCutting::ComputeFirstCut(vector<double> & utility, vector<double> & maxUtility, vector<int> & firstCut)
{
	maxUtility[0] = utility[0];
	firstCut[0] = 0;

	for (unsigned int i = 1; i < utility.size(); i ++) {
		maxUtility[i] = -1;
		for (unsigned int j = 0; j < i; j ++) {
			double current = utility[j] + maxUtility[i - j - 1];
			if (maxUtility[i] < current) {
				maxUtility[i] = current;
				firstCut[i] = j;
			}
		}
		if (maxUtility[i] < utility[i]) {
			maxUtility[i] = utility[i];
			firstCut[i] = i;
		}
	}
}






void RodCutting::PrintResult(vector<double> & utility)
{
	int i = (int)utility.size();
	
	vector<double> maxUtility(i);
	vector<int> firstCut(i);

	ComputeFirstCut(utility, maxUtility, firstCut);
	
	i--;
	while (i >= 0) {
		cout << firstCut[i] << " ";
		i = i - firstCut[i] - 1;
	}
	cout << endl;
}

