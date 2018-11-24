//
// Created by thamian on 13.05.17.
//

#include "Kruskal.h"

Kruskal::Kruskal() {

}

void Kruskal::execute(ListGraph *listGraph) {
    numberOfEdges_ = listGraph->getNumberOfEdges();
    priorityQueue = new EdgeHeap(numberOfEdges_);       // Rozmiar ustalany z góry - optymalizacja.
    numberOfVertices_ = listGraph->getNumberOfVertices();

    int numberOfAllResultEdges = numberOfVertices_ - 1;

    Edge **results = new Edge * [numberOfAllResultEdges];

    Node *vertexFromList;

    for (int i = 0; i < numberOfVertices_; i++) {
        vertexFromList = listGraph->getLinkedList(i)->getHead();

        while (vertexFromList != NULL) {
            priorityQueue->push(new Edge(vertexFromList->getWeight(), i, vertexFromList->getValue()));
            vertexFromList = vertexFromList->getNext();
        }
    }

    subsets_ = new Subset * [numberOfVertices_];
    for (int j = 0; j < numberOfVertices_; j++) {
        subsets_[j] = new Subset(j);
    }

    int currentResultEdge = 0;
    int firstSubset;
    int secondSubset;
    Edge *currentEdge;
    while (currentResultEdge < numberOfAllResultEdges) {
        currentEdge = priorityQueue->pop();

        firstSubset = findSubset(currentEdge->getSourceVertex());
        secondSubset = findSubset(currentEdge->getDestinationVertex());

        if (firstSubset != secondSubset) {
            makeUnion(firstSubset, secondSubset);
            results[currentResultEdge] = currentEdge;
            currentResultEdge++;
        }
    }
/*
    int suma = 0;
    for (int k = 0; k < numberOfAllResultEdges; k++) {
        std::cout << "(" << results[k]->getSourceVertex() << ", " << results[k]->getDestinationVertex() << ") W: " << results[k]->getWeight() << "\n";
        suma += results[k]->getWeight();
    }
    std::cout << "MST = " << suma << "\n";
*/
    for (int l = 0; l < numberOfVertices_; ++l) {
        delete subsets_[l];
    }

    delete priorityQueue;
    delete [] subsets_;
    delete [] results;
}

void Kruskal::execute(MatrixGraph *matrixGraph) {
    numberOfEdges_ = matrixGraph->getNumberOfEdges();
    priorityQueue = new EdgeHeap(numberOfEdges_);       // Rozmiar ustalany z góry - optymalizacja.
    numberOfVertices_ = matrixGraph->getNumberOfVertices();

    int numberOfAllResultEdges = numberOfVertices_ - 1;

    Edge **results = new Edge * [numberOfAllResultEdges];

    for (int i = 0; i < numberOfVertices_; i++) {
        for (int j = 0; j < numberOfVertices_; j++) {
            if (matrixGraph->adjacencyMatrix_[i][j] != INT32_MAX) {
                priorityQueue->push(new Edge(matrixGraph->adjacencyMatrix_[i][j], i, j));
            }
        }
    }

    subsets_ = new Subset * [numberOfVertices_];
    for (int j = 0; j < numberOfVertices_; j++) {
        subsets_[j] = new Subset(j);
    }

    int currentResultEdge = 0;
    int firstSubset;
    int secondSubset;
    Edge *currentEdge;
    while (currentResultEdge < numberOfAllResultEdges) {
        currentEdge = priorityQueue->pop();

        firstSubset = findSubset(currentEdge->getSourceVertex());
        secondSubset = findSubset(currentEdge->getDestinationVertex());

        if (firstSubset != secondSubset) {
            makeUnion(firstSubset, secondSubset);
            results[currentResultEdge] = currentEdge;
            currentResultEdge++;
        }
    }
/*
    int suma = 0;
    for (int k = 0; k < numberOfAllResultEdges; k++) {
        std::cout << "(" << results[k]->getSourceVertex() << ", " << results[k]->getDestinationVertex() << ") W: " << results[k]->getWeight() << "\n";
        suma += results[k]->getWeight();
    }
    std::cout << "MST = " << suma << "\n";
*/
    for (int l = 0; l < numberOfVertices_; ++l) {
        delete subsets_[l];
    }

    delete priorityQueue;
    delete [] subsets_;
    delete [] results;
}

// findSubset
//
// Tablica subsets zawiera numery wierzchołków i ranking dla każdego z nich.
// Przypomina trochę strukturę drzewiastą - indeks tablicy odpowiada numerowi wierzchołka, a parent_
// jest nadrzędnym elementem, który reprezentuje zbiór.
// Funkcja wykorzystuje optymalizację poprzez kompresję ścieżki - (w skrócie) dla głębiej położonych wierzchołków
// nie zawsze nadrzędnym elementem jest korzeń drzewa. Funkcja ustala korzeń drzewa dla rodzica tych głębiej położonych elementów
// dzięki czemu, wiele wierzchołków będzie wskazywało na korzeń drzewa. Kolejne wyszukiwania będą szybsze.
// Funkcja zwraca reprezentanta podzbioru dla podanego wierzchołka. Na tej podstawie określamy, czy dwa wierzchołki należą do tego samego podzbioru.
// Na tej podstawie określany jest cykl w algorytmie.
int Kruskal::findSubset(int vertexNumber) {
    if (subsets_[vertexNumber]->parent_ != vertexNumber)        // Jeśli rodzic nie jest tym samym elementem, to trzeba znaleźć korzeń drzewa i przypisać dla optymalizacji.
        subsets_[vertexNumber]->parent_ = findSubset(subsets_[vertexNumber]->parent_);
    return subsets_[vertexNumber]->parent_;
}

// makeUnion
//
// Łączy dwa podzbiory, w których są 2 podane wierzchołki.
// Optymalizacja na podstawie rangi - drzewa z mniejszą rangą są przyłączany do tych z większą.
// W przypadku tej samej rangi, jedno drzewo jest przyłączane do drugiego, a ranga nowego drzewa zwiększana o jeden.
void Kruskal::makeUnion(int firstVertex, int secondVertex) {
    int rootOfFirstVertex = findSubset(firstVertex);
    int rootOfSecondVertex = findSubset(secondVertex);

    if (subsets_[rootOfFirstVertex]->rank_ < subsets_[rootOfSecondVertex]->rank_)
        subsets_[rootOfFirstVertex]->parent_ = rootOfSecondVertex;       // Przyłączamy mniejsze drzewo (first) do większego.
    else if (subsets_[rootOfFirstVertex]->rank_ > subsets_[rootOfSecondVertex]->rank_)
        subsets_[rootOfSecondVertex]->parent_ = rootOfFirstVertex;       // Przyłączamy większe drzewo (second) do większego.
    else {
        subsets_[rootOfSecondVertex]->parent_ = rootOfFirstVertex;       // Gdy rangi takie same przyłączamy jedno do drugiego
        subsets_[rootOfFirstVertex]->rank_++;                            // i zwiększamy rangę nowego drzewa.
    }
}

Kruskal::~Kruskal() {

}
