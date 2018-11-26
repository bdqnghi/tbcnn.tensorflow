#ifndef HEAP_H
#define HEAP_H

template<class T>
class Heap {
    private:
        /* Lets fill out in class. */
        T *mHeap;
        int mSize; // Number of elements in the Heap.
        int mCapacity;// How many elements the Heap can currently hold.
    public:

        /* Creates an empty heap. */
        Heap(const int len);

        /* Does a deep copy of the array into the heap. */
        Heap(const T *array, const int size);

        /* Add a given value to the heap.
         * Must maintain ordering!
         */
        void insert(const T &val);

        /* Returns the height of the heap. */
        int getHeight();

        /* Returns the size of the heap. */
        int getSize();

        /* Returns the index if an item if exists in the heap.
         * Otherwise return -1.
         */
        int contains(const T &val) const;

        /* Retrieves the element at position pos */
        T& operator[](const int pos);

        /* Removes and returns the first element */
        T& removeFirst();

        /* Performs a Heap Sort and returns an array of the sorted
         * elements.
         * Note: the heap is empy after the sort!
         */
        T* heapSort();

        ~Heap();
};

/* Since heap templated, we include the .cpp.
 * Templated classes are not implemented until utilized (or explicitly
 * declared.)
 */

#include "heap.cpp"

#endif
