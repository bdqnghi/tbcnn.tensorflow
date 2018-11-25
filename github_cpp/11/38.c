#ifndef HEAP_H
#define HEAP_H

template<class T>
class Heap {
    private:
        
        T *mHeap;
        int mSize; 
        int mCapacity;
    public:

        
        Heap(const int len);

        
        Heap(const T *array, const int size);

        
        void insert(const T &val);

        
        int getHeight();

        
        int getSize();

        
        int contains(const T &val) const;

        
        T& operator[](const int pos);

        
        T& removeFirst();

        
        T* heapSort();

        ~Heap();
};



#include "heap.cpp"

#endif
