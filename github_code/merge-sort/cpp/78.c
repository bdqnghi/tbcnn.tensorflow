#ifndef ALGORITHMS_MERGESORT_H
#define ALGORITHMS_MERGESORT_H

#include <vector>
#include "../IPreparable.h"
#include "../IRunnable.h"

template <class T>
class MergeSort : public IPreparable<T>, public IRunnable<T> {
public:
    MergeSort() {}
    ~MergeSort() { delete[] tab, delete[] temp, delete[] tab_left, delete[] tab_right; std::cout << "destructor called"; }

    void prepare(const T&);
    void run();
    void merge(T[],T[],T,T);
    void mergesort(T[],T[],T,T);
    void optimal_case();
    void normal_case();
    void pesimist_case();
    void print() const;
    void swap(T&,T&);
    void merge_mix(T[],T[],T,T[],T);
    void mix(T[],T);
    const std::string getName() const { return "mergesort"; }

private:
    T data_size;
    T* tab;
    T* temp;
    T* tab_left;
    T* tab_right;
};

template<class T>
inline void MergeSort<T>::swap(T& v1, T& v2)
{
    T tmp = v2;
    v2 = v1;
    v1 = tmp;
}

template <class T>
inline void MergeSort<T>::merge_mix(T tab[], T tab_left[], T left_size, T tab_right[], T right_size)
{
    T i,j;

    for (i=0; i<left_size; i++) {
        tab[i] = tab_left[i];
    }

    for (j=0; j<right_size; j++, i++) {
        tab[i] = tab_right[j];
    }
}

template<class T>
inline void MergeSort<T>::mix(T tab[], T data_size)
{
    if (data_size <= 1) return;

    if (data_size == 2) {
        swap(tab[0], tab[1]);
        return;
    }

    T left_size = data_size/2;
    T right_size = data_size/2;

    //T tab_left[left_size];
    //T tab_right[right_size];

    for (T i=0, j=0; i<data_size; i=i+2, j++) {
        tab_left[j] = tab[i];
    }

    for (T i=1, j=0; i<data_size; i=i+2, j++) {
        tab_right[j] = tab[i];
    }

    mix(tab_left, left_size);
    mix(tab_right, right_size);

    merge_mix(tab, tab_left, left_size, tab_right, right_size);
}

template <class T>
inline void MergeSort<T>::optimal_case() {
    for (auto i = 0; i<data_size; i++) {
        tab[i] = data_size;
    }
}

template <class T>
inline void MergeSort<T>::pesimist_case() {

    for (T i=0; i<data_size; i++) {
        tab[i] = i;//rand() % data_size;
    }

    mix(tab, data_size);

}

template <class T>
inline void MergeSort<T>::normal_case() {
    for (auto i = 0; i<data_size; i++) {
        tab[i] = rand() % data_size;
    }
}

template <class T>
inline void MergeSort<T>::print() const {
    for (auto iter = 0; iter<data_size; iter++) {
        std::cout << tab[iter] << " ";
    }
}

template <class T>
inline void MergeSort<T>::prepare(const T& value) {
    this->data_size = value;
    tab = new T[data_size];
    temp = new T[data_size];
    tab_left = new T[data_size/2];
    tab_right = new T[data_size/2];
}

template <class T>
inline void MergeSort<T>::run() {
    T min = 0;
    mergesort(tab,temp,min,data_size-1);
}

// IMPLEMENTATION USING ARRAY FROM ANSI C

template <typename T>
inline void MergeSort<T>::merge(T array[],T temp[], T first, T last) {
    T mid = (first+last)/2;
    T i1 = 0, i2 = first, i3 = mid+1;

    temp [last-first+1];
    while (i2 <= mid && i3 <= last) { // dopóki prawa i lewa podtablica zawieraja elementy
        if (array[i2] < array[i3]) {
            temp[i1++] = array[i2++];
        } else {
            temp[i1++] = array[i3++];
        }
    }

    while (i2 <= mid) {
        temp[i1++] = array[i2++];
    }

    while (i3 <= last) {
        temp[i1++] = array[i3++];
    }

    for (i1 = 0, i2 = first ; i2 <= last; array[i2++] = temp[i1++]);

    //delete[] temp;
}

template <typename T>
inline void MergeSort<T>:: mergesort(T data[], T temp[],T first, T last) {
    if (first < last) {
        T mid = (first+last)/2 ;
        mergesort(data, temp,first, mid);
        mergesort(data,temp, mid+1, last);
        merge(data,temp,first, last);
    }
}
//template <class T>
//void MergeSort<T>::merge(std::vector<T>& array, std::vector<T>& array1, std::vector<T>& array2) {
//    array.clear();
//    T i,j;
//
//    for (i = j = 0; i < array1.size() && j < array2.size(); ) {
//        if (array1.at(i) < array2.at(j)) {
//            array.push_back(array1.at(i));
//            i++;
//        } else {
//            array.push_back(array2.at(j));
//            j++;
//        }
//    }
//
//    while (i < array1.size()) {
//        array.push_back(array1.at(i));
//        i++;
//    }
//
//    while (j < array2.size()) {
//        array.push_back(array2.at(j));
//        j++;
//    }
//}
//
//template <class T>
//void MergeSort<T>::mergesort(std::vector<T>& array) {
//    if (1 < array.size()) {
//        std::vector<T> array1(array.begin(), array.begin() + array.size() / 2); // left-hand vector
//        mergesort(array1);
//        std::vector<T> array2(array.begin() + array.size() / 2, array.end()); // right-head vector
//        mergesort(array2);
//        merge(array, array1, array2);
//    }
//}

#endif //ALGORITHMS_MERGESORT_H
