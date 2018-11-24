#include<bits/stdc++.h>
using namespace std;

struct Node{

   int data;
   struct Node *left;
   struct Node *right;
   int height;
};

int height(struct Node* node ){
  if(Node == NULL)
     return 0;
  return 1 + max(height(Node->left),height(Node->right)); 

}

bool isBalanced(struct Node *root){
    int lh;
    int rh;

if(root == NULL)
   return 1;

    lh = height(root->left);
    rh = height(root->right);
    
    if(abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
         return 1; 
        																					
return 0;
}

int _B_(Node *root){
   if(root == NULL)
      return 0;
   int lH = _B_(root->left);
   if(lH == -1)
     return -1;
   int rH = _B_(root->right);
    if(rH == -1)
        return -1;
    if(abs(lH - rH) >1)
        return -1;
    return max(lH,rH)+1;
}

bool _B(Node *root){
   if(_)
}


