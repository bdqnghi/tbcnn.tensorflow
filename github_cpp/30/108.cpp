/*
 * Dijkstra.cpp
 *
 *  Created on: 28.05.2014
 *      Author: christoph
 */

#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph* graph) {
	this->graph = graph;

}

Dijkstra::~Dijkstra() {
	//Nichts konstruiert
}

list<Knoten*> Dijkstra::starteDijkstra(Knoten* startKnoten, Knoten* endKnoten) {
	starteDijkstra(startKnoten);
	return (getRoute(startKnoten, endKnoten));
}

void Dijkstra::starteDijkstra(Knoten* startKnoten) {
	Knoten * aktuellerKnoten = NULL;
	PriorityQueue queue = PriorityQueue(graph, startKnoten);
	aktuellerKnoten = queue.getFirst();
	while (aktuellerKnoten != NULL) {
		queue.nacholfgerEintragen(aktuellerKnoten);
		aktuellerKnoten = queue.getFirst();
	}
}

list<Knoten*> Dijkstra::dreheListe(list<Knoten*>* liste) {
	list<Knoten*> rueckwaertsErgebnis;
	list<Knoten*> ergebnis;
	//Jetzt die Liste umdrehen, damit die Strecke nicht von Ende nach Start angezeigt wird
	for (auto it = liste->rbegin(); it != liste->rend(); it++) {
		ergebnis.push_back(*it);
	}
	return (ergebnis);

}

list<Knoten*> Dijkstra::getRoute(Knoten* startKnoten, Knoten* endKnoten) {
	//Ergebnis vom Endknoten aus aufbauen
	list<Knoten*> rueckwaertsErgebnis;
	Knoten* ergebnisKnoten = endKnoten;
	while (ergebnisKnoten != NULL && ergebnisKnoten != startKnoten) {
		rueckwaertsErgebnis.push_back(ergebnisKnoten);
		ergebnisKnoten = ergebnisKnoten->getVorgaenger();
	}
	return (dreheListe(&rueckwaertsErgebnis));
}
