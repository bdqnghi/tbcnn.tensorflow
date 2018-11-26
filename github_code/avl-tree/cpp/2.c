#include <iostream>
using namespace std;

struct node{
    int key,h;
    struct node *left,*right;
}typedef Node;


int getHeight(Node *root){
    if(root!=NULL)
        return root->h;
    return 0; 
}
int calcHeight(Node *root){
    return getHeight(root->left) > getHeight(root->right) ? getHeight(root->left)+1 : getHeight(root->right)+1;
}
Node * insertAvl(Node *root,int key){
    if(root==NULL){
        root = new Node;
        root->key=key;
        root->h=1;
        root->left=root->right=NULL;
        return root;//end here if is a leaf
    }else if(key<root->key){
        root->left = insertAvl(root->left,key);
        root->h = calcHeight(root);
        
        
    }else if(key>root->key){
        root->right = insertAvl(root->right,key);
        root->h = calcHeight(root);
    }
    int bal = getHeight(root->right)-getHeight(root->left);
     if(bal==2 || bal==-2){
         cout << "number "<<root->key<<" is unbalanced\n";
         //rotations here
         if(key<root->key){
             //left cases
            if(key<root->left->key){
                //left left case
                Node *l = root->left;
                Node *lr = l->right;
                root->left = lr;
                l->right = root;
                //update heights root and l
                root->h = calcHeight(root);
                l->h = calcHeight(l);
                
                return l;


            }else{
                //left right case
                Node *b = root->left;
                Node *c= b->right;
                Node *e = c->left;
                Node *d = c->right;
                c->right=root;
                c->left=b;
                b->right=e;
                root->left=d;
                b->h = calcHeight(b);
                c->h = calcHeight(c);
                root->h = calcHeight(root);
                return c;


            }

         }else{
            //right cases  
            if(key>root->right->key){
                //right right case
                Node *r = root->right;
                Node *rl = r->left;
                root->right = rl;
                r->left = root;
                //update heights root and r
                root->h = calcHeight(root);
                r->h=calcHeight(r);
                
                return r;

            }else{
                //right left case
                Node *b = root->right;
                Node *c= b->left;
                Node *d = c->right;
                Node *e = c->left;
                c->left=root;
                c->right=b;
                b->left=d;
                root->right=e;
                b->h = calcHeight(b);
                c->h = calcHeight(c);
                root->h = calcHeight(root);
                return c;


            }           
         }
        
     }
     
     
        return root;

}

void inorder(Node *root) {
	if(root != NULL) {
        int bal = getHeight(root->right)-getHeight(root->left);
		cout << root->key <<" b"<<bal<< endl;
		inorder(root->left);
		inorder(root->right);
	}
}

int main(){
    int key;
    Node *tree=NULL;
    while(cin >> key){
        tree=insertAvl(tree,key);
	
    }
    cout<<endl<<"tree in preorder (each node with respective balance):\n\n";
    inorder(tree);

    return 0;
}
