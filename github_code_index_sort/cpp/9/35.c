/*
EXERCÍCIO EM MONITORIA - 29/08/2016

Selection Sort: A ordenação por seleção consiste, em cada etapa, selecionar o menor (ou o maior) elemento e colocá-lo em sua posição correta dentro da futura lista ordenada.

PSEUDOCÓDIGO:

SELECTION-SORT(A)
para i<-0 até n-1 faça
    min <- i
    para j<-(i+1) até n faça
        se A[j] < A[min] então
            min <- j
    se i != min então
        troca A[i] <-> A[min]


Exercício -
PARTE I - Implementar o algoritmo SELECTION-SORT, analisar o tempo do algoritmo em seu melhor e pior caso, para vetores de entrada grandes.
PARTE II - Calcular a complexidade para o melhor e pior caso, indicando a função de crescimento do algoritmo.
*/

#include <iostream>
#include <ctime>
using namespace std;
#define N 2000

int A[N];
enum Analise{pior_caso, melhor_caso};

void selection_sort();
void inicializa_vetor();
void imprime_vetor();

void imprime_vetor(){
    for(int i =0 ; i < N; i++)
        cout << A[i] << " ";

    cout << endl;
}

void inicializa_vetor(Analise analise){
    if(analise == pior_caso){
        int j = N;
        for(int i = 0; i < N; i++)
            A[i] = j--;
    }else{
        int j = 1;
        for(int i = 0; i < N; i++)
            A[i] = j++;
    }
    
}

void selection_sort(){
    for(int i = 0; i < N - 1; i++){
        int min = i;
        for(int j = i+1; j < N; j++){
            if(A[j] < A[min]){
                min = j;
            }
        }

        if(i!=min){
            int aux = A[i];
            A[i] = A[min];
            A[min] = aux;
        }
    }
}



int main(){
    inicializa_vetor(melhor_caso);
    
    clock_t begin_melhor = clock();
    selection_sort();
    clock_t end_melhor = clock();

    cout << "Melhor Caso: " << (end_melhor - begin_melhor) << endl;

    inicializa_vetor(pior_caso);
    clock_t begin_pior = clock();
    selection_sort();
    clock_t end_pior = clock();

    cout << "Pior Caso: " << (end_pior - begin_pior) << endl;
}