/* Implementation of classic Merge Sort */

#include <iostream>
#include <vector>

using iter = std::vector<int>::iterator;

void sort(iter begin, iter end);
void merge(iter begin, iter mid, iter end);

int main(void) {
    std::vector<int> ivec{2, 5, 4, 7, 6, 9, 1, 4, 0};

    sort(ivec.begin(), prev(ivec.end()));

    std::cout << "Sorted vector: " << std::endl;
    for(auto const i : ivec)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}

void sort(iter begin, iter end) {
    if(begin >= end)
        return;

    iter mid = begin;
    std::advance(mid, std::distance(begin, end) / 2);

    sort(begin, mid);
    sort(std::next(mid), end);
    merge(begin, mid, end);

}

void merge(iter begin, iter mid, iter end) {
    std::vector<int> ivecOne, ivecTwo;
    iter iterOne = begin, iterTwo = std::next(mid);

    while(iterOne <= mid)
        ivecOne.push_back(*iterOne++);

    while(iterTwo <= end)
        ivecTwo.push_back(*iterTwo++);

    iterOne = ivecOne.begin();
    iterTwo = ivecTwo.begin();

    while(iterOne != ivecOne.end() && iterTwo != ivecTwo.end()) {
        if(*iterOne < *iterTwo)
            *begin++ = *iterOne++;
        else
            *begin++ = *iterTwo++;
    }

    while(iterOne != ivecOne.end())
        *begin++ = *iterOne++;

    while(iterTwo != ivecTwo.end())
        *begin++ = *iterTwo++;
}
