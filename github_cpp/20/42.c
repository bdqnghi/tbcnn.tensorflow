#include <cstdio>
#include <cctype>
#include <cassert>
using namespace std;



#define bro(x) (((x)->ftr->lc == (x)) ? ((x)->ftr->rc) : ((x)->ftr->lc))
#define islc(x) ((x) != NULL && (x)->ftr->lc == (x))
#define isrc(x) ((x) != NULL && (x)->ftr->rc == (x))

template<typename T>
class redblacktree {
    protected:
        struct Node;

        Node* _root;    
        Node* _hot; 

        void init(T);
        void connect34(Node*, Node*, Node*, Node*, Node*, Node*, Node*);
        void SolveDoubleRed(Node*); 
        void SolveDoubleBlack(Node*);   
        Node* find(T, const int);   
        Node* rfind(T, const int);  
        Node* findkth(int, Node*);
        int find_rank(T, Node*);
#ifdef __REDBLACK_DEBUG
        void checkconnect(Node*);
        void previs(Node*, int);
        void invis(Node*, int);
        void postvis(Node*, int);
#endif

    public:
        struct iterator;
        redblacktree() : _root(NULL), _hot(NULL) {}
        int get_rank(T);
        iterator insert(T);
        bool remove(T);
        int size();
        bool empty();
        iterator kth(int);
        iterator lower_bound(T);
        iterator upper_bound(T);
#ifdef __REDBLACK_DEBUG
        void vis();
        void correctlyconnected();
#endif
};

template <typename T>
struct redblacktree<T>::Node {
    T val;  
    bool RBc;   
    Node* ftr;  
    Node* lc;   
    Node* rc;   
    int s;      

    Node(   T v = T(), bool RB = true,
            Node* f = NULL, Node* l = NULL, Node* r = NULL ,int ss = 1  )
        : val(v), RBc(RB), ftr(f), lc(l), rc(r), s(ss) {}

    Node* succ() {      
        Node* ptn = rc;
        while(ptn->lc != NULL) {
            --(ptn->s);
            ptn = ptn->lc;
        }
        return ptn;
    }

    Node* left_node() {     
        Node* ptn = this;
        if(!lc) {
            while(ptn->ftr && ptn->ftr->lc == ptn)
                ptn = ptn->ftr;
            ptn = ptn->ftr;
        } else
            while(ptn->lc)
                ptn = ptn->lc;
        return ptn;
    }

    Node* right_node() {    
        Node* ptn = this;
        if(!rc) {
            while(ptn->ftr && ptn->ftr->rc == ptn)
                ptn = ptn->ftr;
            ptn = ptn->ftr;
        } else
            while(ptn->rc)
                ptn = ptn->rc;
        return ptn;
    }

    void maintain() {   
        s = 1;
        if(lc) s += lc->s;
        if(rc) s += rc->s;
    }
};

template <typename T>
struct redblacktree<T>::iterator {
    private:

        Node* _real__node;

    public:

        iterator& operator++() {
            _real__node = _real__node->right_node();
            return *this;
        }

        iterator& operator--() {
            _real__node = _real__node->left_node();
            return *this;
        }

        T operator*() {
            return _real__node->val;
        }

        iterator(Node* node_nn = NULL) : _real__node(node_nn) {}
		iterator(T const &val_vv) : _real__node(rfind(val_vv), 0){}
        
        
		iterator(iterator const& iter) : _real__node(iter._real__node) {}
};

template <typename T>
typename
redblacktree<T>::iterator redblacktree<T>::insert(T v) {
    Node* ptn = find(v, 1);
    if(_hot == NULL) {
        init(v);
        return iterator(_root);
    }
    ptn = new Node(v, true, _hot, NULL, NULL, 1);
    if( _hot->val <= v  )
        _hot->rc = ptn;
    else
        _hot->lc = ptn;
    SolveDoubleRed(ptn);
    return iterator(ptn);
}

template <typename T>
void redblacktree<T>::init(T v) {
    _root = new Node(v, false, NULL, NULL, NULL, 1);
#ifdef __REDBLACK_DEBUG
    ++blackheight;
#endif
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::find(T v, const int op) {
    Node* ptn = _root;  
    _hot = NULL;    
    while(ptn != NULL) {
        _hot = ptn;
        ptn->s += op;
        if(ptn->val > v)
            ptn = ptn->lc;
        else
            ptn = ptn->rc;
    }
    return ptn;
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::rfind(T v, const int op) {
	Node* ptn = _root;
	_hot = NULL;
	while(ptn != NULL && ptn -> val != v) {
		_hot = ptn;
		ptn->s += op;
		if(ptn->val > v)
			ptn = ptn->lc;
		else
			ptn = ptn->rc;
	}
	return ptn;
}

template <typename T>
void redblacktree<T>::SolveDoubleRed(Node* nn) {
    while((!(nn->ftr)) || nn->ftr->RBc) {
        if(nn == _root) {
            _root->RBc = false;
#ifdef __REDBLACK_DEBUG
            ++blackheight;
#endif
            return;
        }
        Node* pftr = nn->ftr;
        if(!(pftr->RBc)) return;            
        Node* uncle = bro(nn->ftr);
        Node* grdftr = nn->ftr->ftr;
        if(uncle != NULL && uncle->RBc) {   
            grdftr->RBc = true;
            uncle->RBc = false;
            pftr->RBc = false;
            nn = grdftr;
        } else {                            
            if(islc(pftr)) {
                if(islc(nn)) {
                    pftr->ftr = grdftr->ftr;
                    if(grdftr == _root) _root = pftr;
                    else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = pftr;
                    else grdftr->ftr->rc = pftr;
                    connect34(pftr, nn, grdftr, nn->lc, nn->rc, pftr->rc, uncle);
                    pftr->RBc = false;
                    grdftr->RBc = true;
                } else {
                    nn->ftr = grdftr->ftr;
                    if(grdftr == _root) _root = nn;
                    else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = nn;
                    else grdftr->ftr->rc = nn;
                    connect34(nn, pftr, grdftr, pftr->lc, nn->lc, nn->rc, uncle);
                    nn->RBc = false;
                    grdftr->RBc = true;
                }
            } else {
                if(islc(nn)) {
                    nn->ftr = grdftr->ftr;
                    if(grdftr == _root) _root = nn;
                    else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = nn;
                    else grdftr->ftr->rc = nn;
                    connect34(nn, grdftr, pftr, uncle, nn->lc, nn->rc, pftr->rc);
                    nn->RBc = false;
                    grdftr->RBc = true;
                } else {
                    pftr->ftr = grdftr->ftr;
                    if(grdftr == _root) _root = pftr;
                    else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = pftr;
                    else grdftr->ftr->rc = pftr;
                    connect34(pftr, grdftr, nn, uncle, pftr->lc, nn->lc, nn->rc);
                    pftr->RBc = false;
                    grdftr->RBc = true;
                }
            }
            return;
        }
    }
}

template <typename T>
void redblacktree<T>::connect34(    Node* nroot,    Node* nlc,      Node* nrc,
                                    Node* ntree1,   Node* ntree2,   Node* ntree3,   Node* ntree4) {
    nlc->lc = ntree1;
    if(ntree1 != NULL) ntree1->ftr = nlc;
    nlc->rc = ntree2;
    if(ntree2 != NULL) ntree2->ftr = nlc;
    nrc->lc = ntree3;
    if(ntree3 != NULL) ntree3->ftr = nrc;
    nrc->rc = ntree4;
    if(ntree4 != NULL) ntree4->ftr = nrc;
    nroot->lc = nlc;
    nlc->ftr = nroot;
    nroot->rc = nrc;
    nrc->ftr = nroot;
    nlc->maintain();
    nrc->maintain();
    nroot->maintain();
}

template <typename T>
typename
redblacktree<T>::iterator redblacktree<T>::lower_bound(T v) {
    Node* ptn = _root;
    while(ptn) {
        _hot = ptn;
        if(ptn->val < v) {
            ptn = ptn->rc;
        } else {
            ptn = ptn->lc;
        }
    }
    if(_hot->val < v) {
        ptn = _hot;
    } else {
        ptn = _hot->left_node();
    }
    return iterator(ptn);
}

template <typename T>
typename
redblacktree<T>::iterator redblacktree<T>::upper_bound(T v) {
    Node* ptn = _root;
    while(ptn) {
        _hot = ptn;
        if(ptn->val > v) {
            ptn = ptn->lc;
        } else {
            ptn = ptn->rc;
        }
    }
    if(_hot->val > v) {
        ptn = _hot;
    } else {
        ptn = _hot->right_node();
    }
    return iterator(ptn);
}

template <typename T>
typename
redblacktree<T>::iterator redblacktree<T>::kth(int rank) {
    return iterator(findkth(rank, _root));
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::findkth(int rank, Node* ptn) {
    if(!(ptn->lc)) {
        if(rank == 1) {
            return ptn;
        } else {
            return findkth(rank - 1, ptn->rc);
        }
    } else {
        if(ptn->lc->s == rank - 1) return ptn;
        else if(ptn->lc->s >= rank) return findkth(rank, ptn->lc);
        else return findkth(rank - (ptn->lc->s) - 1, ptn->rc);
    }
}

template <typename T>
int redblacktree<T>::get_rank(T v) {
    return find_rank(v, _root);
}

template <typename T>
int redblacktree<T>::find_rank(T v, Node* ptn) {
    if(!ptn) return 1;
    else if(ptn->val >= v) return find_rank(v, ptn->lc);
    else return (1 + ((ptn->lc) ? (ptn->lc->s) : 0) + find_rank(v, ptn->rc));
}

template <typename T>
int redblacktree<T>::size() {
    return _root->s;
}

template <typename T>
bool redblacktree<T>::empty() {
    return !_root;
}

template <typename T>
bool redblacktree<T>::remove(T v) {
    Node* ptn = rfind(v, -1);
    if(!ptn) return false;
    Node* node_suc;
    while(ptn->lc || ptn->rc) { 
        if(!(ptn->lc)) {
            node_suc = ptn->rc;
        } else if(!(ptn->rc)) {
            node_suc = ptn->lc;
        } else {
            node_suc = ptn->succ();
        }
        --(ptn->s);
        ptn->val = node_suc->val;
        ptn = node_suc;
    }
    if(!(ptn->RBc)) {
        --(ptn->s);
        SolveDoubleBlack(ptn);
    }
    if(ptn == _root) {
        _root = NULL;
        delete ptn;
        return true;
    }
    if(ptn->ftr->lc == ptn)
        ptn->ftr->lc = NULL;
    else
        ptn->ftr->rc = NULL;
    delete ptn;
    return true;
}

template <typename T>
void redblacktree<T>::SolveDoubleBlack(Node* nn) {
    while(nn != _root) {
        Node* pftr = nn->ftr;
        Node* bthr = bro(nn);
        if(bthr->RBc) {                 
            bthr->RBc = false;
            pftr->RBc = true;
            if(_root == pftr) _root = bthr;
            if(pftr->ftr) {
                if(pftr->ftr->lc == pftr)
                    pftr->ftr->lc = bthr;
                else
                    pftr->ftr->rc = bthr;
            }
            bthr->ftr = pftr->ftr;
            if(islc(nn)) {
                connect34(bthr, pftr, bthr->rc, nn, bthr->lc, bthr->rc->lc, bthr->rc->rc);
            } else {
                connect34(bthr, bthr->lc, pftr, bthr->lc->lc, bthr->lc->rc, bthr->rc, nn);
            }
            bthr = bro(nn);
            pftr = nn->ftr;
        }
        if(bthr->lc && bthr->lc->RBc) { 
            bool oldRBc = pftr->RBc;
            pftr->RBc = false;
            if(pftr->lc == nn) {
                if(pftr->ftr) {
                    if(pftr->ftr->lc == pftr)
                        pftr->ftr->lc = bthr->lc;
                    else
                        pftr->ftr->rc = bthr->lc;
                }
                bthr->lc->ftr = pftr->ftr;
                if(_root == pftr) _root = bthr->lc;
                connect34(bthr->lc, pftr, bthr, pftr->lc, bthr->lc->lc, bthr->lc->rc, bthr->rc);
            } else {
                bthr->lc->RBc = false;
                if(pftr->ftr) {
                    if(pftr->ftr->lc == pftr)
                        pftr->ftr->lc = bthr;
                    else
                        pftr->ftr->rc = bthr;
                }
                bthr->ftr = pftr->ftr;
                if(_root == pftr) _root = bthr;
                connect34(bthr, bthr->lc, pftr, bthr->lc->lc, bthr->lc->rc, bthr->rc, pftr->rc);
            }
            pftr->ftr->RBc = oldRBc;
            return;
        } else if(bthr->rc && bthr->rc->RBc) {  
            bool oldRBc = pftr->RBc;
            pftr->RBc = false;
            if(pftr->lc == nn) {
                bthr->rc->RBc = false;
                if(pftr->ftr) {
                    if(pftr->ftr->lc == pftr)
                        pftr->ftr->lc = bthr;
                    else
                        pftr->ftr->rc = bthr;
                }
                bthr->ftr = pftr->ftr;
                if(_root == pftr) _root = bthr;
                connect34(bthr, pftr, bthr->rc, pftr->lc, bthr->lc, bthr->rc->lc, bthr->rc->rc);
            } else {
                if(pftr->ftr) {
                    if(pftr->ftr->lc == pftr)
                        pftr->ftr->lc = bthr->rc;
                    else
                        pftr->ftr->rc = bthr->rc;
                }
                bthr->rc->ftr = pftr->ftr;
                if(_root == pftr) _root = bthr->rc;
                connect34(bthr->rc, bthr, pftr, bthr->lc, bthr->rc->lc, bthr->rc->rc, pftr->rc);
            }
            pftr->ftr->RBc = oldRBc;
            return;
        }
        if(pftr->RBc) {                 
            pftr->RBc = false;
            bthr->RBc = true;
            return;
        } else {                        
            bthr->RBc = true;
            nn = pftr;
        }
    }
#ifdef __REDBLACK_DEBUG
    --blackheight;
#endif
}


#ifdef __REDBLACK_DEBUG

int blackheight(0);

template <typename T>   
void redblacktree<T>::previs(Node* ptn, int cnt) {
    if(ptn == NULL) {
        if(blackheight == -1) blackheight = cnt;
        assert(blackheight == cnt);
        return;
    }
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
    if(!(ptn->RBc)) ++cnt;
    previs(ptn->lc, cnt);
    previs(ptn->rc, cnt);
}

template <typename T>   
void redblacktree<T>::invis(Node* ptn, int cnt) {
    if(ptn == NULL) {
        if(blackheight == -1) blackheight = cnt;
        assert(blackheight == cnt);
        return;
    }
    if(!(ptn->RBc)) ++cnt;
    invis(ptn->lc, cnt);
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
    invis(ptn->rc, cnt);
}

template <typename T>   
void redblacktree<T>::postvis(Node* ptn, int cnt) {
    if(ptn == NULL) {
        if(blackheight == -1) blackheight = cnt;
        assert(blackheight == cnt);
        return;
    }
    if(!(ptn->RBc)) ++cnt;
    postvis(ptn->lc, cnt);
    postvis(ptn->rc, cnt);
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
}

template <typename T>   
void redblacktree<T>::vis() {
    printf("BlackHeight:\t%d\n", blackheight);
    printf("------pre-vis------\n");
    previs(_root, 0);
    printf("------in-vis------\n");
    invis(_root, 0);
    printf("------post-vis------\n");
    postvis(_root, 0);
}

template <typename T>   
void redblacktree<T>::checkconnect(Node* ptn) {
    if(!ptn) return;
    assert(ptn->s > 0);
    if(ptn->lc && ptn->lc->ftr != ptn) {
        printf("Oops! %d has a lc %d, but it failed to point its ftr!\n", ptn->val, ptn->lc->val);
    }
    if(ptn->rc && ptn->rc->ftr != ptn) {
        printf("Oops! %d has a rc %d, but it failed to point its ftr!\n", ptn->val, ptn->rc->val);
    }
    int sss = ptn->s;
    if(ptn->lc) sss -= ptn->lc->s;
    if(ptn->rc) sss -= ptn->rc->s;
    if(sss - 1) {
        printf("Damn! %d's size is %d, but the sum of its children's size is %d!\n", ptn->val, ptn->s, ptn->s - sss);
    }
    checkconnect(ptn->lc);
    checkconnect(ptn->rc);
}

template <typename T>
void redblacktree<T>::correctlyconnected() {
    checkconnect(_root);
}
#endif

inline
int readint() {
    int ret(0);
    int sgn(1);
    char c;
    while(isspace(c = getchar()));
    if(c == '-') {
        sgn = -1;
        c = getchar();
    }
    while(isdigit(c)) {
        ret = (ret << 3) + (ret << 1) + c - '0';
        c = getchar();
    }
    return ret * sgn;
}
#define ri readint()

int opt, x;

int tot;

redblacktree<int> my_tree;

int main() {
    int i;
    tot = ri;
    redblacktree<int>::iterator it;
    for(i = 0; i < tot; ++i) {
        opt = ri;
        x = ri;
        switch(opt) {
            case 1:
                my_tree.insert(x);
                break;
            case 2:
                my_tree.remove(x);
                break;
            case 3:
                printf("%d\n", my_tree.get_rank(x));
                break;
            case 4:
                it = my_tree.kth(x);
                printf("%d\n", *it);
                break;
            case 5:
                it = my_tree.lower_bound(x);
                printf("%d\n", *it);
                break;
            case 6:
                it = my_tree.upper_bound(x);
                printf("%d\n", *it);
                break;
            default:
                break;
        }
    }

    return 0;
}

