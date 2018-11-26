#ifndef Quicksort_hpp
#define Quicksort_hpp

#include "Random.h"

const int INS_THRESH = 20;

#define TT template<class T>
#define TTi template<class T> inline
#define TTU template<class T, class U>
#define TTUV template<class T, class U, class V>

TT inline void quicksort_Swap(T & a, T & b) {
    T c = a;
    a = b;
    b = c;
}

TTU void quicksortEx(T * t, int n, U & cmp) {
    T v;
    int i,j;
    while (n > INS_THRESH) {
        j = n - 1; // right scan (will start at random number)
        i = int(Ran0()*j);
        v = t[i]; // v -- pivot
        t[i] = t[j];
        t[j] = v;
        i = 0; // left scan
        for (;;) { // partition here
            while (cmp.Greater(v, t[i])) i++;
            while (--j > i && cmp.Greater(t[j], v)) {}
            if (i >= j) break;
            quicksort_Swap(t[i], t[j]);
        }
        v = t[i];
        j = n-1;
        t[i] = t[j];
        t[j] = v;
        quicksortEx(t,i, cmp);
        i++; // advance i past the partition element
        t += i; // this is equivalent to quicksort(t+i, n-i);
        n -= i;
    }
    for (i = 1; i < n; i++) {
        v = t[i];
        for (j = i; j > 0 && cmp.Greater(t[j-1], v); j--)
            t[j] = t[j-1];
        t[j] = v;
    }
}

TT void quicksort(T * t, int n) {
    T v;
    int i, j;
    while (n > INS_THRESH) {
        j = n - 1; // right scan (will start at random number)
        i = int(Ran0()*j);
        v = t[i]; // v -- pivot
        t[i] = t[j];
        t[j] = v;
        i = 0; // left scan
        for (;;) { // partition here
            while (v > t[i]) i++;
            while (--j > i && t[j] > v) {}
            if (i >= j) break;
            quicksort_Swap(t[i], t[j]);
        }
        v = t[i];
        j = n-1;
        t[i] = t[j];
        t[j] = v;
        quicksort(t,i);
        i++; // advance i past the partition element
        t += i; // this is equivalent to quicksort(t+i, n-i);
        n -= i;
    }
    for (i = 1; i < n; i++) {
        v = t[i];
        for (j = i; j > 0 && t[j-1] > v; j--)
            t[j] = t[j-1];
        t[j] = v;
    }
}

TTU void quicksort2(T * t, U * l, int n) {
    int i, j;
    T v;

    while (n > INS_THRESH) {
        j = n - 1; // right scan (will start at random number)
        i = int(Ran0()*j);
        quicksort_Swap(t[i], t[j]);
        quicksort_Swap(l[i], l[j]);
        i = 0; // left scan
        v = t[j]; // v -- pivot
        for (;;) { // partition here
            while (v > t[i]) i++;
            while (--j > i && t[j] > v) {}
            if (i >= j) break;
            quicksort_Swap(t[i], t[j]);
            quicksort_Swap(l[i], l[j]);
        }
        j = n-1;
        quicksort_Swap(t[i], t[j]);
        quicksort_Swap(l[i], l[j]);
        quicksort2(t,l,i);
        i++; // advance i past the partition element
        t += i; // this is equivalent to quicksort2(t+i, l+i, n-i);
        l += i;
        n -= i;
    }
    U w;
    for (i = 1; i < n; i++) {
        v = t[i];
        w = l[i];
        for (j = i; j > 0 && t[j-1] > v; j--) {
            t[j] = t[j-1];
            l[j] = l[j-1];
        }
        t[j] = v;
        l[j] = w;
    }
}

TTU void quicksort3(const T * t, U * l, int n) {
    int i, j;
    T v;

    while (n > INS_THRESH) {
        j = n - 1; // right scan (will start at random number)
        i = int(Ran0()*j);
        quicksort_Swap(l[i], l[j]);
        i = 0; // left scan
        v = t[l[j]]; // v -- pivot
        for (;;) { // partition here
            while (v > t[l[i]]) i++;
            while (--j > i && t[l[j]] > v) {}
            if (i >= j) break;
            quicksort_Swap(l[i], l[j]);
        }
        j = n-1;
        quicksort_Swap(l[i], l[j]);
        quicksort3(t,l,i);
        i++; // advance i past the partition element
        l += i; // this is equivalent to quicksort3(t+i, l+i, n-i);
        n -= i;
    }
    U w;
    for (i = 1; i < n; i++) {
        v = t[l[i]];
        w = l[i];
        for (j = i; j > 0 && t[l[j-1]] > v; j--) {
            l[j] = l[j-1];
        }
        l[j] = w;
    }
}

TTUV void quicksort4(T * t, U * l, V * r, int n) {
    int i, j;
    T v;

    while (n > INS_THRESH) {
        j = n - 1; // right scan (will start at random number)
        i = int(Ran0()*j);
        quicksort_Swap(t[i], t[j]);
        quicksort_Swap(l[i], l[j]);
        quicksort_Swap(r[i], r[j]);
        i = 0; // left scan
        v = t[j]; // v -- pivot
        for (;;) { // partition here
            while (v > t[i]) i++;
            while (--j > i && t[j] > v) {}
            if (i >= j) break;
            quicksort_Swap(t[i], t[j]);
            quicksort_Swap(l[i], l[j]);
            quicksort_Swap(r[i], r[j]);
        }
        j = n-1;
        quicksort_Swap(t[i], t[j]);
        quicksort_Swap(l[i], l[j]);
        quicksort_Swap(r[i], r[j]);
        quicksort4(t,l,r,i);
        i++; // advance i past the partition element
        t += i; // this is equivalent to quicksort2(t+i, l+i, n-i);
        l += i;
        r += i;
        n -= i;
    }
    U w;
    V z;
    for (i = 1; i < n; i++) {
        v = t[i];
        w = l[i];
        z = r[i];
        for (j = i; j > 0 && t[j-1] > v; j--) {
            t[j] = t[j-1];
            l[j] = l[j-1];
            r[j] = r[j-1];
        }
        t[j] = v;
        l[j] = w;
        r[j] = z;
    }
}

#undef TTUV
#undef TTU
#undef TTi
#undef TT

#endif // Quicksort_hpp
