#include "LinearRegression.h"



LinearRegression::LinearRegression(bool intermediateCalculation) :
	calc(intermediateCalculation),
	rref(intermediateCalculation),
	type(intermediateCalculation)
{
	//Init intermiate calculations through out the code
	(intermediateCalculation == 0 || intermediateCalculation == 1) ? _intermediateCalculation = intermediateCalculation : _intermediateCalculation = 0;

	//Construct a 1x1 matrix
	resultMatrix.columns = 1;
	resultMatrix.rows = 1;
	calc.constructMatrix(&resultMatrix);

	//Construct a base result
	results.freeVariable = 0;
	results.size = 0;
	calc.constructMatrixResult(&results);

	//Init regression
	calc.constructRegression(&_regression);
}


LinearRegression::~LinearRegression()
{
	//Deconstruc objects constructed in the constructor
	calc.deconstructMatrix(&resultMatrix);
	calc.deconstructMatrixResult(&results);
	calc.deconstructRegression(&_regression);
}


Regression * LinearRegression::findStandardRegression(Matrix *orginalDataSet, Regression *orginalRegression)	//What if the regression doesn't have as many vaiables?
{
	//Copy dataSet
	calc.deconstructMatrix(&resultMatrix);
	resultMatrix.columns = orginalDataSet->columns;
	resultMatrix.rows = orginalDataSet->rows;
	calc.constructMatrix(&resultMatrix);
	calc.mergeMatrix(&resultMatrix, orginalDataSet);

	//SortData
	//Linear regressions doesn't need to be sorted.
	
	//Find regression
	findRegression(orginalRegression);

	//Return result
	return &_regression;
}

Regression * LinearRegression::findBestRegression(Matrix *orginalDataSet, int leftSide, int rightSide)
{
	//Copy dataSet
	calc.deconstructMatrix(&resultMatrix);
	resultMatrix.columns = orginalDataSet->columns;
	resultMatrix.rows = orginalDataSet->rows;
	calc.constructMatrix(&resultMatrix);
	calc.mergeMatrix(&resultMatrix, orginalDataSet);


	return &_regression;
}


void LinearRegression::precision(Matrix *dataSet, Regression *orginalRegression)
{
	for (size_t i = 0; i < orginalRegression->variate; i++)
	{
		orginalRegression->precision[i] = regressionPredicsion(dataSet, orginalRegression, i);
	}

	
}


void LinearRegression::copyRegression(Regression *orginalRegession)
{


}


void LinearRegression::printRegression(Regression *orginalRegression)
{
	//Print for each part of the regression
	for (size_t i = 0; i < orginalRegression->variate; i++)
	{
		for (size_t j = 0; j < orginalRegression->regression.size(); j++)
		{
			switch (orginalRegression->regression[i].type)	//Defines if it will be a constant or beta value that will be printet first, for the given part
			{
			case 1:
				cout << orginalRegression->answers[i][j];
			case 2:
				cout << orginalRegression->regression[i].constant <<"*e^(";
			case 3:
				cout << orginalRegression->regression[i].constant << "*sin(";
			case 4:
				cout << orginalRegression->regression[i].constant << "*log2(";
			}

			for (size_t m = 0; orginalRegression->regression[i].variables[m] != '\0'; m++)
			{
				if (orginalRegression->regression[i].variables[m] != '1')
				{
					cout << "*X" << m;								//Defines how many x's that need to be printet out in cascade after eah other	
				}
			}
			switch (orginalRegression->regression[i].type)			//Defines the end of the part, to parantheses or other things
			{
			case 1:
				cout << "^(" << orginalRegression->regression[i].constant << ")" << endl;
			case 2:
				cout << "*" << orginalRegression->answers[i][j] << ")" << endl;
			case 3:
				cout << "*" << orginalRegression->answers[i][j] << ")" << endl;
			case 4:
				cout << "*" << orginalRegression->answers[i][j] << ")" << endl;
			}
		}
	}
}


void LinearRegression::addRegressionPart(Regression *orginalRegression, RegressionPart orginalPart)	//It's not a pointer because we don't want to point it.
{
	orginalRegression->regression.push_back(orginalPart);
}


double LinearRegression::valueAtCoordinate(Matrix *dataSet, Regression *orginalRegression, int time)
{


	return 0.0;
}


void LinearRegression::findRegression(Regression *orginalRegression)
{
	//setup left and rightside matrices
	Matrix leftSide;
	Matrix rightSide;
	Matrix bufferMatrixOne;
	Matrix bufferMatrixTwo;

	leftSide.rows = resultMatrix.columns;
	rightSide.rows = leftSide.rows;

	leftSide.columns = orginalRegression->regression.size();
	rightSide.columns = orginalRegression->rightSide.size();

	calc.constructMatrix(&leftSide);
	calc.constructMatrix(&rightSide);
	calc.constructMatrix(&bufferMatrixOne);
	calc.constructMatrix(&bufferMatrixTwo);

	//Split it up
	createLeftSide(&leftSide, orginalRegression);
	createRightSide(&rightSide, orginalRegression);		//Do i need the result matrix after this point? - if 

	//-------calculate the linear regression-------
	//Calculate the transposed leftside
	calc.transpose(&leftSide);
	calc.copyMatrix(&bufferMatrixOne);

	//Calculate leftSide times transposed leftside
	calc.multiplication(&leftSide, &bufferMatrixOne);
	calc.copyMatrix(&bufferMatrixTwo);

	//Calculate the transposed leftSide times the rightSide
	calc.multiplication(&bufferMatrixOne, &rightSide);
	calc.copyMatrix(&bufferMatrixOne);

	//Calculate the inverted matrix
	rref.invert(&bufferMatrixTwo);
	rref.copyMatrix(&bufferMatrixTwo);
	
	//Calculate the beta values
	calc.multiplication(&bufferMatrixTwo, &bufferMatrixOne);
	calc.copyMatrix(&bufferMatrixOne);


	//Put the values into the regression - How to handle the values, when it's a multi variable regression?
	for (size_t i = 0; i < bufferMatrixOne.rows; i++)	//wrong, it's the number of 1's in the rightSide
	{
		for (size_t j = 0; j < bufferMatrixOne.columns; j++)
		{
			orginalRegression->answers[j][i] = bufferMatrixOne.matrix[j][i];	//If it doesn't work, it's the regression contructor that need to made different
		}
	}


	//Deconstruct matrices
	calc.deconstructMatrix(&leftSide);
	calc.deconstructMatrix(&rightSide);
	calc.deconstructMatrix(&bufferMatrixOne);
	calc.deconstructMatrix(&bufferMatrixTwo);
}


Regression * LinearRegression::findDominantRegression(Matrix *, Regression *)
{


	return nullptr;
}


Regression * LinearRegression::getRegressionFromCoordinates(Matrix *, Regression *)
{


	return nullptr;
}


double LinearRegression::regressionPredicsion(Matrix *dataSet, Regression *orginalRegression, int variateColumn)		//For each variate
{
	//Create variables
	double gatheredLength = 0;
	double lengthPoint = 0;
	double lengthGraph = 0;
	int yRow = 0;

	//Find y row
	for (size_t i = 0; i<variateColumn+1;)
	{
		yRow++;
		if (orginalRegression->rightSide[i] == 1)
		{
			i++;
		}
	}
	yRow -= 1;

	//Find length to each point
	for (size_t i = 0; i < dataSet->columns; i++)
	{
		lengthPoint = dataSet->matrix[i][yRow];
		lengthGraph = valueAtCoordinate(dataSet, orginalRegression, 1);	//Det kan jeg ikke g�re - der m� bare ikke v�re for mange mellem regninger i funktionen

		gatheredLength += (lengthPoint > lengthGraph) ? lengthPoint - lengthGraph : lengthGraph - lengthPoint;
	}


	//Calculate avage and return the number
	return gatheredLength/dataSet->columns;
}


void LinearRegression::createLeftSide(Matrix *leftSide, Regression *orginalRegression)		//Resultmatrix er datas�ttet
{


}


void LinearRegression::createRightSide(Matrix *rightSide, Regression *)						//Beh�ves jeg to funktioner?
{


}


