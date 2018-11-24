#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Aresta{
public:
	int origem, destino, peso;

	Aresta(int origem, int destino, int peso){
		this->origem = origem;
		this->destino = destino;
		this->peso = peso;
	}
};

bool compara(Aresta num1, Aresta num2){
	return (num1.peso < num2.peso);
}

void exibevector(vector<Aresta>grafo){
	for(int i = 0; i < grafo.size(); i++){
		cout << " " << grafo[i].origem;
		cout << "-" << grafo[i].destino;
		cout << " " << grafo[i].peso << endl;
	}
}

int main(){

	vector<Aresta> grafo;
	vector<Aresta> solucao;
	vector<Aresta> aux;

	int tamanho = 0, custo = 0;

	//Lendo a matriz a partir de um arquivo
	ifstream grafo_matriz("dij10.txt", ios::in);
	
	grafo_matriz >> tamanho; //salva o tamanho da matriz

	int matriz[tamanho][tamanho]= {0};

	int estimativa[tamanho];
	int pai[tamanho];
	bool verificado[tamanho];

	//inicia estimativa, pai e verificado com seus respectivos valores 
	for(int i = 0; i < tamanho; i++){
		estimativa[i] = 2147483647;
		pai[i] = -1;
		verificado[i] = false;
	}

	for (int i = 0; i < tamanho; i++){
		for (int j = i; j < tamanho; j++){
			if (i == j)
				continue;
			grafo_matriz >> matriz[i][j];
			
		}
	}

	for (int i = 0; i < tamanho; i++){
		for (int j = i + 1; j < tamanho; j++){
			Aresta aresta(i,j,matriz[i][j]);
			grafo.push_back(aresta);
		}
	}

	//Adicionando os adjacentes ao vertice inicialS
	for(int i = 0; i < grafo.size(); i++){
			if(grafo[i].origem == 0){
				aux.push_back(grafo[i]);
			}
	}

	sort(aux.begin(), aux.end(), compara);

	solucao.push_back(aux[0]);
	estimativa[0] = 0;
	estimativa[aux[0].destino] = aux[0].peso;
	pai[0] = 0;
	pai[aux[0].destino] = aux[0].origem;
	verificado[0] = true;
	int indice = aux[0].destino;
	aux.erase(aux.begin());
	
	bool auxiliar = false;
	int t = 0;

	while(true){
		for(int i = 0; i < grafo.size(); i++){
			if(grafo[i].origem == indice){
				aux.push_back(grafo[i]);
			}	
		}
		
		sort(aux.begin(), aux.end(), compara);
		
		if(aux[0].peso < estimativa[aux[0].destino]){
			estimativa[aux[0].destino] = aux[0].peso + estimativa[pai[aux[0].origem]];
			pai[aux[0].destino] = aux[0].origem;
			solucao.push_back(aux[0]);
			indice = aux[0].destino;
			aux.erase(aux.begin());
		}else{
			aux.erase(aux.begin());
		}
		
		verificado[indice] = true;

		if(solucao.size() == tamanho - 1)
			break;
	}

	exibevector(solucao);

	for (int i = 0; i < solucao.size(); i++){
		
		custo += solucao[i].peso;
	}
	cout << "Custo da solução: " << custo << endl;
	
	return 0;

}

