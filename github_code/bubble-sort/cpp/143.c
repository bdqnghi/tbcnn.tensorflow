#include <iostream>
#include <vector>

void bubblesort(std::vector<int>& vec);

int main() {
    std::vector<int> vec;
    int num;
    while (std::cin >> num) { vec.emplace_back(num); }
    bubblesort(vec);
    for (auto && i : vec) {
        std::cout << i << " ";
    }
}

void bubblesort(std::vector<int> & vec) {
    bool flag = false;
    while (!flag) {
        flag = true;
        for(int i = 1; i < vec.size(); ++i) {
            if (vec[i - 1] > vec[i]) {
                flag = false;
                std::swap(vec[i - 1], vec[i]);
            }
        }
    }
}