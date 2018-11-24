#include <iostream>
#include <vector>
#include <cstddef>

using std::vector;
using std::cout;
using std::endl;

class PermutationGenerator {
    private:
        vector<int> base;
        size_t size;
        void swap(vector<int>::iterator a, vector<int>::iterator b) {
            int tmp = *a;
            *a = *b;
            *b = tmp;
        }

    public:
        PermutationGenerator (size_t n):size(n){}
        
        vector<int> operator()() {
            if (base.empty()) {
                for (size_t i = 0; i < size; ++i) {
                    base.push_back(i + 1);
                }
                return base;
            }

            // Find the firt ascending order iterator
            vector<int>::iterator itr = base.end() - 2;
            while(itr >= base.begin() && *itr > *(itr + 1)) {
                if (itr == base.begin()) {
                    return vector<int>{};
                }
                --itr;
            }
            
            // Find the next value that bigger than *itr
            vector<int>::iterator nextBiggerIter = base.end() - 1;
            while(nextBiggerIter >= base.begin() && *nextBiggerIter < *itr) {
                nextBiggerIter --;
            }
            swap(itr, nextBiggerIter);

            auto left = itr + 1;
            auto right = base.end() - 1;
            while (left < right) {
                swap(left, right);
                ++left;
                --right;
            }
            
            return base;
        }   

};

void print(vector<int> v) {
    vector<int>::const_iterator citr = v.cbegin();
    while( citr < v.cend()) {
        cout<< *citr << "\t" ;
        advance(citr, 1);
    }
    cout << endl;
}

/** 
 * Using Dynamic Programming to implement fibnacci sequence.
 */
int fib(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    vector<int> bottomUpRes = {1, 1};
    for (int i = 3; i <= n; ++i) {
        bottomUpRes.push_back(*(bottomUpRes.end() - 1) + *(bottomUpRes.end() - 2));
    }
    return *(bottomUpRes.end() - 1);
}

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

int main() {
    cout << "fib:" << fib(5) <<endl;
    cout << "fib:" << fib(8) <<endl;
    cout << "fib:" << fib(15) <<endl;
    cout << "fib:" << fib(100) <<endl;
    cout << factorial(4) <<endl;
    PermutationGenerator p(3);
    int num = factorial(3);
    for (int i = 0; i < num; ++i) {
        cout << (i + 1) << "th:";
        print(p());
    }

    PermutationGenerator p4(4);
    num = factorial(4);
    for (int i = 0; i < num; ++i) {
        cout << (i + 1) << "th:";
        print(p4());
    }
    return 0;
}
