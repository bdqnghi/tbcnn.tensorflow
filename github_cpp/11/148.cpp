#include "binaryheap.hpp"
#include <iostream>
#include <vector>

namespace adt
{
    template<typename T, HeapSortTraits SortTrait>
    BinaryHeap<T, SortTrait>::BinaryHeap() :
        _heapSize(0)
    {
        _heap.push_back(T());
    }

    template<typename T, HeapSortTraits SortTrait>
    BinaryHeap<T, SortTrait>::BinaryHeap(const std::vector<T>& values) :
        _heapSize(values.size())
    {
        _heap.reserve(_heapSize + 1);
        _heap.push_back(T());
        _heap.insert(_heap.end(), values.begin(), values.end());
        for (size_t index = _heapSize / 2; index > 0; index--)
        {
            percolateDown(index);
        }
    }

    template<typename T, HeapSortTraits SortTrait>
    size_t BinaryHeap<T, SortTrait>::minimumChildIndex(size_t index) const
    {
        if (index * 2 + 1 > _heapSize || _heap[index * 2] < _heap[index * 2 + 1])
        {
            return index * 2;
        }
        else
        {
            return index * 2 + 1;
        }
    }

    template<typename T, HeapSortTraits SortTrait>
    size_t BinaryHeap<T, SortTrait>::maximumChildIndex(size_t index) const
    {
        if (index * 2 + 1 > _heapSize || _heap[index * 2] > _heap[index * 2 + 1])
        {
            return index * 2;
        }
        else
        {
            return index * 2 + 1;
        }
    }

    template<typename T, HeapSortTraits SortTrait>
    void BinaryHeap<T, SortTrait>::percolateDown(size_t index)
    {
        for (;;)
        {
            size_t childIndex = (SortTrait == HeapSortTraits::MinimumHeap) ?
                minimumChildIndex(index) : maximumChildIndex(index);
            bool percolate = (SortTrait == HeapSortTraits::MinimumHeap) ?
                childIndex <= _heapSize && _heap[childIndex] < _heap[index] :
                childIndex <= _heapSize && _heap[childIndex] > _heap[index];
            if (percolate)
            {
                T swap = _heap[childIndex];
                _heap[childIndex] = _heap[index];
                _heap[index] = swap;
                index = childIndex;
            }
            else
            {
                break;
            }
        }
    }

    template<typename T, HeapSortTraits SortTrait>
    void BinaryHeap<T, SortTrait>::percolateUp(size_t index)
    {
        for (;;)
        {
            size_t parentIndex = index / 2;
            bool percolate = (SortTrait == HeapSortTraits::MinimumHeap) ?
                parentIndex > 0 && _heap[index] < _heap[parentIndex] :
                parentIndex > 0 && _heap[index] > _heap[parentIndex];
            if (percolate)
            {
                T swap = _heap[parentIndex];
                _heap[parentIndex] = _heap[index];
                _heap[index] = swap;
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    template<typename T, HeapSortTraits SortTrait>
    void BinaryHeap<T, SortTrait>::push(T value)
    {
        _heap.push_back(value);
        _heapSize++;
        percolateUp(_heapSize);
    }

    template<typename T, HeapSortTraits SortTrait>
    T BinaryHeap<T, SortTrait>::pop()
    {
        if (empty())
        {
            return end();
        }

        T value = _heap[1];
        _heap[1] = _heap[_heapSize];
        _heap.pop_back();
        _heapSize--;
        percolateDown(1);
        return value;
    }

    template<typename T, HeapSortTraits SortTrait>
    T BinaryHeap<T, SortTrait>::top() const
    {
        if (empty())
        {
            return end();
        }

        return _heap[1];
    }

    template<typename T, HeapSortTraits SortTrait>
    std::ostream& BinaryHeap<T, SortTrait>::write(std::ostream& out) const
    {
        if (!empty())
        {
            out << _heap[1];
            for (size_t index = 2; index <= _heapSize; index++)
            {
                out << ", " << _heap[index];
            }
        }

        return out;
    }
}

template<typename T, adt::HeapSortTraits SortTrait>
std::ostream& operator<<(std::ostream& out, const adt::BinaryHeap<T, SortTrait>& heap)
{
    return heap.write(out);
}