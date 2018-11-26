//============================================================================
// Author      	: David Dorta Acosta
// email       	: alu0100851236@ull.edu.es
// Asignatura  	: Algoritmos y Estructura de Datos Avanzadas
// Curso			: 2017-2018
// Práctica 5	: Implementación de métodos de ordenación
//============================================================================

#include "common_types.hpp"

using namespace std;

template <class T>
class ShellSort{
	private:
		int tam_vec;
		int comparaciones;
		T* datos;

	public:
		// CONSTRUCTOR
		ShellSort(int tam);

		// DESTRUCTOR
		~ShellSort();

		// METODOS
		void setDato(T dato, int pos);
		void baja (int pos, int n);
		void ordenar (double alfa, bool imprimir);
		void deltasort(int delta, bool imprimir);
		void mostrar ();
		int getComparaciones ();
};

template <class T>
ShellSort<T>::ShellSort(int tam):
		tam_vec(tam),
		comparaciones(0),
		datos(new T[tam_vec])
		{}

template <class T>
ShellSort<T>::~ShellSort(){}

template <class T>
void ShellSort<T>::setDato(T dato, int pos)
{
	datos[pos] = dato;
}

template <class T>
void ShellSort<T>::ordenar(double alfa, bool imprimir)
{
	int delta = alfa * tam_vec;

	while (delta >= 1)
	{
		// ## CONTADOR DE LAS COMPARACIONES PARA LAS ESTADÍSTICAS
		comparaciones++;

		// ## MOSTRAR TRAZA PARA EL MODO DEMOSTRACIÓN
		if (imprimir == true)
			cout << endl << "  # Delta: " << delta << endl;
		// ## FIN DE TRAZA

		deltasort(delta, imprimir);
		delta = delta / 2;
	}
}

template <class T>
void ShellSort<T>::deltasort(int delta, bool imprimir)
{
	for (int i = delta; i < tam_vec; i++)
	{
		T x = datos[i];
		int j = i;

		// ## MOSTRAR TRAZA PARA EL MODO DEMOSTRACIÓN
		if (imprimir == true)
		{
			cout << "    # - Subsecuencia " << i << ": " << endl;
			cout << "    # - Número en la posición " << i << " es, " << setfill('0') << setw(8) << datos[i] << endl;
			cout << "    # - Número en la posición " << j - delta << " es, " << setfill('0') << setw(8) << datos[j - delta] << endl;
			cout << "  # - El vector en la subsecuencia " << i << " es, " << endl;
			mostrar();
			cout << "  # - Pulsar enter para continar" << endl;
			string t;
			getline(cin,t);
		}
		// ## FIN DE TRAZA

		while ((j >= delta) && (x < datos[j - delta]))
		{
			datos[j] = datos[j - delta];
			j = j - delta;

			// ## CONTADOR DE LAS COMPARACIONES PARA LAS ESTADÍSTICAS
			comparaciones++;
		}

		datos[j] = x;
	}
}

template <class T>
void ShellSort<T>::mostrar(){
	cout << "  # " ;
	for (int i = 0; i < tam_vec; i++)
	{
		cout << setfill('0') << setw(8) << datos[i] << ", ";
	}
	cout << endl;
}

template <class T>
int ShellSort<T>::getComparaciones()
{
	return comparaciones;
}
