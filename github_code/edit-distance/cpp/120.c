/*
 *  evenshtein.cpp
 *  TextMiningServer
 *
 *  Created by Alex on 23/11/10.
 *  Copyright 2010 Epita. All rights reserved.
 *
 */

#include "levenshtein.hh"

#define PRINT_MATRIX 1

int min(int v1, int v2)
{
	if (v1 < v2)
		return v1;
	return v2;
}

int distanceLeven(std::string str1, std::string str2)
{
	int tab[str1.size() + 1][str2.size() + 1];
	int db = 0;
	for (int i = 0 ; i <= str1.size(); i++)
		for (int j = 0; j <= str2.size(); j++)
			tab[i][j] = 0;
	for (int i = 0; i <= str1.size(); i++)
		tab[i][0] = i;
	for (int j = 0; j <= str2.size(); j++)
		tab[0][j] = j;
	for (int i = 1; i <= str1.size(); i++)
	{
		db = 0;
		for (int j = 1; j <= str2.size(); j++)
		{
			if (str1[i - 1] == str2[j - 1])
				db = 0;
			else
				db = 1;
			tab[i][j] = min(min(tab[i - 1][j] + 1, tab[i][j - 1] + 1), tab[i-1][j-1] + db);
			if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1])
				tab[i][j] = min(tab[i][j], tab[i-2][j-2] + db);

		}
	}
#if PRINT_MATRIX
	for (int i = 0 ; i <= str1.size(); i++)
	{
		for (int j = 0; j <= str2.size(); j++)
			std::cout << tab[i][j] << " ";
		std::cout << std::endl;
	}
#endif
	return tab[str1.size()][str2.size()];
}