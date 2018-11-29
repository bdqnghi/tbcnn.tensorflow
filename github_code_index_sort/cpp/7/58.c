#ifndef SHELLSORT
#define SHELLSORT

#include <iostream>
#include "Ordenacion/ordenacion.h"

using namespace std;

template <class T>
class shellSort
{
	private:
		int contador_;
	public:
		shellSort();
		~shellSort();

		int get_contador();
		void algoritmo(T* secuencia, int tam, int metodo);

		ostream& write(ostream& os, T* secuencia, int tam, int j, int k);
};

template <class T>
shellSort<T>::shellSort():
	contador_(0)
{}

template <class T>
shellSort<T>::~shellSort()
{
	contador_ = 0;
}

template <class T>
int shellSort<T>::get_contador()
{
	return contador_;
}

template <class T>
void shellSort<T>::algoritmo(T* secuencia, int tam, int metodo)
{
	float alpha;

	if (metodo == 1){
		alpha=2;
		while ((alpha < 0) || (alpha > 1)){
			cout << "Introduzca el alpha [0 < alpha < 1]:" << endl;
			cin >> alpha;
		}
	}
	else
		alpha = 0.5;

	int imp = 1;

	for(int del = alpha*tam; del > 0; del/=2)
	{
		for (int i = del; i < tam; i++)
		{
			for (int j = i-del; j >= 0; j -= del)
			{
				if(metodo == 1){
					write(cout, secuencia, tam, j, j+del);
					if(imp == 1){
						cin.ignore();
						imp++;
					}
					cin.ignore();
				}
				else
					contador_++;

				if(secuencia[j] > secuencia[j+del]){
					T temp = secuencia[j];
					secuencia[j] = secuencia[j+del];
					secuencia[j+del] = temp;
				}
				else
					break;
			}
		}
	}
	if(metodo == 1)
		write(cout, secuencia, tam, -1, -1);
}

template <class T>
ostream& shellSort<T>::write(ostream& os, T* secuencia, int tam, int j, int k)
{
	for (int i = 0; i < tam; i++)
	{
		if ((i != j) && (i != k))
			os << secuencia[i] << " ";
		else
			cout << "[" << secuencia[i] << "] ";
	}
	os << endl;
	return os;
}

#endif // SHELLSORT

