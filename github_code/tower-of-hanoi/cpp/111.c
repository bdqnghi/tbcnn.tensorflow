#ifndef ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_ITERATIVE_H_
#define ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_ITERATIVE_H_

#include "tower.h"
#include <cmath>
#include <iostream>

template <typename T>
class TowerOfHanoi {
public:
    TowerOfHanoi();
    ~TowerOfHanoi();

    void Compute(RECURRENCE::Tower<T>& A,
		 RECURRENCE::Tower<T>& B,
		 RECURRENCE::Tower<T>& C);

private:
    void m_move(RECURRENCE::Tower<T>& A,
		RECURRENCE::Tower<T>& B);
    void m_execute(const bool& is_odd,
		   RECURRENCE::Tower<T>& A,
		   RECURRENCE::Tower<T>& B,
		   RECURRENCE::Tower<T>& C);
    void m_print(const RECURRENCE::Tower<T>& A,
		 const RECURRENCE::Tower<T>& B,
		 const RECURRENCE::Tower<T>& C);
};

template <typename T>
TowerOfHanoi<T>::TowerOfHanoi() {}

template <typename T>
TowerOfHanoi<T>::~TowerOfHanoi() {}

template <typename T>
void TowerOfHanoi<T>::Compute(RECURRENCE::Tower<T>& A,
			      RECURRENCE::Tower<T>& B,
			      RECURRENCE::Tower<T>& C) {
    m_print(A, B, C);
    int n = static_cast<int>(std::pow(2, A.Size())) - 1;

    while (1) {
	m_execute(A.Size() % 2, A, B, C);
	n -= 3;

	if (n < 3)
	    break;
    }

    if (n) {
	m_move(A, C);
	m_print(A, B, C);
    }
}

template <typename T>
void TowerOfHanoi<T>::m_move(RECURRENCE::Tower<T>& A,
			     RECURRENCE::Tower<T>& B) {
    // Let's check if both are empty
    if (A.Size() == 0 && B.Size() == 0)
	return;

    // A has element and B is empty, A -> B
    if (A.Size() && B.Size() == 0) {
	B.Back(A.Back());
	return;
    }

    // B has element and A is empty, B -> A
    if (B.Size() && A.Size() == 0) {
	A.Back(B.Back());
	return;
    }

    // Both have element's check their top elemnt value
    if (A.Last() > B.Last())
	A.Back(B.Back());
    else
	B.Back(A.Back());
}

template <typename T>
void TowerOfHanoi<T>::m_execute(const bool& is_odd,
				RECURRENCE::Tower<T>& A,
				RECURRENCE::Tower<T>& B,
				RECURRENCE::Tower<T>& C) {
    if (is_odd) {
	m_move(A, C);
	m_print(A, B, C);
	m_move(A, B);
	m_print(A, B, C);
	m_move(B, C);
	m_print(A, B, C);
    } else {
	m_move(A, B);
	m_print(A, B, C);
	m_move(A, C);
	m_print(A, B, C);
	m_move(B, C);
	m_print(A, B, C);
    }
}

template <typename T>
void TowerOfHanoi<T>::m_print(const RECURRENCE::Tower<T>& A,
			      const RECURRENCE::Tower<T>& B,
			      const RECURRENCE::Tower<T>& C) {
    std::cout << "-------------------------------------------------------------" << std::endl;
    A.Print();
    std::cout << " >>>>> ";
    B.Print();
    std::cout << " >>>>> ";
    C.Print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
}

#endif // ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_ITERATIVE_H_
