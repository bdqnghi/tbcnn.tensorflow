#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

class SuffixTree {
 public:
    static constexpr int SIGMA = 27;
    static constexpr char EOFCHAR = 0;

    SuffixTree() : size(0) {
        root = new Node;
    }

    void append(const char c) {
        // Active node
        static Node *active = root;
        // Active node transformation. -1 for not determind
        static char dir = -1;
        // Walked length
        static int len = 0;
        // Current suffix length
        static int cnt = 0;

        // Increase suffix length
        cnt++;
        Node *last = nullptr;
        while (cnt) {
            // Correct Walked length by suffix length
            if (cnt <= len) {
                len = cnt - 1;
                dir = len ? str[size - len + 1] : -1;
            }

            // If walked length is not less than the length of edge,
            // we can walk to the next node
            while (dir >= 0 && len >= length(active->trans[dir])) {
                len -= length(active->trans[dir]);
                active = active->trans[dir]->next;
                dir = len ? str[size - len + 1] : -1;
            }  // while

            // Try finding a transformation contain c
            if ((dir >= 0 && str[active->trans[dir]->left + len] == c) ||
                (dir < 0 && active->trans[c])) {
                // If exist
                // dir < 0 means the active node not started
                if (dir < 0)
                    dir = c;

                len++;

                // Set suffix link
                // There may be someone jump to here,
                // it must be a suffix to the previous one
                if (last)
                    last->suffix_link = active;

                // Stop, since all the suffix exist in the tree
                break;
            }

            Node *x;
            if (len == 0) {
                // Make a new leaf
                active->trans[c] = new Edge(size + 1, 0, new Node);
                x = active;
            } else {
                // Cut the edge
                Edge *t = active->trans[dir];
                x = new Node;

                x->trans[c] = new Edge(size + 1, 0, new Node);
                x->trans[str[t->left + len]] =
                    new Edge(t->left + len, t->right, t->next);
                t->right = t->left + len - 1;
                t->next = x;
            }

            // Set suffix link
            // for the same reason above
            if (last)
                last->suffix_link = x;

            // x becomes the last one
            last = x;

            // Follow the suffix link to the next suffix
            if (active != root)
                active = active->suffix_link;
            cnt--;
        }  // while

        // Append char
        str[++size] = c;
    }

    void sort(int *sa) {
        int pos = 0;
        _sort(root, sa, pos);
    }

 private:
    struct Node {
        struct Edge {
            Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

            int left, right;
            Node *next;
        };  // struct Edge

        Node() : suffix_link(nullptr) {
            memset(trans, 0, sizeof(trans));
        }

        Node *suffix_link;
        Edge *trans[SIGMA];
    };  // struct Node

    typedef Node::Edge Edge;

    int length(const Edge *e) {
        return e->right ? e->right - e->left + 1 : size - e->left + 1;
    }

    void _sort(Node *x, int *sa, int &pos, int depth = 0) {
        bool has_child = false;
        for (int p = 0; p < SIGMA; p++) {
            if (x->trans[p]) {
                has_child = true;

                _sort(x->trans[p]->next, sa, pos, depth + length(x->trans[p]));
            }
        }  // for

        if (!has_child)
            sa[++pos] = size - depth + 1;
    }

    Node *root;
    int size;
    char str[NMAX + 10];
};  // class SuffixTree

static int n;
static char buffer[NMAX + 10];
static int sa[NMAX + 10];
static int rnk[NMAX + 10];
static int lcp[NMAX + 10];

int main() {
    scanf("%s", buffer + 1);
    n = strlen(buffer + 1);

    SuffixTree *tree = new SuffixTree;
    for (int i = 1; buffer[i]; i++) {
        tree->append(buffer[i] - 'a' + 1);
    }  // for
    tree->append(SuffixTree::EOFCHAR);

    tree->sort(sa);
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i + 1];
    }  // for

    for (int i = 1; i <= n; i++) {
        rnk[sa[i]] = i;
    }  // for

    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (rnk[i] == 1)
            continue;

        j--;

        if (j < 0)
            j = 0;

        while (buffer[sa[rnk[i]] + j] == buffer[sa[rnk[i] - 1] + j]) {
            j++;
        }  // while

        lcp[rnk[i]] = j;
    }  // for

    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }  // for
    printf("\n");

    for (int i = 2; i <= n; i++) {
        printf("%d ", lcp[i]);
    }  // for
    printf("\n");

    return 0;
}  // function main
