#include <cstdio>
#include <cctype>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define CMAX 1000000

struct Node {
    Node () {}
    Node (int l, int r)
        : left(l), right(r), cnt(0),
          leftchild(NULL), rightchild(NULL) {}

    int left;
    int right;
    int cnt;
    Node *leftchild;
    Node *rightchild;

    void update() {
        cnt = 0;
        if (leftchild)
            cnt += leftchild->cnt;
        if (rightchild)
            cnt += rightchild->cnt;
    }
};

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static Node *persistent_modify(Node *x, int pos, int delta) {
    Node *y = new Node;
    *y = *x;
    x = y;

    if (x->left == x->right) {
        x->cnt += delta;
    } else {
        int mid = (x->left + x->right) / 2;

        if (pos <= mid)
            x->leftchild = persistent_modify(x->leftchild, pos, delta);
        else
            x->rightchild = persistent_modify(x->rightchild, pos, delta);

        x->update();
    }

    return x;
}

static int query(Node *x, int left, int right) {
    if (left <= x->left && x->right <= right)
        return x->cnt;
    else {
        int mid = (x->left + x->right) / 2;
        int answer = 0;
        
        if (left <= mid)
            answer += query(x->leftchild, left, right);
        if (right > mid)
            answer += query(x->rightchild, left, right);

        return answer;
    }
}

typedef set<int>::iterator iterator_t;

static int n, q;
static vector<int> G[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static int color[NMAX + 10];
static int seq[NMAX + 10];
static int val[NMAX + 10];
static set<int> list[CMAX + 10];
static Node *version[NMAX + 10];

static void fenwick_modify(int ver, int pos, int delta) {
    for (; ver <= n; ver += ver & (-ver)) {
        version[ver] = persistent_modify(
            version[ver], pos, delta
        );
    }
}

static int fenwick_query(int ver, int left, int right) {
    int answer = 0;

    for (; ver; ver -= ver  & (-ver)) {
        answer += query(
            version[ver], left, right
        );
    }

    return answer;
}

static void dfs(int x, int f) {
    in[x] = ++timestamp;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;

        dfs(v, x);
    }

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        seq[in[i]] = color[i];
    }

    version[0] = build(0, CMAX);
    for (int i = 1; i <= n; i++) {
        version[i] = version[0];
    }

    for (int i = 1; i <= CMAX; i++) {
        list[i].insert(0);
    }

    for (int i = 1; i <= n; i++) {
        val[i] = *list[seq[i]].rbegin();
        list[seq[i]].insert(i);
        fenwick_modify(i, val[i], 1);
    }
}

inline void change(int p, int v) {
    fenwick_modify(p, val[p], -1);
    fenwick_modify(p, v, 1);
    val[p] = v;
}

int main() {
    initialize();

    scanf("%d", &q);
    while (q--) {
        int command;
        scanf("%d", &command);

        if (command == 1) {
            int x;
            scanf("%d", &x);
            int l = in[x], r = out[x];

            int answer = fenwick_query(r, 0, l - 1) -
                         fenwick_query(l - 1, 0, l - 1);
            printf("%d\n", answer);
        } else {
            int p, c;
            scanf("%d%d", &p, &c);
            p = in[p];

            iterator_t iter1 = list[seq[p]].find(p);
            iterator_t iter2 = list[c].insert(p).first;
            iterator_t next1 = next(iter1);
            iterator_t next2 = next(iter2);

            if (next1 != list[seq[p]].end())
                change(*next1, *prev(iter1));
            if (next2 != list[c].end())
                change(*next2, p);
            list[seq[p]].erase(iter1);
            change(p, *prev(iter2));
            seq[p] = c;
        }
    }

    return 0;
}
