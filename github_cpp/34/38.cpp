// ==================================================
//
// Author: GIFTED-BOY
// Email: 120138380@qq.com
// Create Time: 2018.4.21
// Version: v1.0
//
// ==================================================

#include "NaiveBayes.h"
#include <unordered_set>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <time.h>
#include <iostream>

NaiveBayes::NaiveBayes(vector<vector<string> > x, vector<int> y, int m, int c) : dataSet(x), labels(y), sampleNum(m), classKindNum(c)
{
	classProb = vector<double>(c);
	vocabList = getVocabList();
	vocabNum = vocabList.size();
	wordsProb = vector<vector<double> >(c, vector<double>(vocabNum));
}

void NaiveBayes::train()
{
	calcClassProb();
	calcWordsProb(getSetOfWordsMatrix());
}

int NaiveBayes::classify(vector<string> x) { return getClass(x, x.size()); }

vector<string> NaiveBayes::getVocabList()
{
	unordered_set<string> vocabSet;
	for (int i = 0; i < sampleNum; i++)
	{
		int n = dataSet[i].size();
		for (int j = 0; j < n; j++)
			if (!vocabSet.count(dataSet[i][j])) vocabSet.insert(dataSet[i][j]);
	}

	vector<string> vocabList(vocabSet.size());
	copy(vocabSet.begin(), vocabSet.end(), vocabList.begin());

	return vocabList;
}

vector<int> NaiveBayes::getSetOfWordsVector(vector<string> x, int n)
{
	vector<int> setOfWordsVector(vocabNum, 0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < vocabNum; j++)
		{
			if (x[i] == vocabList[j])
			{
				setOfWordsVector[j] = 1;
				break;
			}
		}
	}
	return setOfWordsVector;
}

vector<vector<int> > NaiveBayes::getSetOfWordsMatrix()
{
	vector<vector<int> > setOfWordsMatrix(sampleNum, vector<int>(vocabNum));
	for (int i = 0; i < sampleNum; i++) setOfWordsMatrix[i] = getSetOfWordsVector(dataSet[i], dataSet[i].size());
	return setOfWordsMatrix;
}

void NaiveBayes::calcClassProb()
{
	vector<int> classNum(classKindNum, 0);
	for (int i = 0; i < sampleNum; i++) classNum[labels[i]]++;
	for (int i = 0; i < classKindNum; i++) classProb[i] = (double) classNum[i] / sampleNum;
}

void NaiveBayes::calcWordsProb(vector<vector<int> > setOfWordsMatrix)
{
	vector<vector<int> > wordsNum(classKindNum, vector<int>(vocabNum, 1));
	vector<int> wordsTotalNum(classKindNum, 2);
	for (int i = 0; i < sampleNum; i++)
	{
		for (int j = 0; j < vocabNum; j++)
		{
			wordsNum[labels[i]][j] += setOfWordsMatrix[i][j];
			wordsTotalNum[labels[i]] += setOfWordsMatrix[i][j];
		}
	}

	for (int i = 0; i < classKindNum; i++)
		for (int j = 0; j < vocabNum; j++) wordsProb[i][j] = log((double) wordsNum[i][j] / wordsTotalNum[i]);
}

int NaiveBayes::getClass(vector<string> x, int n)
{
	vector<int> setOfWordsVector = getSetOfWordsVector(x, n);
	double maxProb = -LDBL_MAX;
	int cls = 0;
	for (int i = 0; i < classKindNum; i++)
	{
		double p = 0.0;
		for (int j = 0; j < vocabNum; j++) p += setOfWordsVector[j] * wordsProb[i][j];
		p += log(classProb[i]);
		if (p > maxProb)
		{
			maxProb = p;
			cls = i;
		}
	}
	return cls;
}




vector<string> getWordsVector(string s)
{
	vector<string> wordsVector;
	int left = 0, size = s.size(), right;
	for (right = 0; right < size; right++)
	{
		if (!((s[right] >= 'a' && s[right] <= 'z') || (s[right] >= 'A' && s[right] <= 'Z') || (s[right] >= '0' && s[right] <= '9')))
		{
			if (right - left > 2) wordsVector.push_back(s.substr(left, right - left));
			left = right + 1;
		}
	}
	if (right - left > 2) wordsVector.push_back(s.substr(left, size - left));
	return wordsVector;
}

string getSample(string fileName)
{
	string sample = "";
	ifstream in(fileName);
	string str;
	while (getline(in, str))
	{
		//cout << str << endl;
		sample += str + " ";
	}
	in.close();
	return sample;
}

void getDataSet_NB(vector<vector<string> > &dataSet, vector<int> &labels)
{
	for (int i = 1; i <= 25; i++)
	{
		string fileName = to_string(i) + ".txt";
		dataSet.push_back(getWordsVector(getSample("dataset/Ch04/spam/" + fileName)));
		labels.push_back(1);
		dataSet.push_back(getWordsVector(getSample("dataset/Ch04/ham/" + fileName)));
		labels.push_back(0);
	}
}

void NBTest()
{
	srand((unsigned) time(NULL));
	vector<vector<string> > dataSet;
	vector<int> labels;
	getDataSet_NB(dataSet, labels);

	int sampleNum = dataSet.size();
	int testingNum = 10;
	int testTimes = 10;
	double totalCorretRate = 0.0;
	for (int i = 0; i < testTimes; i++)
	{
		cout << "round " << i << ":" << endl;
		vector<vector<string> > trainingDataSet = dataSet;
		vector<int> trainingLabels = labels;
		vector<vector<string> > testingDataSet;
		vector<int> testingLabels;
		for (int i = 0; i < testingNum; i++)
		{
			int randIndex = rand() % (sampleNum - i);
			testingDataSet.push_back(trainingDataSet[randIndex]);
			testingLabels.push_back(trainingLabels[randIndex]);
			trainingDataSet.erase(trainingDataSet.begin() + randIndex);
			trainingLabels.erase(trainingLabels.begin() + randIndex);
		}
		NaiveBayes nb(trainingDataSet, trainingLabels, trainingDataSet.size(), 2);
		nb.train();
		int correctNum = 0;
		for (int j = 0; j < testingNum; j++)
		{
			int cls = nb.classify(testingDataSet[j]);
			if (cls == testingLabels[j]) correctNum++;
			cout << "nb: " << cls << "\treal: " << testingLabels[j] << endl;
		}
		cout << "testing num: " << testingNum << endl;
		cout << "correct num: " << correctNum << endl;
		cout << "correct rate: " << (double) correctNum / testingNum << endl << endl;
		totalCorretRate += (double) correctNum / testingNum;
	}
	cout << "avg correct rate: " << totalCorretRate / testTimes << endl;
}