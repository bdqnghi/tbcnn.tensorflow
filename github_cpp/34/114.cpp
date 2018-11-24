#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

#define NUM_CLASSIFICATIONS 2
#define NUM_INDICATOR_OUTCOMES 2
#define IS_MAP true
#define IS_MLE false

/** The model is setup as such:
 *		model[the indicator variable][the outcome of the indicator][the outcome of the vector as a whole]
 */
vector<double **> setupModel(int numVariables)
{
	vector<double **> model(numVariables);

	for(int i = 0; i < numVariables; i++)
	{
		double **x = new double*[NUM_INDICATOR_OUTCOMES];
		x[0] = new double[NUM_INDICATOR_OUTCOMES * NUM_CLASSIFICATIONS];
		
		for (int j = 0; j < NUM_INDICATOR_OUTCOMES; j++) 
			x[j] = x[0] + j * NUM_CLASSIFICATIONS;

		model[i] = x;
	}

	return model;
}

/* get the result of the vector */
int getResult(ifstream &file){
	string line;
	getline(file, line);
	return line[line.length() - 1] - '0'; // last character on the line, guaranteed. Convert from char to int
}

/* create the model, without normalizing */
void readModel(vector<double **> model, int numVariables, int numVectors, ifstream &file, double *outcomeVector)
{
	int currBin;
	int *currVector = new int[numVariables];

	for(int i = 0; i < numVectors; i++)
	{
		/* get the vector */
		for(int j = 0; j < numVariables; j++)
			file >> currVector[j];

		/* get the binary output of the vector */
		currBin = getResult(file);
			
		/* add the vector to the model */
		for(int j = 0; j < numVariables; j++)
			model[j][currVector[j]][currBin]++;

		/* update the outcome vector */
		outcomeVector[currBin]++;
	}

	delete []currVector;	
}

/* normalize the model and the P(Y) vector */
void normalizeVectors(vector<double **> model, double *outcomeVector, int numVariables, int denominator) 
{
	/* Normalize model vectors */
	for(int i = 0; i < numVariables; i++)
		for(int j = 0; j < NUM_INDICATOR_OUTCOMES; j++)
			for(int k = 0; k < NUM_CLASSIFICATIONS; k++)
				model[i][j][k] /= denominator;

	/* Normalize outcome vector */
	for(int i = 0; i < NUM_CLASSIFICATIONS; i++)
		outcomeVector[i] /= denominator;
}

void initModel(vector<double **> model, bool isMAP, int numVariables)
{
	for (int i = 0; i < numVariables; i++)
		for(int j = 0; j < NUM_INDICATOR_OUTCOMES; j++)
			for(int k = 0; k < NUM_CLASSIFICATIONS; k++)
				model[i][j][k] = isMAP ? 1 : 0;
}

/* free memory */
void cleanupModel(vector<double **> model, int numVariables)
{
	for(int i = 0; i < numVariables; i++)
	{
		delete [] model[i][0];
		delete [] model[i];
	}
}

/* set array to whatever value */
void initArray(double *arr, int numElem, int value)
{
	for(int i = 0; i < numElem; i++) arr[i] = value;
}

/* train the model using naive bayesian classificatoin */
void trainModel(bool isMAP, vector<double **>model, double *outcomeVector, int numVariables, ifstream &file)
{
	int numVectors;
	file >> numVectors;
	
	initModel(model, isMAP, numVariables);
	initArray(outcomeVector, NUM_CLASSIFICATIONS, 0);
	readModel(model, numVariables, numVectors, file, outcomeVector);

	int denominator = isMAP ? numVectors + NUM_INDICATOR_OUTCOMES*NUM_CLASSIFICATIONS : numVectors;
	normalizeVectors(model, outcomeVector, numVariables, denominator);
}

int getMax(double *arr, int size)
{
	int maxIndex = 0;
	for (int i = 0; i < size; i++)
		if(arr[i] > arr[maxIndex]) maxIndex = i;
	return maxIndex;
}

void calculateProbabilities(vector<double **>model, double *outcomeVector, double *probability, int *currVector, int numVariables)
{
	for(int j = 0; j < NUM_CLASSIFICATIONS; j++) // get the probability for this classification
	{
		for(int k = 0; k < numVariables; k++) // given these indicators, calculate the naive bayes probability
			probability[j] += log(model[k][currVector[k]][j] / outcomeVector[j]); // use logs to prevent underflow
		probability[j] += log(outcomeVector[j]);
	}
}

void testModel(vector<double **>model, double *outcomeVector, ifstream &file, double *numTestedPerClass, double *numCorrectPerClass)
{
	int numVariables, numVectors; 
	file >> numVariables >> numVectors;
	
	int numCorrect = 0;
	double probability[NUM_CLASSIFICATIONS];
	int *currVector = new int[numVariables];

	for(int i = 0; i < numVectors; i++) // for each vector
	{
		initArray(probability, NUM_CLASSIFICATIONS, 1);

		/* read in the vector */
		for(int j = 0; j < numVariables; j++)
			file >> currVector[j];
		int actualResult = getResult(file);
		numTestedPerClass[actualResult]++;

		/* calculate probabilities */
		calculateProbabilities(model, outcomeVector, probability, currVector, numVariables);

		/* calculate and test result */
		int myResult = getMax(probability, NUM_CLASSIFICATIONS);
		if(myResult == actualResult) numCorrectPerClass[actualResult]++;
	}

	delete []currVector;
}
void printResults(double *numTestedPerClass, double *numCorrectPerClass)
{
	double totalTested = 0;
	double totalCorrect = 0;
	
	for (int i = 0; i < NUM_CLASSIFICATIONS; i++)
	{
		cout << "Class " << i << ": tested " << numTestedPerClass[i] << ", correctly classified " << numCorrectPerClass[i] << "." << endl;
		
		totalTested += numTestedPerClass[i];
		totalCorrect += numCorrectPerClass[i];
	}
	
	cout << "Overall: tested " << totalTested << ", correctly classified " << totalCorrect << "." << endl;
	cout << "Accuracy = " << totalCorrect/totalTested << endl << endl;
}

void runTest(const char *train, const char *test, bool isMAP)
{
	ifstream trainFile(train);
	ifstream testFile(test);

	/* setup */
	double outcomeVector[NUM_CLASSIFICATIONS];
	double numTestedPerClass[NUM_CLASSIFICATIONS], numCorrectPerClass[NUM_CLASSIFICATIONS];
	initArray(numTestedPerClass, NUM_CLASSIFICATIONS, 0); initArray(numCorrectPerClass, NUM_CLASSIFICATIONS, 0);
	int numVariables;
	trainFile >> numVariables;
	vector<double **> model = setupModel(numVariables);
	
	/* train and test model */
	trainModel(isMAP, model, outcomeVector, numVariables, trainFile);
	testModel(model, outcomeVector, testFile, numTestedPerClass, numCorrectPerClass);

	
	/* print out results */	
	string modelType = isMAP ? "Laplace estimation" : "MLE";
	cout << "For " << test << " on " << modelType << ":" << endl;
	printResults(numTestedPerClass, numCorrectPerClass);

	 /* cleanup */
	 trainFile.close();
	 testFile.close();
	 cleanupModel(model, numVariables);
}

int main()
{
	/* simple on MLE */
	runTest("datasets/simple-train.txt", "datasets/simple-test.txt", IS_MLE);
	/* simple on Laplace */
	runTest("datasets/simple-train.txt", "datasets/simple-test.txt", IS_MAP);

	/* vote on MLE */
	runTest("datasets/vote-train.txt", "datasets/vote-test.txt", IS_MLE);
	/* vote on Laplace */
	runTest("datasets/vote-train.txt", "datasets/vote-test.txt", IS_MAP);

	/* heart on MLE */
	runTest("datasets/heart-train.txt", "datasets/heart-test.txt", IS_MLE);
	/* heart on Laplace */
	runTest("datasets/heart-train.txt", "datasets/heart-test.txt", IS_MAP);

	getchar(); // prevent command window from closing
	return 0;
}
