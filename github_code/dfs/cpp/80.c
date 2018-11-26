#ifndef CPP_LIB_DEPTH_FIRST_SEARCH_H
#define CPP_LIB_DEPTH_FIRST_SEARCH_H

#include <vector>
#include <set>

using std::vector;
using std::set;

class DepthFirstSearch {
// 200. Number of Islands
public:
    int numIslands(const vector<vector<char>>& grid);
private:
	vector<set<int>> genIslands(const vector<vector<char>>& grid);
	bool isExistedIsland(const vector<set<int>>& islands, int point);
	void genIsland(const vector<vector<char>>& grid,
						vector<set<int>>& islands, int start_point);

// 695. Max Area of Island
public:
	int maxAreaOfIsland(vector<vector<int>>& grid);
private:
	int getAreaOfIsland(vector<vector<int>>& grid, int position);

// 547. Friend Circles
public:
	int findCircleNum(vector<vector<int>>& M);
private:
	void findCircle(vector<vector<int>> &M, int person);
};

#endif