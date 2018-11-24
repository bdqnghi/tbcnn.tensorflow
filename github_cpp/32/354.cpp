#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Aresta {

	int origem, destino, peso;

};

struct Grafo{

	int V, A;

	struct Aresta* aresta;

};


struct Grafo* criaGrafo(int V, int A) {
	struct Grafo* grafo = new Grafo;
	grafo->V = V;
	grafo->A = A;

	grafo->aresta = new Aresta[A];

	return grafo;
}

struct subconjunto{
	int pai;
	int classificacao;
};

int buscaConjunto(struct subconjunto subconjuntos[], int i) {

	if (subconjuntos[i].pai != i)
		subconjuntos[i].pai = buscaConjunto(subconjuntos, subconjuntos[i].pai);

	return subconjuntos[i].pai;
}


void uniaoConjunto(struct subconjunto subconjuntos[], int x, int y) {

	int xroot = buscaConjunto(subconjuntos, x);
	int yroot = buscaConjunto(subconjuntos, y);

	if (subconjuntos[xroot].classificacao < subconjuntos[yroot].classificacao) {
		subconjuntos[xroot].pai = yroot;
	} else if (subconjuntos[xroot].classificacao > subconjuntos[yroot].classificacao) {
		subconjuntos[yroot].pai = xroot;
	} else {
		subconjuntos[yroot].pai = xroot;
		subconjuntos[xroot].classificacao++;
	}

}


int comparaPesos(const void* a, const void* b) {

	struct Aresta* a1 = (struct Aresta*)a;
	struct Aresta* b1 = (struct Aresta*)b;
	return a1->peso > b1->peso;

}


void Kruskal(struct Grafo* grafo) {

	int V = grafo->V;
	struct Aresta resultado[V];
	int a = 0;
	int i = 0;

	qsort(grafo->aresta, grafo->A, sizeof(grafo->aresta[0]), comparaPesos);

	struct subconjunto *subconjuntos =
		(struct subconjunto*) malloc( V * sizeof(struct subconjunto) );


	for (int v = 0; v < V; ++v)
	{
		subconjuntos[v].pai = v;
		subconjuntos[v].classificacao = 0;
	}

	while (a < V - 1) {

		struct Aresta next_aresta = grafo->aresta[i++];

		int x = buscaConjunto(subconjuntos, next_aresta.origem);
		int y = buscaConjunto(subconjuntos, next_aresta.destino);

		if (x != y) {

			resultado[a++] = next_aresta;
			uniaoConjunto(subconjuntos, x, y);

		}

	}

	printf("As seguintes arestas foram construídas com MST\n");

	for (i = 0; i < a; ++i){

		printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino,
												resultado[i].peso);
	}
	return;

}

int main() {



	int V = 4;
	int A = 5;
	struct Grafo* grafo = criaGrafo(V, A);


	grafo->aresta[0].origem = 0;
	grafo->aresta[0].destino = 1;
	grafo->aresta[0].peso = 10;


	grafo->aresta[1].origem = 0;
	grafo->aresta[1].destino = 2;
	grafo->aresta[1].peso = 6;

	grafo->aresta[2].origem = 0;
	grafo->aresta[2].destino = 3;
	grafo->aresta[2].peso = 5;


	grafo->aresta[3].origem = 1;
	grafo->aresta[3].destino = 3;
	grafo->aresta[3].peso = 15;

	grafo->aresta[4].origem = 2;
	grafo->aresta[4].destino = 3;
	grafo->aresta[4].peso = 4;

	Kruskal(grafo);

	return 0;

}
