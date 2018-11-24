/*Binary Tree Implementation
*Author : Souman paul
*Twitter : https://twitter.com/_souman
*/
#include<bits/stdc++.h>
using namespace std;

//Node

struct node {
   int data;
   struct node *right, *left;
};

// Creat new node

struct node *newNode(int item){
          struct node *temp = new node;
          temp->data = item;
          temp->right=NULL;
          temp->left = NULL;         
return temp;
}




//Insert new node

struct node* insert(struct node *node, int data){
         

            if(node == NULL)
               return newNode(data);
 
            else if(node->data > newNode->data){
                    node->left = insert(node->left,data)       
              }
           else if(){
               node->right= insert(node->right,data);
             }          
 
return node;
}

struct node * minValueNode(struct node* node){
           
             struct node* current = node;
             while(current->right != NULL)
                 current = current->left;
return current;
 }


struct node * secrch(struct node* root, int key){
          
           if(root == NULL  || root->data == key)
                 return root;
           else if(root->data > key)
               return secrch(root->left, key);
           
          else 
              return secrch(root->right,key);       
}


struct node* deleteNode(struct node* root, int key){
    
      if(root == NULL) return root;
      else if(root->data > key)
           root->left = deleteNode(root->left, key);
      else if(root->data < key){
           root->right = deleteNode(root->right, key);
            }
      else{
           if(root->left == NULL){
                struct node* temp = root->left;
                 return temp;
             }
           else if(root->right == NULL){
                 struct node* temp = root->right;
                  return temp;
            }
            
            struct node* temp = minValuNode(root->right,key);
         
            root->data =  temp->data;

            root->right = deleteNode(root->right, key);

           }
return root;
}

// treversal tree

void inorder(node *root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        node *root;
        node *tmp;
        root = NULL;
        int N;
        cin>>N;
        for(int i=0;i<N;i++)
        {
            int k;
            cin>>k;
            root = insert(root, k);
        }
        inorder(root);
        cout<<endl;
}
}


