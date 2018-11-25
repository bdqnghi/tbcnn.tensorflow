#include "Graph.h"

class DepthFirstSearch{

	public:
		int time;
		List *topologica;
		int compConexas;

		DepthFirstSearch();
		void visit(Graph *graph, int index);
		void visitTopologica(Graph *graph, int index);
		void visitCc(Graph *graph, int index);
		void DFS(Graph *graph);
		void ordenacaoTopologica(Graph *graph);
		void checaCiclo(Graph *graph);
		void componentesConexas(Graph *graph);
		~DepthFirstSearch();
};

DepthFirstSearch::DepthFirstSearch(){

	time = 0;
	topologica = new List();
	compConexas = 0;
}

void DepthFirstSearch::visit(Graph *graph, int index){

	Node *aux;
	time++;
	graph->vertexes[index].timePush = time;
	graph->vertexes[index].paint();
	cout<<"Visitei o vértice "<<index<<" e empilhei!"<<endl;
	for(aux = graph->vertexes[index].neighbors->first;  aux != NULL; aux = aux->next){

		if(graph->vertexes[aux->value].color == 'w'){

			graph->vertexes[aux->value].previous = &graph->vertexes[index];
			visit(graph, aux->value);
		}
	}

	cout<<"Desempilhei "<<index<<endl;
	graph->vertexes[index].paint();
	time++;
	graph->vertexes[index].timePop = time;
}


void DepthFirstSearch::visitCc(Graph *graph, int index){

	Node *aux;
	time++;
	graph->vertexes[index].timePush = time;
	graph->vertexes[index].paint();
	cout<<"Visitei o vértice "<<index<<" e empilhei!"<<endl;
	for(aux = graph->vertexes[index].neighbors->first;  aux != NULL; aux = aux->next){

		if(graph->vertexes[aux->value].color == 'w'){

			graph->vertexes[aux->value].previous = &graph->vertexes[index];
			visitCc(graph, aux->value);
		}
	}

	cout<<"Desempilhei "<<index<<endl;
	compConexas++;
	graph->vertexes[index].paint();
	time++;
	graph->vertexes[index].timePop = time;
}



void DepthFirstSearch::visitTopologica(Graph *graph, int index){
	Node *aux;
	time++;
	graph->vertexes[index].timePush = time;
	graph->vertexes[index].paint();
	cout<<"Visitei o vértice "<<index<<" e empilhei!"<<endl;
	for(aux = graph->vertexes[index].neighbors->first;  aux != NULL; aux = aux->next){

		if(graph->vertexes[aux->value].color == 'w'){

			graph->vertexes[aux->value].previous = &graph->vertexes[index];
			visitTopologica(graph, aux->value);
		}
	}
	
	cout<<"Desempilhei "<<index<<endl;
	topologica->insertFirst(index);
	graph->vertexes[index].paint();
	time++;
	graph->vertexes[index].timePop = time;
	
}

void DepthFirstSearch::DFS(Graph *graph){

	for(int i = 0; i < graph->numVertexes; i++)
		if(graph->vertexes[i].color == 'w')
			visit(graph, i);

}

void DepthFirstSearch::componentesConexas(Graph *graph){

	for(int i = 0; i < graph->numVertexes; i++){
		if(graph->vertexes[i].color == 'w'){
			compConexas=0;
			visitCc(graph, i);
		}
		cout<< "Numero de Componentes conexas em "<< i << ": " << compConexas <<endl;
	}

}


void DepthFirstSearch::ordenacaoTopologica(Graph *graph){

	for(int i = 0; i < graph->numVertexes; i++)
		if(graph->vertexes[i].color == 'w')
			visitTopologica(graph, i);

	cout<< "A resposta da ordenação topologica é: " <<endl;
	topologica->printList();
}

void DepthFirstSearch::checaCiclo(Graph *graph){

	for(int i = 0; i < graph->numVertexes; i++){
		if(graph->vertexes[i].color == 'w')
			visit(graph, i);

		else if(graph->vertexes[i].color == 'g')
			cout<<"Ciclo" <<endl;
	}

}


DepthFirstSearch::~DepthFirstSearch(){}