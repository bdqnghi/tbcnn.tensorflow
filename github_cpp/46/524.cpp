#include <iostream>

using namespace std;

#define getLeftChild (node * 2)
#define getRightChild (node * 2 + 1)
#define getMiddle (left + (right - left) / 2)

const int N = (int)1e5;
int tree[N * 2 + 10];
int lazy[N * 2 + 10];
int elements[N + 10];

void propagate(int node, int left, int right) {
    tree[node] += (right - left + 1) * lazy[node]; 
    if(left != right) {
        lazy[getLeftChild] = lazy[node];
        lazy[getRightChild] = lazy[node];
    }
    lazy[node] = 0;
}
void recalculate(int node, int left, int right) {
    tree[node] = tree[getLeftChild] + tree[getRightChild];
}

void build(int node, int left, int right) {
    if(left == right) {
        // assume elements is 0-indexed.
        tree[node] = elements[left - 1];
    } else {
        int middle = getMiddle;
        build(getLeftChild, left, middle);
        build(getRightChild, middle + 1, right);
        recalculate(node, left, right);
    }
}

void update(int node, int x, int y, int left, int right, int value) {
    propagate(node, left, right);
    if(x <= left and y >= right) {
        lazy[node] += value;
        return;
    }
    // handle invalid input.
    if(x > right) return;
    if(y < left) return;

    int middle = getMiddle;
    if(x <= middle) update(getLeftChild, x, y, left, middle, value);
    if(y >= middle + 1) update(getRightChild, x, y, middle + 1, right, value);

    // update current node only after children has updated.
    propagate(getLeftChild, left, middle);
    propagate(getRightChild, middle + 1, right);
    recalculate(node, left, right);
}

int query(int node, int x, int y, int left, int right) {
    propagate(node, left, right);
    if(x <= left and y >= right) {
        return tree[node];
    }
    if(x > right) return 0;
    if(y < left) return 0;
    int middle = getMiddle;
    int result = 0;
    if(x <= middle) result += query(getLeftChild, x, y, left, middle); 
    if(y >= middle + 1) result += query(getRightChild, x, y, middle + 1, right);
    return result;
}

int main() {
    // run test here.
    return 0;
}

