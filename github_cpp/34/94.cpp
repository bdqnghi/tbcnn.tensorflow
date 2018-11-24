/*
 * @file naive_bayes.cpp
 * @author Anuraj Kanodia, Stuti Sabharwal
 *
 * Implementation of the Naive Bayes classifier for
 * face recognition.
 *
 * C++11 standard required.
 *
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> trainingLabels; //Vector to store the training labels
vector<int> testingLabels; //Vector to store the Testing labels
int trainingDataset[2][70][60] = {0}; //3-D array to store the frequencies of '#' occurrences at each pixel
int frequency[2] = {0};	//Frequency array to store the frequency of Face and Non Face images in the Training set

void getTrainingLabels() {	//Function to read the Training labels
	int i;
	string s;
	int temp;
	ifstream ifs ("facedatatrainlabels", ifstream::in); //Open the file
	
	for(i=0; i<451; i++) {
		getline(ifs, s);
		temp = stoi(s);
		
		if(!temp)				//Storing frequency
			frequency[0]++;
		else
			frequency[1]++;
				
		trainingLabels.push_back(temp); 	
	}
	
	ifs.close();
	return;
}

void getTestingLabels() {	//Function to read the Testing Labels
	int i;
	string s;
	ifstream ifs ("facedatatestlabels", ifstream::in);	//Open the file
	
	for(i=0; i<150; i++) {
		getline(ifs, s);
		testingLabels.push_back(stoi(s)); 	
	}
	
	ifs.close();
	return;
}


void getTrainingData() {	//Read the images and store frequency of '#' at each pixel 
	
	int i,j,k;
	string s;
	ifstream ifs ("facedatatrain", ifstream::in);
	
	for(i=0; i<trainingLabels.size(); i++) {
		for(j=0; j<70; j++) {
			getline(ifs, s);
			for(k=0; k<s.length(); k++) {
				if(s[k] == '#')
					trainingDataset[trainingLabels[i]][j][k]++;		
			}
		}
	}	
	
	ifs.close();
	return; 
}


void testModel() {
	int i,j,k,l;
	int output;
	int temp[70][60];	//Temp array to store pixel values of Test Image
	long double numerator = 0.0;	
	long double denominator = 0.0;
	long double max, product;
	double correct = 0.0, incorrect = 0.0;	//Number of Correct and Incorrect classifications
	double accuracy;	//Stores the accuracy
	string s;
	int constant=1;	//Smoothing constant used is 1
	int TP=0,TN=0,FP=0,FN=0;	//Stores the True-Positives, True-Negatives, False-Positives, False-Negatives
	ifstream ifs ("facedatatest", ifstream::in);
	
	
	for(i=0; i<testingLabels.size(); i++) {
		for(j=0; j<70; j++) {
			getline(ifs, s);
			for(k=0; k<s.length(); k++) {	
				if(s[k] == '#')
					temp[j][k] = 1;
				else
					temp[j][k] = 0;	

			}
		}
		
		max = INT_MIN; output = 0;	//Initializing max and output
		for(l=0; l<2; l++) {	//For each Output value, 0 and 1
			long double sum = 0.0;
			for(j=0; j<70; j++) {
				for(k=0; k<60; k++) {		//Calculating Probabilities for each pixel
					if(temp[j][k] == 0) 	
            			numerator = frequency[l]-trainingDataset[l][j][k]+constant;	//If it is a blank
                     else 	
                     	numerator = trainingDataset[l][j][k]+constant;	//If it is a '#'
                     
                     denominator = frequency[l]+constant+1;
                    
                    numerator=log(numerator);
                    denominator=log(denominator);
                    long double fig=numerator-denominator;	
                    	//fig=log(fig);	//Taking natural log 
                    sum = sum +fig ;             
				}
			}
			
			double fig1=log(frequency[l]);
			fig1=fig1-log(451.0);	//Probability of Output	
			//fig1=log(fig1);
			sum = sum + fig1;
			//sum=exp(sum);
			
			if(sum > max) {
				max = sum; 	//Setting the maximum value
				output = l;	//Output either 0 or 1, for which we get the maximum value
			}
		}
		
		if(testingLabels[i] == output) {	//If the testing label is the same as predicted output then increase number of correct outputs
			correct++;
			if(testingLabels[i] == 1)
				TP++;
			else 
				TN++;
		}
		else {
			incorrect++;
			if(testingLabels[i] == 0) {
				cout<<"Test input #"<<i+1<<" Actual: No face; Predicted Output: Face"<<endl;
				FP++;
			}
			else { 	
				cout<<"Test input #"<<i+1<<" Actual: Face; Predicted Output: No Face"<<endl;
				FN++;
			}
		}
	}

	ifs.close();
	accuracy = (correct/(correct+incorrect))*100.0; 
	cout << "accuracy of the NB classifier is: " << accuracy << "%" << endl;	
	cout<<"False Negative:"<<FN<<" False Positive:"<<FP<<" True Negative:"<<TN<<" True Positive:"<<TP<<endl;	
	return;
}


int main() {
	cout<<log(451.0)<<endl;
	getTrainingLabels();
	getTrainingData();
	getTestingLabels();
	testModel();
	
	return 0;
}
