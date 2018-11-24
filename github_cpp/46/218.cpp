/* HDU 1166 Partial Code */

struct ST{
    struct Node{
        int value,lazy;
        Node *lc,*rc;
        Node():lc(NULL),rc(NULL),lazy(0){}
        void pull(){ value = lc->value + rc->value; }
        void push(){
            if(!lazy) return;
            if(lc){ lc->lazy = lazy;lc->value += lazy; }
            if(rc){ rc->lazy = lazy;rc->value += lazy; }
            lazy = 0;
        }
    };
    
    vector<int> A;

    Node* build(int L,int R){
        Node *node = new Node();
        if(L == R){
            node->value = A[L];
            return node;
        }
        int mid = (L+R)>>1;
        node->lc = build(L,mid);
        node->rc = build(mid+1,R);
        node->pull();
        return node;
    }

    void modify(Node *node,int L,int R,int ql,int qr,int d){
        if(R < ql || qr < L) return;
        if(ql <= L && R <= qr){
            node->lazy += d;
            node->value += d;
            return;
        }
        node->push();
        int mid = (L+R)>>1;
        modify(node->lc,L,mid,ql,qr,d);
        modify(node->rc,mid+1,R,ql,qr,d);
        node->pull();
    }

    int query(Node* node,int L,int R,int ql,int qr){
        if(R < ql || qr < L) return 0;
        if(ql <= L && R <= qr) return node->value;
        node->push();
        int mid = (L+R)>>1;
        return query(node->lc,L,mid,ql,qr) + query(node->rc,mid+1,R,ql,qr);
    }

    void delete_(Node* now){
        if(!now) return;
        delete_(now->lc);
        delete_(now->rc);
        delete now;
    }
};
