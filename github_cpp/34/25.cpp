// reading a text file
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//Loads data from CSV file to arrays
void LoadData(string fileName,vector<vector<string> > &d)
{
	string line;

	ifstream myfile (fileName.c_str());

	if (myfile.is_open())
	{
		getline (myfile,line) ; //skip first line
		int row =0;

		while ( getline (myfile,line) )
		{
			std::vector<std::string> elems;
		  std::vector<std::string> x = split(line, ',',elems);

		  d.push_back(x);

		  row++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	}




 vector<string> retrieveLabels (vector<vector<string> > trainingData){

    //the function goes to the last column and loop through all the values and find distinct class values and return a vector

  std::vector<string> labels;
  bool find = false;
  int col = trainingData[0].size();
  for (int i = 0; i < trainingData.size(); i++){
  	string el = trainingData[i][col-1];

   if (std::find(labels.begin(), labels.end(), el) != labels.end()) //using loop through the existing labels to check whether the new value is unique or not
   {
       find = true;
    }

    else {
   labels.push_back(el);
   find = false;
   }

  }

return labels;

}


float computePrior (vector<vector<string> > trainingData, string classLabel){

    //computePrior calculates the prior probability of the classLabel. It is simple; Just calculate the probability of the classLabel

	int class_var = 0;
	int col = trainingData[0].size();
    for (int i = 0; i < trainingData.size(); i++){
  	string el = trainingData[i][col-1];
  	if (el == classLabel)
  		class_var++;
  }

  return (float)class_var/(float)trainingData.size();

}

float computeConditional (vector<vector<string> > trainingData, int colIndex, string colValue, string classLabel){

    //calculate the condition prob. The formula is P(A|B) = P (A AND B) / P(B)

 	int class_val = 0;
    int cl = 0;//one counter of class value
      //one counter attribute value
 	int col = trainingData[0].size();

   for (int i = 0; i < trainingData.size(); i++) {

   	string attribute = trainingData[i][colIndex];
   	string label = trainingData[i][col-1];
   	  if (label == classLabel){

        cl++;
   	  }
   	  if (attribute == colValue && label == classLabel){ // here we are ANDing the prob P(A AND C)

   	  	class_val++;

   	  }
   }

  return (float) class_val / (float)cl; // P (A AND C) / P(C)
 }


float computePosterior(vector<vector<string> > &trainingData, vector <string> record  ,string classLabel){

    //calculate Posterior probability. PRIOR PROBABILITY * Conditional. Later this will be used to predict the class through comparison

	float prob = 1;
	for (int i = 0; i < record.size()-1; i++){ // minus 1 because we don't want to consider the last row having classes
		prob = prob * computeConditional (trainingData, i, record[i], classLabel);
	}
	return computePrior(trainingData, classLabel) * prob;
}



string Predicted(vector<vector<string> > &trainingData, vector <string> record ){

 //Prediction of class on the basis of comparison comparison
   vector<string> labels;
   float max_post = 0.0;
   string max_lab;
   labels = retrieveLabels(trainingData); //using retrieveLabels to retrieve all the labels in order to compute Posterior with respect to every label. The compare and return the one with the max prob.

for(std::vector<int>::size_type i = 0; i != labels.size(); i++) {
   if (computePosterior(trainingData, record, labels[i]) > max_post) {
     max_post = computePosterior(trainingData, record, labels[i]);
     max_lab = labels[i];
   }
}
return max_lab;
}


void model (vector<vector<string> > &trainingData,vector<vector<string> > &testData, int &accuracy, int &precision,int &recall) {

  //In this code, have to apply the trained strategy onto test data.  We calculate the actual value using
  // testData. Test data's last column gives the actual value. Furthermore, using Prediction we can return the class label, which is our predicted value
  //we compare both of them in order to see whether is e-positive, e-negative, p-positive, p-negative as mentioned in the lecture slides.


  string actual, predicted;
  int ep =0; //e-positive
  int en =0; //e-negative
  int pp =0; //p-positive
  int pn =0; //p-negative


 for (int j = 0; j < trainingData.size(); j++){

     predicted = Predicted(trainingData, testData[j]);
     actual = testData[j][testData[0].size()-1];

       if (predicted == "e" && actual = "e"){
            ep++;
        }
        else if (predicted == "e" && actual = "p"){
            en++;
        }
        else if (predicted == "p" && actual = "p"){
            pp++;
        }
        else if (predicted == "p" && actual = "e"){
            pn++;
        }

 }
accuracy = ep + pp / (ep+en+pp+pn);
precision = ep / (ep + en);
recall = ep / (ep + pn);

}





