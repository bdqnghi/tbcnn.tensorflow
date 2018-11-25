#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 5
int vetor[MAX];

void ordena(int *aux, int aa, int pp);
int main();


int inserir(){
	
	for(int i=0;i<MAX;i++){
		printf("Valor a ser digitado:");
		scanf("%i",&vetor[i]);
	}	
	ordena(vetor,0, MAX - 1);
	system("cls");
	return 0;
}


void ordena(int *aux, int aa, int pp){
	 int i, j, x, y;
	 i = aa;
     j = pp;
     x = aux[(aa + pp) / 2];
     
    while(i <= j) {
        while(aux[i] < x && i < pp) {
            i++;
        }
        while(aux[j] > x && j > aa) {
            j--;
        }
        if(i <= j) {
            y = aux[i];
            aux[i] = aux[j];
            aux[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > aa) {
        ordena(aux, aa, j);
    }
    if(i < pp) {
        ordena(aux, i, pp);
    }
}

void exibir(){
	
	printf("Imprimindo os valores inseridos em ordem\n");
    for (int i=0; i<MAX; i++){
        printf("\n Posi��o: %i | N�mero: %i",i+1,vetor[i]);
    }
    
    printf("\n\n\n");
	system("pause");
	system("cls");
}

int main(){
	int op=0;
	setlocale(LC_ALL,"Portuguese");
	printf("Estrutura de Dados I - Quick Sort\n");
	for(;;){
			printf("Digite a op��o desejada\n\n1 - Inserir\n2 - Exibir\n3 - Sair\n\nOp��o:");
		scanf("%i",&op);			
		
		
		if(op==1){
			inserir();
		}
		if(op==2){
			exibir();
		}
		
		if(op==3){
			printf("\n\nSaindo...");
			exit(1);
		}
	}
}
