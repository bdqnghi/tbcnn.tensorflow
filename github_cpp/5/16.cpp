









#include <iostream>
#include <math.h>
#include <iomanip>
#include <ctime>

using namespace std;

void computeTheoRunTimes();
void printFunc(double[]);
void fillFunc(double[], int);
void insertionSort(double[], int);
void quickSort(double [], int, int);
void merge(double [], int, int, int);
void mergeSort(double [], int, int);
int partition(double [], int, int);
void insertRealTime(double [], int, int);
void quickRealTime(double [], int, int, int);
void mergeRealTime(double [], int, int, int);
void swap(double*, double*);
int calculateInsert(int);
int calculateMerge(int);
int calculateQuick(int);
int main(){
    int choice;
    int nSize[7] = {1000, 10000, 25000, 50000, 100000, 150000, 200000};
    int n = sizeof(nSize)/sizeof(nSize[0]);
    
    
    cout << "\nMain Menu\n";
    cout << "Please choose one of the following running time camparison types\n";
    
    cout << "1 - Asymptotic notation based running time\n";
    
    cout << "2 - Actual running time\n";
    cout << "3 - Quit\n";
    cout << "Selection: ";
    cin >> choice;

    
    if(choice == 1){
        cout << "\nAsymptotic notation based running time: \n";
        computeTheoRunTimes();
    }
    
    else if(choice == 2){
        cout << "\nActual running time: \n";
        for(int i = 0; i < n; i++){
            double insertRandom[nSize[i]];
            double quickRandom[nSize[i]];
            double mergeRandom[nSize[i]];
            int nValue = nSize[i];
            int ranSize = sizeof(insertRandom)/sizeof(insertRandom[0]);
            srand((unsigned)time(NULL));
            fillFunc(insertRandom, ranSize);
            fillFunc(quickRandom, ranSize);
            fillFunc(mergeRandom, ranSize);

            insertRealTime(insertRandom, ranSize, nValue);
            mergeRealTime(mergeRandom, 0, ranSize-1, nValue);
            quickRealTime(quickRandom, 0, ranSize-1, nValue);  
        }
        main();
    }
    else if(choice == 3){
        return 0;
    }
    else{
        cout<< "Enter Value 1-3" << endl;
        main();
    }
    return 0;
} 


void insertRealTime(double arr[], int n, int nValue){
    clock_t begin = clock();
    insertionSort(arr, n);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "\nn = " << nValue <<endl;
    cout << "INSERTION-SORT: \t";
    cout << "T(n)= "  << std::fixed << std::setprecision(2) << elapsed_secs << " sec" << endl;
    
}


void mergeRealTime(double arr[], int low, int high, int nValue){
    clock_t mbegin = clock();
    mergeSort(arr, low, high);
    clock_t mend = clock();
    double melapsed_secs = double(mend - mbegin) / CLOCKS_PER_SEC;
    cout << "MERGE-SORT: \t\t" ;
    cout << "T(n)= " << std::fixed << std::setprecision(2) << melapsed_secs << " sec" << endl;
    
}


void quickRealTime(double arr[], int low, int high, int nValue){
    clock_t qbegin = clock();
    quickSort(arr, low, high);
    clock_t qend = clock();
    double qelapsed_secs = double(qend - qbegin) / CLOCKS_PER_SEC;
    cout << "QUICK-SORT: \t\t";
    cout << "T(n)= " << std::fixed << std::setprecision(2) << qelapsed_secs << " sec" << endl;
    
}


void computeTheoRunTimes(){
    int nSize[7] = {1000, 10000, 25000, 50000, 100000, 150000, 200000};
    double insertTime;
    double mergeTime;
    double quickTime;
    for(int i = 0; i < 7; i++){
        int nValue = nSize[i];
        insertTime = calculateInsert(nValue);
        mergeTime = calculateMerge(nValue);
        quickTime = calculateQuick(nValue);

        cout << "\nn = " << nValue <<endl;
        cout << "INSERTION-SORT: \t";
        cout << "T(n)= "  << std::fixed << std::setprecision(2) << insertTime << endl;
        cout << "MERGE-SORT: \t\t" ;
        cout << "T(n)= " << std::fixed << std::setprecision(2) << mergeTime <<endl;
        cout << "QUICK-SORT: \t\t";
        cout << "T(n)= " << std::fixed << std::setprecision(2) << quickTime << endl;
    }
    main();
}


int calculateInsert(int n){
    double result = n*n;
    return result;
}


int calculateMerge(int n){
    double result = n*(log2(n));
    return result;
}

int calculateQuick(int n){
    double result = n*(log2(n));
    return result;
}

void fillFunc(double arr[], int n){
    for (int i = 1; i < n; i++){
        double result = (rand() % 900) + 100.00;
        arr[i] = result;
    }
}

void printFunc(double arr[]){
    for (int i = 1; i < 25; i++){
        cout << std::fixed << std::setprecision(2) << arr[i] << ", ";
    }
}


void insertionSort(double arr[], int n){
   int i, key, j;
   for (i = 1; i < n; i++){
       key = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > key){
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

void swap(double* a, double* b){
    double t = *a;
    *a = *b;
    *b = t;
}
 

int partition(double arr[], int low, int high){
    int pivot = arr[high];    
    int i = (low - 1);  
    for (int j = low; j <= high- 1; j++){
        if (arr[j] <= pivot){
            i++;   
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(double arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(double arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(double arr[], int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
    


  

