#pragma once
#include <iostream>
#include <vector>
using namespace std;

/*template <class X>
struct cell
{
	X info;
	int ID;
    cell* left;
    cell* right;
	char balance;
};*/

template <class X>
class Tree
{
private:
    struct cell
    {
        X info;
        int ID;
        cell* left;
        cell* right;
        char balance;
    };

    //cell* T;
    cell* T;
    char bal;


	//Fun��es estruturadas
    void _Ins(cell**,X,int,char*);
    void RotationLeft(cell**);
    void RotationRight(cell**);
    void _OnPoint(cell*);
    void _OnOrder(cell*,vector<int> *);
    int _find(cell*, X);
public:
    Tree(void){T = NULL;}
	~Tree(void);
	void OnPoint();
	void Ins(X,int);
	void OnOrder(vector<int> *);
    int find(X);
};
template <class X>
void Tree<X>::OnOrder(vector<int> *ID)
{
    _OnOrder(T,ID);
}

template <class X>
int Tree<X>::find(X elem)
{
    return this->_find(T, elem);
}

template <class X>
void Tree<X>::_OnOrder(cell* _Tree,vector<int> *_ID)
{
	if(_Tree != NULL)
	{
		_OnOrder(_Tree->left,_ID);
		_ID->push_back(_Tree->ID);
		_OnOrder(_Tree->right,_ID);
    }
}

//quero o id
template <class X>
int Tree<X>::_find(cell* _Tree, X elem)
{
    if(_Tree == NULL)
        return -1; //caso o t for nulo retorna codigo -1
    else
        if(elem == _Tree->info)
            return _Tree->ID; //encontrou retorna o id
        else
            if (elem < _Tree->info)
                return _find(_Tree->left, elem);
            else
                return _find(_Tree->right, elem);
}

template <class X>
void Tree<X>::_OnPoint(cell* _Tree)
{
	if(_Tree != NULL)
	{
		cout <<	_Tree->info << " ";
		_OnPoint(_Tree->left);
		_OnPoint(_Tree->right);
	}
	else cout << ".";
}

template <class X>
void Tree<X>::_Ins(cell** _Tree,X _X,int _ID,char *H)
{
	if((*_Tree) == (NULL))
		 {
            (*_Tree) = new cell;
			(*_Tree)->left = (*_Tree)->right = NULL;
			(*_Tree)->info = _X;
			(*_Tree)->ID = _ID;
			(*_Tree)->balance = 0;
			*H = 1;
		 }
	else if(_X <= (*_Tree)->info)
		 {
			_Ins(&((*_Tree)->left),_X,_ID,H);
			if(*H)
			{
				switch((*_Tree)->balance)
				{
				case 0: (*_Tree)->balance = -1; break;
				case 1: (*_Tree)->balance = 0; *H = 0; break;
				case -1: RotationRight(_Tree); *H = 0; break;
				}
			}
		 }
	 	 else 
		 {
			 _Ins(&((*_Tree)->right),_X,_ID,H);
			if(*H)
			{
				switch((*_Tree)->balance)
				{
				case 0: (*_Tree)->balance = 1; break;
				case -1: (*_Tree)->balance = 0; *H = 0; break;
				case 1: RotationLeft(_Tree); *H = 0; break;
				}
			}
		 }
}

template <class X>
void Tree<X>::RotationLeft(cell** _Tree)
{
    cell* pointB = (*_Tree)->right;
	if(pointB->balance == 1)
		{
			(*_Tree)->right = pointB->left;
			pointB->left = (*_Tree);
			pointB->balance = 0;
			(*_Tree)->balance = 0;
			(*_Tree) = pointB;
		}
	else
		{
            cell* pointC = pointB->left;
			pointB->left = pointC->right;
			pointC->right = pointB;
			(*_Tree)->right = pointC->left;
			pointC->left = (*_Tree);
			if(pointC->balance == 1)
			{
				pointB->balance = 0;
				(*_Tree)->balance = -1;
			}
			else
			{
				pointB->balance = 1;
				(*_Tree)->balance = 0;	
			}
			(*_Tree) = pointC;
			(*_Tree)->balance = 0;
		}
}

template <class X>
void Tree<X>::RotationRight(cell** _Tree)
{
    cell* pointB = (*_Tree)->left;
	if(pointB->balance == -1)
		{
			(*_Tree)->left = pointB->right;
			pointB->right = (*_Tree);
			pointB->balance = 0;
			(*_Tree)->balance = 0;
			(*_Tree) = pointB;
		}
	else
		{
            cell* pointC = pointB->right;
			pointB->right = pointC->left;
			pointC->left = pointB;
			(*_Tree)->left = pointC->right;
			pointC->right = (*_Tree);
			if(pointC->balance == -1)
			{
				pointB->balance = 0;
				(*_Tree)->balance = 1;
			}
			else
			{
				pointB->balance = -1;
				(*_Tree)->balance = 0;	
			}
			(*_Tree) = pointC;
			(*_Tree)->balance = 0;
		}
}

template <class X>
void Tree<X>::OnPoint()
{
	this->_OnPoint(T);
}

template <class X>
void Tree<X>::Ins(X _X,int _ID)
{
	this->_Ins(&T,_X,_ID,&bal);
}
