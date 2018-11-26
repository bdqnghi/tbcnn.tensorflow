/*
 * Jungsik Byun 0459077
 * Assignments sortingHwk
 * Nov 12, 2017
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;


template <class T>
void display( T * items , unsigned start, unsigned end){
    for (start ; start<end ; start++){
        cout<<items[start]<<endl;
    }
}

template <class T>
int patition(T * nums, int first, int last )
{
    int  p = first;
    int pivotElement = nums[first];

    for(int i = first+1 ; i <= last ; i++)
    {
      if(nums[i] <= pivotElement)
        {
            p++;
            swap(nums[i], nums[p]);
        }
    }
    swap(nums[p], nums[first]);
    return p;
}

template <class T>
int randPatition(T * nums, int first, int last )
{

    int i=rand()%(last-first);
    int temp;
    temp=nums[last];
    nums[last]=nums[i];
    nums[i]=temp;
    return patition(nums,first,last);
}


template <class T>
void quickSort( T * nums, int first, int last )
{

    if(last-first<1){

    }else{
        int p = patition(nums, first, last);
        quickSort(nums, first, p-1);
        quickSort(nums, p+1, last);
    }
}

template <class T>
void randomizedQuickSort( T * nums, int first, int last )
{

    if(last-first<1){

    }else{
        int p = randPatition(nums, first, last);
        quickSort(nums, first, p-1);
        quickSort(nums, p+1, last);
    }
}

template <class T>
void merge(T *items, int start, int mid, int end)
{
    int i, j, k, temp[end-start+1];
    i = start;
    k = 0;
    j = mid + 1;

    while (i <= mid && j <= end)
    {
        if (items[i] < items[j])
        {
            temp[k] = items[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = items[j];
            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        temp[k] = items[i];
        k++;
        i++;
    }

    while (j <= end)
    {
        temp[k] = items[j];
        k++;
        j++;
    }

    for (i = start; i <= end; i++)
    {
        items[i] = temp[i-start];
    }
}

template <class T>
void mergeSort(T * items, unsigned start, unsigned end){
    if(end-start<1){

    }else{
        int mid = (start+end)/2;
        mergeSort(items,start,mid);
        mergeSort(items,mid+1,end);
        merge(items,start,mid,end);
    }
}

void heapify(int arr[], int start, int end)
{
    int largest = start;
    int l = 2*start + 1;
    int r = 2*start + 2;

    if (l < end && arr[l] > arr[largest])
        largest = l;

    if (r < end && arr[r] > arr[largest])
        largest = r;

    if (largest != start)
    {
        swap(arr[start], arr[largest]);
        heapify(arr, end, largest);
    }
}

template <class T>
void heapSort(T * items, int start, int end)
{

    for (int i = end / 2 - 1; i >= start; i--)
        heapify(items, i, end);


    for (int i=end; i>=start; i--)
    {
        swap(items[start], items[i]);

     heapify(items, start, i);
    }
}



int main() {
    ifstream data("random1000000.txt");
    int SIZE = 1000000;
    int counter = 0;
    int *randomArry= new int[SIZE];


    if(data.is_open()) {
        int temp;
        for (int i = 0; i < SIZE; i++) {
            data >> temp;
            randomArry[counter]=temp;
            counter++;
        }
    }



    cout<<"quick sort array"<<endl;
    int *quickSortArr = new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        quickSortArr[i]=randomArry[i];
    }
    auto quicks = get_time::now();
    quickSort(quickSortArr,0,SIZE-1);
    auto quicke = get_time::now();
    auto quickdiff = quicke - quicks;
    cout<<chrono::duration_cast<ns>(quickdiff).count()<<"ms";
    cout<<endl;

    delete [] quickSortArr;

    int *randomizedQuickSortArr= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        randomizedQuickSortArr[i]=randomArry[i];
    }

    cout<<"randomized quick sort array"<<endl;

    auto randomizedstart = get_time::now();
    randomizedQuickSort(randomizedQuickSortArr,0,SIZE-1);
    auto randomizedend = get_time::now();
    auto randomizeddiff = randomizedend - randomizedstart;
    cout<<chrono::duration_cast<ns>(randomizeddiff).count()<<"ms";
    cout<<endl;

    delete [] randomizedQuickSortArr;


    cout<<"merge sort array"<<endl;
    int *mergeSortArr= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        randomizedQuickSortArr[i]=randomArry[i];
    }
    auto mergeSortArrstart = get_time::now();
    mergeSort(mergeSortArr,0,SIZE-1);
    auto mergeSortArrend = get_time::now();
    auto mergeSortArrdiff = mergeSortArrend - mergeSortArrstart;
    cout<<chrono::duration_cast<ns>(mergeSortArrdiff).count()<<"ms";
    cout<<endl;
    delete [] mergeSortArr;



    cout<<"heap sort array"<<endl;
    int *heapSortArr= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        randomizedQuickSortArr[i]=randomArry[i];
    }
    auto heapSortArrst = get_time::now();
    heapSort(heapSortArr,0,SIZE-1);
    clock_t endHeap = clock();
    auto heapSortArren = get_time::now();
    auto heapSortArrdiff = heapSortArren - heapSortArrst;
    cout<<chrono::duration_cast<ns>(heapSortArrdiff).count()<<"ms";
    cout<<endl;
    delete [] heapSortArr;

    delete [] randomArry;

    ifstream data1("notRandom1000000.txt");
    if(data1.is_open()) {
        int temp;
        for (int i = 0; i < SIZE; i++) {
            data1 >> temp;
            randomArry[counter]=temp;
            counter++;
        }
    }

    cout<<"quick sort array with not random 1000000"<<endl;
    int *quickSortArr1 = new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        quickSortArr1[i]=randomArry[i];
    }
    auto quickSortArr1st = get_time::now();
    quickSort(quickSortArr1,0,SIZE-1);

    auto quickSortArr1en = get_time::now();
    auto quickSortArr1diff = quickSortArr1en - quickSortArr1st;
    cout<<chrono::duration_cast<ns>(quickSortArr1diff).count()<<"ms";
    cout<<endl;

    delete [] quickSortArr1;

    int *randomizedQuickSortArr1= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        randomizedQuickSortArr1[i]=randomArry[i];
    }

    cout<<"randomized quick sort array with not random 1000000"<<endl;

    auto randomizedQuickSortArr1st = get_time::now();
    randomizedQuickSort(randomizedQuickSortArr1,0,SIZE-1);
    clock_t endRand1 = clock();
    auto randomizedQuickSortArr1en = get_time::now();
    auto randomizedQuickSortArr1diff = randomizedQuickSortArr1en - randomizedQuickSortArr1st;
    cout<<chrono::duration_cast<ns>(randomizedQuickSortArr1diff).count()<<"ms";
    cout<<endl;

    delete [] randomizedQuickSortArr1;


    cout<<"merge sort array with not random 1000000"<<endl;
    int *mergeSortArr1= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        mergeSortArr1[i]=randomArry[i];
    }
    auto mergeSortArr1st = get_time::now();
    mergeSort(mergeSortArr,0,SIZE-1);
    auto mergeSortArr1en = get_time::now();
    auto mergeSortArr1stdiff = mergeSortArr1en - mergeSortArr1st;
    cout<<chrono::duration_cast<ns>(mergeSortArr1stdiff).count()<<"ms";
    cout<<endl;
    delete [] mergeSortArr1;



    cout<<"heap sort array with not random 1000000"<<endl;
    int *heapSortArr1= new int[SIZE];

    for(int i = 0 ; i<SIZE ; i++){
        randomizedQuickSortArr[i]=randomArry[i];
    }
    auto heapSortArr1st = get_time::now();
    heapSort(heapSortArr,0,SIZE-1);
    auto heapSortArr1sten = get_time::now();
    auto heapSortArr1stdiff = heapSortArr1sten - heapSortArr1st;
    cout<<chrono::duration_cast<ns>(heapSortArr1stdiff).count()<<"ms";
    cout<<endl;
    delete [] heapSortArr1;

    return 0;
}