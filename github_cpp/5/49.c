#include <iostream>


void insertionSort(int vetor[], int tam){
    for (int i = 1; i < tam; i++) {
            int escolhido = vetor[i];
            int j = i - 1;
            while ((j >= 0) && (vetor[j] > escolhido)) {
                vetor[j + 1] = vetor[j];
                j--;
            }
            
            vetor[j + 1] = escolhido;
        }
}


int main(){
    int array[7] = {6,5,13,11,15,1,50};
    
    for(int i =0;i<7;i++){
         std::cout<< array[i] <<std::endl;
    }
    insertionSort(array,7);
    
    for(int i =0;i<7;i++){
        std::cout<< array[i] <<std::endl;
    } 
    return 0;
}