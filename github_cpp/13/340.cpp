#include <iostream>
#include <vector>

//recrursive implimentation
/* NOTE TO SELF: Seems to fail merging + sorting the final two sub-arrays */

std::vector<int> Merge(std::vector<int> &l, std::vector<int> &r);

void Swap (int &a, int &b) {
    auto temp = b;
    b = a;
    a = temp;
}

std::vector<int> MergeSort(std::vector<int> &v){
    if (v.size() <= 1) { return v; } // simplest case: list of one element

    std::vector<int> left, right;
    for(int i = 0; i < v.size(); ++i) {
        if(i < v.size()/2){
            left.push_back(v[i]);
        }
        else{
            right.push_back(v[i]);
        }
    }

    left = MergeSort(left);
    right = MergeSort(right);

    return Merge(left, right);
}

std::vector<int> Merge(std::vector<int> &l, std::vector<int> &r) {
  
    std::vector<int> result;
    while(l.empty() == false && r.empty() == false) {
        if(l.front() < r.front()) {
            result.push_back(l.front());
            l.erase(l.begin() + 0);
        }
        else {
            result.push_back(r.front());
            r.erase(r.begin() + 0);
        }
    }

    while (l.size() != 0) {
        result.push_back(l.front());
        l.erase(l.begin() + 0);
    }

    while (r.size() != 0) {
        result.push_back(r.front());
        r.erase(r.begin() + 0);
    }

    return result;
}

int main() {
    std::vector<int> arr = {2, 1, 32, 7, 5, 3};

    auto out = MergeSort(arr);

    for (auto i : out) {
        std::cout << i << "\t";
    }

    return 0;
}
