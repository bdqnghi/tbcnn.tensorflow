// Ian Michael Terry
// CIS 4930: Data Mining
// 4-4-2016
//
// Implementation of a Naive Bayes classifier. Requires two inputs, 
// a training file and a test file, in that order.
//


#include <fstream>
#include <iostream> 
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <set>
#include <iterator>

using namespace std;

int main(int argc, char *argv[]){                              // Gets input filenames from user
							       // and checks for error
	if(argc != 3){
		cout << "Please enter two arguments, a training file and a test file" << '\n';
		cout << argc;
		return 1;
	}

	ifstream trainStream (argv[1]);
	ifstream testStream (argv[2]);
	
	if(!trainStream.is_open()){
		cout<< "Could not open training file." << '\n';
		return 1;
	}else if(!testStream.is_open()){
		cout << "Could not open testing file." << '\n';
		return 1;
	}

	//vector<string> train_lines;
	//vector<string> test_lines;
	string line;
	unordered_map<int, int> trainMap;
	vector<unordered_map<int, int>> trainMapVector;
	unordered_map<int, int> testMap;	
	vector<unordered_map<int, int>> testMapVector;
	int highestKey=0;
	unordered_map<int, set<int>> possibleAttributeValues;

	while(getline(trainStream, line)){			// loads testing and training data into two vectors
								// of maps, with attributes mapped to their values
		
		istringstream streamer;
		streamer.str(line);
		int booleanVal, tempVal1, tempVal2;
		char tempChar;

		streamer >> booleanVal;
		trainMap[0]=booleanVal;
		while(streamer >> tempVal1 >> tempChar >> tempVal2){
			trainMap[tempVal1] = tempVal2;
			if(tempVal1>highestKey){
				highestKey=tempVal1;
			}					// set of possible values for each attribute is 
								// created for later use
			possibleAttributeValues[tempVal1].insert(tempVal2);
		}

		trainMapVector.push_back(trainMap);
		trainMap.clear();
		//train_lines.push_back(line);
	
	}
	trainStream.close();

	while(getline(testStream, line)){
        
		
		istringstream streamer;
		streamer.str(line);
		int booleanVal, tempVal1, tempVal2;
		char tempChar;

		streamer >> booleanVal;
		testMap[0]=booleanVal;
		while(streamer >> tempVal1 >> tempChar >> tempVal2){
			testMap[tempVal1] = tempVal2;
			if(tempVal1>highestKey){
				highestKey=tempVal1;
			}
		}

		testMapVector.push_back(testMap);
		testMap.clear();
		//test_lines.push_back(line);
        }
        testStream.close();
								// nested maps mapping an attribute to a map of its 
								// possible values, which are mapped to counts of 
								// occurrences of their value
								
	unordered_map<int, unordered_map<int, double>> positiveMap;
	unordered_map<int, unordered_map<int, double>> negativeMap;
	
	
	for(int i = 1; i <= highestKey; i++){			// sets all counts to 0
		set<int>::iterator itr;
		for(itr = possibleAttributeValues[i].begin(); itr != possibleAttributeValues[i].end(); ++itr){
			positiveMap[i][*itr]=0;
			negativeMap[i][*itr]=0;
		
		}
	}
	

	int positiveCount = 0;					// counts occurrences of attributes so that their 
	int negativeCount = 0;					// probabilities can be calculated
	int totalCount = 0;
	for(unsigned int i = 0; i < trainMapVector.size(); i++){
		if(trainMapVector[i].count(0) != 0) {
			if(trainMapVector[i][0]==-1){
				negativeCount++;
				for(int j=1; j <= highestKey; ++j){
					if(trainMapVector[i].count(j)!=0){
						negativeMap[j][trainMapVector[i][j]]++;
					}
				}
			
			}else{
				positiveCount++;	
				for(int j=1; j <= highestKey; ++j){
					if(trainMapVector[i].count(j)!=0){
						positiveMap[j][trainMapVector[i][j]]++;
					}
				}
			}
			totalCount++;
		}
	
	}

	int trainTruePos=0;
	int trainFalseNeg=0;
	int trainFalsePos=0;
	int trainTrueNeg=0;
	int testTruePos=0;
	int testFalseNeg=0;
	int testFalsePos=0;
	int testTrueNeg=0;

	double positiveLikelihood = 1.0;
	double negativeLikelihood = 1.0;			// likelihoods of positive and negative occurences
								// are calculated, given the attribute values

	for(unsigned int i=0; i<trainMapVector.size(); ++i){
		for(int j=1; j<=highestKey; ++j){
		
			if(trainMapVector[i].count(j)!=0){
				
				positiveLikelihood *= positiveMap[j][trainMapVector[i][j]];
				positiveLikelihood /= positiveCount;

				negativeLikelihood *=negativeMap[j][trainMapVector[i][j]];
				negativeLikelihood /= negativeCount;

			}
		
		}

		//int prediction;
		int trueValue=trainMapVector[i][0];
		
		if(negativeLikelihood> positiveLikelihood){	// comparison to true values to evalueate 
								// the classifier
			//prediction=-1;
	
			if(trueValue==-1){
				trainTrueNeg++;
			}else{
				trainFalseNeg++;
			}
		}else{ 
			//prediction=1;

			if(trueValue==1){
				trainTruePos++;
			}else{
				trainFalsePos++;
			}
		}

		positiveLikelihood=1.0;
		negativeLikelihood=1.0;
	
	}


	for(unsigned int i=0; i<testMapVector.size(); ++i){
		for(int j=1; j<=highestKey; ++j){
		
			if(testMapVector[i].count(j)!=0){
				
				positiveLikelihood *= positiveMap[j][testMapVector[i][j]];
				positiveLikelihood /= positiveCount;

				negativeLikelihood *=negativeMap[j][testMapVector[i][j]];
				negativeLikelihood /= negativeCount;

			}
		
		}

		//int prediction;
		int trueValue=testMapVector[i][0];
		
		if(negativeLikelihood> positiveLikelihood){
			//prediction=-1;
	
			if(trueValue==-1){
				testTrueNeg++;
			}else{
				testFalseNeg++;
			}
		}else{ 
			//prediction=1;

			if(trueValue==1){
				testTruePos++;
			}else{
				testFalsePos++;
			}
		}

		positiveLikelihood=1.0;
		negativeLikelihood=1.0;
	
	}

	//cout << "positive count: "  <<  positiveCount << '\n' << "negative Count: " << negativeCount << '\n' << "total count: " << totalCount << '\n';

	
	//cout <<"trainTruePos: " << trainTruePos << '\n' << "trainFalsePos: " << trainFalsePos << '\n' << "trainTrueNeg: " << trainTrueNeg << '\n' << "train FalseNeg: " << trainFalseNeg << '\n';
	
	cout << trainTruePos << ' ' << trainFalseNeg << ' ' << trainFalsePos << ' ' << trainTrueNeg << '\n';
	cout << testTruePos << ' ' << testFalseNeg << ' ' << testFalsePos << ' ' << testTrueNeg << '\n';

}
