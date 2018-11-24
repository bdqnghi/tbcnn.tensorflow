#include<iostream>
#include<vector>

using namespace std;
class RBTree{
private:
	
public:
struct node{
	int type; // black 1, red 2, double black 3
	int val;
	bool conflict;
	node* left;
	node* right;
	node(int v): type(2), val(v), conflict(false), left(NULL), right(NULL){};
};

node* dummy;

RBTree()
{
	dummy = new node(0);
}

node* left_part(node* root)
{
	
	if(root->left->right && root->left->right->type == 2)
	{
		//left rotation
		left_part_left_rotation(root);
	}
	return left_part_right_rotation(root);

}

void left_part_left_rotation(node *root)
{

	//left rotation
	node* tmp = root->left->right;
	root->left->right = tmp->left;
	tmp->left = root->left;
	root->left = tmp;
	
}

node* left_part_right_rotation(node* root)
{
	//right rotation
	node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	//exchange color
	swap(root->type, tmp->type);
	return tmp;
	
}
node* right_part(node* root)
{
	if(root->right->left && root->right->left->type == 2)
	{
		//right rotation
		right_part_right_rotation(root);
		
	}
	//left rotation
	return right_part_left_rotation(root);
}

void right_part_right_rotation(node* root)
{
	node* tmp = root->right->left;
	root->right->left = tmp->right;
	tmp->right = root->right;
	root->right = tmp;
}
node* right_part_left_rotation(node* root)
{
	node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	//exchange color
	swap(root->type, tmp->type);
	return tmp;
}
node* insertion(node* root, int i)
{
	if(!root)
		return new node(i);
	else{
		if(root->val == i)
			return root;	
		if(root->val > i)
			root->left = insertion(root->left, i);
		else
			root->right = insertion(root->right, i);
		
		if(root->type == 2 && (root->left && root->left->type == 2 || root->right && root->right->type == 2))
			root->conflict = true;
		if(root->type == 1)
		{
			if(root->left && root->left->conflict)
			{
				root->left->conflict = false;
				if(root->right && root->right->type == 2)
				{
					root->left->type = root->right->type = 1;
					root->type = 2;
				
				}
				else{
					return left_part(root);
				}
			}
			else{
				if(root->right && root->right->conflict)
				{
					root->right->conflict = false;
					if(root->left && root->left->type == 2)
					{
						root->left->type = root->right->type = 1;
						root->type = 2;
						
					}
					else{
						return right_part(root);
					}
				}
			}
		}
		return root;
	}
	
}


node* deletion_find(int i)
{
	node* root = dummy->left;
	while(root)
	{
		if(root->val == i)	
		{
			
			return root;
		}
		else{
			if(root->val > i)
				root = root->left;
			else
				root = root->right;
		}
	}	
	return NULL;
}

node* case2_left(node* root)
{
	
	root = right_part_left_rotation(root);
	node* tmp = root->left;
	if((!tmp->right->left || tmp->right->left->type == 1) && (!tmp->right->right || tmp->right->right->type == 1))
	{
		//case 4
		case4_left(tmp);
	}
	else
	{
		if(!tmp->right->right || tmp->right->right->type == 1)
			root->left = case5_left(tmp);
		else
			root->left = case6_left(tmp);
	}
	return root;
}
node* case2_right(node* root)
{
	
	left_part_right_rotation(root);
	node* tmp = root->right;
	if((!tmp->left->left || tmp->left->left->type == 1) && (!tmp->left->right || tmp->left->right->type == 1))
		case4_right(tmp);
	else{
		if(!tmp->left->left|| tmp->left->left->type == 1)
			root->right = case5_right(tmp);
		else
			root->right = case6_right(tmp);
	}
	return root;
}

node* case3_left(node* root)
{

	root->left->type = 1;
	root->type = 3;
	root->right->type = 2;
	return root;
}

node* case3_right(node* root)
{

	root->right->type = 1;

	root->type = 3;
	root->left->type = 2;

	return root; 
}
node* case4_left(node* root)
{

	root->type = 1;

	root->left->type = 1;	

	root->right->type = 2;

	return root;
}
node* case4_right(node* root)
{
//cout << "4 r"<<endl;
	root->type = 1;
	root->right->type = 1;
	root->left->type = 2;
	return root;
}

node* case5_left(node* root)
{
//cout << "5 l"<<endl;
	root->right = left_part_right_rotation(root->right);
	return case6_left(root);
}
node* case5_right(node* root)
{
//cout << "5 r"<<endl;
	root->left = right_part_left_rotation(root->left);
	return case6_right(root);
}

node* case6_left(node* root)
{
//cout << "6 l"<<endl;	
	root = right_part_left_rotation(root);
	root->right->type = root->left->left->type = 1;
	return root;
}

node* case6_right(node* root)
{
//cout << "6 r"<<endl;
	root = left_part_right_rotation(root);
	root->left->type = root->right->right->type = 1;
	return root;
}
node* deletion_balance(node* root, int i)
{
	if(root->val == i)
	{
		root->type = 3;//double black
		return root;
	}
	else{
		if(root->val > i)
		{
			root->left = deletion_balance(root->left, i);
			if(root->left->type == 3)
			{
				// need balance
				if(root->right->type == 2)
				{
					//case 2
					
					return case2_left(root);
					
				}
				else{
					if(root->right->right && root->right->right->type == 2)
						return case6_left(root);
					else{
						if(root->right->left && root->right->left->type == 2)
							return case5_left(root);
						else{
							if(root->type == 2)
								return case4_left(root);
							else
								return case3_left(root);
						}
					}
				}
			}
		}
		else
		{

			root->right = deletion_balance(root->right, i);
			if(root->right->type == 3)
			{
				if(root->left->type == 2)
					return case2_right(root);
				else{
					if(root->left->left && root->left->left->type == 2)
						return case6_right(root);
					else{
						if(root->left->right && root->left->right->type == 2)
							return case5_right(root);
						else{
							if(root->type == 2)
								return case4_right(root);
							else
								return case3_right(root);
						}
					}
				}
			}
		}
		
		
	}
	return root;
}
void deletion_node(int i)
{
	//cout << "deletion_node" << endl;
	node* father = dummy, * root = dummy->left;
	while(root)
	{
	if(root->val == i)
	{
		node* tmp = root->left ? root->left : root->right;
		if(tmp)
			tmp->type = 1;
		if(father->left == root)
			father->left = tmp;
		else
			father->right = tmp;
		delete root;
		break;
	}
	else{
		father = root;
		root  = root->val > i ? root->left : root->right;		
	}
	}
	return;
}

void deletion(int i)
{
	node* origin = deletion_find(i);
	if(origin)
	{
		node* target = origin;
		if(target->left && target->right)
		{
			target = target->right;
			while(target->left)	
				target = target->left;
		}
		//cout << "deletion: " << target->type <<" " << target->val << endl;
		if(target->type == 1 && !target->left && !target->right)
			dummy->left = deletion_balance(dummy->left, target->val);
		if(dummy->left->type == 3)
			dummy->left->type = 1;//case 1
		int tmp = target->val, tmp2 = origin->val;
		//cout << "hello" << endl;
		deletion_node(tmp);
		if(tmp != tmp2)
			origin->val = tmp;
			
	}
}
void display()
{
	node* cur = dummy->left, *p;
	vector<int> res;
	if(cur)
	{
		while(cur)
		{
			if(!cur->left)
			{
				res.push_back(cur->val);
				cur = cur->right;
			}
			else{
				p = cur->left;
				while(p->right && p->right != cur)
					p = p->right;
				if(!p->right)
				{
					p->right = cur;
					cur = cur->left;
				}
				else{
					res.push_back(cur->val);
					p->right = NULL;
					cur = cur->right;
				}


			}
		}	
		
	}
	for(auto& i: res)
		cout << i << " " ;
}



};

int main()
{
	RBTree *a = new RBTree();
	vector<int> insert_value{1,2,3,4,5,6,7,8,9};
	for(auto& i : insert_value)
	{
		a->dummy->left = a->insertion(a->dummy->left, i);
		a->dummy->left->type = 1;
	}
	vector<int> delete_value{2,6,9,14,1,2};
	for(auto& i : delete_value)
		a->deletion(i);
	a->display();
	return 0;
}

