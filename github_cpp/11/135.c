

#include "heap.hpp"
#include "message.hpp"
#include <vector>
#include <random>
#include <iterator>

void heap() {
    const int array_size = 10;
    const int value_digit = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, value_digit);

    int array[array_size];
    std::vector<int> v;

    for (int i = 0; i < array_size; i++) {
        array[i] = dis(gen);
        v.push_back(dis(gen));
    }

    std::cout << "_________HEAP_SORT_________" << std::endl;
    std::cout << "_____sorting_of_array______" << std::endl;

    message(std::begin(array), std::end(array));
    heap_sort(std::begin(array), std::end(array));
    message(std::begin(array), std::end(array));

    std::cout << std::endl << "_____sorting_of_vector_____" << std::endl;

    message(v.begin(), v.end());
    heap_sort(v.begin(), v.end());
    message(v.begin(), v.end());
}

int main(int argc, char const *argv[]) {
    heap();
    return 0;
}
