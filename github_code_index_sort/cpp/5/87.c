#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;

void bubblesort(int *v, int tam){
  int aux;
  for(int i = 1; i < tam; i++){
    for(int j = 0; j < tam-1; j++){
      if (v[j] > v[j+1]){
        aux = v[j];
        v[j]=v[j+1];
        v[j+1]=aux;
      }
    }
  }
}

int main(){
  int v[10];

  for (int k = 0; k<10; k++)
    v[k] = 0;

  for (int i=0; i<10; i++)
  {
     printf("Digite o valor de v[%d]:", i);
     scanf("%d", &v[i]);
  }

  bubblesort(v,10);

  for(int i = 0; i < 10; i++){
    printf("v[%d] = %d\n", i,v[i]);
  }

  return(0);

}
