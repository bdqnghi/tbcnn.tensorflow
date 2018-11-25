#include <iostream>
#include <vector>
#include <cstdlib>

#include "Medicion.hpp"
#include "Funciones.hpp"

#include "Quicksort.hpp"
#include "QuicksortInsercion.hpp"
#include "QuicksortMediana.hpp"

using namespace std;

int main() {

	srand(time(NULL));

	system("clear");

	unsigned int numeroElementos;
	do {
		cout << "Introduce el número de elementos del vector: ";
		cin >> numeroElementos;
	} while (not numeroElementos);
	

	
	Quicksort qs;
	QuicksortInsercion qsI;
	QuicksortMediana qsM;

	unsigned int elementosInsercion = 0;
	do {
		cout << endl << "Introduzca el limite inferior para ordenar el vector segun el metodo de Insercion: ";
		cin >> elementosInsercion;
	} while (0 >= elementosInsercion);
	qsI.setElementosInsercion(elementosInsercion);


	unsigned int elementosMediana = 0;
	do {
		cout << "Introduzca el limite para usar la mediana en el quicksort: ";
		cin >> elementosMediana;
	} while (0 >= elementosMediana);
	qsM.setElementosMediana(elementosMediana);


	cout << endl;





	
	

	Clock clock;
	Medicion quicksort, quicksortInsercion, quicksortMediana;

	vector<int> vector, aux, auxII, auxIII;

	rellenarVector(vector, numeroElementos);

	aux = vector;

	cout << endl << endl << "Número de elementos: " << numeroElementos << endl;

	
	clock.start();
	qs.quickSort(aux, 0,  aux.size()-1);
	clock.stop();
	assert(estaOrdenado(aux));

	quicksort.appendTime(clock.elapsed());
	quicksort.appendX(numeroElementos);
	cout << endl << "  tiempo Quicksort : " << clock.elapsed() << endl;


	cout << endl;
	
	for (unsigned int j = elementosInsercion; j < elementosInsercion*10; j+= elementosInsercion) {
		auxII = vector;
		assert(auxII == vector);

		qsI.setElementosInsercion(j);

		clock.start();
		qsI.quickSort(auxII, 0,  auxII.size()-1);
		clock.stop();
		assert(estaOrdenado(auxII));
		quicksortInsercion.appendTime(clock.elapsed());
		quicksortInsercion.appendX(j);
		cout << "  tiempo Quicksort-Insercion (x=" << j << "): " << clock.elapsed() << endl;
	}


	cout << endl;
	
	for (unsigned int j = elementosMediana; j < elementosMediana*10; j+=elementosMediana) {
		auxIII = vector;
		assert(auxIII == vector);
		qsM.setElementosMediana(j);

		clock.start();
		qsM.quickSort(auxIII, 0,  auxIII.size()-1);
		clock.stop();
		assert(estaOrdenado(auxIII));
		quicksortMediana.appendTime(clock.elapsed());
		quicksortMediana.appendX(j);
		cout << "  tiempo Quicksort-Mediana (x=" << j << "): " << clock.elapsed() << endl;
	}

	
	for (unsigned int i = 0; i < aux.size(); i++) {
		assert(aux[i] == auxII[i]);
		assert(auxII[i] == auxIII[i]);
	}

	vector.clear();
	aux.clear();
	auxII.clear();
	auxIII.clear();




	guardarDatos(
		numeroElementos,
		
		quicksort.getTiempos()[0],
		quicksortInsercion.getTiempos(),
		quicksortInsercion.getNumElementos(),
		quicksortMediana.getTiempos(),
		quicksortMediana.getNumElementos()
	);

	return 0;
}
