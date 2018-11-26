/*!
 * \file 
 * \brief  levenshtein.cpp
 *
 * \date   Aug 15, 2013
 * \author Ruben Vereecken
 */

#include "meta.h"

using namespace std;

inline int min(int a, int b, int c) {
	int d = (a < b) ? a : b;
	return (d < c) ? d : c;
}

int levenshteinDistance(string a, string b) {
	int size_a = a.size();
	int size_b = b.size();

	if (!size_a) return size_b;
	if (!size_b) return size_a;


	return min(levenshteinDistance(a.substr(0, size_a - 1), b) + 1,
			   levenshteinDistance(a, b.substr(0, size_b - 1)) + 1,
			   levenshteinDistance(a.substr(0, size_a - 1), b.substr(0, size_b - 1)) +
			   (a[size_a - 1] != b[size_b - 1]));
}

