//伸展树（splay-tree）
#include<cstdio>
#include<iostream>
#include<stdlib.h>
#define SIZE 10000000
#define ll long long
using namespace std;

template<class T>
struct node{
    node(){}
    node(T d):data(d),left(0),right(0),right(0),cnt(1),sum(0){}

    T data;
    int cnt;//以该节点为根的子树的节点数
    ll sum;//和
    node * left;
    node * right;
    node * f;
};
struct client{
    int idx;
    ll f;
    ll d;
};

node<client> pool[SIZE];
int idx;

template<class T>
node<T> * get( T _data){
    pool[idx].data = _data;
    pool[idx].left = 0;
    pool[idx].right = 0;
    pool[idx].f = 0;
    pool[idx].cnt = 1;
    pool[idx].sum = 0;
    return pool + (idx++);
}

template<class T>
class splay{
public:
    splay():rt(0),idx(0){}

    int GetCnt(node<T> * p){
        return p == 0 ? 0:p->cnt;
    }

    ll GetSum(node<T> * p){
        return p == 0?0:p->sum;
    }

    void push_up(node<T> * p){
        p->cnt = GetCnt(p->left)+GetCnt(p->right)+1;
        p->sum = GetSum(p->left) + GetSum(p->right) + (p->data).d;
    }

    void push_down(node<T> * p){
        if( p->left != 0){
            (p->left->data).f += (p->data).f;
            p->left->sum += p->left->cnt * (p->data).f;
            (p->left->data).d += (p->data).f;
        }

        if(p->right != 0){
            (p->right->data).f += (p->data).f;
             p->right->sum += p->right->cnt * (p->data).f;
            (p->right->data).d += (p->data).f;
        }

        (p->data).f = 0;

    }

    void _insert(node<T> * root,node<T> * t){
        if(root->data > t->data){
            if(root->left != 0){
                _insert(root->left,t);
            }
            else{
                root->left = t;
                t->f = root;
            }
        }
        else{
            if(root->right != 0){
                _insert(root->right,t);
            }
            else{
                root->right = t;
                t->f = root;
            }
        }
        push_up(root);
    }

    void Insert(T _data){//插入操作
        node<T> * tmp = get( _data ) ;

        if(rt == 0) rt = tmp;
        else{
            _insert(rt,tmp);

            Splay(tmp,1);
        }
    }

    node<T> * _find(node<T> * root,T _data){
        if(root == 0 || root ->data == _data ) return root;

        if( (root->data).f != 0 ) push_down(root);//若遇到懒惰标记，将其下延

        if( root->data > _data)    return _find(root->left,_data);
        else  return _find(root->right,_data);
    }

    node<T>* Find(T _data){
        node<T> * tmp = _find(rt,_data);
        if(tmp == 0) return 0;
        else{//查找，如果查找成功，则splay
            Splay(tmp,1);
            return tmp;
        }
    }

    node<T> * _target(int p){
        if(p == 1) return rt;
        else return rt->right;
    }

    void Splay(node<T> * x,int xx){
        if( (x->data).f != 0 ) push_down(x);//若遇到懒惰标记，将其下延

        if(x == _target(xx)) return;
        if( x->f == _target(xx)){//如果x的父节点是根节点
            if(x->f->left == x){//x为其左孩子
                zig(x);
            }
            else{
                zag(x);
            }
            return;
        }
        else{

            //if(x == rt && root != rt)

            /*if(x == 0){
                printf("x\n");
            }

            if(x->f == 0){
                printf("x->f\n");
            }*/


            if( x->f->left == x){//x为其父节点的左孩子
                if( x->f->f->left == x->f){
                //x的父节点也为其父节点的左孩子 zig-zig
                    zig(x->f);
                    zig(x);
                }
                else{
                //x的父节点为其父节点的右孩子 zig-zag
                    zig(x);
                    zag(x);
                }
            }
            else{
                if(x->f->f->right == x->f){
                    zag(x->f);
                    zag(x);
                }
                else{
                    zag(x);
                    zig(x);
                }
            }
            Splay(x,xx);
        }
    }

    void _display(node<T> * root){
        if(root == 0) return;
        _display(root->left);
        //cout<<root->data<<endl;
        print(root);
        _display(root->right);
    }

    void print( node<T> * root){
        printf("( idx:%d,sum:%lld,value:%d )\n",(root->data).idx,root->sum,(root->data).d );
    }

    void Display(){
        _display(rt);
    }

    node<T>* Suc(node<T> * p){//保证不存在p->right == 0的情况
        node<T> * x = p->right;
        while( x->left!=0){
            x = x->left;
        }
        return x;
    }

    void Delete(node<T> * p){
        if( !( p->left != 0  && p->right != 0 ) ){//如果p不是有两个孩子，直接删除
            if( p == rt){
                if( p->left != 0){
                    p->left->f = 0;
                    rt = p->left;
                }
                else if(p->right != 0){
                    p->right->f = 0;
                    rt = p->right;
                }
                else{
                    rt = 0;
                }
            }
            else{
                node<T> ** x;
                if(p == p->f->left) x = & (p->f->left );
                else x = &(p->f->right);

                if(p->left != 0 ){
                    p->left->f = p->f;
                    (*x) = p->left;
                }
                else if(p->right != 0){
                    p->right->f = p->f;
                    (*x) = p->right;
                }
                else{
                    (*x) = 0;
                }
                Splay(p->f,1);
            }
        }
        else{
            node<T> * t = Suc(p);
            p->data = t->data;

            node<T> ** x;
            if(t == t->f->left) x =&(t->f->left);
            else x = &(t->f->right);

            if(t->right != 0){
                t->right->f = t->f;
                (*x) = t->right;
            }
            else (*x) = 0;
            Splay(p,1);
        }
    }

    node<T> * Max(){
        if(rt == 0) return 0;
        node<T> * p = rt;
        while(p->right != 0){
            p = p->right;
        }
        return p;
    }

    node<T> * Min(){
        if(rt == 0) return 0;
        node<T>*p = rt;
        while(p->left != 0){
            p = p->left;
        }
        return p;
    }

    //for poj 3468
    ll Query(int a,int b){
        client t1,t2;

        t1.idx = a-1;
        t2.idx = b+1;

        node<T> * l = Find(t1);
        node<T> * r = Find(t2);
        Splay(l,1);

        //print(rt);

        Splay(r,2);

        //print(rt->right);

        return r->left->sum;
    }

    void Update(int a,int b,int c){
        client t1,t2;

        t1.idx = a-1;
        t2.idx = b+1;

        node<T> * l = Find(t1);
        node<T> * r = Find(t2);
        Splay(l,1);

        Splay(r,2);

        r->left->sum += r->left->cnt * c;
        (r->left->data).d += c;
        (r->left->data).f += c;

    }
private:
    node<T> * rt;
    int idx;

    void zig(node<T> * x){
    //右旋操作
        node<T> * y = x->f;
        node<T> * p = x->right;
        x->right = y;
        x->f = y->f;
        if( y->f != 0){
            if(y->f->left == y)     y->f->left = x;
            else y->f->right = x;
        }
        y->f = x;
        y->left = p;
        if( p !=0 ) p->f = y;
        if(x->f == 0) rt = x;//更改根节点

        push_up(y);
        push_up(x);
    }

    void zag(node<T> * x){
    //左旋
        node<T> * y = x->f;
        node<T> * p = x->left;
        x->left = y;
        x->f = y->f;
        if(y->f != 0){
            if(y->f->left == y) y->f->left = x;
            else y->f->right = x;
        }
        y->f = x;
        y->right = p;
        if(p!=0) p->f = y;
        if(x->f == 0) rt = x;//更改根节点

        push_up(y);
        push_up(x);

    }


};




bool operator < (client a,client b){
    return a.idx<b.idx;
}

bool operator > (client a,client b){
    return a.idx>b.idx;
}

bool operator == (client a,client b){
    return a.idx == b.idx;
}

int main()
{

    int n,q,i,a,b,c;
    char op[4];
    client tmp;
    while(scanf("%d%d",&n,&q) != EOF){
        splay<client> s;
        tmp.idx = 0;
        tmp.f = 0;
        tmp.d = 0;
        s.Insert(tmp);
        for(i=1;i<=n;i++){
            scanf("%lld",&tmp.d);
            tmp.idx = i;
            s.Insert(tmp);
        }
        tmp.idx = n+1;
        s.Insert(tmp);
        //s.Display();
        while(q--){
            scanf("%s",op);
            scanf("%d%d",&a,&b);
            if(op[0]=='Q'){
                printf("%lld\n",s.Query(a,b));
            }
            else{
                scanf("%d",&c);
                s.Update(a,b,c);
            }
        }
    }
    return 0;
}
