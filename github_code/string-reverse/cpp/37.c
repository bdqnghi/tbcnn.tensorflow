/*
 * ReverseString.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: rafael
 */

#include "ReverseString.h"

#include <iostream>

string ReverseString::reverseString(string s) {
	string result(s);
	auto length = s.length();
	decltype(length) i = 0;

	for (; i < length; i++) {
		result[i] = s[length - i - 1];
	}

	return result;
}

void ReverseString::run() {
	cout << "hello" << " <-> " << reverseString("hello") << endl;
	cout << "world" << " <-> " << reverseString("world") << endl;
}

// static Leetcode *lc = new ReverseString();
