







#include "MetodosDeOrdenacao.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

void ComandosPadrao::inserir(long N){
    vetor[indice] = N;
    indice++;
}
void ComandosPadrao::mostrar(){
    for (int i=0;i<TAM;i++){
        printf("%ld ",vetor[i]);
    }
}





SelectionSort::SelectionSort(long tam){
    Selection.TAM = tam;
    Selection.vetor = (long*)malloc(sizeof(long)*tam);
    Selection.indice = 0;
    Selection.numeros_de_repeticoes = 0;
    Selection.numero_de_comparacoes = 0;
    cout << "Vetor Criado com sucesso: "<<tam<<endl;
}
void SelectionSort::inserir(long N){
    Selection.inserir(N);
}



void SelectionSort::ordenaSelectionSort(){
    int i, menor, j;
    for (i=0;i<Selection.TAM;i++){
        menor = i;
        for (j=i+1;j< Selection.TAM+1; j++) {
            
           ++Selection.numeros_de_repeticoes;
            if(Selection.vetor[j] < Selection.vetor[menor]){
                menor = j;
            }
        }
        if (i !=menor){
            trocar(i, menor);
            
            Selection.numero_de_comparacoes ++;
            Selection.numeros_de_repeticoes ++;
        }
    }
}
void SelectionSort::mostrar(){
    Selection.mostrar();
}

void SelectionSort::trocar(int i,int j){
    long aux;
    aux = Selection.vetor[i];
    Selection.vetor[i] = Selection.vetor[j];
    Selection.vetor[j] = aux;
}







QuickSort::QuickSort(long tam){
    Quick.TAM = tam;
    Quick.vetor = (long*) malloc(sizeof(long)*tam);
    Quick.indice = 0;
    Quick.numeros_de_repeticoes = 0;
    Quick.numero_de_comparacoes = 0;
    cout << " Vetor cirado com sucesso!" << tam <<endl;
}

void QuickSort::inserir(long N){
    Quick.inserir(N);
}

long QuickSort::particao(long inicio, long fim){
    long *vetaux = (long*)malloc(sizeof(long)*Quick.TAM);
    long q,r;
    long esquerda, direita;
    long pivot;
    
    pivot = Quick.vetor[inicio];
    esquerda = inicio;
    direita = fim;
    for (q = inicio+1; q<=fim;q++){\
        
       ++Quick.numeros_de_repeticoes;
        if(Quick.vetor[q] < pivot){
             Quick.numero_de_comparacoes ++;
            vetaux[esquerda] = Quick.vetor[q];
            esquerda++;
        }else{
            vetaux[direita] = Quick.vetor[q];
            direita--;
        }
    }
    vetaux[direita] = pivot;
    for (r = inicio;r<=fim;r++) {
        Quick.vetor[r] = vetaux[r];
    }
    return direita;
}
void QuickSort::quicksort(long inicio,long fim){
    if (inicio < fim){
        long p = particao(inicio,fim);
        quicksort(inicio, p-1);
        quicksort(p+1,fim);
    }
}
void QuickSort::mostrar(){
    Quick.mostrar();
}




CountSort::CountSort(long tam){
    Count.TAM = tam;
    Count.vetor = (long*)malloc(sizeof(long)*tam);
    Count.vetorB = (long*)malloc(sizeof(long)*tam);
    Count.indice  = 0;
    Count.numeros_de_repeticoes = 0;
    
    cout << "VetorA e VetorB criados com sucesso: " <<endl;
}
void CountSort::inserir(long N){
    Count.inserir(N);
}

long CountSort::maximo(){
    long maior = -100;
    
    for (int i = 0; i < Count.TAM;  i ++) {
        if (maior < Count.vetor[i]) {
            maior = Count.vetor[i];
        }
    }
    return maior;
}

void CountSort::ordenaCountSort(){
    long maior = maximo();
    long *vetorC;
    vetorC = (long*)malloc(sizeof(long)*maior);
    for (int i = 0; i <= maior; i++) {
        vetorC[i] = 0;
    }
    for (int j = 0; j < Count.TAM; j++) {
        ++vetorC[Count.vetor[j]];
    }
    for (int k = 1; k <= maior; k++){
        vetorC[k] = vetorC[k] + vetorC[k - 1];
    }
    for (int g = 0; g < Count.TAM; g++){
        Count.vetorB[vetorC[Count.vetor[g]] -1] = Count.vetor[g];
        vetorC[Count.vetor[g]] = vetorC[Count.vetor[g]] - 1;
    }
    
    
}






