
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


size_t LevenshteinDistance::getDistance(string a, string b){
	size_t distance = 0;

	
	a = " " + a;
	b = " " + b;

	
	WordEditMatrix matrix = WordEditMatrix();
	matrix.initialize(b.size()+1, a.size()+1);

	
	int xPos = 1;
	int yPos = 1;

	for (int i = 0; i < a.size(); i++) {
		char ac = a.at(i);
		char bc;

		for (int j = 0; j < b.size(); j++) {
			bc = b.at(j);

			size_t newCost;

			
			if (ac == bc) {
				newCost = matrix.getCostAt(xPos-1,yPos-1); 
				matrix.setCostAt(xPos, yPos, newCost);

			}else {
				
				int deletion = matrix.getCostAt(xPos, yPos - 1) + 1;
				int insertion = matrix.getCostAt(xPos - 1, yPos) + 1;
				int substitution = matrix.getCostAt(xPos - 1, yPos - 1) + 1;

				int newCost = min(deletion, min(insertion, substitution));
				matrix.setCostAt(xPos, yPos, newCost);

			}

			xPos += 1;
		}

		
		xPos = 1;
		yPos += 1;
	}

	
	cout << matrix.print();

	
	distance += matrix.getTotalCost();

	
	
	

	return distance;
}

WordEditMatrix* LevenshteinDistance::initializeStepwise() {

	
	WordEditMatrix* matrix = new WordEditMatrix();
	matrix->initialize(0, 0);

	
	
	this->stepwiseDistance(matrix, " ", " ");
	this->stepwiseDistance(matrix, " ", " ");

	return matrix;
}

WordEditMatrix* LevenshteinDistance::stepwiseDistance(WordEditMatrix* matrix, string sub_a, string sub_b) {

	
	matrix->update(matrix->maxHeight +1, matrix->maxWidth + 1);

	
	matrix->stringA += sub_a;
	matrix->stringB += sub_b;

	
	int xPos = (int)matrix->maxWidth - 2;
	int yPos = 1;

	char ac = matrix->stringA.at(xPos);

	for (; yPos < matrix->stringB.size(); yPos++) {
		char bc = matrix->stringB.at(yPos);

		size_t newCost;

		
		if (ac == bc) {
			newCost = matrix->getCostAt(xPos - 1, yPos - 1);
			matrix->setCostAt(xPos, yPos, newCost);

		}
		else {
			
			int deletion = matrix->getCostAt(xPos, yPos - 1) + 1;
			int insertion = matrix->getCostAt(xPos - 1, yPos) + 1;
			int substitution = matrix->getCostAt(xPos - 1, yPos - 1) + 1;

			int newCost = min(deletion, min(insertion, substitution));
			matrix->setCostAt(xPos, yPos, newCost);

		}
	}

	
	xPos = 1;
	yPos = (int)matrix->maxHeight - 2;

	char bc = matrix->stringB.at(yPos);

	
	for (; xPos < matrix->stringA.size(); xPos++) {
		char ac = matrix->stringA.at(xPos);

		size_t newCost;

		
		if (ac == bc) {
			newCost = matrix->getCostAt(xPos - 1, yPos - 1);
			matrix->setCostAt(xPos, yPos, newCost);

		}
		else {
			
			int deletion = matrix->getCostAt(xPos, yPos - 1) + 1;
			int insertion = matrix->getCostAt(xPos - 1, yPos) + 1;
			int substitution = matrix->getCostAt(xPos - 1, yPos - 1) + 1;

			int newCost = min(deletion, min(insertion, substitution));
			matrix->setCostAt(xPos, yPos, newCost);

		}
	}

	
	cout << matrix->print();

	return matrix;
}
