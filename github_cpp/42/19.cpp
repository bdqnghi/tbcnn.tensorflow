#include <iostream> 

using namespace std;


// this function will populate the list
void arrpopulate(int* &arr, int n, int &count)
{
	 		
	
	int i=0;
	int input;
	
	do
	{
		// takes user input and plugs it into an array 
		cin >> input;		
		arr[i] = input;
		i++;		
		count++;
		
		//checks if arr is full	
		if (n == i)
		{
			// new array with double the size in memory  
			int *newarr = new int[n * 2];	//doubles the size 
		        	
			//deep copy data from old array to new larger array
			for (int k = 0; k < n; k++)
			{
				newarr[k] = arr[k]; 			 
			}
			delete[] arr;
			n = 2*n;			
			arr = newarr;
		}
	} while (input != -999);
cout << endl;	
return;
}


// this function will print out he list
void arrPrint(int *arr)
{
	int i = 0; 
	do{
	   cout << arr[i]
<< "\t";
	   if (i % 10 == 0)
	   {
	      cout << endl;
	   }
	}while( arr[i++] != -999 );
cout <<endl;
return;
}


// this function will sort the list using select sort algorithm 
int* selectionSort(int* &arr, int &count)
{
	int* newSort = arr;
	int tmp;
	cout << "count: " << count << endl;
	for(int i=0; i < count - 1; i++)
	{
		for (int j=i+1; j < count-1; j++)
		{
			if ( newSort[j] < newSort[i]){	
				tmp = newSort[i];
				newSort[i] = newSort[j];
				newSort[j] = tmp;
			}	
		}
	}
	return newSort;
}

		/* *** MAIN START *** */
int main(int argc, char** argv)
{

// creating dynamic array
int n = 4;
int count = -1; 

int *arr = new int[n];
// populate the array 
arrpopulate(arr, n, count);

// prints the array;
cout << "Original List: " << endl;
arrPrint(arr);

cout << "Select sort on List: " << endl;

arrPrint(selectionSort(arr, count));

    
cout << endl;
return 0;
}
