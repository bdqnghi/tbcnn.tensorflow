/*
A program, to Create, Edit and Update/Modify an AVL-Tree.
-Balancing BST, Normal properties, except, the Left Sub-Tree can have atmost length 1
greater than the Right sub-tree, ad this property follows recursiely, if void, a rotation takes place in 
the sub-tree.

Rotation_Explanations: (http://pages.cs.wisc.edu/~paton/readings/liblitVersion/AVL-Tree-Rotations.pdf)
|
Practice Question number:Q6.
Ankit Vadehra
ankitvad@gmail.com
*/

#include <iostream>
using namespace std;

/*
Tree-Node-Decleration
*/
template <class T>  //...Data-Type
struct AVLNode
{
T data;
AVLNode *left; 
AVLNode *right;
int ht;  //...Height of the Sub-Tree, at any AVLNode.
};

//AVLNode<int> *root;

template <class T>  //...Data-Type
class AVLTree
{
public:
	AVLNode<T> *root;
	AVLTree()
	{
		root=NULL;
	};

	int height(AVLNode<T> *);
	int height_difference(AVLNode<T> *);  //...To calclate the Balancing_Factor

	/*
	The 4 Rotation Coditions:
	1)right_right_rotation
	2)left_left_rotation
	3)left_right_rotation
	4)right_left_rotation
	*/
	AVLNode<T> *right_right_rotation(AVLNode<T> *);
	AVLNode<T> *left_left_rotation(AVLNode<T> *);
	AVLNode<T> *left_right_rotation(AVLNode<T> *);
	AVLNode<T> *right_left_rotation(AVLNode<T> *);
	//AVLNode<T> *balance_tree(AVLNode<T> *);  //...For after deleting a AVLNode.
	AVLNode<T> *insert(AVLNode<T> *, const T &key);
	AVLNode<T> *lookup(AVLNode<T> *, const T &key);  //...Using Inorder Traversal/
	void *inorder(AVLNode<T> *);
	//void remove(const T &key);
	AVLNode<T> *remove(AVLNode<T> *, const T &key);
	
	

};

/*
...Calculating the Height
*/
template <class T>  //...Data-Type
int AVLTree<T>::height(AVLNode<T> *temp)
{
	int left_height,right_height;
	  //...Checking for Null Condition, on existing AVLNode.
	if(temp==0)
		{
			return(0);
		}
		//...For Left Node.
	if(temp->left==NULL)
		{left_height=0;}
	else
		left_height=1+(temp->left->ht);
	  //...For Right AVLNode.
	if(temp->right==NULL)
		{right_height=0;}
	else
		right_height=1+(temp->right->ht);
	  //...Maximum Height is Choosen, as Node Height
	if(left_height>right_height)
		return(left_height);
	else
		return(right_height);
}
template <class T>
int AVLTree<T>::height_difference(AVLNode<T> *temp)
{
	  //...Calculation of the Balancing_Factor ie.(LH-RH)
	int left_height=height(temp->left);
	int right_height=height(temp->right);
	int balancing_factor=left_height - right_height;
	return balancing_factor;
}

  //...Right-Right-Rotation(1)
template <class T>
AVLNode<T> *AVLTree<T>::right_right_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->right;
	parent_AVLNode->right=temp->left;
	temp->left=parent_AVLNode;
	parent_AVLNode->ht=height(parent_AVLNode);
	temp->ht=height(temp);
	return(temp);
}

  //...Left-Left-Rotation(2)
template <class T>
AVLNode<T> *AVLTree<T>::left_left_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->left;
	parent_AVLNode->left=temp->right;
	temp->right=parent_AVLNode;
	parent_AVLNode->ht=height(parent_AVLNode);
	temp->ht=height(temp);
	return(temp);
}

  //...Left-Right-Rotation(3)
template <class T>
AVLNode<T> *AVLTree<T>::left_right_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->left;
	parent_AVLNode->left=right_right_rotation(temp);
	return left_left_rotation(parent_AVLNode);
}

//...Right-Left-Rotation(4)
template <class T>
AVLNode<T> *AVLTree<T>::right_left_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->right;
	parent_AVLNode->right=left_left_rotation(temp);
	return right_right_rotation(parent_AVLNode);
}

/*...Balancing The AVL-Tree, and Inserting the values/\.
Here we take into account the property of an AVL-Tree, to check whether or not 
the left child has atmost 1 more height than right, if this property is void, it is'nt 
an AVL-Tree, and hence a succession of rotations have to be performed, to make it one,
And then the value is inserted.PS: since the height that can be achieved is only +2 or -2,
we use direct checking properties.
*/

template<class T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *temp, const T &key)  //...Same numbers are Omitted and not inserted.
{
	//...Initial-Condition, Creation of AVL-Tree
	if(temp==NULL)
	{
		temp=new AVLNode<T>();
		temp->data=key;
		temp->left=NULL;
		temp->right=NULL;
		root=temp;//Root points to first AVLNode. Important for Remoe function.	
	}
	else
	{
		/*...The Binary_Search_Tree property, 
			left side smaller, right side greater.*/
		if(key>temp->data)  			
		{
			temp->right=insert(temp->right,key);  //..Recursion.
			if(height_difference(temp)==-2)
			{
				if(key>temp->right->data)
					temp=right_right_rotation(temp);
				else
					temp=right_left_rotation(temp);
			}

		}
		else
		if(key<temp->data)
		{
			temp->left=insert(temp->left,key);  //...Recursion.
			if(height_difference(temp)==2)
			{
				if(key<temp->left->data)
					temp=left_left_rotation(temp);
				else
					temp=left_right_rotation(temp);
			}
		}
	}
	temp->ht=height(temp);
	return(temp);
}
template<class T>
void *AVLTree<T>::inorder(AVLNode<T> *root)  //...Using Inorder Traversal/
{
	//Inorder printing:
	AVLNode<T> *temp=root;
	if(temp!=NULL)
	{
		inorder(temp->left);
		cout<<"\n"<<temp->data<<"[ BF= "<<height_difference(temp)<<" ] ";
		inorder(temp->right);
	}
}
template<class T>
AVLNode<T> *AVLTree<T>::lookup(AVLNode<T> *root, const T &key)  //...Using Inorder Traversal/
{
	T x=key;
	int flag=0;//to check condition in the end.(returning value)
	//Inorder printing:
	AVLNode<T> *temp=root;
	if(temp!=NULL)		
	{
		lookup(temp->left,x);
		if(temp->data==x)
			{
				flag=1;
				cout<<"\nThe Number Was Found in The AVL_Tree";
				return(temp);				
			}
		//cout<<"\n"<<temp->data<<"[ BF= "<<height_difference(temp)<<" ] ";
		lookup(temp->right,x);
	}
	if(!flag)  //...Checks for the 0 condition of the Flag-Variable.
	{
		return(0);
	}
}

template<class T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *temp , const T &key)
{
	AVLNode<T> *p;
	if(temp==NULL)
		{return 0;}
	else
		if(key>temp->data)
			{
				temp->right=remove(temp->right,key);
				if(height_difference(temp)==2)
				{
					if(height_difference(temp->left)>=0)
						temp=left_left_rotation(temp);
					else
						temp=left_right_rotation(temp);
				}

			}
			else
				if(key<temp->data)
				{
					temp->left=remove(temp->left,key);
					if (height_difference(temp)==-2)	
					{
							if(height_difference(temp->right)<=0)
							temp=right_right_rotation(temp);
							else
								temp=right_left_rotation(temp);
					}
				}
				else
				{
					if(temp->right!=NULL)
					{
						p=temp->right;
						while(p->left!=NULL)
							{p=p->left;}
						temp->data=p->data;	
						temp->right=remove(temp->right,p->data);
						if(height_difference(temp)==2)
						{
							if(height_difference(temp->left)>=0)
								temp=left_left_rotation(temp);
								else
								temp=left_right_rotation(temp);

						}
					}
						else
						return(temp->left);

				}
				temp->ht=height(temp);
				return(temp);

}




int main()
{

	AVLTree<int> avl;
	int item;
	int choice;
	char ch='y';
	AVLNode<int> *root=NULL;
	AVLNode<int> *temp=NULL;

	do
	{

		cout<<"\nPlease Enter The umber corresponding to the Choice:";
		cout<<"\n1)Insert Element in the AVL_Tree.\t2)Display the Tree(inorder)\n3)Search for an element.\t4)Delete an Element";
		cin>>choice;

		switch(choice)
		{
			case 1: cout<<"\nPlease Insert The Number to Enter:";
					cin>>item;
					root=avl.insert(root,item);
					break;
			case 2: cout<<"\nThe Inorder Display of the tree is:";
					avl.inorder(root);
					break;
			case 3:cout<<"\n Please Enter the Element to search:";
			       cin>>item;
			       temp=avl.lookup(root,item);//To Print The Node Value.
			       if(temp)
			       {
			       	cout<<"\n"<<temp->data;
			       }

			       break;
			case 4: cout<<"\nEnter the number to delete:";
					cin>>item;
					avl.remove(root,item);
					//avl.balance_tree(root);
					cout<<"\nThe AVL Tree after deletion is:\n";
					avl.inorder(root);
					break;
			default: cout<<"\n Please enter the correct number.";
		}

		cout<<"\nDo You wish to cotinue: (y/n)";
		cin>>ch;
	}while(ch=='Y'||ch=='y');

	/*
	for(int i=0; i<6; i++)
	{
		cout<<"\n Please enter the item:";
		cin>>item;
		root=avl.insert(root,item);
	}
	int a=2;
	avl.inorder(root);



	cout<<"\n\n";
	cout<<"\nPlease Enter the number to show, stuff";
	int x;
	cin>>x;
	avl.remove(a);
	cout<<"\n\n";
	avl.inorder(root);
*/

	return 0;
}

