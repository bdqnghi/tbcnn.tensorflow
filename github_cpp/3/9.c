

#include <iostream>
using namespace std;


template <class T>  
struct AVLNode
{
T data;
AVLNode *left; 
AVLNode *right;
int ht;  
};



template <class T>  
class AVLTree
{
public:
	AVLNode<T> *root;
	AVLTree()
	{
		root=NULL;
	};

	int height(AVLNode<T> *);
	int height_difference(AVLNode<T> *);  

	
	AVLNode<T> *right_right_rotation(AVLNode<T> *);
	AVLNode<T> *left_left_rotation(AVLNode<T> *);
	AVLNode<T> *left_right_rotation(AVLNode<T> *);
	AVLNode<T> *right_left_rotation(AVLNode<T> *);
	
	AVLNode<T> *insert(AVLNode<T> *, const T &key);
	AVLNode<T> *lookup(AVLNode<T> *, const T &key);  
	void *inorder(AVLNode<T> *);
	
	AVLNode<T> *remove(AVLNode<T> *, const T &key);
	
	

};


template <class T>  
int AVLTree<T>::height(AVLNode<T> *temp)
{
	int left_height,right_height;
	  
	if(temp==0)
		{
			return(0);
		}
		
	if(temp->left==NULL)
		{left_height=0;}
	else
		left_height=1+(temp->left->ht);
	  
	if(temp->right==NULL)
		{right_height=0;}
	else
		right_height=1+(temp->right->ht);
	  
	if(left_height>right_height)
		return(left_height);
	else
		return(right_height);
}
template <class T>
int AVLTree<T>::height_difference(AVLNode<T> *temp)
{
	  
	int left_height=height(temp->left);
	int right_height=height(temp->right);
	int balancing_factor=left_height - right_height;
	return balancing_factor;
}

  
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

  
template <class T>
AVLNode<T> *AVLTree<T>::left_right_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->left;
	parent_AVLNode->left=right_right_rotation(temp);
	return left_left_rotation(parent_AVLNode);
}


template <class T>
AVLNode<T> *AVLTree<T>::right_left_rotation(AVLNode<T> *parent_AVLNode)
{
	AVLNode<T> *temp;
	temp=parent_AVLNode->right;
	parent_AVLNode->right=left_left_rotation(temp);
	return right_right_rotation(parent_AVLNode);
}



template<class T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *temp, const T &key)  
{
	
	if(temp==NULL)
	{
		temp=new AVLNode<T>();
		temp->data=key;
		temp->left=NULL;
		temp->right=NULL;
		root=temp;
	}
	else
	{
		
		if(key>temp->data)  			
		{
			temp->right=insert(temp->right,key);  
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
			temp->left=insert(temp->left,key);  
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
void *AVLTree<T>::inorder(AVLNode<T> *root)  
{
	
	AVLNode<T> *temp=root;
	if(temp!=NULL)
	{
		inorder(temp->left);
		cout<<"\n"<<temp->data<<"[ BF= "<<height_difference(temp)<<" ] ";
		inorder(temp->right);
	}
}
template<class T>
AVLNode<T> *AVLTree<T>::lookup(AVLNode<T> *root, const T &key)  
{
	T x=key;
	int flag=0;
	
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
		
		lookup(temp->right,x);
	}
	if(!flag)  
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
			       temp=avl.lookup(root,item);
			       if(temp)
			       {
			       	cout<<"\n"<<temp->data;
			       }

			       break;
			case 4: cout<<"\nEnter the number to delete:";
					cin>>item;
					avl.remove(root,item);
					
					cout<<"\nThe AVL Tree after deletion is:\n";
					avl.inorder(root);
					break;
			default: cout<<"\n Please enter the correct number.";
		}

		cout<<"\nDo You wish to cotinue: (y/n)";
		cin>>ch;
	}while(ch=='Y'||ch=='y');

	

	return 0;
}

