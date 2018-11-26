#include <Windows.h>
#include "stdafx.h"
#include <algorithm>
#include "LevenshteinDistanceCpp.h"

namespace LevenshteinDistanceCpp
{
	int Functions::findMinimum(int a, int b, int c) {
		return ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)));
	}
	void Functions::initializeLevMatrix(unsigned int** levTab, size_t len1, size_t len2) {
		levTab[0][0] = 0;
		for (unsigned int i = 1; i <= len1; ++i) {
			levTab[i][0] = i;
		}
		for (unsigned int i = 1; i <= len2; ++i) {
			levTab[0][i] = i;
		}
	}
	void Functions::countDiagonally(unsigned int** levTab, int index, std::string& s1, std::string& s2) {
		levTab[index][index] = findMinimum(levTab[index - 1][index] + 1, levTab[index][index - 1] + 1, levTab[index - 1][index - 1] + 
			(s1[index - 1] == s2[index - 1] ? 0 : 1));
	}
	void Functions::countLevenshteinDistance(unsigned int** levTable, const std::string& s1, const std::string& s2, int dir, int index) {
		const std::size_t len1 = s1.size(), len2 = s2.size();
		if (1 == dir) {
			for (int i = index; i <= len1; ++i) {
				levTable[i][index] = findMinimum(levTable[i - 1][index] + 1, levTable[i][index - 1] + 1, levTable[i - 1][index - 1] + 
					(s1[i - 1] == s2[index - 1] ? 0 : 1));
			}
		}
		else {
			for (unsigned int j = index; j <= len2; ++j) {
				levTable[index][j] = findMinimum(levTable[index - 1][j] + 1, levTable[index][j - 1] + 1, levTable[index - 1][j - 1] 
					+ (s1[index - 1] == s2[j - 1] ? 0 : 1));
			}
		}
	}
}
