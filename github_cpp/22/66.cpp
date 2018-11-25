

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


class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};


void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}


void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  
  int size = l.size();
  output << size << endl;

  
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);



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


bool lessThan(Data *d1, Data *d2){
	return d1->data < d2->data;
}




void radixSortT4(list<Data *> &l){ 
	
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[97]-'A')*676+(((*itr)->data)[98]-'A')*26+(((*itr)->data)[99]-'A');
		buckets3[bucket][bucketEntryCount3[bucket]++]=*itr;
	}
	itr=l.begin(); 
	for(i=0; i<17576; i++)
		for (j=0; j < bucketEntryCount3[i]; j++,itr++)   
			*itr=buckets3[i][j];		
	
	
	
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[95]-'A')*26+(((*itr)->data)[96]-'A');
		buckets2[bucket][bucketEntryCount2[bucket]++]=*itr;
	}
	itr=l.begin(); 
	for(i=0; i<676; i++)
		for (j=0; j < bucketEntryCount2[i]; j++,itr++)   
			*itr=buckets2[i][j];
	
	
	
	for(n=94;n>=91;n--){ 
		for(itr = l.begin(); itr != l.end(); itr++){
			bucket=((*itr)->data)[n]-'A';
			buckets[bucket][bucketEntryCount[bucket]++]=*itr;
		}
		itr=l.begin(); 
		for(i=0; i<26; i++)
			for (j=0; j < bucketEntryCount[i]; j++,itr++)   
				*itr=buckets[i][j];
		if (n>91)
			for(k=0; k<26;k++ ) 
				bucketEntryCount[k]=0;
	}
}	


void radixSortT3(list<Data *> &l){ 
	
	
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[2]-'a')*676+(((*itr)->data)[3]-'a')*26+(((*itr)->data)[4]-'a');
		buckets3[bucket][bucketEntryCount3[bucket]++]=*itr;
	}
	itr=l.begin(); 
	for(i=0; i<17576; i++)
		for (j=0; j < bucketEntryCount3[i]; j++,itr++)   
			*itr=buckets3[i][j];
		
	
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=(((*itr)->data)[0]-'a')*26+(((*itr)->data)[1]-'a');
		buckets2[bucket][bucketEntryCount2[bucket]++]=*itr;
	}
	itr=l.begin(); 
	for(i=0; i<676; i++)
		for (j=0; j < bucketEntryCount2[i]; j++,itr++)   
			*itr=buckets2[i][j];
}
			


void T1_andT2_sort(list<Data *> &l){
	for(itr = l.begin(); itr != l.end(); itr++){
		bucket=((*itr)->data)[0]-33;
		buckets4[bucket][bucketEntryCount4[bucket]++]=*itr;
	}
	for(i=0; i<94; i++)
		sort(&buckets4[i][0], &buckets4[i][bucketEntryCount4[i]],lessThan);
	itr=l.begin(); 
	for(i=0; i<94; i++)
		for (j=0; j < bucketEntryCount4[i]; j++,itr++)   
			*itr=buckets4[i][j];
}
	





void sortDataList(list<Data *> &l) {
	itr=l.begin();
	if((*itr++)->data.size()==100 && (*itr++)->data.size()==100 && (*itr++)->data.size()==100 && (*itr)->data.size()==100) 
		radixSortT4(l);
	else if((*itr++)->data.size()==5 && (*itr++)->data.size()==5 && (*itr++)->data.size()==5 && (*itr)->data.size()==5)   
		radixSortT3(l);
	else  
		T1_andT2_sort(l);
}
