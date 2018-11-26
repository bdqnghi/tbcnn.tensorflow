#ifndef SHELLSORT_H
#define SHELLSORT_H

namespace ycg {

template <class Type>
class ShellSort {
public:
    void operator() (Type *a, int n);
private:
    int nextGap(int n);
};

template <class Type>
void ShellSort<Type>::operator ()(Type *a,int n) {
    int gap = n;
    do {
        gap = nextGap(gap);
        for(int i = gap; i < n; ++i) {
            Type key = a[i];
            int j = i - gap;
            while(j >= 0 && key < a[j]) {
                a[j+gap] = a[j];
                j -= gap;
            }
            a[j+gap] = key;
        }
    } while(gap > 1);
}

template <class Type>
inline int ShellSort<Type>::nextGap(int n) {
    return n / 3 + 1;
}

} //~ namespace ycg

#endif // SHELLSORT_H
