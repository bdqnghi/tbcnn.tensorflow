#include <bits/stdc++.h>

using namespace std;

template <typename T>
class SegmentTree {
    vector<T> original_data; // the original data / vector
    vector<T> segment_tree; // the actual tree
    function<T(T,T)> operation; // operation on the segments

  public:
    SegmentTree(const vector<T> &data, const function<T(T, T)> &op) {
        original_data = data;
        segment_tree.resize(2 * original_data.size());
        operation = op;
        
        for (int i = 0 ; i < original_data.size() ; i++) {
            segment_tree[original_data.size() + i] = original_data[i];
        }

        for (int i = original_data.size() - 1 ; i > 0 ; i--) {
            segment_tree[i] = operation(segment_tree[2 * i], segment_tree[2 * i + 1]);
        }
    };

    void update(int loc, T newVal) {
        segment_tree[loc + original_data.size()] = newVal; // updat leaf
        for (int i = loc + original_data.size() ; i > 1 ; i /= 2) {
            segment_tree[i / 2] = operation(segment_tree[i], segment_tree[i^1]);
        }
    };

    T query(int lbound, int rbound, T def = 0) {
        // XXX lbound and rbound are 1 indexed!!!
        // return query of l and r
        T result = def;
        for (int l = original_data.size() + lbound, r = original_data.size() + rbound ; l <= r ; l /= 2, r /= 2) {
            if (l&1) {
                result = operation(segment_tree[l], result);
                l++;
            }
            if (!(r&1)) {
                result = operation(result, segment_tree[r]);
                r--;
            }
        }
        return result;
    };
};

int main(int argc, char *argv[]) {
    int N;
    cin >> N;
    vector<int> inputs(N);
    for (int i = 0 ; i < N ; i++) {
        cin >> inputs[i];
    }
    SegmentTree<int> seg_tree(inputs, [](int a, int b){return a + b;});
    
    int Q;
    cin >> Q;
    for (int i = 0 ; i < Q ; i++) {
        int l, r;
        cin >> l >> r;
        cout << seg_tree.query(l, r) << '\n';
    }

    int U;
    cin >> U;
    for (int i = 0 ; i < U ; i++) {
        int p, v;
        cin >> p >> v;
        seg_tree.update(p, v);
    }

    cin >> Q;
    for (int i = 0 ; i < Q ; i++) {
        int l, r;
        cin >> l >> r;
        cout << seg_tree.query(l, r) << '\n';
    }

}
