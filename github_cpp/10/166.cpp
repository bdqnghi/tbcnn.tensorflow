#include <algorithm>
#include <string>
#include <iostream>
#include "EditDistance.h"

EditDistance::EditDistance(std::string a, std::string b) {
	this->a = a;
	this->b = b;
}

int EditDistance::editDistance(int i, int j) {
	if (i >= a.size() || j >= b.size()) {
		if (i >= a.size())
			return b.size() - j;
		return a.size() - i;
	}

	if (a[i] == b[j])
		return editDistance(i + 1, j + 1);

	return std::min(editDistance(i + 1, j + 1), std::min(editDistance(i + 1, j), editDistance(i, j + 1))) + 1;
}

int EditDistance::editDistance(std::string a, std::string b) {
	EditDistance * dist = new EditDistance(a, b);
	return dist->editDistance(0, 0);
}