/*************************************************************************
    > File Name: heap.cpp
    > Author: fas
    > Created Time: 2018年07月14日 星期六 13时05分22秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void PrintVector(const std::vector<T>& vec) {
    for (const auto &val:vec) {
        std::cout << val << " ";
    }   
    std::cout << std::endl;
}

template <class Iter, class Comp>
void heap_sort(Iter start, Iter end, Comp compare) {
    while (end - start > 1) {
        std::make_heap(start, end, compare);
        // 交换两个iter所指向的元素
        std::iter_swap(start, --end);
    }
}

template <class Iter, class Comp>
void heap_sort_pop_heap(Iter start, Iter end, Comp compare) {
    std::make_heap(start, end, compare);
    while (end - start > 1) {
        // 交换两个iter所指向的元素
        std::pop_heap(start, end--, compare);
    }
}

int main(int argc, char** atgv) {
    std::vector<int> seq = {2, 4, 6, 8, 9, 10, 4, 3, 7, 5, 0};
    std::cout <<  "make_heap + less 构造大根堆" << std::endl;
    std::make_heap(seq.begin(), seq.end(), std::less<int>());
    PrintVector(seq);
    
    std::cout <<  "make_heap + greater 构造小根堆" << std::endl;
    std::make_heap(seq.begin(), seq.end(), std::greater<int>());
    PrintVector(seq);   

    std::cout <<  "make_heap + greater + push_heap 添加元素后继续保持小根堆" << std::endl;
    seq.push_back(-1);
    std::push_heap(seq.begin(), seq.end(), std::greater<int>());
    PrintVector(seq);   

    std::cout <<  "heap_sort + less 从小到大排序" << std::endl;
    heap_sort(seq.begin(), seq.end(), std::less<int>());
    PrintVector(seq);
    
    std::cout <<  "heap_sort + greater 从大到小排序" << std::endl;
    heap_sort(seq.begin(), seq.end(), std::greater<int>());
    PrintVector(seq);
  
    std::cout <<  "heap_sort_pop_heap + greater 从大到小排序" << std::endl;
    heap_sort_pop_heap(seq.begin(), seq.end(), std::greater<int>());
    PrintVector(seq);
  
    std::cout <<  "make_heap + sort_heap + greater 从大到小排序" << std::endl;
    std::make_heap(seq.begin(), seq.end(), std::greater<int>());
    sort_heap(seq.begin(), seq.end(), std::greater<int>());
    PrintVector(seq);
    
    std::cout <<  "make_heap + sort_heap + less 从小到大排序" << std::endl;
    std::make_heap(seq.begin(), seq.end(), std::less<int>());
    sort_heap(seq.begin(), seq.end(), std::less<int>());
    PrintVector(seq);
    return 0;
}
