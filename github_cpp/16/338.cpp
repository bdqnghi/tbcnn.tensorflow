/*
 * =====================================================================================
 *
 *       Filename:  Topological-sort.cpp
 *
 *    Description:  implement topological sort, use DFS as the 
 *    underlying algorithm
 *
 *        Version:  1.0
 *        Created:  2012年09月08日 16时16分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Graph.h"
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <assert.h>
#include <stack>
const int White = 0;
const int Gray = 1;
const int Black = 2;
const int NotAcess = INT_MAX;
const int nil = -1;

std::ostream& operator<<( std::ostream& out, const std::vector<int>& vi) {
	for( int i = 0 ; static_cast<unsigned>(i) < vi.size() ; i++ )
	{
		out << "\t" << vi[i] ;
	}

	out << std::endl;
	return out ;	
}
typedef std::vector<int> veci;

void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, 
		int start, int& time, bool& haveCircle) ;

bool topologicalSort(const AdjacentGraph& adjG, 
		veci &sortingVertice) {
	std::vector<int> colors(adjG.getSize(), White);
	std::vector<int> d(adjG.getSize(), NotAcess);
	std::vector<int> pai(adjG.getSize(), nil);
	std::vector<int> finish(adjG.getSize(), NotAcess);

	bool haveCircle = false;
	int time = 1;

	for( int i = 0; i < adjG.getSize(); i++ ) {
		if(colors[i] == White) {
			colors[i] = Gray;
			d[i] = time;
			time += 1;
			pai[i] = nil;
			std::cout << "visit " << i << std::endl;
			DFSAuxliary(adjG, colors, d, pai, finish, 
					i, time, haveCircle);
			if(haveCircle)
				return false;
		}
	}

	
	std::cout << "start " << d << std::endl;
	std::cout << "finish " << finish << std::endl;


	typedef std::pair<int, int> finishIndex;
	std::vector<finishIndex> tmp;

	for( int i = 0 ; static_cast<unsigned>(i) < finish.size() ; i++ )
	{
		tmp.push_back(std::make_pair(finish[i], i));
	}

	std::sort(tmp.begin(), tmp.end());

	for( int i = 0 ; static_cast<unsigned>(i) < tmp.size() ; i++ )
	{
		sortingVertice.push_back(tmp[i].second);
	}

	for( int i = 0, j = tmp.size() - 1 ;
		   	i < j ; i++, j-- )
	{
		std::swap(sortingVertice[i], sortingVertice[j]);
	}
	return true;

}

void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, 
		int start, int& time, bool& haveCircle) {
	for( int i = 0 ; static_cast<unsigned>(i) < adjG[start].size() ; i++ )
	{
		edge e = adjG[start][i];
		if(color[e.first] == White) {
			d[e.first] = time;
			time += 1;

			color[e.first] = Gray;
			pai[e.first] = start;

			std::cout << "visit " << e.first << std::endl;
			DFSAuxliary(adjG, color, d, pai, finish, 
					e.first, time, haveCircle);
		} else if(color[e.first] == Gray) {
			haveCircle = true;
		}
	}
	color[start] = Black;
	finish[start] = time;
	time += 1;
}


int main(int argc, char *argv[])
{
	AdjacentGraph aG("Graph-3.txt");
	veci topvertice;
	assert(topologicalSort(aG, topvertice) == false);

	AdjacentGraph aG1("Graph-4.txt");	
	assert(topologicalSort(aG1, topvertice) == true);
	std::cout << topvertice;
	return 0;
}
