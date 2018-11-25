/********************************************
*	Nathaniel Lewis
* 	nlewis
*	CSCI 446 AI
*	Fall 2017
*	Assignment 02 - Search
*	File - DepthFirst.cpp
********************************************/

#include "DepthFirst.h"
#include "Town.h"
#include <stack>
#include <map>
#include <string>
#include <iostream>

Town DepthFirst::strategy(std::map<std::string, Town> newMap, std::stack<std::string> newFringe, std::stack<std::string> newPath){
	std::stack<std::string> fringe2 = newFringe;
	std::map<std::string, Town> maps = newMap;
	Town next = maps[fringe2.top()];
	return next;
}

DepthFirst::DepthFirst(std::map<std::string, Town> map, std::string startingTown) 
	: GenericSearch(map, startingTown){
}