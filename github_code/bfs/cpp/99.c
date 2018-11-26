//
// Created by rudi on 13.05.2017.
//
#include <iostream>
#include "Position.h"
#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(Maze *maze)
{
	this->solution = new int[maze->getWidth() * maze->getHeight()]{};
	this->positionQueue = new queue<Position>();
	this->lastField = nullptr;
	this->lengthOfShortestPath = -1;
	this->maze = maze;
};

BreadthFirstSearch::~BreadthFirstSearch()
{
	delete positionQueue;
	delete lastField;
}

bool
BreadthFirstSearch::solve(int &steps)
{
	bool solved = false;
	pushFreeAdjacentFields(BreadthFirstSearch::getStartPos(
		maze->getWidth(), maze->getHeight(), maze, Maze::Start));
	while (!positionQueue->empty() && lastField == nullptr)
	{
		consumePosition();
		steps++;
	}

	if (lastField != nullptr)
	{
		lengthOfShortestPath = BreadthFirstSearch::getField(maze->getWidth(),
															maze->getHeight(), solution, lastField->getColumn(),
															lastField->getRow());
		plotSolution(*lastField);
		solved = true;
	}
	return solved;
}

void
BreadthFirstSearch::pushFreeAdjacentFields(Position *position)
{
	// consume right field
	consumeField(*position, 1, 0);
	// consume left field
	if (lastField == nullptr)
		consumeField(*position, -1, 0);
	// consume upper field
	if (lastField == nullptr)
		consumeField(*position, 0, 1);
	// consume lower field
	if (lastField == nullptr)
		consumeField(*position, 0, -1);
}

void
BreadthFirstSearch::consumePosition()
{
	Position position = positionQueue->front();
	pushFreeAdjacentFields(&position);
	positionQueue->pop();
}

void
BreadthFirstSearch::plotSolution(Position position)
{
	maze->setMazeField(position.getColumn(), position.getRow(), Maze::Result);
	int steps = BreadthFirstSearch::getField(maze->getWidth(),
											 maze->getHeight(), solution, position.getColumn(), position.getRow());
	int newSteps = steps - 1;
	if (newSteps != 0)
		plotSolution(*searchForNextFieldOnShortestPath(
			position, newSteps));
}

void
BreadthFirstSearch::consumeField(Position position,
								 const int columnOffset,
								 const int rowOffset)
{
	Position fieldToBeConsumed = Position(position.getColumn() + columnOffset,
										  position.getRow() + rowOffset);

	if (fieldToBeConsumed.getRow() >= 0
		&& fieldToBeConsumed.getRow() < maze->getHeight()
		&& fieldToBeConsumed.getColumn() >= 0
		&& fieldToBeConsumed.getColumn() < maze->getWidth())
	{
		int mazeField = maze->getMazeField(fieldToBeConsumed.getColumn(),
										   fieldToBeConsumed.getRow());
		int solutionField = BreadthFirstSearch::getField(maze->getWidth(),
														 maze->getHeight(), solution, fieldToBeConsumed.getColumn(),
														 fieldToBeConsumed.getRow());
		if (mazeField == Maze::Way && solutionField == 0)
		{
			positionQueue->push(fieldToBeConsumed);
			int *newStepCount = new int(BreadthFirstSearch::getField(
				maze->getWidth(), maze->getHeight(), solution,
				position.getColumn(), position.getRow()));
			*newStepCount += 1;
			BreadthFirstSearch::setField(maze->getWidth(), maze->getHeight(),
										 solution, fieldToBeConsumed.getColumn(),
										 fieldToBeConsumed.getRow(), newStepCount);
		}
		else if (mazeField == Maze::End)
		{
			this->lastField = new Position(position.getColumn(),
										   position.getRow());
		}
	}
}

Position *
BreadthFirstSearch::searchForNextFieldOnShortestPath(
	Position position, int steps) const
{
	int result = BreadthFirstSearch::getField(maze->getWidth(),
											  maze->getHeight(), solution, position.getColumn(),
											  position.getRow() - 1);
	if (result == steps)
		return new Position(position.getColumn(), position.getRow() - 1);

	result = BreadthFirstSearch::getField(maze->getWidth(), maze->getHeight(),
										  solution,
										  position.getColumn() + 1,
										  position.getRow());
	if (result == steps)
		return new Position(position.getColumn() + 1, position.getRow());

	result = BreadthFirstSearch::getField(maze->getWidth(), maze->getHeight(), solution,
										  position.getColumn(),
										  position.getRow() + 1);
	if (result == steps)
		return new Position(position.getColumn(), position.getRow() + 1);

	result = BreadthFirstSearch::getField(maze->getWidth(), maze->getHeight(), solution,
										  position.getColumn() - 1,
										  position.getRow());
	if (result == steps)
		return new Position(position.getColumn() - 1, position.getRow());

	return nullptr;
}

Position *
BreadthFirstSearch::getStartPos(const int COLUMNS, const int ROWS,
								Maze *maze, const int START_ID)
{
	// upper row
	int index = 0;
	while (index < COLUMNS)
	{
		if (maze->getMazeField(index, 0) == START_ID)
			return new Position(index, 0);
		index++;
	}

	// lower row
	index = 0;
	while (index < COLUMNS)
	{
		if (maze->getMazeField(index, ROWS - 1) == START_ID)
			return new Position(index, ROWS - 1);
		index++;
	}

	// left column
	index = 0;
	while (index < ROWS)
	{
		if (maze->getMazeField(0, index) == START_ID)
			return new Position(0, index);
		index++;
	}

	// right column
	index = 0;
	while (index < ROWS)
	{
		if (maze->getMazeField(COLUMNS - 1, index) == START_ID)
			return new Position(COLUMNS - 1, index);
		index++;
	}
	return nullptr;
}

int
BreadthFirstSearch::getField(const int COLUMNS, const int ROWS,
							 int matrix[], const int column,
							 const int row)
{
	if (!(0 <= column && column < COLUMNS
		&& 0 <= row && row < ROWS))
		throw invalid_argument("Row or column out of bounds!");
	return matrix[(row) * COLUMNS + column];
}

void
BreadthFirstSearch::setField(const int COLUMNS, const int ROWS,
							 int matrix[], const int column,
							 const int row, int *content)
{
	if (!(0 <= column && column < COLUMNS
		&& 0 <= row && row < ROWS))
		throw invalid_argument("Row or column out of bounds!");
	const int index = row * COLUMNS + column;
	if (!matrix[index] == 0)
		throw invalid_argument("You can only edit fields which are set "
								   "to zero!");
	matrix[index] = *content;
}

int *
BreadthFirstSearch::getSolution() const
{
	return solution;
}

queue<Position> *
BreadthFirstSearch::getPositionQueue() const
{
	return positionQueue;
}

Position *
BreadthFirstSearch::getLastField() const
{
	return lastField;
}

int
BreadthFirstSearch::getLengthOfShortestPath() const
{
	return lengthOfShortestPath;
}
