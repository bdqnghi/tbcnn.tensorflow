#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "_arquivosHeader/selectionSort.h"
#include "_arquivosHeader/insertionSort.h"
#include "_arquivosHeader/mergeSort.h"
#include "_arquivosHeader/shellSort.h"
#include "_arquivosHeader/quickSort.h"
#include "_arquivosHeader/heapSort.h"
#include "_arquivosHeader/Commons.h"

using namespace std;

int main(){
	int elementos01[10];
	int elementos02[100];
	int elementos03[1000];
	int elementos04[10000];
	int elementos05[100000];
	char local[50];
	int i = 0, temp = 0;

	cout << "------------------\n";
	cout << "Amostra tamanho 10\n";
	cout << "------------------\n";

	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("SelectionSort - aleatoria: %f .\n", selectionSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("SelectionSort - ordenada Cre.: %f .\n", selectionSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("SelectionSort - ordenada Dec.: %f .\n", selectionSort(elementos01, 10, 'C'));
//	
	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("InsertionSort - aleatoria: %f .\n", insertionSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("InsertionSort - ordenada Cre.: %f .\n", insertionSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("InsertionSort - ordenada Dec.: %f .\n", insertionSort(elementos01, 10, 'C'));
//
	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("MergeSort - aleatoria: %f .\n", mergeSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("MergeSort - ordenada Cre.: %f .\n", mergeSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("MergeSort - ordenada Dec.: %f .\n", mergeSort(elementos01, 10, 'C'));
//
	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("ShellSort - aleatoria: %f .\n", shellSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("ShellSort - ordenada Cre.: %f .\n", shellSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("ShellSort - ordenada Dec.: %f .\n", shellSort(elementos01, 10, 'C'));
//	
	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("QuickSort - aleatoria: %f .\n", quickSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("QuickSort - ordenada Cre.: %f .\n", quickSort(elementos01, 10, 'C'));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("QuickSort - ordenada Dec.: %f .\n", quickSort(elementos01, 10, 'C'));	
//	
	strcpy(local, "_arquivos/a01.txt");
	lerFile(local, elementos01);
	printf("HeapSort - aleatoria: %f .\n", heapSort(elementos01, 10));
	
	strcpy(local, "_arquivos/c01.txt");
	lerFile(local, elementos01);
	printf("HeapSort - ordenada Cre.: %f .\n", heapSort(elementos01, 10));
	
	strcpy(local, "_arquivos/d01.txt");
	lerFile(local, elementos01);
	printf("HeapSort - ordenada Dec.: %f .\n", heapSort(elementos01, 10));
//
	cout << "-------------------\n";
	cout << "Amostra tamanho 100\n";
	cout << "-------------------\n";
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("SelectionSort - aleatoria: %f .\n", selectionSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("SelectionSort - ordenada Cre.: %f .\n", selectionSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("SelectionSort - ordenada Dec.: %f .\n", selectionSort(elementos02, 100, 'C'));
//	
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("InsertionSort - aleatoria: %f .\n", insertionSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("InsertionSort - ordenada Cre.: %f .\n", insertionSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("InsertionSort - ordenada Dec.: %f .\n", insertionSort(elementos02, 100, 'C'));
//
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("MergeSort - aleatoria: %f .\n", mergeSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("MergeSort - ordenada Cre.: %f .\n", mergeSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("MergeSort - ordenada Dec.: %f .\n", mergeSort(elementos02, 100, 'C'));
//
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("ShellSort - aleatoria: %f .\n", shellSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("ShellSort - ordenada Cre.: %f .\n", shellSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("ShellSort - ordenada Dec.: %f .\n", shellSort(elementos02, 100, 'C'));
//	
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("QuickSort - aleatoria: %f .\n", quickSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("QuickSort - ordenada Cre.: %f .\n", quickSort(elementos02, 100, 'C'));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("QuickSort - ordenada Dec.: %f .\n", quickSort(elementos02, 100, 'C'));	
//	
	strcpy(local, "_arquivos/a02.txt");
	lerFile(local, elementos02);
	printf("HeapSort - aleatoria: %f .\n", heapSort(elementos02, 100));
	
	strcpy(local, "_arquivos/c02.txt");
	lerFile(local, elementos02);
	printf("HeapSort - ordenada Cre.: %f .\n", heapSort(elementos02, 100));
	
	strcpy(local, "_arquivos/d02.txt");
	lerFile(local, elementos02);
	printf("HeapSort - ordenada Dec.: %f .\n", heapSort(elementos02, 100));
//
	cout << "--------------------\n";
	cout << "Amostra tamanho 1000\n";
	cout << "--------------------\n";
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("SelectionSort - aleatoria: %f .\n", selectionSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("SelectionSort - ordenada Cre.: %f .\n", selectionSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("SelectionSort - ordenada Dec.: %f .\n", selectionSort(elementos03, 1000, 'C'));
//	
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("InsertionSort - aleatoria: %f .\n", insertionSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("InsertionSort - ordenada Cre.: %f .\n", insertionSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("InsertionSort - ordenada Dec.: %f .\n", insertionSort(elementos03, 1000, 'C'));
//
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("MergeSort - aleatoria: %f .\n", mergeSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("MergeSort - ordenada Cre.: %f .\n", mergeSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("MergeSort - ordenada Dec.: %f .\n", mergeSort(elementos03, 1000, 'C'));
//
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("ShellSort - aleatoria: %f .\n", shellSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("ShellSort - ordenada Cre.: %f .\n", shellSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("ShellSort - ordenada Dec.: %f .\n", shellSort(elementos03, 1000, 'C'));
//	
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("QuickSort - aleatoria: %f .\n", quickSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("QuickSort - ordenada Cre.: %f .\n", quickSort(elementos03, 1000, 'C'));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("QuickSort - ordenada Dec.: %f .\n", quickSort(elementos03, 1000, 'C'));	
//	
	strcpy(local, "_arquivos/a03.txt");
	lerFile(local, elementos03);
	printf("HeapSort - aleatoria: %f .\n", heapSort(elementos03, 1000));
	
	strcpy(local, "_arquivos/c03.txt");
	lerFile(local, elementos03);
	printf("HeapSort - ordenada Cre.: %f .\n", heapSort(elementos03, 1000));
	
	strcpy(local, "_arquivos/d03.txt");
	lerFile(local, elementos03);
	printf("HeapSort - ordenada Dec.: %f .\n", heapSort(elementos03, 1000));
//	
	cout << "---------------------\n";
	cout << "Amostra tamanho 10000\n";
	cout << "---------------------\n";
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("SelectionSort - aleatoria: %f .\n", selectionSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("SelectionSort - ordenada Cre.: %f .\n", selectionSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("SelectionSort - ordenada Dec.: %f .\n", selectionSort(elementos04, 10000, 'C'));
//	
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("InsertionSort - aleatoria: %f .\n", insertionSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("InsertionSort - ordenada Cre.: %f .\n", insertionSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("InsertionSort - ordenada Dec.: %f .\n", insertionSort(elementos04, 10000, 'C'));
//
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("MergeSort - aleatoria: %f .\n", mergeSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("MergeSort - ordenada Cre.: %f .\n", mergeSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("MergeSort - ordenada Dec.: %f .\n", mergeSort(elementos04, 10000, 'C'));
//
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("ShellSort - aleatoria: %f .\n", shellSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("ShellSort - ordenada Cre.: %f .\n", shellSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("ShellSort - ordenada Dec.: %f .\n", shellSort(elementos04, 10000, 'C'));
//	
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("QuickSort - aleatoria: %f .\n", quickSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("QuickSort - ordenada Cre.: %f .\n", quickSort(elementos04, 10000, 'C'));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("QuickSort - ordenada Dec.: %f .\n", quickSort(elementos04, 10000, 'C'));	
//	
	strcpy(local, "_arquivos/a04.txt");
	lerFile(local, elementos04);
	printf("HeapSort - aleatoria: %f .\n", heapSort(elementos04, 10000));
	
	strcpy(local, "_arquivos/c04.txt");
	lerFile(local, elementos04);
	printf("HeapSort - ordenada Cre.: %f .\n", heapSort(elementos04, 10000));
	
	strcpy(local, "_arquivos/d04.txt");
	lerFile(local, elementos04);
	printf("HeapSort - ordenada Dec.: %f .\n", heapSort(elementos04, 10000));
//
	cout << "----------------------\n";
	cout << "Amostra tamanho 100000\n";
	cout << "----------------------\n";
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("SelectionSort - aleatoria: %f .\n", selectionSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("SelectionSort - ordenada Cre.: %f .\n", selectionSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("SelectionSort - ordenada Dec.: %f .\n", selectionSort(elementos05, 100000, 'C'));
//	
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("InsertionSort - aleatoria: %f .\n", insertionSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("InsertionSort - ordenada Cre.: %f .\n", insertionSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("InsertionSort - ordenada Dec.: %f .\n", insertionSort(elementos05, 100000, 'C'));
//
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("MergeSort - aleatoria: %f .\n", mergeSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("MergeSort - ordenada Cre.: %f .\n", mergeSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("MergeSort - ordenada Dec.: %f .\n", mergeSort(elementos05, 100000, 'C'));
//
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("ShellSort - aleatoria: %f .\n", shellSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("ShellSort - ordenada Cre.: %f .\n", shellSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("ShellSort - ordenada Dec.: %f .\n", shellSort(elementos05, 100000, 'C'));
//	
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("QuickSort - aleatoria: %f .\n", quickSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("QuickSort - ordenada Cre.: %f .\n", quickSort(elementos05, 100000, 'C'));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("QuickSort - ordenada Dec.: %f .\n", quickSort(elementos05, 100000, 'C'));	
//	
	strcpy(local, "_arquivos/a05.txt");
	lerFile(local, elementos05);
	printf("HeapSort - aleatoria: %f .\n", heapSort(elementos05, 100000));
	
	strcpy(local, "_arquivos/c05.txt");
	lerFile(local, elementos05);
	printf("HeapSort - ordenada Cre.: %f .\n", heapSort(elementos05, 100000));
	
	strcpy(local, "_arquivos/d05.txt");
	lerFile(local, elementos05);
	printf("HeapSort - ordenada Dec.: %f .\n", heapSort(elementos05, 100000));
	
	return 0;
}
