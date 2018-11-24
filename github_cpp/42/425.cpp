/* Impelementation of the classic Selection Sort algorithm using both index ops
 * and C++ iterators
 */

#include <iostream>
#include <vector>
#include <algorithm>

void sortIndex(std::vector<int>& ivec);
void sortIter(std::vector<int>& ivec);
void print(const std::vector<int>& ivec);

int main(void) {
    std::vector<int> ivecOne{3, 2, 6, 5, 8, 9, 6, 0}, ivecTwo{4, 1, 5, 8, 3, 6, 9, 8, 0};

    std::cout << "Vector One after Sorting: ";
    sortIndex(ivecOne);
    print(ivecOne);

    std::cout << "Vector Two after Sorting: ";
    sortIter(ivecTwo);
    print(ivecTwo);

    return 0;
}

void sortIndex(std::vector<int>& ivec) {
    std::vector<int>::size_type pIndex, sIndex, minIndex;

    for(pIndex = 0; pIndex != ivec.size() - 1; ++pIndex) {
        minIndex = pIndex;

        for(sIndex = pIndex + 1; sIndex != ivec.size(); ++sIndex)
            if(ivec.at(sIndex) < ivec.at(minIndex))
                minIndex = sIndex;

        std::swap(ivec.at(pIndex), ivec.at(minIndex));
    }
}

void sortIter(std::vector<int>& ivec) {
    std::vector<int>::iterator pIter, sIter, minIter;

    for(pIter = ivec.begin(); pIter != prev(ivec.end()); ++pIter) {
        minIter = pIter;

        for(sIter = next(pIter); sIter != ivec.end(); ++sIter) {
            if(*sIter < *minIter)
                minIter = sIter;

        std::swap(*pIter, *minIter);
        }
    }
}

void print(const std::vector<int>& ivec) {
    for(auto const elem : ivec)
        std::cout << elem << ' ';

    std::cout << std::endl;
}
