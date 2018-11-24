#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class Permutation {
    std::vector<int> array;

    public:
        Permutation(const std::string &s): array(0) {
            std::stringstream stream;
            stream << s;
            int x;
            while ((stream >> x))
                array.push_back(x);
        }

        operator std::string() const { // cout << string(pi); Вывод: 1 2 3
            std::stringstream stream;
            for (unsigned i = 0; i < array.size(); i++)
                stream << array[i] << " ";
            return stream.str();
        }
    //    operator const char * () const; // cout << pi; Вывод: 1 2 3
        const Permutation &operator++() {
            std::next_permutation(array.begin(), array.end());
            return *this;
        }

        Permutation operator++(int) {
            Permutation tmp = *this;
            ++(*this);
            return tmp;
        }
};
/*
int main() {
    return 0;
}*/