
#include"funcaoadd.h"
#include"includes.h"

//Merge sort
void mergeSort(long *vetor, long tamvetor, long *vetoraux) {
	
	long meio = (tamvetor/2);
	if(tamvetor > 1){
		mergeSort(vetor, meio,vetoraux);
		mergeSort(vetor + meio, tamvetor - meio, vetoraux);
		merge(vetor, tamvetor,vetoraux);
	}
}
void merge(long *vetor, long tamvetor,long *vetoraux) {
	
	long i, j, k ,meio = tamvetor / 2;

	i = 0;
	j = meio;
	k = 0;
	while (i < meio && j < tamvetor) 
	{
		if (vetor[i] < vetor[j])
		{
			vetoraux[k] = vetor[i];
			++i;
		}
		else
		{
			vetoraux[k] = vetor[j];
			++j;
		}
		++k;
	}

	if (i == meio)
	{
		while (j < tamvetor) {
			vetoraux[k] = vetor[j];
			++j;
			++k;
		}
	}
	else
	{
		while (i < meio) {
			vetoraux[k] = vetor[i];
			++i;
			++k;
		}
	}
	for (i = 0; i < tamvetor; ++i)
	{
		vetor[i] = vetoraux[i];
	}
}


