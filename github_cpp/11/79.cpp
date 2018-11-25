#include <iostream>



#include "nodo1.cpp"

using namespace std;

const int cantt=140;

 
class heapSemaforos  {
public:
    heapSemaforos();
    void insert(int*);
	  void print();
   int lugaresDisponibles();
    int size();
    void eliminar();
    int esvaciodesde();
  int eliminarFondo();
 void heapify(int* arr[], int n, int i);
 void heapSort(int* arr[], int n);


private:
   
    int semaforosadentro;

    int *vector[cantt];
    int *ptr[cant];
 	int parasacar[cant];
    int total;
   	int aux;
  
  
  	
  

};

heapSemaforos::heapSemaforos(){


	semaforosadentro=0;
	total=0;
	for(int i=0;i<cantt;i++){
		vector[i]=0;
	}
} 
int heapSemaforos::lugaresDisponibles(){
	int contador=cantt;
	for(int i=0; i<cantt;i++){
		
			if(vector[i]>=0){
			
		contador--;
		}
	}
	return contador;
}

int heapSemaforos::size(){
	int contador=0;
	for(int i=0; i<cantt;i++){
		contador++;
	}
	return contador;
}

int heapSemaforos::esvaciodesde(){
	for(int i=0 ; i<cantt; i++){
		if(vector[i]== 0){
	
			return i;
		}
	
	}

}
void heapSemaforos::insert(int* da) {

	if(semaforosadentro<140){

	vector[semaforosadentro]= da;

	semaforosadentro++;


	}	else {
	cout<<"Cola llena"<< endl;
	}
	
	
	if(semaforosadentro==cantt){
			
	heapSort( vector, semaforosadentro);



}
}

void heapSemaforos::heapSort(int* arr[], int n)
{
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    
    for (int i=n-1; i>=0; i--)
    {
        
        swap(arr[0], arr[i]);
 
        
        heapify(arr, i, 0);
    }
}

void heapSemaforos::heapify(int* arr[], int n, int i)
{
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    
    if (l < n && *arr[l] < *arr[largest])
        largest = l;
 
    
    if (r < n && *arr[r] < *arr[largest])
        largest = r;
 
    
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
 
        
        heapify(arr, n, largest);
    }
}
 

void heapSemaforos::print(){
	for(int i=0;i<cantt;i++)	{
	

	
	cout<<*vector[i]<<endl;


	
}
}




void heapSemaforos::eliminar()
{
	
	
	*vector[0]=*vector[0]-1;
	
	
	


}

 









