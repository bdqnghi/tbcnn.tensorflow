#include <fstream>
#include <iostream>
#include <string>

#include "Heap.h"

namespace Mrowka {

	Heap::Heap() {
		this->_size = 0;
		this->_heap = nullptr;
	}

	Heap::Heap(std::string path) {
		std::fstream file;
		int j, father, x;
		file.open(path, std::ios::in);
		
		if (file.good()) {
			std::cout << "Udalo sie otworzyc plik.\n";
			file >> _size;
			this->_heap = new int[_size];

			for (int i = 0; i < _size; ++i) {
				file >> _heap[i];
			}

			for (int i = 1; i < _size; ++i) {
				father = ((i + 1) / 2) - 1;
				j = i;
				x = _heap[i];

				while (x > _heap[father] && father >= 0) {
					_heap[j] = _heap[father];
					_heap[father] = x;
					j = father;
					father = ((father + 1) / 2) - 1;
				}
			}
		}
		else {
			std::cout << "Nie udalo sie otworzyc pliku.\n";
		}

		file.close();
	}

	Heap::~Heap() {
		delete[] this->_heap;
		this->_heap = nullptr;
	}

	bool Heap::Add(int value) {
		int *heap;
		int x, father, j;
		heap = new int[_size + 1];

		for (int i = 0; i < _size; ++i) {
			heap[i] = _heap[i];
		}

		heap[_size] = value;
		delete[] this->_heap;
		++_size;
		this->_heap = heap;

		// przywrocenie struktury

		x = _heap[_size - 1];
		father = (_size / 2) - 1;
		j = _size - 1;

		while (x > _heap[father] && father >= 0) { // przesuwanie nowego elementu w stron� korzenia
			_heap[j] = _heap[father];
			_heap[father] = x;
			j = father;
			father = ((father + 1) / 2) - 1;
		}

		return true;		
	}

	bool Heap::Delete(int value) {
		int j = -1;
		int father, x;
		bool found = false;

		if (value == _heap[0]) {
			_heap[0] = _heap[_size - 1];
			found = true;
		}
		else {
			
			for (int i = 0; i < _size; ++i) {

				if (value == _heap[i]) {
					j = i;
					i = i + _size;
				}
			}

			if (j != -1)
			{
				_heap[j] = _heap[_size - 1];
			}
			
			found = true;
		}

		if (found) {
			int * heap;
			heap = new int[_size - 1];
			--_size;

			for (int i = 0; i < _size; ++i) {
				heap[i] = _heap[i];
			}

			delete[] _heap;
			_heap = heap;

			for (int i = 1; i < _size; ++i) {
				father = ((i + 1) / 2) - 1;
				j = i;
				x = _heap[i];

				while (x > _heap[father] && father >= 0) {
					_heap[j] = _heap[father];
					_heap[father] = x;
					j = father;
					father = ((father + 1) / 2) - 1;
				}
			}

			return true;
		}
		else {
			return false;
		}
	}

	bool Heap::Search(int value) {
		if (value == _heap[0]) {
			return true;
		}
		else if (value > _heap[0]) { // na szczycie jest najwieksza wartosc, wiec jesli wyszukiwana jest wieksza niz korzen, to znaczy ze nie ma takiej wartosci
			return false;
		}
		else {

			for (int i = 1; i < _size; ++i) {
				
				if (_heap[i] == value) {
					return true;
				}
			}
		}

		return false;
	}

	int Heap::GetSize() {
		return _size;
	}

	void Heap::View(std::string sp, std::string sn, int v) {
		std::string cr, cl, cp, s;
		cr = cl = cp = "  ";
		cr[0] = 218; cr[1] = 196;
		cl[0] = 192; cl[1] = 196;
		cp[0] = 179; // uzycie kodow ascii, aby stworzyc 'ramke'

		if (v < _size) {
			s = sp; 
			
			if (cr == sn) { 
				s[s.length() - 2] = ' ';
			}

			View((s + cp), cr, (2 * v + 2));
			s = s.substr(0, sp.length() - 2);
			std::cout << s << sn << _heap[v] << std::endl;
			s = sp;

			if (sn == cl) {
				s[s.length() - 2] = ' ';
			}

			View((s + cp), cl, (2 * v + 1));
		}
	}

}