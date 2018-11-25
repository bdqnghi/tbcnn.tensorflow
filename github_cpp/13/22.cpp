#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <array>
#include <fstream>
#include "algorithms.h"

using namespace std;

void test_selectionSort_best();
void test_selectionSort_worst();
void test_selectionSort_average();
void test_bubbleSort_best();
void test_bubbleSort_worst();
void test_bubbleSort_average();
void test_improved_bubbleSort_best();
void test_improved_bubbleSort_worst();
void test_improved_bubbleSort_average();

int main(){
    
    srand(time(NULL));
    
    test_improved_bubbleSort_worst();
}

void test_selectionSort_best(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Increasing(list);

        double start = omp_get_wtime();
            list = selectionSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("selectionSort_best.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_selectionSort_worst(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Decreasing(list);

        double start = omp_get_wtime();
            list = selectionSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("selectionSort_worst.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_selectionSort_average(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        Random_List(list);

        double start = omp_get_wtime();
            list = selectionSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("selectionSort_average.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_bubbleSort_best(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Increasing(list);

        double start = omp_get_wtime();
            list = bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("bubbleSort_best.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_bubbleSort_worst(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Decreasing(list);

        double start = omp_get_wtime();
            list = bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("bubbleSort_worse.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_bubbleSort_average(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        Random_List(list);

        double start = omp_get_wtime();
            list = bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("bubbleSort_average.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_improved_bubbleSort_best(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Increasing(list);

        double start = omp_get_wtime();
            list = improved_bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("improved_bubbleSort_best.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_improved_bubbleSort_worst(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        List_Decreasing(list);

        double start = omp_get_wtime();
            list = improved_bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("improved_bubbleSort_worse.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

void test_improved_bubbleSort_average(){
    ofstream file;
    vector<int> list;
    int n;
    
    for(n = 1000;n <= 20000;n+=100){
        vector<int> list(n,0);
        Random_List(list);

        double start = omp_get_wtime();
            list = improved_bubbleSort(list, n);
        double end = omp_get_wtime();
        
        cout << "List size: " << n << " ,  Sort time: " << end-start << endl;
        file.open("improved_bubbleSort_average.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}


