#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int lsum, rsum, sum, maxs;
};

class SegTree {
public:
    const static int MAXN = 50005;
    Node* tree[4 * MAXN];
    int A[MAXN];
    int N;

    SegTree(int NN){
        N = NN;
    }

    void initialize(int node_num, int st, int ed) {
        tree[node_num] = new Node();
        if (st == ed) {
            tree[node_num]->lsum = A[st];
            tree[node_num]->rsum = A[st];
            tree[node_num]->sum  = A[st];
            tree[node_num]->maxs = A[st];
            return;
        }
        int mid = (st + ed) / 2;
        initialize(node_num * 2, st, mid);
        initialize(node_num * 2 + 1, mid + 1, ed);
        update_val(node_num);
        return;
    }

    void update_val(int node_num) {
        tree[node_num]->lsum = max(tree[node_num * 2]->lsum, tree[node_num * 2]->sum + tree[node_num * 2 + 1]->lsum);
        tree[node_num]->rsum = max(tree[node_num * 2 + 1]->rsum, tree[node_num * 2]->rsum + tree[node_num * 2 + 1]->sum);
        tree[node_num]->sum = tree[node_num * 2]->sum + tree[node_num * 2 + 1]->sum;
        tree[node_num]->maxs = max(tree[node_num * 2]->maxs, tree[node_num * 2 + 1]->maxs);
        tree[node_num]->maxs = max(tree[node_num]->maxs, tree[node_num * 2]->rsum + tree[node_num * 2 + 1]->lsum);
        return;
    }

    bool update(int node_num, int st, int ed, int pos, int val) {
        if (pos > ed || pos < st)
            return false;
        if (st == ed && st == pos) {
            A[st] = val;
            tree[node_num]->lsum = A[st];
            tree[node_num]->rsum = A[st];
            tree[node_num]->sum  = A[st];
            tree[node_num]->maxs = A[st];
            return true;
        }
        int mid = (st + ed) / 2;
        bool left_changed = false, right_changed = false;
        left_changed = update(node_num * 2, st, mid, pos, val);
        right_changed = update(node_num * 2 + 1, mid + 1, ed, pos, val);
        if (left_changed || right_changed) {
            update_val(node_num);
            return true;
        }
        return false;
    }

    Node* query(int node_num, int st, int ed, int i, int j) {
        if (st == i && ed == j)
            return tree[node_num];
        int mid = (st + ed) / 2;

        if (j <= mid) {
            return query(node_num * 2, st, mid, i, j);
        }

        if (i > mid) {
            return query(node_num * 2 + 1, mid + 1, ed, i, j);
        }

        Node* left = query(node_num * 2, st, mid, i, mid);
        Node* right = query(node_num * 2 + 1, mid + 1, ed, mid + 1, j);

        Node* ret = new Node();
        ret->lsum = max(left->lsum, left->sum + right->lsum);
        ret->rsum = max(right->rsum, left->rsum + right->sum);
        ret->sum = left->sum + right->sum;
        ret->maxs = max(left->maxs, right->maxs);
        ret->maxs = max(ret->maxs, left->rsum + right->lsum);
        return ret;
    }
};

int main(){
    int N,x;
    scanf("%d",&N);
    
    SegTree* ST = new SegTree(N);

    for(int i=1;i<=N;i++){
        scanf("%d",&x);
        ST->A[i] = x;
    }

    ST->initialize(1, 1, N);
    int Q;
    scanf("%d",&Q);
    int type, y;

    while(Q--) {
        scanf("%d %d %d", &type, &x, &y);
        if(type==0)
            ST->update(1, 1, N, x, y);
        else {
            Node* ans = ST->query(1, 1, N, x, y);
            printf("%d\n",ans->maxs);
        }
    }
}