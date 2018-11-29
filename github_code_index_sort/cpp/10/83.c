/* Hasan Abdullah: BucketSort.cpp - bucketsort using array/vector */

#include <iostream>
#include <vector>
using namespace std;

const int SIZE=10;

void Swap(float &a, float &b);
void Print(float* arr, int size);
void BucketSort(float* arr, int n);
void InsertionSort(vector<float> arr, int size);

int main(int argc, char **argv) {
  float A[SIZE]={0.73,0.44,0.12,0.09,0.51,0.35,0.09,0.26,0.68,0.73};
  cout<<"Original array:"<<endl;
  Print(A,SIZE);
  cout<<"Array sorted using bucket sort:"<<endl;
  BucketSort(A,SIZE);
  Print(A,SIZE);
  return 0;
}

void Swap(float &a, float &b) {
  float temp=a; a=b; b=temp;
}

void Print(float* arr, int size) {
  for (int i=0; i<size; i++)
    cout<<arr[i]<<"  ";
  cout<<endl;
}

void BucketSort(float* arr, int n) {
  //create n empty buckets (each initialized as empty "lists")
  vector< vector<float> > buckets(n, vector<float>(0,0));
  for (int i=0; i<n; i++) {
    //insert arr[i] into the current bucket[<floor of n*arr[i]>]'s list
    buckets[(int)n*arr[i]].push_back(arr[i]);
  }
  //since each bucket is already sorted, we just need to sort each bucket's list
  for (int j=0; j<n; j++) {
    //sort each bucket's list using insertion sort
    InsertionSort(buckets[j],buckets[j].size());
  }
  int size_list, arr_i=0;   //arr_i indexes original array arr
  for (int k=0; k<n; k++) {
    size_list=buckets[k].size();   //holds current bucket's list's size
    for (int L=0; L<size_list; L++) {
      //concatenate the list into original array
      arr[arr_i]=buckets[k][L];
      arr_i++;
    }
  }
}

void InsertionSort(vector<float> arr, int size) {
  int j;
  for (int i=1; i<size; i++) { //int i=0 is pointless since while loop will fail
    j=i;
    while (j>0 && arr[j]<arr[j-1]) {
      Swap(arr[j],arr[j-1]);
      j--;
    }
  }
}
