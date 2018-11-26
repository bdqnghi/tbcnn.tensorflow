/*
 * BreadthFirstSearch.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Christine
 */

#include "BreadthFirstSearch.hpp"
#include <stack>
#include <cstdlib>

BreadthFirstSearch::BreadthFirstSearch(const Maze& maze)  : Robot(maze,"BreadthFirstSearch")
{
}

BreadthFirstSearch::~BreadthFirstSearch()
{
}

void BreadthFirstSearch::findSolution()
{
	int i = 0;
	char cmd = 'E';
	std::deque<std::pair<int, int> > open;
	std::pair<int, int> current;
	std::pair<int,int> target;
	open.push_back(maze->getEnd());
	maze->mark(maze->getEnd(), 'X');
	bool found = false;

	while(!found)
	{
		current = open.front();
		for(i = 0; i<4; i++)
		{
			target = current;
			switch(i)
			{
			case 0:		target.second++;
						break;

			case 1:		target.first--;
						break;

			case 2:		target.second--;
						break;

			case 3: 	target.first++;
						break;

			default:	break;
			}
			if(target == maze->getStart())
			{
				found = true;
			}
			if(!maze->isMarked(target) && maze->passable(target))
			{
				maze->mark(target, i+48);
				open.push_back(target);
			}
		}
		//maze->printMaze();
		open.pop_front();
	}
	open.clear();
	//maze->printMaze();

	pos = maze->getStart();
	while(pos != maze->getEnd())
	{
		cmd = maze->getMark(pos);
		maze->mark(pos, 'B');

		switch(cmd)
		{
			case '0':
				pos.second--;
				break;

			case '1':
				pos.first++;
				break;

			case '2':
				pos.second++;
				break;

			case '3':
				pos.first--;
				break;

			default:
				std::cout << "Found: " << cmd << " BreadthFirstSearch has encountered a problem" << std::endl;
				exit(-1);
		}
		steps++;
	}

	maze->clearMark('0');
	maze->clearMark('1');
	maze->clearMark('2');
	maze->clearMark('3');
}

void BreadthFirstSearch::printResult()
{
	int i = 0;
	int digits = countDigits(steps);

	std::cout << name <<" |";

	for(i=0;i<((7-digits)/2);i++)
	{
		std::cout <<" ";
	}
	std::cout << steps;

	for(i=0;i<((7-digits)/2);i++)
	{
		std::cout <<" ";
	}

	if(((7-digits)%2) == 1)
	{
		std::cout <<" ";
	}

	std::cout <<"|" << std::endl;
}

