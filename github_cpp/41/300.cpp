//red-black-tree
#include<cstdio>
#define MAX 100010
using namespace std;

class node{
public:
    int left;   //left child
    int right;  //right child
    int color;  //1 for black,0 for red
    int key;    //data field
    int p;      //pointer to father
    int size;   //the size of the tree , whose root is the node
    int id;     //the satellite data in my program
};


node tot[MAX];
const int nil = 0;

class rbt{
public:
    int root,idx;

    rbt(){
        root = nil;
        idx = 1;
        tot[nil].color = 1;
        tot[nil].size = 0;
    }
    void l_rot(int x){//left rotation
        int y = tot[x].right;
        tot[x].right = tot[y].left;
        if( tot[y].left != nil) tot [ tot[y].left ].p = x;
        tot[y].p = tot[x].p;
        if( tot[x].p == nil) root = y;
        else if(x == tot [ tot[x].p ].left ) tot [ tot[x].p ].left = y;
        else tot[ tot[x].p ].right = y;
        tot[y].left = x;
        tot[x].p = y;
        tot[x].size = tot[ tot[x].left ].size + tot[ tot[x].right ].size+1;
        tot[y].size = tot[ tot[y].left ].size + tot[ tot[y].right ].size+1;
    }

    void r_rot(int x){//right rotation
        int y = tot[x].left;
        tot[x].left = tot[y].right;
        if( tot[y].right != nil) tot [ tot[y].right ].p = x;
        tot[y].p = tot[x].p;
        if( tot[x].p == nil) root = y;
        else if(x == tot [ tot[x].p ].left ) tot [ tot[x].p ].left = y;
        else tot[ tot[x].p ].right = y;
        tot[y].right = x;
        tot[x].p = y;
        tot[x].size = tot[ tot[x].left ].size + tot[ tot[x].right ].size+1;
        tot[y].size = tot[ tot[y].left ].size + tot[ tot[y].right ].size+1;
    }

    void rb_insert(int val,int id){//insert method
        tot[idx].key = val;
        tot[idx].id = id;
        int z = idx;
        idx++;
        int y = nil;
        int x = root;
        while( x != nil){
            y = x;
            if( tot[z].key < tot[x].key) x = tot[x].left;
            else x = tot[x].right;
        }

        tot[z].p = y;
        if(y == nil) root = z;
        else if (tot[z].key < tot[y].key) tot[y].left = z;
        else tot[y].right = z;
        tot[z].left = nil;
        tot[z].right = nil;
        tot[z].color = 0;
        tot[z].size = 1;
        rb_insert_fixup(z);
        x = tot[z].p;
        while(x != nil){
            tot[x].size = tot[ tot[x].left ].size + tot[ tot[x].right ].size +1;
            x = tot[x].p;
        }
    }

    void rb_insert_fixup(int  z){
        while( tot [ tot[ z ].p ].color == 0){
            if( tot[z].p ==  tot[ tot[ tot[z].p ].p ].left ){
                int y = tot[ tot[ tot[z].p ].p ].right;
                if( tot[y].color == 0){
                    tot[ tot[z].p ].color = 1;
                    tot[y].color = 1;
                    tot[ tot[ tot[z].p ].p ].color = 0;
                    z = tot[ tot[z].p ].p;
                }
                else{
                    if( z == tot[ tot[z].p ].right){
                        z = tot[z].p;
                        l_rot(z);
                    }
                    tot[ tot[z].p ].color = 1;
                    tot[ tot[ tot[z].p ].p ].color = 0;
                    r_rot(tot[ tot[z].p ].p);
                }
            }
            else{
                int y = tot[ tot[ tot[z].p ].p ].left;
                if( tot[y].color == 0){
                    tot[ tot[z].p ].color = 1;
                    tot[y].color = 1;
                    tot[ tot[ tot[z].p ].p ].color = 0;
                    z = tot[ tot[z].p ].p;
                }
                else{
                    if( z == tot[ tot[z].p ].left){
                        z = tot[z].p;
                        r_rot(z);
                    }
                    tot[ tot[z].p ].color = 1;
                    tot[ tot[ tot[z].p ].p ].color = 0;
                    l_rot(tot[ tot[z].p ].p);
                }
            }
        }
        tot[ root ].color = 1;
    }

    void print(int r){// print all the elements in the red-black tree,using inorder traversal
        if(r==nil) return;
        if(tot[r].left != nil) print(tot[r].left);
        printf("%d : %d : %d\n",tot[r].key,tot[r].id,tot[r].size);
        if(tot[r].right != nil) print(tot[r].right);
    }

    int minimum(int x){//the minimum element in the tree , whose root is x
        while(tot[x].left != nil){
            x = tot[x].left;
        }
        return x;
    }

    int successor(int x){//the successor of x in the inorder traversal
        if(tot[x].right != nil) return minimum(tot[x].right);
        int y = tot[x].p;
        while( y != nil && x == tot[y].right){
            x = y;
            y = tot[y].p;
        }
        return y;
    }
    void rb_delete(int z){//delete
        int y;
        if( tot[z].left == nil || tot[z].right == nil) y = z;
        else y = successor(z);
        int x;
        if( tot[y].left != nil ) x = tot[y].left;
        else x = tot[y].right;

        tot[x].p = tot[y].p;

        if( tot[y].p == nil)   root = x;
        else if(y == tot[ tot[y].p ].left) tot[ tot[y].p ].left = x;
        else tot[ tot[y].p ].right = x;
        if(y!=z) {
            tot[z].key = tot[y].key;
            tot[z].id = tot[y].id;
        }

        if( tot[y].color == 1) rb_delete_fixup(x);

        x = tot[x].p;
        while(x != nil){
            tot[x].size = tot[ tot[x].left ].size + tot[ tot[x].right ].size +1;
            x = tot[x].p;
        }
    }

    void rb_delete_fixup(int x){
        int w;
        while(x!=root && tot[x].color == 1){
            if(x == tot[ tot[x].p ].left ){
                w = tot[ tot[x].p ].right;
                if( tot[w].color == 0){
                    tot[w].color = 1;
                    tot[ tot[x].p ].color = 0;
                    l_rot(tot[x].p);
                    w = tot[ tot[x].p ].right;
                }
                if( tot[ tot[w].left ].color == 1 && tot[ tot[w].right ].color == 1){
                    tot[w].color = 0;
                    x = tot[x].p;
                }
                else {
                    if( tot[ tot[w].right ].color == 1 ){
                        tot[ tot[w].left ].color = 1;
                        tot[w].color = 0;
                        r_rot(w);
                        w = tot[ tot[x].p ].right;
                    }
                    tot[w].color = tot[ tot[x].p ].color;
                    tot[ tot[x].p ].color = 1;
                    tot[ tot[w].right ].color = 1;
                    l_rot(tot[x].p);
                    x = root;
                }
            }
            else{
                if(x == tot[ tot[x].p ].right ){
                    w = tot[ tot[x].p ].left;
                    if( tot[w].color == 0){
                        tot[w].color = 1;
                        tot[ tot[x].p ].color = 0;
                        r_rot(tot[x].p);
                        w = tot[ tot[x].p ].left;
                    }
                    if( tot[ tot[w].left ].color == 1 && tot[ tot[w].right ].color == 1){
                        tot[w].color = 0;
                        x = tot[x].p;
                    }
                    else {
                        if( tot[ tot[w].left ].color == 1 ){
                            tot[ tot[w].right ].color = 1;
                            tot[w].color = 0;
                            l_rot(w);
                            w = tot[ tot[x].p ].left;
                        }
                        tot[w].color = tot[ tot[x].p ].color;
                        tot[ tot[x].p ].color = 1;
                        tot[ tot[w].left ].color = 1;
                        r_rot(tot[x].p);
                        x = root;
                    }

                }
            }
        }
        tot[x].color = 1;
    }

    int search(int r,int k){//search for the k-th minimum element in the tree
        int lsize = tot[ tot[r].left ].size;
        if( k <= lsize ) return search(tot[r].left,k);
        else if( k == lsize + 1) return r;
        else return search(tot[r].right, k - lsize-1);
    }
};


int main()
{
    int d,n,i,tmp;
    rbt T;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&d);
        T.rb_insert(d,i);
        T.print(T.root);
    }

    printf("\n");
    for(i=1;i<=n;i++){
        tmp = T.search(T.root,i);
        printf("value %d : %d\n",tot[tmp].key,tot[tmp].id);
    }

    printf("\n");
    for(i=1;i<=n;i++){
        tmp = T.search(T.root,1);
        T.rb_delete(tmp);
        T.print(T.root);
        printf("\n");
    }
    return 0;
}
