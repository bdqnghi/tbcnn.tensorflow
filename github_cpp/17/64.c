#include<iostream>

using namespace std;


struct node
{
  int value;
  struct node* left;
  struct node* right;
};

int insertNodes(struct node*, int);
int lca(struct node*, int, int);
bool lookup(struct node*, int);
void inOrder(struct node*);
void preOrder(struct node*);
void postOrder(struct node*);


int main(int argc, char **argv)
{
  int option, value;
  struct node* root =  new node;
  root->value = 20;
  root->left = NULL;
  root->right = NULL;
  do {
    cout<<endl<<"1. Insert Nodes"<<endl<<"2. Find lowest common factor"<<endl<<"3. Lookup"<<endl<<"4. Preorder Traversal"<<endl<<"5. Inorder Traversal"<<endl<<"6. Postorder Traversal"<<endl<<"7. Exit"<<endl<<"Enter your option: ";
    cin>>option;
    switch(option) {
    case 1:
      int numberOfNodes;
      cout<<endl<<"Enter the number of nodes to be added:";
      cin>>numberOfNodes;
      if(numberOfNodes == insertNodes(root, numberOfNodes))
	cout<<endl<<"Insertion Successful";
      else
	cout<<endl<<"Insertion unsuccessful";
      break;
    case 2:
      int value1, value2;
      cout<<endl<<"Enter 2 values: ";
      cin>>value1>>value2;
      if(value = lca(root, value1, value2))
	cout<<endl<<"Lowest common factor: "<<value;
      else
	cout<<endl<<"Unsuccessful";
      break;
    case 3:
      cout<<endl<<"Enter the value to be looked: ";
      cin>>value;
      if(lookup(root, value))
	cout<<endl<<"Value Found";
      else
	cout<<endl<<"Value not found";
      break;
    case 4:
      preOrder(root);
      break;
    case 5:
      inOrder(root);
      break;
    case 6:
      postOrder(root);
      break;
    case 7:
      exit(0);
      break;
    default:
      cout<<endl<<"Invalid option";
    }
  }while(true);
  return 0;
}


int insertNodes(struct node* root, int values)
{
  int counter = 0, value;
  struct node *curr_node, *tmp;
  try{
    while(counter != values) {
      struct node* temp = new node;
      temp->left = NULL;
      temp->right = NULL;
      cout<<endl<<"Enter value: ";
      cin>>value;
      temp->value = value;
      tmp = root;
      while(tmp!=NULL) {
	curr_node = tmp;
	if (value <= curr_node->value)
	  tmp = curr_node->left;
	else
	  tmp = curr_node->right;
      }
      if (value <= curr_node->value)
	curr_node->left = temp;
      else
	curr_node->right = temp;
      counter++;
    }
  }
  catch(int e) {
      return 0;
    }
  return counter;
}

bool lookup(struct node* root, int value)
{
  struct node* curr_node = root;
  while(curr_node) {
    if(value<curr_node->value)
      curr_node = curr_node->left;
    else if(value>curr_node->value)
      curr_node = curr_node->right;
    else
      return true;
  }
  return false;
}

int lca(struct node* root, int value1, int value2)
{
  while(root!=NULL) {
    if(root->value < value1 && root->value < value2)
      root = root->left;
    else if (root->value > value1 && root->value > value2)
      root = root->left;
    else
      return root->value;
  }
  return false;
}


void preOrder(struct node* node) {
  if(node==NULL) return;
  cout<<node->value<<" ";
  preOrder(node->left);
  preOrder(node->right);
}

void inOrder(struct node* node) {
  if(node==NULL) return;
  inOrder(node->left);
  cout<<node->value<<" ";
  inOrder(node->right);
}

void postOrder(struct node* node){
  if(node == NULL) return;
  postOrder(node->left);
  postOrder(node->right);
  cout<<node->value<<" ";
}
  

