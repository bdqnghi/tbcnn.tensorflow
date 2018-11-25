/*
 * FordFulkerson.h
 *
 *  Created on: Mar 29, 2016
 *      Author: Mamunul
 */

#ifndef FORDFULKERSON_H_
#define FORDFULKERSON_H_

#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>

using namespace std;

namespace src {

class FordFulkerson {
public:
	FordFulkerson();
	virtual ~FordFulkerson();
	int ford_fulkerson();

private:
	deque<bool> visited;
	vector<int> p;
//	int** g;
	bool ford_fulkerson_dfs(int v, int t);
};

} /* namespace src */

#endif /* FORDFULKERSON_H_ */
