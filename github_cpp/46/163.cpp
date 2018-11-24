#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Example of SegmentTree for rmq (range minimum query)
// Note: instead of storing the minimum value, each node will store 
//  the index of the leftmost position of the range in which the minimum
//  value of that range is found

struct SegmentTreeRMQ {
    vi arr; // store original array values
    vi tree; // store nodes of segment tree
    vi leaf; // store index of leaf nodes in segment tree
    int n; // number of leaf nodes (length of arr)
    inline int left (int u) { return u << 1; } // index of left child
    inline int right(int u) { return (u << 1) + 1; } // index of right child

    void build(int u, int i, int j) {
        if (i == j) { // base case: a leaf node
            tree[u] = i;
            leaf[i] = u;
        } else { // recursive case
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
            // store the index of the minimum value,
            // in case of draw choose the leftmost
            int ii = tree[lu], jj = tree[ru];
            tree[u] = (arr[ii] <= arr[jj]) ? ii : jj;
        }        
    }

    // update arr[i] with new_val, and propagate updates in the tree
    // from leaf[i] upwards
    void update(int i, int new_val) {
        arr[i] = new_val;
        int u = leaf[i] >> 1;
        while (u) {
            int lu = left(u), ru = right(u);
            int min_i = (arr[tree[lu]] <= arr[tree[ru]]) ? tree[lu] : tree[ru];
            if (min_i == tree[u]) break; // optimization: no changes, interrupt updates
            // update and move to next parent
            tree[u] = min_i;
            u >>= 1;
        }
    }

    // query for range [a,b], considering that we are at node u
    // which is in charge of range [i, j]
    int query(int a, int b, int u, int i, int j) {
        // case 1: no overlap -> return some neutral / invalid value
        if (j < a or b < i) return -1;
        // case 2: full overlap -> return cached answer
        if (a <= i and j <= b) return tree[u];

        // case 3: partial overlap -> need recursion and merge of answers
        int lu = left(u), ru = right(u), m = (i+j)/2;
        int ii = query(a, b, lu, i, m);
        int jj = query(a, b, ru, m+1, j);
        if (ii == -1) return jj;
        if (jj == -1) return ii;
        return (arr[ii] <= arr[jj]) ? ii : jj; 
    }

    // overloading for easier use
    int query(int a, int b) { return query(a, b, 1, 0, n - 1); }

    SegmentTreeRMQ(const vi& _arr) {
        arr = _arr; // copy content for local usage
        n = arr.size();
        leaf.resize(n);
        tree.resize(4 * n + 5); // reserve enough space for the worst case
        build(1, 0, n - 1); // recursive build from root
    }
    
};
  
// usage
int main() {
    vi arr = { 18, 17, 13, 19, 15, 11, 20 };
    SegmentTreeRMQ st(arr);
    st.query(1, 3);
    st.update(5, 100);
    return 0;
}
