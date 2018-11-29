#ifndef EE205_BUBBLE_SORT_VECTOR_HPP
#define EE205_BUBBLE_SORT_VECTOR_HPP

#include <vector>

#include "ISortable.hpp"

// Did you know that std::vector is actually
// a class template?
template <typename T>
class BubbleSortVector :
    public std::vector<T>,
    public ISortable {
public:
    virtual void sort() override;
};

// Note: templates cannot be implmented in .cpp files.
//
// To still keep a separation between declaration
// and definition as we have in the past in .hpp and .cpp files,
// by convention, people may use .tcc files to store the
// implementations of any templated functions, such as sort()
// here which is on the class template BubbleSortVector.

#include "BubbleSortVector.tcc"

#endif // EE205_BUBBLE_SORT_VECTOR_HPP
