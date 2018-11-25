
#include "BubbleSort.h"


BubbleSort::BubbleSort()
{
	numTrocas = 0;
	numCompar = 0;
	tempoGasto = 0.0;
}


BubbleSort::~BubbleSort()
{
}


int BubbleSort::getNumTrocas()
{
	return numTrocas;
}


int BubbleSort::getNumComparacoes()
{
	return numCompar;
}


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




void BubbleSort::troca(Tweet* &t1, Tweet* &t2)
{
	if (t1 != t2) 
	{
		Tweet* aux = t1;
		t1 = t2;
		t2 = aux;
		numTrocas++;
	}
}




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