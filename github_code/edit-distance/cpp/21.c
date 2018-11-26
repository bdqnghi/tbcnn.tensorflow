
#include "stdafx.h";
#include "LevenshteinDistance.h";
#include "WordEditMatrix.h";
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


size_t LevenshteinDistance::getStepwiseDistance(size_t current, string sub_a, string sub_b) {
	return 0;
}

// using dynamic programming
size_t LevenshteinDistance::getDistance(string a, string b){
	size_t distance = 0;

	// add empty space to strings
	a = " " + a;
	b = " " + b;

	// create and initialize a matrix
	WordEditMatrix matrix = WordEditMatrix();
	matrix.initialize(b.size()+1, a.size()+1);

	// step by step calculation
	int xPos = 1;
	int yPos = 1;

	for (int i = 0; i < a.size(); i++) {
		char ac = a.at(i);
		char bc;

		for (int j = 0; j < b.size(); j++) {
			bc = b.at(j);

			size_t newCost;

			// if the characters are equal, cost is 0
			if (ac == bc) {
				newCost = matrix.getCostAt(xPos-1,yPos-1); 
				matrix.setCostAt(xPos, yPos, newCost);

			}else {
				//calculate costs for operations
				int deletion = matrix.getCostAt(xPos, yPos - 1) + 1;
				int insertion = matrix.getCostAt(xPos - 1, yPos) + 1;
				int substitution = matrix.getCostAt(xPos - 1, yPos - 1) + 1;

				int newCost = min(deletion, min(insertion, substitution));
				matrix.setCostAt(xPos, yPos, newCost);

			}

			xPos += 1;
		}

		// reset x
		xPos = 1;
		yPos += 1;
	}

	// for debug 
	cout << matrix.print();

	// add the word distance 
	distance += matrix.getTotalCost();

	// add the length distance
	// int lenDiff = a.size() - b.size();
	// size_t lenDist = abs(lenDiff);

	return distance;// + lenDist;
}

WordEditMatrix* LevenshteinDistance::initializeStepwise() {

	// create and initialize a matrix
	WordEditMatrix* matrix = new WordEditMatrix();
	matrix->initialize(0, 0);

	// spaces for alignment
	// TODO optimize
	this->stepwiseDistance(matrix, " ", " ");
	this->stepwiseDistance(matrix, " ", " ");

	return matrix;
}

WordEditMatrix* LevenshteinDistance::stepwiseDistance(WordEditMatrix* matrix, string sub_a, string sub_b) {

	//update matrix
	matrix->update(matrix->maxHeight +1, matrix->maxWidth + 1);

	//add substrings to stringA/B
	matrix->stringA += sub_a;
	matrix->stringB += sub_b;

	// calculcate current x to update the column at x
	int xPos = (int)matrix->maxWidth - 2;
	int yPos = 1;

	char ac = matrix->stringA.at(xPos);

	for (; yPos < matrix->stringB.size(); yPos++) {
		char bc = matrix->stringB.at(yPos);

		size_t newCost;

		// if the characters are equal, cost is 0
		if (ac == bc) {
			newCost = matrix->getCostAt(xPos - 1, yPos - 1);
			matrix->setCostAt(xPos, yPos, newCost);

		}
		else {
			//calculate costs for operations (+1)
			int deletion = matrix->getCostAt(xPos, yPos - 1) + 1;
			int insertion = matrix->getCostAt(xPos - 1, yPos) + 1;
			int substitution = matrix->getCostAt(xPos - 1, yPos - 1) + 1;

			int newCost = min(deletion, min(insertion, substitution));
			matrix->setCostAt(xPos, yPos, newCost);

		}
	}

	// calculcate current y to update the row at y
	xPos = 1;
	yPos = (int)matrix->maxHeight - 2;

	char bc = matrix->stringB.at(yPos);

	//update column on x
	for (; xPos < matrix->stringA.size(); xPos++) {
		char ac = matrix->stringA.at(xPos);

		size_t newCost;

		// if the characters are equal, cost is 0
		if (ac == bc) {
			newCost = matrix->getCostAt(xPos - 1, yPos - 1);
			matrix->setCostAt(xPos, yPos, newCost);

		}
		else {
			//calculate costs for operations (+1)
			int deletion = matrix->getCostAt(xPos, yPos - 1) + 1;
			int insertion = matrix->getCostAt(xPos - 1, yPos) + 1;
			int substitution = matrix->getCostAt(xPos - 1, yPos - 1) + 1;

			int newCost = min(deletion, min(insertion, substitution));
			matrix->setCostAt(xPos, yPos, newCost);

		}
	}

	// for debug 
	cout << matrix->print();

	return matrix;
}
