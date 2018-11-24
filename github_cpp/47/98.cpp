#include <iostream>

using namespace std; 

int main()
{
	int N, temp, num = 0; 
	
	cout<<"Ingrese el tamano del vector"<<endl;
	cin >> N;
	
	int A[N]; 
	
	for (int i = 0; i < N; i++)
	{
		cout << "Ingrese el elemento " << i + 1 << endl; 
		cin >> A[i]; 
	}
	
	for (int i = 0; i < N; i++)
	{ 
	    for(int j = 0; j < N - 1; j++)
	    {
            if (A[j] > A[j+1])
            {
               temp = A[j];
               A[j] = A[j+1];
               A[j+1] = temp;
            }
	    }
	}
	
	cout<< "El vector ordenado es" << endl;
   	
	for (int i = 0; i < N; i++)
    {
       	cout << A[i] <<"   ";
    }
	cout << endl;
	
	cout << "Ingrese un numero para buscar: " << endl; 
	cin >> num; 
	
	num = num; 
	
	int first, middle, last; 
	
	first = 0; 
   	last = N - 1; 
    
	while (first <= last)
	{
		middle = (first + last) / 2; 
		
		if (A[middle] == num)
		{
			cout << num << " fue encontrado en la posicion " << middle + 1 << endl; 
			break; 
		}
		else if (A[middle] < num)
		{
			first = middle + 1; 
		}		
		else if (A[middle] > num)
		{
			last = middle - 1; 
		}
	}
	if (first > last)
	{
		cout << num << " no fue encontrado en la serie de numeros ingresados " << endl; 
	}
     
	return 0;
}
