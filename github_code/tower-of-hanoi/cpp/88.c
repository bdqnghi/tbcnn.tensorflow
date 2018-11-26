#ifndef ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_H_
#define ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_H_

/*
  Implementation of Tower of Hanoi problem with Recurrence.

  Time Compexity.
  T(n) = {0              ,if n = 0}
  {2T(n - 1) + 1  ,if n > 0}

  Author:Rakesh Kumar cpp.rakesh@gmail.com
  Date: August 23rd, 2016
*/

#include "tower.h"

namespace RECURRENCE {
    template <typename T>
        class TowerOfHanoi {
    public:
	TowerOfHanoi();
	~TowerOfHanoi();

	void Compute(Tower<T> tower);

    private:
	void m_compute(const int &n,
		       Tower<T>& source,
		       Tower<T>& temp,
		       Tower<T>& target);
	Tower<T> m_get_tower(const TOWER_TYPE& type,
			     const Tower<T>& source,
			     const Tower<T>& temp,
			     const Tower<T>& target);
	void m_print(const Tower<T>& source,
		     const Tower<T>& temp,
		     const Tower<T>& target);
    };
};

template <typename T>
RECURRENCE::TowerOfHanoi<T>::TowerOfHanoi() {}

template <typename T>
RECURRENCE::TowerOfHanoi<T>::~TowerOfHanoi() {}

template <typename T>
void RECURRENCE::TowerOfHanoi<T>::Compute(Tower<T> tower) {
    Tower<T> temp(TEMP);
    Tower<T> target(TARGET);
    m_print(tower, temp, target);
    m_compute(tower.Size() - 1, tower, temp, target);
}

template <typename T>
void RECURRENCE::TowerOfHanoi<T>::m_compute(const int& n,
					    Tower<T>& source,
					    Tower<T>& temp,
					    Tower<T>& target) {
    if (n >= 0) {
	m_compute(n - 1, source, target, temp);
	target.Front(source.Front());

	m_print(source, temp, target);

	m_compute(n - 1, temp, source, target);
    }
}

template <typename T>
RECURRENCE::Tower<T> RECURRENCE::TowerOfHanoi<T>::m_get_tower(const TOWER_TYPE& type,
							      const Tower<T>& source,
							      const Tower<T>& temp,
							      const Tower<T>& target) {
    if (type == source.Type())
	return source;
    else if (type == temp.Type())
	return temp;
    else
	return target;
}

template <typename T>
void RECURRENCE::TowerOfHanoi<T>::m_print(const Tower<T>& source,
					  const Tower<T>& temp,
					  const Tower<T>& target) {
    std::cout << "-------------------------------------------------------------" << std::endl;
    m_get_tower(SOURCE, source, temp, target).Print();
    std::cout << " >>>>> ";
    m_get_tower(TEMP, source, temp, target).Print();
    std::cout << " >>>>> ";
    m_get_tower(TARGET, source, temp, target).Print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
}

#endif // ALGORITHMS_RECURRENCE_TOWER_OF_HANOI_H_
