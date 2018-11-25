#include <iostream> 

using namespace std;



void arrpopulate(int* &arr, int n, int &count)
{
	 		
	
	int i=0;
	int input;
	
	do
	{
		
		cin >> input;		
		arr[i] = input;
		i++;		
		count++;
		
		
		if (n == i)
		{
			
			int *newarr = new int[n * 2];	
		        	
			
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

		
int main(int argc, char** argv)
{


int n = 4;
int count = -1; 

int *arr = new int[n];

arrpopulate(arr, n, count);


cout << "Original List: " << endl;
arrPrint(arr);

cout << "Select sort on List: " << endl;

arrPrint(selectionSort(arr, count));

    
cout << endl;
return 0;
}
