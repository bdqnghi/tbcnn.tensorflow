#include <iostream>

#define TAM 8

using namespace std;

void mostrarVetor(int *vetor);
void shellSort(int *vetor);

int main() {
  int vetor[] = {35,33,42,10,14,19,27,44};
  mostrarVetor(vetor);
  shellSort(vetor);
  mostrarVetor(vetor);
  return 0;
}

void mostrarVetor(int *vetor) {
  for(int i = 0; i < TAM; i++) {
    cout << vetor[i] << " ";
  }
  cout << endl;
}

void shellSort(int *vetor) {
  int intervalo = 1;
  while(intervalo < (TAM/3)) {
    intervalo = (intervalo * 3) + 1;
  }
  while(intervalo > 0) {
    for(int i = intervalo; i < TAM; i ++) {
      int aux = vetor[i];
      int j = i;
      while(j > intervalo-1 && vetor[j-intervalo] >= aux) {
        vetor[j] = vetor[j-intervalo];
        j = j - intervalo;
      }
      vetor[j] = aux;
    }
    intervalo = (intervalo-1)/3;
  }
}
