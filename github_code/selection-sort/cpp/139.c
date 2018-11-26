/*
Indre Ionut

Bubble Sort
Insertion Sort
Selection Sort

Am folosit un vector principal in care am inserat valori random cu ajutorul functiei FillRandomArray.
Am folosit 3 vectori adiacenti cu ajutorul carora am calculat pentru fiecare metoda in parte cele 3 cazuri.
Se observa ca pentru a reflecata un best case este necesar ca vectorul sa fie ordonat crescator, iar pentru un worst case vectorul trebuie sa fie
ordonat descrecator. In cazul average valorile fiind aleatoare neordonate.

*/

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include "Profiler.h"
#include<time.h>

#define maxSize 1000
#define minSize 10
#define up 100

Profiler profiler ("profiler");

//Bubble Sort Worst O(n^2)/Average O(n^2)/Best O(n)
void bubbleSort(int a [],int n)
{
	int i, aux, j;

	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{
			profiler.countOperation("ComparatiiBubbleSort", n);
			profiler.countOperation("AtribuiriBubbleSort + ComparatiiBubbleSort",n);
			if ( a[j] > a[j+1])
			{
				aux = a[j];
				a[j] = a[j+1];
				a[j+1] = aux;
				profiler.countOperation("AtribuiriBubbleSort", n , 3);
				profiler.countOperation("AtribuiriBubbleSort + ComparatiiBubbleSort", n , 3);
			}
		}
	}
}

//SelectionSort Worst O(n^2)/Average O(n^2)/Best O(n^2)
void selectionSort(int a [],int n)
{
	int i, iMin, j, min;

	for (i = 0; i < n-1 ; i++)
	{
		
		profiler.countOperation("AtribuiriSelectionSort + ComparatiiSelectionSort", n);
		profiler.countOperation("AtribuiriSelectionSort", n);
		min=a[i];
		iMin=i;
		for (j = i+1; j < n; j++)
		{
			profiler.countOperation("ComparatiiSelectionSort", n);
			profiler.countOperation("AtribuiriSelectionSort + ComparatiiSelectionSort", n);
			if (a[j] < min)
			{
				min = a[j];
				iMin = j;
				profiler.countOperation("AtribuiriSelectionSort", n);
				profiler.countOperation("AtribuiriSelectionSort + ComparatiiSelectionSort", n);
			}
		}

		profiler.countOperation("ComparatiiSelectionSort", n);
		profiler.countOperation("AtribuiriSelectionSort + ComparatiiSelectionSort", n);
		if(iMin != i)
		{
			a[iMin] = a[i];
			a[i] = min;
			profiler.countOperation("AtribuiriSelectionSort", n, 2);
			profiler.countOperation("AtribuiriSelectionSort + ComparatiiSelectionSort", n, 2);
		}
	}
}

//InsertionSort Worst O(n^2)/Average O(n^2)/Best O(n)
void insertionSort(int a [],int n)
{
	int i, j, x;

	for (i = 1; i < n; i++)
	{
		x = a[i];
		j = i;
		profiler.countOperation("AtribuiriInsertionSort", n);
		profiler.countOperation("AtribuiriInsertionSort + ComparatiiInsertionSort", n);
		while( j > 0 && a[j-1] > x)
		{
			a[j] = a[j-1];
			a[j-1] = x;
			j = j-1;
			profiler.countOperation("AtribuiriInsertionSort", n, 2);
			profiler.countOperation("AtribuiriInsertionSort + ComparatiiInsertionSort", n, 2);
		}
		a[j] = x;
		profiler.countOperation("AtribuiriInsertionSort", n);
		profiler.countOperation("ComparatiiInsertionSort", n);
		profiler.countOperation("AtribuiriInsertionSort + ComparatiiInsertionSort", n, 2);
	}

}

int main()
{
	int vect[maxSize], vect1[maxSize], vect2[maxSize], vect3[maxSize];
	int i, n, selectie;

	


	printf("1 - BestCase; 2 - AverageCase; 3 - WorstCase; \n");
	scanf("%d" ,&selectie);

	switch(selectie)
	{
		//BestCase
	case 0:
		//Demonstratie
	
	int vector[9] = {1,6,4,9,35,95,5,2,7};
	bubbleSort(vector,9);
	printf("\n BUBBLE SORT \n");
	for ( i = 0; i <= 8; i++)
	{
	printf("%d ", vector[i]);
	}

	selectionSort(vector,9);
	printf("\n SELECTION SORT \n");
	for ( i = 0; i <= 8; i++)
	{
	printf("%d ", vector[i]);
	}

	insertionSort(vector,9);
	printf("\n INSERTION SORT \n");
	for ( i = 0; i <= 8; i++)
	{
	printf("%d ", vector[i]);
	}
	
	system("PAUSE");
	
		break;

	case 1:
		for(n = minSize; n < maxSize; n += up)
		{
			printf("\n BestCase RANDOM Array \n ");
			FillRandomArray(vect , n , 100, 10000, false, 1);
			for(i = 0; i < n; i++)
			{
				printf("%d", vect[i]);
				vect1[i] = vect[i];
				vect2[i] = vect[i];
				vect3[i] = vect[i];
			}

			printf("\n Vectorul sortat prin BubbleSort - BestCase \n ");
			bubbleSort(vect1, n);		
			for(i = 0; i < n; i++)
			{
				printf("%d ",vect1[i]);
			}
	
			printf("\n  Vectorul sortat prin SelectionSort - BestCase \n ");
			selectionSort(vect2, n);
			for(i = 0; i < n; i++)
			{
				printf("%d ",vect2[i]);
			}
	
			printf("\n Vectorul sortat prin InsertionSort - BestCase \n ");
			insertionSort(vect3, n);
			for(i = 0; i < n; i++)
			{
				printf("%d ",vect3[i]);
			}
		}
		break;

		//AverageCase
		case 2:
			for(int k = 1; k <= 5; k++)
			{
				for(n = minSize; n < maxSize; n+=up)
			{
				printf("\n AverageCase RANDOM Array \n ");
				FillRandomArray(vect, n, 100, 10000, false, 0);
			for(i = 0; i<n; i++)
			{
			
				printf("%d ", vect[i]);
				vect1[i] = vect[i];
				vect2[i] = vect[i];
				vect3[i] = vect[i];
			}

			printf("\n Vectorul sortat prin BubbleSort - AverageCase \n ");
			bubbleSort(vect1, n);
			for(i=0;i<n;i++)
			{
				printf("%d ",vect1[i]);
			}
	
			printf("\n Vectorul sortat prin SelectionSort - AverageCase \n ");
			selectionSort(vect2, n);
			for(i = 0; i < n; i++)
			{
				printf("%d ",vect2[i]);
			}
	
			printf("\n Vectorul sortat prin InsertionSort - AverageCase \n ");		
			insertionSort(vect3,n);
			for(i = 0; i < n; i++)
			{
				printf("%d ",vect3[i]);
			}
			
			}
			}
		break;

		//WorstCase
			case 3:
		for(n = minSize; n < maxSize; n+=up)
		{
			printf("\n WorstCase RANDOM Array \n ");
			FillRandomArray(vect, n, 100, 10000, false, 2);
			for(i = 0; i < n; i++)
			{
				printf("%d ", vect[i]);
				vect1[i] = vect[i];
				vect2[i] = vect[i];
				vect3[i] = vect[i];
			}

			printf("\n Vectorul sortat prin BubbleSort - WorstCase \n ");
			bubbleSort(vect1, n);
			for(i=0;i<n;i++)
			{
				printf("%d",vect1[i]);
			}
	
			printf("\n  Vectorul sortat prin SelectionSort - WorstCase \n ");		
			selectionSort(vect2, n);
			for(i=0;i<n;i++)
			{
				printf("%d",vect2[i]);
			}
	
			printf("\n Vectorul sortat prin InsertionSort - WorstCase\n ");
			
			insertionSort(vect3, n);
			for(i=0;i<n;i++)
			{
				printf("%d",vect3[i]);
			}
		}
		break;
	}

	profiler.createGroup("Atribuiri" ,"AtribuiriSelectionSort", "AtribuiriInsertionSort", "AtribuiriBubbleSort");
	profiler.createGroup("Comparatii","ComparatiiSelectionSort", "ComparatiiInsertionSort", "ComparatiiBubbleSort");
	profiler.createGroup("Atribuiri + Comparatii","AtribuiriSelectionSort + ComparatiiSelectionSort", "AtribuiriInsertionSort + ComparatiiInsertionSort", "AtribuiriBubbleSort + ComparatiiBubbleSort");
	profiler.showReport();
	getch();
	return(0);
}
	