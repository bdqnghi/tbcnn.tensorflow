#include <GenericClassifierWeka.h>
using namespace std;	

/*
* execute: g++ NaiveBayesClassification.cpp  -L${$JAVA_HOME/jre/lib/amd64/server/} -ljvm -o executable
* ./executable
*/
int main(int n, char *argv[]) {
	
	GenericClassifierWeka classifier;
	
	char modelFilePath[] = "NaiveBayes-semeion.model";
	char propertiesFilePath[] = "semeion.properties";
	int indexOfClass = 257;


	try{
		classifier.loadClassifier(modelFilePath,propertiesFilePath,indexOfClass);
		
		double p1[] = {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0};
		int sizeOfVector = sizeof(p1)/sizeof(*p1);
		double classOfInstance = classifier.classify(p1,sizeOfVector);
		cout << "Class of instance 1: " << classOfInstance << endl;

		
		double p2[] = {0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0};
		sizeOfVector = sizeof(p2)/sizeof(*p2);
		vector<double> a2(p2, p2+sizeOfVector);
		classifier.classify(a2);
		classOfInstance = classifier.classify(a2);
		cout << "Class of instance 2: " << classOfInstance << endl;
		
		return -1;
	}catch(const char* ErrorMsg){
		cerr << ErrorMsg << endl;
	}
}


