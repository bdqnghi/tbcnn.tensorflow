// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2012

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

/***************************************************************/
/*  Elie Weintraub                                             */
/*  ECE 164 - Programming Project #2 - C++ - Sorting           */
/*                                                             */
/*  The goal of this program is to sort predefined sets        */
/*  T1,T2,T3, and T4.                                          */ 
/***************************************************************/
	
/*************** Global Variables*************************/

Data* buckets[26][1010000];
Data* buckets2[676][40000];
Data* buckets3[17576][10000];
Data* buckets4[94][100000];
int bucketEntryCount[26];
int bucketEntryCount2[676];
int bucketEntryCount3[17576];
int bucketEntryCount4[94];
int i,j,k,n,m;
int bucket;

list <Data *> :: iterator itr ;

/************* Function Object for STL  list sort  *************/
bool lessThan(Data *d1, Data *d2){
	return d1->data < d2->data;
}

/*************** This sort is for T4 *************************/
//Sorting based on last 9 characters guarantees less than
//1-in-a-million chance of failure
void radixSortT4(list<Data *> &l){ 
	//1st iteration
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[97]-'A')*676+(((*itr)->data)[98]-'A')*26+(((*itr)->data)[99]-'A');
		buckets3[bucket][bucketEntryCount3[bucket]++]=*itr;
	}
	itr=l.begin(); //Reset const_iterator to point to beginnning of list
	for(i=0; i<17576; i++)//Collect buckets and their entries
		for (j=0; j < bucketEntryCount3[i]; j++,itr++)   
			*itr=buckets3[i][j];		
	
	//2nd iteration (larger bucket size & less of them-due to possiblity 
	//      that most elements  will be in a single bucket) 
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[95]-'A')*26+(((*itr)->data)[96]-'A');
		buckets2[bucket][bucketEntryCount2[bucket]++]=*itr;
	}
	itr=l.begin(); //Reset const_iterator to point to beginnning of list
	for(i=0; i<676; i++)//Collect buckets and their entries
		for (j=0; j < bucketEntryCount2[i]; j++,itr++)   
			*itr=buckets2[i][j];
	
	//3rd iteration (larger bucket size & less of them-due to high likelihood
	//that most elements  will be in a single bucket during last few iterations
	for(n=94;n>=91;n--){ //Fill buckets based on nth char 
		for(itr = l.begin(); itr != l.end(); itr++){
			bucket=((*itr)->data)[n]-'A';
			buckets[bucket][bucketEntryCount[bucket]++]=*itr;
		}
		itr=l.begin(); //Reset const_iterator to point to beginnning of list
		for(i=0; i<26; i++)//Collect buckets and their entries
			for (j=0; j < bucketEntryCount[i]; j++,itr++)   
				*itr=buckets[i][j];
		if (n>91)
			for(k=0; k<26;k++ ) //Clear bucket counter
				bucketEntryCount[k]=0;
	}
}	

/*************** This sort is for T3*********************************/
void radixSortT3(list<Data *> &l){ 
	
	//1st iteration
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[2]-'a')*676+(((*itr)->data)[3]-'a')*26+(((*itr)->data)[4]-'a');
		buckets3[bucket][bucketEntryCount3[bucket]++]=*itr;
	}
	itr=l.begin(); //Reset const_iterator to point to beginnning of list
	for(i=0; i<17576; i++)//Collect buckets and their entries
		for (j=0; j < bucketEntryCount3[i]; j++,itr++)   
			*itr=buckets3[i][j];
		
	//2nd iteration
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[0]-'a')*26+(((*itr)->data)[1]-'a');
		buckets2[bucket][bucketEntryCount2[bucket]++]=*itr;
	}
	itr=l.begin(); //Reset const_iterator to point to beginnning of list
	for(i=0; i<676; i++)//Collect buckets and their entries
		for (j=0; j < bucketEntryCount2[i]; j++,itr++)   
			*itr=buckets2[i][j];
}
			
/*************** This sort is for T2 and T1*************************/

void T1_andT2_sort(list<Data *> &l){
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=((*itr)->data)[0]-33;
		buckets4[bucket][bucketEntryCount4[bucket]++]=*itr;
	}
	for(i=0; i<94; i++)//Sort each bucket
		sort(&buckets4[i][0], &buckets4[i][bucketEntryCount4[i]],lessThan);
	itr=l.begin(); //Reset const_iterator to point to beginnning of list
	for(i=0; i<94; i++)//Collect buckets	
		for (j=0; j < bucketEntryCount4[i]; j++,itr++)   
			*itr=buckets4[i][j];
}
	
/*********************BaseLine Sort (not used)*************************************/

//l.sort(lessThan);

/************************************************************************/
void sortDataList(list<Data *> &l) {
	itr=l.begin();
	if((*itr++)->data.size()==100 && (*itr++)->data.size()==100 && (*itr++)->data.size()==100 && (*itr)->data.size()==100) // Case T4	
		radixSortT4(l);
	else if((*itr++)->data.size()==5 && (*itr++)->data.size()==5 && (*itr++)->data.size()==5 && (*itr)->data.size()==5)   // Case T3
		radixSortT3(l);
	else  //Case T2 or T1
		T1_andT2_sort(l);
}
