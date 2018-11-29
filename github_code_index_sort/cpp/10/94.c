/************ P R O J E C T ****************
Course : TCP2101 Algorithm Design And Analysis
Session: Trimester 2, 2014/15
********************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "timer.h"
using namespace std;

void print(int* arr, int size)
{
  for(int i=0;i<size;i++)
    cout << arr[i] << " ";
  cout << endl;
}



void generateDescendingOrder(vector<int>& vec, int* arr, int inputSize)
{
  cout << "Generating numbers from 1 to " << inputSize << " in descending order..." << endl;

  srand(time(NULL));
 
  for(int i = 0; i < inputSize; i++)
    vec.push_back(i+1);
  
  for(int i = 0; i < inputSize; i++)
  {
    arr[i] = vec.back();
    //arr2[i] = vec.back();
    vec.pop_back();
  }

  vector<int>().swap(vec); //a trick to free memory allocation
  cout << "Task completed." <<endl << endl;
}

void generateAscendingOrder(vector<int>& vec, int* arr, int inputSize)
{
  cout << "Generating numbers from 1 to " << inputSize << " in ascending order..." << endl;

  srand(time(NULL));
 
  for(int i = inputSize; i > 0; i--)
    vec.push_back(i);
  
  for(int i = 0; i < inputSize; i++)
  {
    arr[i] = vec.back();
    //arr2[i] = vec.back();
    vec.pop_back();
  }

  vector<int>().swap(vec); //a trick to free memory allocation
  cout << "Task completed." << endl<< endl;
}

void generateUnsortedNumbers(vector<int>& vec, int* arr,int inputSize)
{
  cout << "Generating unsorted numbers from 1 to " << inputSize << "..." << endl;
  srand(time(NULL));

  for(int i = 0; i < inputSize; i++)
    vec.push_back(i+1);
  
  for(int i = 0; i < 10; i++) //sort 10 times 
    random_shuffle (vec.begin(), vec.end());
    
  for(int i = 0; i < inputSize; i++)
  {
    arr[i] = vec.back();
   // arr2[i] = vec.back();
    vec.pop_back();
  }

  vector<int>().swap(vec); //a trick to free memory allocation
  cout << "Task completed." << endl<< endl;
}

bool bucketSort(int* arr, vector<int> b[], int inputSize, int bucketSize, int numOfBucket)
{

  //Fill the buckets
  int num;
  for (int i = 0; i < inputSize; ++i)
  {
    num = (arr[i])/bucketSize;
    b[num].push_back(arr[i]);
   // cout << arr[i] << " is placed into bucket no." << num << "." << endl;
  }
 // cout << endl;

  //Sort buckets
  
  // for(int i = 0; i< b[i].size();i++)
  // {
    // cout << "Bucket no." << i << " contains: " << endl;
    // for (int j = 0; j < b[i].size(); j++)
    // {
      // cout << b[i][j] << ", ";
    // }
    // cout << endl;
  // }
  
  for (int i=0; i<numOfBucket; i++)
  {
    sort(b[i].begin(), b[i].end());
   // cout << "Bucket no." << i << " is sorted." << endl;
  }
  //Combine all buckets into arr
  int index = 0;
  for (int i = 0; i < numOfBucket; i++)
  {
    
      for (int j = 0; j < b[i].size(); j++)
      {
        arr[index++] = b[i][j];
       // cout << b[i][j] << " from bucket no." << i << " is put into array." << endl;
      }
     // cout << endl;
  }
  //cout << endl; 
}

void startBucketSort(int* arr, int inputSize, int max)
{

    double dbucketSize=static_cast<double> (max)/10;
    dbucketSize = dbucketSize + 1;
    int bucketSize = static_cast<int> (dbucketSize); //cout << "Bucket Size : " << bucketSize << endl;
    int numOfBucket=11;
    vector<int> b[numOfBucket];
    
    for(int i = 0; i < numOfBucket; i++)
    {
      b[i].reserve(inputSize/10);
    }

    bucketSort(arr,b,inputSize, bucketSize, numOfBucket); 
    
}

void merge(int* A, int* B, int l, int m, int r)
{
  int i, j;
  for (i = m + 1; i > l; i--)
  {
    B[i-1] = A[i-1];
    //cout << "B[" << i-1 << "] = A[" << i-1 << "] : " << B[i-1] << " = " << A[i-1] << endl; 
  }
    //B[12] = A[12]
    //B[11] = A[11]
    //B[10] = A[10]
    //... B[0] = A[0]
    // i = 0
    
  for (j = m; j < r; j++)
  {
    B[r + m-j] = A[j + 1];
    //cout << "B[" << r+m-j << "] = A[" << j+1 << "] : " << B[r + m-j] << " = " << A[j + 1] << endl;
  }
  //B[24] = A[13]
    //B[23] = A[14]
    //...B[13] = A[24]
    // j = 24
 
 
 // Misch-Schritt
  
  for (int k = l; k <= r; k++)
  {
    //bool test = B[j]<B[i];
 //   cout << "B[" << j << "] < B[" << i << "] : " <<  B[j] << " < " << B[i] << " : " << test << endl;
    if (B[j] < B[i])
    {
        //  cout << " A[k] <= B[j]: A[" <<k << "] = B[" << j << "] :" << A[k] << " = " << B[j] << endl; 
      A[k] = B[j--];

    }
    else
    {
          //cout << " A[k] <= B[i] : A[" << k << "] = B[" << i <<"] :"<< A[k] << " = " << B[i] << endl; 
      A[k] = B[i++];
    
    }
  }
} 

void mergesort(int* A, int* B, int l, int r)
{
 // cout << "Enter mergesort: ";
  // for(int i = 0; i < r-l+1; i++)
    // cout << A[i] << " ";
  // cout << endl;

  if (l < r)
  {
    int m = (r + l) / 2;
    mergesort(A, B, l, m);   
    mergesort(A, B, m + 1, r);
    merge(A, B, l, m, r);
  }
}

void startMergeSort(int* A, int l, int r)
{
  int* B = new int[r + 1];
  mergesort(A,B,l,r);
  delete [] B;
}

void printNum(int* arr, int inputSize, string status)
{
  int max;
  if(inputSize >= 10)
    max = 10;
  else
    max = inputSize;
    
  cout << "First 10 " << status << " numbers: ";
  for(int i = 0; i < max; i++)
    cout << arr[i] << ' ';
  cout << endl;
  cout << "Last 10 " << status << " numbers: ";
  for(int i = inputSize-max; i < inputSize; i++)
    cout << arr[i] << ' ';
  cout << endl << endl;
}

void beginAnalysis()
{
  vector<int> vec;
  
  bool k = false; // boolean to check if k is selected ( if k is selected, user can key in custom values)
  cout << "Data size?\n a) 10k\n b) 50k\n c) 100k\n d) 500k\n e) 1m\n f) 10m\n g) 50m\n h) 100m\n i) custom size\n k) key in your own values\n=> ";
  char choice;
  cin >> choice;
  int inputSize = 0;
  int val = 0;

  switch(choice)
  {
    case 'a':
    inputSize = 10000;
    break;
    
    case 'b':
    inputSize = 50000;
    break;
    
    case 'c':
    inputSize = 100000;
    break;
    
    case 'd':
    inputSize = 500000;
    break;
    
    case 'e':
    inputSize = 1000000;
    break;
    
    case 'f':
    inputSize = 10000000;
    break;
    
    case 'g':
    inputSize = 50000000;
    break;
    
    case 'h':
    inputSize = 100000000;
    break;
    
    case 'i':
    cout << "Size => ";
    cin >> inputSize;
    cout << endl;
    if(inputSize> 100000000)
    {
      cout << "Input size must not be larger than 100m." <<endl;
      return;
    }
    break;
    
    case 'k':

    cout << "Please enter your values (-ve to stop): ";
    while(val >= 0)
    {
      cin >> val;
      if(val >= 0)
        vec.push_back(val);
    }

    inputSize = vec.size();
    k = true;
    break;
    
    default:
    cout << "Invalid input.\n\n";
    return;
  }

  vec.reserve(inputSize); 
  int* arr = new int[inputSize];
  int max = 0; 
  if(!k) // if k is not selected, generate a sequence of numbers to be the analysis input
  {
    max = inputSize;
    char inputType;
    cout << "Input type?\n a) Ascending order\n b) Descending order\n c) Random\n=> ";
    cin >> inputType;
    
    switch(inputType)
    {
      case 'a':
      generateAscendingOrder(vec,arr,inputSize);
      break;
      
      case 'b':
      generateDescendingOrder(vec,arr,inputSize);
      break;
      
      case 'c':
      generateUnsortedNumbers(vec,arr,inputSize);
      break;
      
      default:
      cout << "Invalid input."<< endl;
      return;      
    }
  }
  else //if k is selected, transfer values from vector to array
  {
    max = vec[0];
    for(int i = 0; i < vec.size(); i++)
    {
      arr[i] = vec[i];
      
      if(max < vec[i])
        max = vec[i];
    }
  }
  
  int* arr2 = new int[inputSize]; //create another array for bucket-sort input
  for(int i = 0; i < inputSize; i++) 
     arr2[i] = arr[i]; //copy values from array1 to array2

  string sorted = "sorted";
  string unsorted = "unsorted";
  
  cout << "----------------------------------------------------" << endl;
  cout << "                    MERGE SORT                      "<< endl;
  cout << "----------------------------------------------------" << endl <<endl;

  printNum(arr,inputSize,unsorted); //print first 10 and last 10 unsorted values of array1

  TICK();
  startMergeSort(arr,0,inputSize-1); //sort array1 using merge-sort
  TOCK();

  printNum(arr,inputSize,sorted); //print first 10 and last 10 sorted values of array1
  delete[] arr;
  
  cout << "Duration of Merge Sort: " << DURATION() << endl << endl; //print the runtime of merge-sort
  cout << "----------------------------------------------------" << endl;  
  cout << "                   BUCKET SORT                      "<< endl;
  cout << "----------------------------------------------------" << endl <<endl;
  
  printNum(arr2,inputSize,unsorted); //print first 10 and last 10 unsorted values of array2
  
  TICK();
  startBucketSort(arr2,inputSize, max); //sort array2 using bucket-sort
  TOCK();
  
  printNum(arr2,inputSize,sorted); //print first 10 and last 10 sorted values of array2

  cout << "Duration of Bucket Sort: " << DURATION() << endl << endl; //print the runtime of bucket-sort
  cout << "====================================================" << endl << endl;
  
  delete[] arr2;
}

int main()
{
  beginAnalysis();
  return 0;
}
