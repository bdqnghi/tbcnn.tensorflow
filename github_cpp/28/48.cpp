// https://blog.csdn.net/qq_34374664/article/details/77888508

void Init() {
    node_cnt = 0;
    T[0].fa = T[0].sz = T[0].ch[0] = T[0].ch[1] = T[0].rev = T[0].lazy = 0;

    rep(i, 0, n) scanf("%d", a+i);
    ans.init(a, n);
    /// 一定记得之后的所有区间操作都要对 l, r 加 1，区间从 1 开始
}

#define lson T[x].ch[0]
#define rson T[x].ch[1]

struct Node {
    int val, sz, fa, ch[2], mi, rev, lazy;
};
Node T[N]; int node_cnt;
struct Splay {
    int root;
    void init(int *val, int n) {    // 序列存在 val[0 ~ n-1]
        root = 0;
        T[node_cnt+1].val = T[node_cnt+n+2].val = INF;
        rep(i, 2, n+2) T[node_cnt+i].val = val[i-2];
        build(root, node_cnt+1, node_cnt+n+2, 0);
        pushup(root);
        node_cnt += n + 2;
    }
    void update_rev(int x) {
        if (!x) return ;
        swap(lson, rson);
        T[x].rev ^= 1;
    }
    void update_add(int x, int v) {
        if (!x) return ;
        T[x].lazy += v; T[x].val += v; T[x].mi += v;
    }
    void newnode(int x, int v, int fa) {
        T[x].fa = fa; T[x].sz = 1;
        T[x].val = T[x].mi = v;
        lson = rson = T[x].rev = T[x].lazy = 0;
    }
    void pushup(int x) {
        if (!x) return ;
        T[x].sz = 1; T[x].mi = T[x].val;
        if (lson) T[x].sz += T[lson].sz, T[x].mi = min(T[x].mi, T[lson].mi);
        if (rson) T[x].sz += T[rson].sz, T[x].mi = min(T[x].mi, T[rson].mi);
    }
    void pushdown(int x) {
        if (!x) return ;
        if (T[x].lazy) {
            update_add(lson, T[x].lazy);
            update_add(rson, T[x].lazy);
            T[x].lazy = 0;
        }
        if (T[x].rev) {
            update_rev(lson);
            update_rev(rson);
            T[x].rev = 0;
        }
    }
    void build(int &x, int l, int r, int fa) {
        if (l > r) return ;
        int mid = (l + r) >> 1;
        x = mid; newnode(x, T[x].val, fa);
        build(lson, l, mid-1, x);
        build(rson, mid+1, r, x);
        pushup(x);
    }
    void rotate(int x, int p) {     // p = 0 左旋， p = 1 右旋
        int y = T[x].fa, z = T[y].fa;
        pushdown(y); pushdown(x);
        T[y].ch[!p] = T[x].ch[p];
        if(T[x].ch[p]) T[T[x].ch[p]].fa = y;
        T[x].fa = z;
        if (z) T[z].ch[T[z].ch[1]==y] = x;
        T[y].fa = x; T[x].ch[p] = y;
        pushup(y); pushup(x);
    }
    void splay(int x, int goal) {
        pushdown(x);
        while (T[x].fa != goal) {
            int y = T[x].fa, z = T[y].fa;
            pushdown(z); pushdown(y); pushdown(x);
            if (T[y].fa == goal) rotate(x, T[y].ch[0] == x);
            else {
                int p = T[T[y].fa].ch[0] == y;
                if (T[y].ch[p] == x) rotate(x, !p), rotate(x, p);
                else rotate(y, p), rotate(x, p);
            }
        }
        pushup(x);
        if (goal == 0) root = x;
    }
    int extreme(int x, int p) {     // 以 x 为根的子树的极值点，0 极小，1 极大
        while (T[x].ch[p]) x = T[x].ch[p];
        splay(x, 0);
        return x;
    }
    int kth(int x, int k) {     // 以节点编号 x 为根的子树，第 k 个数的节点编号
        pushdown(x);
        if (T[lson].sz + 1 == k) return x;
        else if (T[lson].sz >= k) return kth(lson, k);
        return kth(rson, k - T[lson].sz - 1);
    }
    void exchange(int a, int b, int c) {    // 交换区间 [a, b-1] 和 [b, c]
        if (b > c) return ;
        int x = kth(root, b-1), y = kth(root, c+1);
        splay(x,0), splay(y,x);
        int tmp = T[y].ch[0]; T[y].ch[0] = 0; //“剪贴下来”
        pushup(y); pushup(x);
        x = kth(root, a-1),y = kth(root, a);
        splay(x,0), splay(y,x);
        T[y].ch[0] = tmp;
        T[tmp].fa = y;
        pushup(y); pushup(x);
    }
    void exchange(int l1, int r1, int l2, int r2) {     // 交换区间 [l1, r1] 和 [l2, r2]
        exchange(l1, r1+1, l2-1);
        exchange(l1, l2, r2);
    }
    void reversal(int l, int r) {   // 翻转区间 [l, r]
        int x = kth(root, l-1), y = kth(root, r+1);
        splay(x, 0); splay(y, x);
        update_rev(T[y].ch[0]);
    }
    void addval(int l, int r, int v) {  // 区间加
        int x = kth(root, l-1), y = kth(root, r+1);
        splay(x, 0); splay(y, x);
        update_add(T[y].ch[0], v);
    }
    void ins(int k, int x) {    // 在第 k 个数后插入值为 x 的节点
        int r = kth(root, k), rr = kth(root, k+1);
        splay(r, 0), splay(rr, r);
        newnode(++node_cnt, x, rr); T[rr].ch[0] = node_cnt;
        for (r = rr; r; r = T[r].fa) pushdown(r), pushup(r);
        splay(rr, 0);
    }
    void del(int k) {   // 删除第 k 位置的数
        splay(kth(root, k-1), 0);
        splay(kth(root, k+1), root);
        T[T[root].ch[1]].ch[0] = 0;
        pushup(T[root].ch[1]);
        pushup(root);
    }
    int get_min(int l, int r) {
        int x = kth(root, l-1), y = kth(root, r+1);
        splay(x, 0); splay(y, x);
        return T[T[y].ch[0]].mi;
    }
    void out(int x) {
        pushdown(x);
        if (lson) out(lson);
        printf("%d ", T[x].val);
        if (rson) out(rson);
    }
};
