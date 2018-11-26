#ifndef STOP_WATCH_HEAPSORT_H
#define STOP_WATCH_HEAPSORT_H


#include "../IRunnable.h"
#include "../IPreparable.h"

template<class T>
class HeapSort : public IRunnable<T>, public IPreparable<T> {
public :
    HeapSort() {};
    ~HeapSort() {delete[] tab; std::cout << "destructor called";};

    void prepare(T const&);
    void run();
    void heapsort(T [],T);
    void swap(T&, T&);
    void heapify(T [], T,T);
    void optimal_case();
    void normal_case();
    void pesimist_case();
    void print() const;
    const std::string getName() const { return "heapsort"; }

private:
    T data_size;
    T* tab;
};


template <class T>
inline void HeapSort<T>::pesimist_case() {
    for (auto i = 0; i<data_size/2; i++) {
        tab[2*i] = data_size-i;
        tab[2*i+1] = data_size-2*(i+1);
    }
}

template <class T>
inline void HeapSort<T>::normal_case() {
    for (auto i = 0; i<data_size; i++) {
        tab[i] = rand() % data_size*25;
    }
}

template <class T>
inline void HeapSort<T>::optimal_case() {
    for (auto i = 0; i<data_size; i++) {
        tab[i] = data_size;
    }
}

template <class T>
inline void HeapSort<T>::prepare(const T& value) {
    this->data_size = value;
    tab = new T[data_size];
}

template <class T>
inline void HeapSort<T>::run() {
    heapsort(tab, data_size);
}

template <class T>
void HeapSort<T>::print() const {
    for (auto iter = 0; iter<data_size; iter++) {
        std::cout << tab[iter] << " ";
    }
}

template<typename T>
inline void HeapSort<T>::swap(T& v1, T& v2)
{
    T tmp = v2;
    v2 = v1;
    v1 = tmp;
}

template<typename T>
inline void HeapSort<T>::heapify(T data[], T i, T size) {               // kopcuje,dzieli na poddrzewa z wezlami i
    T root = i;
    T left = 2*i ;
    T right = 2*i + 1;

    if(left < size && data[left] > data[root])
        root = left;
    if(right < size && data[right] > data[root])
        root = right;
    if(root != i){
        swap(data[i],data[root]);
        heapify(data, root, size);
    }
}
template<class T>
inline void HeapSort<T>::heapsort(T data[], T size) {
    T i, min = 0;
    for(i = size/2 - 1; i>=0; i--)               // utworzenie sterty
        heapify(data,i,size);

    for(i = size-1; i>=0; i--){                 // wyciaganie jeden po drugim elementu ze sterty
        swap(data[min],data[i]);                // przesuniecie największego el,korzenia do data[i]
        heapify(data,min,i);                    // przywrocenie sterty, zmniejszenie o najwiekszy el
    }
}

#endif //STOP_WATCH_HEAPSORT_H
