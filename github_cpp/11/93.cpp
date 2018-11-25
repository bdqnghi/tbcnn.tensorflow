#include <iostream>
#include <algorithm>
#include "heapsort.h"

std::vector<int>& THeapSorter::Sort(std::vector<int> &sequence) {
    int size = sequence.size();

    Clear();

    for (int i = 0; i < size; ++i) {
        Insert(sequence[i]);
    }

    for (int i = 0; i < size; ++i) {
        sequence[i] = ExtractMin();
    }

    return sequence;
}

void THeapSorter::Clear() {
    list.clear();
}

void THeapSorter::Insert(int item) {
    list.push_back(item);
    SiftUp(static_cast<int>(list.size()) - 1);
}

int THeapSorter::ExtractMin() {
    int min = list[0];
    list[0] = list[static_cast<int>(list.size()) - 1];
    list.pop_back();
    SiftDown(0);
    return min;
}

void THeapSorter::SiftUp(int index) {
    while (list[index] < list[(index - 1) / 2]) {
        std::swap(list[index], list[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void THeapSorter::SiftDown(int index) {
    int left;
    int right;
    int min;
    while (2 * index + 1 < list.size()) {
        left = 2 * index + 1;
        right = 2 * index + 2;

        min = left;
        if (right < list.size() && list[right] < list[left]) {
            min = right;
        }

        if (list[index] < list[min] || list[index] == list[min]) {
            break;
        }

        std::swap(list[index], list[min]);
        index = min;
    }
}


THeapSorter::THeapSorter() {
    name = __func__;
}
