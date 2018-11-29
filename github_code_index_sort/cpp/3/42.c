#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_
#include "listaAdj/Grafo.h"
#include "BuscaEmProfundidade.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using listaAdj::Grafo;

namespace grafos {

    /* Definição do Header da classe topological */
    class Topological {
        
    private:
            
        int numRestantes, numVertices, *t;
        bool *restantes;

    public: 

        Grafo *grafo;

        Topological (Grafo *grafo); 
        ~Topological (); 

        int maxTT ();
        void obterTopological () const;
        void imprime ();    
    };
    /* Fim da definição do Header da classe Topological */

    //-------------[ Implementação ]  
   
    /* Construtor */
    Topological::Topological (Grafo *grafo) {
        this->grafo = grafo;

        this->t = new int[this->grafo->_numVertices ()];
        this->restantes = new bool[this->grafo->_numVertices ()];
        this->numVertices = this->numRestantes = this->grafo->_numVertices ();
    }

    /* Destrutor */
    Topological::~Topological () {
        this->grafo = NULL;

        delete [] t;
        delete [] restantes;
    }

    /* Retorna o vértice com o maior tempo de término */
    int Topological::maxTT () {
        int vMax = 0;

        while (!this->restantes[vMax]) {
            vMax++;
        }

        for (int i = 0; i < this->numVertices; i++) {
            if (this->restantes[i]) {
                if (this->t[i] > this->t[vMax]) {
                    vMax = i;
                }
            }
        }
        this->restantes[vMax] = false;
        return vMax;
    }

    /* Obter topological-sort */
    void Topological::obterTopological () const {
        BuscaEmProfundidade dfs (this->grafo);
        dfs.buscaEmProfundidade ();

        for (int u = 0; u < this->grafo->_numVertices (); u++) {
            this->t[u] = dfs._t (u);
            this->restantes[u] = true;
        }
    }

    void Topological::imprime () {
        int *time = new int[this->numVertices];
        for (int i = 0; i < this->numVertices; i++) {
            time[i] = t[i];
        }

        std::sort(time, time + this->numVertices);

        for (int i = 0; i < this->numVertices; i++) {
            for (int j = 0; j < this->numVertices; j++) {
                if (time[i] == t[j]){
                    cout << j+1 << " ";
                }
            }
            //cout << this->maxTT()+1 << " ";
        }
        cout << endl;
    }
}
#endif
