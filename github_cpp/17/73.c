#include<bits/stdc++.h>
using namespace std;
typedef struct tree
{
	int val;
	tree *left;
	tree *right;
}tree;
typedef struct tree1
{
	int val;
	tree1 *left;
	tree1 *right;
	bool right_thread;
}tree1;
tree * newnode(int data)
{
	tree *node;
	node=(tree *)malloc(sizeof(tree));
	node->val=data;
	node->left=NULL;
	node->right=NULL;
	return(node);
}
void inorder(tree *node)
{
	if(node==NULL)
		return;
	inorder(node->left);
	cout << node->val;
	inorder(node->right);
}
void postorder(tree *node)
{
	if(node==NULL)
		return;
	postorder(node->left);
	postorder(node->right);
	cout << node->val;
}
void preorder(tree *node)
{
	if(node==NULL)
		return;
	cout << node->val;
	preorder(node->left);
	preorder(node->right);
}
int size(tree *node)
{
	if(node==NULL)
		return 0;
	else
		return(size(node->left) + 1 + size(node->right));
}
int check_identical(tree *node1, tree *node2)
{
	if(node1==NULL && node2==NULL)
		return 1;
	if(node1!=NULL && node2!=NULL)
	{
		return(
				(node1->val==node2->val) &&
				(check_identical(node1->left, node2->left)) &&
				(check_identical(node1->right, node2->right)));
	}
	return 0; 
}
int max_depth(tree *node)
{
	int ldepth, rdepth;
	if(node==NULL)
		return 0;
	else
	{
		ldepth=max_depth(node->left);
		rdepth=max_depth(node->right);
		if(ldepth>rdepth)
			return(ldepth+1);
		else 
			return(rdepth+1);
	}
}
void delete_tree(tree *node)
{
	if(node==NULL)
		return;
	else
	{
		delete_tree(node->left);
		delete_tree(node->right);
		cout << "THE DELETED NODE IS : " << node->val << "\n";
		free(node);
	}
}
void mirror(tree *node)
{
	tree *temp;
	if(node==NULL)
		return;
	else
	{
		mirror(node->left);
		mirror(node->right);

		temp=node->left;
		node->left=node->right;
		node->right=temp;
		return;
	}
}
void print_array(int path[], int pathlen)
{
	int i;
	for(i=0;i<pathlen;i++)
		cout << path[i] << " ";
	cout << endl;
}
void print_path(tree *node, int path[], int pathlen)
{
	if(node==NULL)
		return;
	path[pathlen]=node->val;
	pathlen++;
	if(node->left==NULL && node->right==NULL)
		print_array(path,pathlen);
	else
	{
		print_path(node->left,path,pathlen);
		print_path(node->right,path,pathlen);
	}
}
int leaf_count(tree *node)
{
	if(node==NULL)
		return 0;
	if(node->left==NULL && node->right==NULL)
		return 1;
	else
		return(
				leaf_count(node->left)+leaf_count(node->right));
}
int children_sum(tree *node)
{
	int l,r;
	l=0;
	r=0;
	if(node==NULL || (node->left==NULL && node->right==NULL))
		return 1;
	if(node->left!=NULL)
		l=node->left->val;
	if(node->right!=NULL)
		r=node->right->val;
	if((node->val==l+r) && children_sum(node->left) && children_sum(node->right))
		return 1;
	else
		return 0;
}
int check_sub_tree(tree *node,tree *node3)
{
	if(node3==NULL)
		return 1;
	if(node==NULL)
		return 0;
	if(check_identical(node,node3))
		return 1;
	else
		return(
		check_sub_tree(node->left,node3)||
		check_sub_tree(node->right,node3));
	return 0;
}
int sum(tree *root)
{
	if(root==NULL)
		return 0;
	return(sum(root->left) + root->val + sum(root->right));
}
int is_sum_tree_m1(tree *node)
{
	int ls,rs;
	ls=0;
	rs=0;
	if(node==NULL || (node->left==NULL && node->right==NULL))
		return 1;
	ls=sum(node->left);
	rs=sum(node->right);
	if(node->val==ls+rs && is_sum_tree_m1(node->left) && is_sum_tree_m1(node->right))
		return 1;
	return 0;
}
int is_leaf(tree *node)
{
	if(node==NULL)
		return 0;
	if(node->left==NULL && node->right==NULL)
		return 1;
	return 0;
}
int is_sum_tree_m2(tree *node)
{
	int ls,rs;
	ls=0;
	rs=0;
	if(node==NULL || is_leaf(node))
		return 1;
	if(is_sum_tree_m2(node->left) && is_sum_tree_m2(node->right))
	{
		if(node->left==NULL)
			ls=0;
		else if(is_leaf(node->left))
			ls=node->left->val;
		else
			ls=2*node->left->val;
		if(node->right==NULL)
			rs=0;
		else if(is_leaf(node->right))
			rs=node->right->val;
		else
			rs=2*node->right->val;
		return(node->val==ls+rs);
	}
}
tree1 * new_node(int data, bool fl)
{
	tree1 *node;
	node=(tree1 *)malloc(sizeof(tree1));
	node->left=NULL;
	node->right=NULL;
	node->val=data;
	node->right_thread=fl;
	return node;
}
tree1 * leftmost(tree1 *node)
{
	if(node==NULL)
		return NULL;
	while(node->left!=NULL)
		node=node->left;
	return node;
}
void threaded_inorder_traversal(tree1 *node)
{
	tree1 *curr;
	curr=node;
	curr=leftmost(curr);
	while(curr!=NULL)
	{
		cout << curr->val << " ";
		if(curr->right_thread)
			curr=curr->right;
		else
			curr=leftmost(curr->right);
	}
	cout << endl;
}
bool find_sum_of_path(tree *node, int sum, int w)
{
	if(node==NULL)
		return 0;
	sum=sum+node->val;
	if(node->left==NULL && node->right==NULL)
	{
		if(sum==w)
			return 1;
		else
			sum=sum-node->val;
		sum=0;
	}
	return(find_sum_of_path(node->left,sum,w) || find_sum_of_path(node->right,sum,w));
}
void nodes_at_k_distance(tree *node,int k,int w)
{
	k++;
	if(node==NULL)
		return;
	if(w==k)
	{
		cout << node->val << " ";
		return;
	}
	nodes_at_k_distance(node->left,k,w);
	nodes_at_k_distance(node->right,k,w);
	return;
}
int print_ancestor(tree *node, int w)
{
	int fl=0;
	if(node==NULL)
		return 0;
	if(node->val==w)
	{
		return 1;
	}
	fl=print_ancestor(node->left,w);
	if(fl==1)
	{
		cout << node->val << " ";
		return 1;
	}
	fl=print_ancestor(node->right,w);
	if(fl==1)
	{
		cout << node->val << " ";
		return 1;
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	int i,w,pathlen,path[100];
	pathlen=0;
	tree *root, *root1, *root2, *root3, *root4;
	tree1 *root5;
	bool ans;
	cout << "PRESS 1 TO ENTER A NODE IN B-TREE\n";
	cout << "PRESS 2 TO PRINT B-TREE IN INORDER\n";
	cout << "PRESS 3 TO PRINT B-TREE IN POSTORDER\n";
	cout << "PRESS 4 TO PRINT B-TREE IN PREORDER\n";
	cout << "PRESS 5 TO CALCULATE THE SIZE OF THE TREE\n";
	cout << "PRESS 6 TO COMPARE TWO B-TRESS\n";
	cout << "PRESS 7 TO FIND THE DEPTH OF THE B-TREE\n";
	cout << "PRESS 8 TO DELETE THE TREE\n";
	cout << "PRESS 9 TO GENERATE THE MIRROR OF THE B-TREE\n";
	cout << "PRESS 10 TO PRINT EACH THE PATH OF A B-TREE IN A NEW LINE\n";
	cout << "PRESS 11 TO FIND THE NUMBER OF LEAF IN A B-TREE\n";
	cout << "PRESS 12 TO CHECK WHETHER SUM OF A CHILDREN IS EQUAL TO THE PARENT NODE IN A B-TREE\n";
	cout << "PRESS 13 TO CHECK WHETHER A B-TREE IS A SUB OF ANOTHER B-TREE\n";
	cout << "PRESS 14 TO CHECK WHETHER A B-TREE IS A SUM TREE USING TIME COMPLEXITY OF O(n^2)\n";
	cout << "PRESS 15 TO CHECK WHETHER A B-TREE IS A SUM TREE USING TIME COMPLEXITY OF O(n)\n";
	cout << "PRESS 16 TO FIND THREADED INORDER TRAVERSAL IN A B-TREE\n";
	cout << "PRESS 17 TO CHECK WHETHER A NUMBER HAS SUM EQUAL TO TREE'S PATH OR NOT\n";
	cout << "PRESS 18 TO PRINT ALL THE NODES THAT ARE AT 'K' DISTANCE FROMM ROOT IN A BINARY TREE\n";
	cout << "PRESS 19 TO PRINT ANCESTOR OF A NODE IN A B-TREE\n";
	while(true)
	{
		cin >> i;
		if(i==1)
		{
			root=newnode(1);
			root->left=newnode(2);
			root->right=newnode(3);
			root->left->left=newnode(4);
			root->left->right=newnode(5);
		}
		else if(i==2)
		{
			inorder(root);
			cout << endl;
		}
		else if(i==3)
		{
			postorder(root);
			cout << endl;
		}
		else if(i==4)
		{
			preorder(root);
			cout << endl;
		}
		else if(i==5)
		{
			w=size(root);
			cout << "THE SIZE OF THE BINARY TREE IS : "<< w << endl;
		}
		else if(i==6)
		{
			root1=newnode(1);
			root1->left=newnode(2);
			root1->right=newnode(3);
			root1->left->left=newnode(4);
			root1->left->right=newnode(5);

			root2=newnode(1);
			root2->left=newnode(2);
			root2->right=newnode(3);
			root2->left->left=newnode(4);
			root2->left->right=newnode(5);

			w=check_identical(root1,root2);
			if(w==1)
				cout << "B-TRESS ARE INDENTICAL\n";
			else
				cout << "B-TREE ARE NOT IDENTICAL\n";
		}
		else if(i==7)
		{
			w=max_depth(root);
			cout << "THE DEPTH OF THE B-TREE IS : " << w << endl;
		}
		else if(i==8)
		{
			delete_tree(root1);
		}
		else if(i==9)
		{
			cout << "THE INORDER TRAVERSAL BEFORE TAKING THE MIRROR IMAGE is : ";
			inorder(root2);
			cout << endl;
			mirror(root2);
			cout << "THE INORDER TRAVERSAL AFTER MIRROR IMAGE IS : ";
			inorder(root2);
			cout << endl;
		}
		else if(i==10)
		{
			print_path(root,path,pathlen);
		}
		else if(i==11)
		{
			w=leaf_count(root);
			cout << "NUMBER OF LEAVES IN A B-TREE IS : " << w << endl;
		}
		else if(i==12)
		{
			root1=newnode(10);
			root1->left=newnode(8);
			root1->right=newnode(2);
			root1->left->right=newnode(5);
			root1->left->left=newnode(3);
			w=children_sum(root1);
			if(w==1)
				cout << "THE B-TREE FOLLOWS THE PROPERTY THAT SUM OF A NODE IS EQUAL TO ITS CHILDREN\n";
			else
				cout << "THE B-TREE DOESN'T FOLLOWS THE PROPERTY THAT SUM OF A NODE IS EQUAL TO ITS CHILDREN\n";
		}
		else if(i==13)
		{
			root3=newnode(2);
			root3->left=newnode(4);
			root3->right=newnode(5);
			w=check_sub_tree(root, root3);
			if(w==1)
				cout << "THE B-TREE IS A SUB TREE OF ANOTHER TREE\n";
			else
				cout << "THE B-TREE IS NOT A SUB TREE OF ANOTHER TREE\n";
		}
		else if(i==14)
		{
			root4=newnode(26);
			root4->left=newnode(10);
			root4->right=newnode(3);
			root4->left->right=newnode(6);
			root4->left->left=newnode(4);
			root4->right->right=newnode(3);
			w=is_sum_tree_m1(root4);
			if(w==1)
				cout << "THE B-TREE IS A SUM TREE\n";
			else
				cout << "THE B-TREE IS NOT A SUM TREE\n";
		}
		else if(i==15)
		{
			root4=newnode(26);
			root4->left=newnode(10);
			root4->right=newnode(3);
			root4->left->right=newnode(6);
			root4->left->left=newnode(4);
			root4->right->right=newnode(3);
			w=is_sum_tree_m2(root4);
			if(w==1)
				cout << "THE B-TREE IS A SUM TREE\n";
			else
				cout << "THE B-TREE IS NOT A SUM TREE\n";
		}
		else if(i==16)
		{
			root5=new_node(6,0);
			root5->right=new_node(8,0);
			root5->left=new_node(3,0);
			root5->left->left=new_node(1,1);
			root5->left->right=new_node(5,1);
			root5->right->left=new_node(7,1);
			root5->right->right=new_node(11,0);
			root5->right->right->left=new_node(9,1);
			root5->right->right->right=new_node(13,0);
			threaded_inorder_traversal(root5);
		}
		else if(i==17)
		{
			cout << "ENTER THE NUMBER TO CHECK WHETHER ITS EQUAL TO PATH OF B-TREE\n";
			cin >> w;
			ans=find_sum_of_path(root,0,w);
			if(ans==1)
				cout << "THE NUMBER IS EQUAL TO PATH OF B-TREE\n";
			else
				cout << "THE NUMBER IS NOT EQUAL TO PATH OF B-TREE\n";
		}
		else if(i==18)
		{
			cout << "ENTER THE VALUE OF THE DISTANCE\n";
			cin >> w;
			nodes_at_k_distance(root,-1,w);	
			cout << endl;
		}
		else if(i==19)
		{
			cout << "ENTER THE NODE WHOSE ANCESTOR YOU WOULD LIKE TO PRINT\n";
			cin >> w;
			pathlen=print_ancestor(root,w);
			cout << endl;
			pathlen=0;
		}
	}
	return 0;
}




