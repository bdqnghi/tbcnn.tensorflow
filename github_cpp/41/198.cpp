#include <iostream>
using namespace std;

enum C
{
	RED,BLACK
};

typedef struct RBNode
{
	int val;
	C color;
	struct RBNode *parent;
	struct RBNode *left;
	struct RBNode *right;
}RBN;

class RBTree
{
	private:
		RBN *root;
		RBN *Nil;
	public:
		RBTree()
		{
			Nil=new RBN;
			Nil->color=BLACK;
			Nil->left=NULL;
			Nil->right=NULL;
			Nil->parent=root;
			root=Nil;
		}
		void Lrotation(RBN *ptr)				//Takes grandparent of the node as parmeter,not the node currently working on. (CALLED FROM INSERTFIX FUNCTION)
		{
			RBN *aptr;
			aptr=ptr->right;
			ptr->right=aptr->left;
			aptr->left=ptr;
			if(ptr->right!=Nil)
				ptr->right->parent=ptr;
			if(ptr->parent==Nil)
				root=aptr;
			else if(ptr==ptr->parent->left)
				ptr->parent->left=aptr;
			else
				ptr->parent->right=aptr;
			aptr->parent=ptr->parent;
		}
		void Rrotation(RBN *ptr)
		{
			RBN *aptr;
			aptr=ptr->left;
			ptr->left=aptr->right;
			aptr->right=ptr;
			if(ptr->left!=Nil)
				ptr->left->parent=ptr;
			if(ptr->parent==Nil)
				root=aptr;
			else if(ptr==ptr->parent->left)
				ptr->parent->left=aptr;
			else
				ptr->parent->right=aptr;
			aptr->parent=ptr->parent;
		}
		void InsertFix(RBN *ptr)				//Takes the node currently inserting as a parameter.
		{
			RBN *aptr;
			while(ptr->parent->color==RED)
			{
				if(ptr->parent==ptr->parent->parent->left)
				{
					aptr=ptr->parent->parent->right;
					if(aptr->color==RED)
					{
						aptr->color=BLACK;
						ptr->parent->color=BLACK;
						ptr->parent->parent->color=RED;
					}
					else if(ptr==ptr->parent->right)
					{
						Lrotation(ptr->parent);
					}
					ptr->parent->color=BLACK;
					ptr->parent->parent->color=RED;
					Rrotation(ptr->parent->parent);
					ptr=ptr->parent->parent;
				}
				else
				{
					aptr=ptr->parent->parent->left;
					if(aptr->color==RED)
					{
						aptr->color=BLACK;
						ptr->parent->color=BLACK;
						ptr->parent->parent->color=RED;
					}
					else if(ptr==ptr->parent->left)
					{
						Rrotation(ptr->parent);
					}
					ptr->parent->color=BLACK;
					ptr->parent->parent->color=RED;
					Lrotation(ptr->parent->parent);
					ptr=ptr->parent->parent;
				}
				root->color=BLACK;
			}
		}
		void Insert(RBN *node)
		{
			RBN *y,*x;
			x=root;
			y=Nil;
			while(x!=Nil)
			{
				y=x;
				if(node->val < x->val)
					x=x->left;
				else
					x=x->right;
			}
			node->parent=y;
			node->left=Nil;
			node->right=Nil;
			if(y==Nil)
				root=node;
			else if(node->val < y->val)
				y->left=node;
			else y->right=node;
			
			InsertFix(node);
		}
		void Display(RBN *ptr)
		{
			if(ptr!=Nil)
			{
				cout<<"  {";
				if(ptr->color==BLACK)
					cout<<"BLACK ,";
				else
					cout<<"RED ,";
				cout<<ptr->val;
				cout<<"}";
				Display(ptr->left);
				Display(ptr->right);
			}
		}
		void Menu()
		{
			int choice,n;
			do
			{
				cout<<"\n******** MAIN MENU ***********\n";
				cout<<"\n1.Enter element ";
				cout<<"\n2.Dispay elements ";
				cout<<"\n3.Exit ";
				cout<<"\n  Enter your choice ";
				cin>>choice;
				switch(choice)
				{
					case 1: cout<<"\n  Enter the element to be inserted : ";
							cin>>n;
							RBN *node;
							node=new RBN;
							node->val=n;
							node->color==RED;
							Insert(node);
							break;
					case 2: cout<<"\n  Displaying elements : ";
							RBN *ptr;
							ptr=root;
							Display(ptr);
							break;
					case 3: cout<<"\n  Exiting ... ";
							break;
					case 4: cout<<"\n  Wrong choice, try again ";
							break;
				}
			}
			while(choice!=3);
		}
};

int main()
{
	RBTree R;
	R.Menu();
	return 0;
}
