#include "BubbleSort.h"

//Construtor
BubbleSort::BubbleSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}

//Destrutor
BubbleSort::~BubbleSort()
{
}

//Retorna o numero de trocas feitas
int BubbleSort::getNumTrocas()
{
	return numTrocas;
}

//Retorna o numero de comparacoes feitas
int BubbleSort::getNumComparacoes()
{
	return numCompar;
}

//Retorna o tempo gasto pela ordenacao
double BubbleSort::getTempoGasto()
{
	return tempoGasto;
}

void BubbleSort::limpaDados()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0;
}

//Realiza Troca de Posicoes entre 2 Objetos do tipo Tweet
//ENTRADA: 2 Objetos do tipo Tweet
//SAIDA: Dois objetos trocados de posicao entre si
void BubbleSort::troca(Tweet* &t1, Tweet* &t2)
{
	if (t1 != t2) //Nao troca se t1 e t2 sao iguais, ja que nao precisa
	{
		Tweet* aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}

//Algoritmo BubbleSort
//ENTRADA: Vetor de objetos do tipo Tweet e seu tamanho
//SAIDA: Tal vetor ordenado via BubbleSort
void BubbleSort::bubblesort(Tweet* vet[], int tam)
{
	clock_t relogio;
	relogio = clock();
	for (int i = 0; i < tam - 1; i++)
		for (int j = 0; j < tam - i - 1; j++)
		{
			if (vet[j]->getTweetID() > vet[j + 1]->getTweetID() && ++numCompar)
			{
				troca(vet[j], vet[j + 1]);
			}
		}
	tempoGasto += (clock() - relogio) / (double)CLOCKS_PER_SEC;
}