#pragma once

template<class K, class V>
struct AVLTreeNode
{
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;
    K _key;
    V _value;

    int _bf;        // ƽ������

    AVLTreeNode(const K& key, const V& value)
        :_key(key)
        ,_value(value)
        ,_left(NULL)
        ,_right(NULL)
        ,_parent(NULL)
        ,_bf(0)
    {
    }
};

template<class K, class V>
class AVLTree
{
    typedef AVLTreeNode<K, V> Node;
public:
    AVLTree()
        :_root(NULL)
    {}

    bool Remove(const K& key)
    {

    }

    Node* Find(const K& key);

    bool Insert(const K& key, const V& value)
    {
        //1.����
        if (_root == NULL)
        {
            _root = new Node(key, value);
            return true;
        }

        //2.���Ҳ����λ��
        Node* parent = NULL;
        Node* cur = _root;
        while(cur)
        {
            if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }

        cur = new Node(key, value);
        if (parent->_key > key)
        {
            parent->_left = cur;
            cur->_parent = parent; 
        }
        else
        {
            parent->_right = cur;
            cur->_parent = parent; 
        }

        bool isRotate = false;

        // 3.������
        while (parent)
        {
            if(parent->_left == cur)
                parent->_bf--;
            else
                parent->_bf++;

            if (parent->_bf == 0)
            {
                break;
            }
            else if (parent->_bf == 1 || parent->_bf == -1)
            {
                cur = parent;
                parent = cur->_parent;
            }
            else // 2 -2
            {
                isRotate = true;
                if (parent->_bf == 2)
                {
                    if (cur->_bf == 1)
                    {
                        _RotateL(parent);
                    }
                    else
                    {
                        _RotateRL(parent);
                    }
                }
                else // -2
                {
                    if (cur->_bf == -1)
                    {
                        _RotateR(parent);
                    }
                    else
                    {
                        _RotateLR(parent);
                    }
                }

                break;
            }
        }

        if (isRotate)
        {
            Node* ppNode = parent->_parent;
            if (ppNode == NULL)
            {
                _root = parent;
            }
            else
            {
                if (ppNode->_key < parent->_key)
                {
                    ppNode->_right = parent;
                }
                else
                {
                    ppNode->_left = parent;
                }
            }
        }

        return true;
    }

    void InOrder()
    {
        _InOrder(_root);
        cout<<endl;
    }


    bool IsBlance()
    {
        return _IsBlance(_root);
    }

protected:
    bool _IsBlance(Node* root)
    {
        if (root == NULL)
        {
            return true;
        }

        int left = _Height(root->_left);
        int right = _Height(root->_right);

        int bf = abs(right-left);
        if (bf > 1)
        {
            return false;
        }

        if (bf != abs(root->_bf))
        {
            cout<<root->_key<<":ƽ������������"<<endl;
            return false;
        }

        return _IsBlance(root->_left) && _IsBlance(root->_right);
    }

    int _Height(Node* root)
    {
        if (root == NULL)
        {
            return 0;
        }

        int left = _Height(root->_left) + 1;
        int right = _Height(root->_right) + 1;

        return left > right ? left : right;
    }

    void _InOrder(Node* root)
    {
        if (root == NULL)
        {
            return;
        }

        _InOrder(root->_left);
        cout<<root->_key<<" ";
        _InOrder(root->_right);
    }

    void _RotateL(Node*& parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        parent->_right = subRL;
        if (subRL)
        {
            subRL->_parent = parent;
        }

        subR->_left = parent;
        subR->_parent = parent->_parent;
        parent->_parent = subR;

        parent->_bf = subR->_bf = 0;

        parent = subR;
    }

    void _RotateR(Node*& parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if (subLR)
        {
            subLR->_parent = parent;
        }

        subL->_right = parent;
        subL->_parent = parent->_parent;
        parent->_parent = subL;

        parent->_bf = subL->_bf = 0;

        parent = subL;
    }

    //void _RotateLR(Node*& parent)
    //{
    //    _RotateL(parent->_left);
    //    _RotateR(parent);
    //}
    //
    //void _RotateRL(Node*& parent)
    //{
    //    _RotateR(parent->_right);
    //    _RotateL(parent);
    //}

    void _RotateLR(Node*& parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        // ����
        subL->_right = subLR->_left;
        if (subLR->_left)
        {
            subLR->_left->_parent = subL;
        }

        subLR->_left = subL;
        subLR->_parent = subL->_parent;
        subL->_parent = subLR;

        if (subLR->_bf == 0 || subLR->_bf == -1)
        {
            subL->_bf = 0;
        }
        else // subLR->_bf == 1
        {
            subL->_bf = -1;
        }

        // �ҵ���
        parent->_left = subLR->_right;
        if (subLR->_right)
        {
            subLR->_right->_parent = parent;
        }

        subLR->_right = parent;
        subLR->_parent = parent->_parent;
        parent->_parent = subLR;

        if (subLR->_bf == 0 || subLR->_bf == 1)
        {
            parent->_bf = 0;
        }
        else // subLR->_bf == -1
        {
            parent->_bf = 1;
        }

        subLR->_bf = 0;
        parent = subLR;
    }

    void _RotateRL(Node*& parent)
    {
        Node* subR = parent->_right;
        Node* subRL= subR->_left;

        subR->_left = subRL->_right;
        if (subRL->_right)
        {
            subRL->_right->_parent = subR;
        }

        subRL->_right = subR;
        subR->_parent = subRL;

        if (subRL->_bf == 0 || subRL->_bf == 1)
        {
            subR->_bf = 0;
        }
        else
        {
            subR->_bf = 1;
        }

        parent->_right = subRL->_left;
        if (subRL->_left)
        {
            subRL->_left->_parent = parent;
        }

        subRL->_left = parent;
        subRL->_parent = parent->_parent;
        parent->_parent = subRL;

        if (subRL->_bf == 0 || subRL->_bf == -1)
        {
            parent->_bf = 0;
        }
        else
        {
            parent->_bf = -1;
        }

        subRL->_bf = 0;
        parent = subRL;
    }

protected:
    Node* _root;
};

void Test1()
{
    AVLTree<int, int> t1;
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    for (size_t i = 0; i < sizeof(a)/sizeof(int); ++i)
    {
        t1.Insert(a[i], i);
    }

    t1.InOrder();
    cout<<"IsBlance?"<<t1.IsBlance()<<endl;
}

void Test2()
{
    AVLTree<int, int> t1;
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for (size_t i = 0; i < sizeof(a)/sizeof(int); ++i)
    {
        t1.Insert(a[i], i);
    }

    t1.InOrder();
    cout<<"IsBlance?"<<t1.IsBlance()<<endl;
}