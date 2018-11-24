#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define INF (1 << 30)
#define SQR(a) ((a) * (a))

using namespace std;

const int N = 1111;
int ASYNC_LIM = 100000;

typedef vector<int>::iterator vit;
vector<int> v;

void merge_it(vit target, vit a_begin, vit a_end, vit b_begin, vit b_end) {
    if (a_begin == a_end) {
        copy(b_begin, b_end, target);
    } else if (b_begin == b_end) {
        copy(a_begin, a_end, target);
    } else {
        vit a_med = a_begin + distance(a_begin, a_end) / 2;
        vit b_adj = upper_bound(b_begin, b_end, *a_med);
        int first_half_length =
            distance(a_begin, a_med)  + distance(b_begin, b_adj);
        *(target + first_half_length) = *a_med;
        if (distance(a_begin, a_end) + distance(b_begin, b_end) > ASYNC_LIM) {
            auto f = async(merge_it, target, a_begin, a_med, b_begin, b_adj);
            merge_it(target + first_half_length + 1, b_adj, b_end, a_med + 1, a_end);
            f.get();
        } else {
            merge_it(target, a_begin, a_med, b_begin, b_adj);
            merge_it(target + first_half_length + 1, b_adj, b_end, a_med + 1, a_end);
        }
    }
}

vector<int> merge(vector<int> a, vector<int> b) {
    vector<int> res(a.size() + b.size());
    merge_it(res.begin(), a.begin(), a.end(), b.begin(), b.end());
    return res;
}

vector<int> merge_naive(vector<int> a, vector<int> b) {
    vector<int> res;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (a.size() + b.size() > 0) {
        if (a.size() > 0 && (b.size() == 0 || a.back() < b.back()))
            res.push_back(a.back()), a.pop_back();
        else
            res.push_back(b.back()), b.pop_back();
    }
    return res;
}

vector<int> mergesort_naive(vit l, vit r) {
    if (distance(l, r) == 1) {
        return vector<int>(l, r);
    } else {
        vit mid = l + distance(l, r) / 2;
        return merge_naive(mergesort_naive(l, mid), mergesort_naive(mid, r));
    }
}

vector<int> mergesort(vit l, vit r) {
    if (distance(l, r) == 1) {
        return vector<int>(l, r);
    } else {
        vit mid = l + distance(l, r) / 2;
        if (distance(l, r) > ASYNC_LIM) {
            future<vector<int>> left = async(mergesort, l, mid);
            return merge(left.get(), mergesort(mid, r));
        } else {
            // switching to naive because we'd be getting too many threads otherwise
            return merge_naive(mergesort_naive(l, mid), mergesort_naive(mid, r));
        }
    }
}

vector<int> randomArray(int len = 100'000) {
    vector<int> v(len);
    for (auto &e : v)
        e = rand();
    return v;
}

bool isSorted(const vector<int> &v) {
    for (size_t i = 1; i < v.size(); i++)
        if (v[i] < v[i - 1])
            return false;
    return true;
}

int main() {
    srand(time(NULL));

    v = randomArray(1000000);
    ASYNC_LIM = v.size() / 50;
    vector<int> res = mergesort(v.begin(), v.end());
    // on my machine this is two times faster than the naive version
    assert(isSorted(res));
    cerr << " OK " << endl;

    return 0;
}
