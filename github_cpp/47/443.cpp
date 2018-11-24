
#include <vector>
#include <iostream>
using namespace std;

ostream& operator<<(ostream& o, const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        o << v[i] << " ";
    }
    return o;
}

int SearchRecImpl(const vector<int>& v, int x, size_t start, size_t end) {
    if (end <= start) {
        return v[start] == x ? start : -1;
    }
    int mid = start + (end - start) / 2;
    if (v[mid] > x) {
        return SearchRecImpl(v, x, start, mid - 1);
    } else if (v[mid] < x) {
        return SearchRecImpl(v, x, mid + 1, end);
    } else {
        return mid;
    }
}

int SearchRec(const vector<int>& v, int x) {
    return SearchRecImpl(v, x, 0, v.size() - 1);
}

int SearchIter(const vector<int>& v, int x) {
    size_t start = 0;
    size_t end = v.size() - 1;
    while (true) {
        if (end <= start) {
            return v[start] == x ? start : -1;
        }
        int mid = start + (end - start) / 2;
        if (v[mid] > x) {
            end = mid - 1;
        } else if (v[mid] < x) {
            start = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

void Shift(vector<int>& v, size_t shift) {
    vector<int> tmp(v.end() - shift, v.end());
    for (int i = v.size() - 1; i >= shift; --i) {
        v[i] = v[i-shift];
    }
    for (int i = 0; i < shift; ++i) {
        v[i] = tmp[i];
    }
}

int FindShift(const vector<int>& v) {
    // find minimal element that is smaller than first one
    size_t start = 0;
    size_t end = v.size() - 1;
    while (true) {
        if (end == start) {
            return 0;
        }
        if (end == start + 1) {
            return v[start] > v[end] ? end : 0;
        }
        int mid = start + (end - start) / 2;
        if (v[mid] > v[0]) {
            start = mid; 
        } else {
            end = mid;
        }
    }
    return -1;
}

int main() {
    vector<int> v;
    int x;

    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(9);
    v.push_back(10);
    v.push_back(14);
    v.push_back(15);
    v.push_back(16);
    v.push_back(18);
    v.push_back(20);
    cout << v << endl;

    x = 5;
    cout << x << ": " << SearchRec(v, x) << endl;
    cout << x << ": " << SearchIter(v, x) << endl;

    x = 20;
    cout << x << ": " << SearchRec(v, x) << endl;
    cout << x << ": " << SearchIter(v, x) << endl;

    x = 2;
    cout << x << ": " << SearchRec(v, x) << endl;
    cout << x << ": " << SearchIter(v, x) << endl;

    x = 15;
    cout << x << ": " << SearchRec(v, x) << endl;
    cout << x << ": " << SearchIter(v, x) << endl;

    x = 8;
    cout << x << ": " << SearchRec(v, x) << endl;
    cout << x << ": " << SearchIter(v, x) << endl;

    size_t shift;

    cout << v << endl;
    cout << "shift: " << FindShift(v) << endl;

    shift = 1;
    Shift(v, shift);
    cout << v << endl;
    cout << "shift: " << FindShift(v) << endl;

    shift = 3;
    Shift(v, shift);
    cout << v << endl;
    cout << "shift: " << FindShift(v) << endl;

    shift = 7;
    Shift(v, shift);
    cout << v << endl;
    cout << "shift: " << FindShift(v) << endl;

    return 0;
}
