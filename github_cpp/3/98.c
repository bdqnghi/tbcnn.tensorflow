




#include <iostream> 
#include <algorithm> 

using namespace std;


class node {
public:
    int value;
    int height;
    int child; 
    node * parent;
    node * l_child;
    node * r_child;
    node() {}
    node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }
};

class avl_tree {
public:
    node * root;
    avl_tree() {
        root = nullptr;
    }
    void add_node(int i);
    void in_order_traversal(node *p);  
    node * height_adjustment(node *p, int &pattern); 
    void L_Rotate(node *p); 
    void R_Rotate(node *p); 
    void remove_node(int i);
    node * replace(node * p1);
};

void avl_tree::remove_node(int i)
{
    node* nodeToRmv = root; 
    int pattern = 0;
    node * actionNode = nullptr;
    bool rmvExist = true;
    
    
    while(nodeToRmv->value != i)
    {
        if (i < nodeToRmv->value) 
        {
            nodeToRmv = nodeToRmv->l_child;
        }
        else if (i > nodeToRmv->value) 
        {
            nodeToRmv = nodeToRmv->r_child;
        }
        
        if(nodeToRmv == nullptr)
        {
            rmvExist = false;
            break;
        }
    }
    
    
    if(rmvExist)
    {
        node * nodeToUpdate = replace(nodeToRmv);
        actionNode = height_adjustment(nodeToUpdate, pattern);
    }

    
    
    if (actionNode != nullptr)
    {
        switch (pattern)
        {
            case 1:  
            {
                R_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
            case 2:  
            {
                node * preLeftOfAN = actionNode->l_child; 
                L_Rotate(actionNode->l_child); 
                height_adjustment(preLeftOfAN, pattern);

                R_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
            case 3: 
            {
                node * preRightOfAN = actionNode->r_child; 
                R_Rotate(actionNode->r_child);
                height_adjustment(preRightOfAN, pattern); 
                
                L_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
            case 4: 
            {
                L_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
        }
    }
}

node * avl_tree::replace(node * p1)
{
    node* nodeToRmv = p1;
    node * parentOfRmv = nodeToRmv->parent;
    node * rightOfRmv = nodeToRmv->r_child;
    node * leftOfRmv = nodeToRmv->l_child;
    
    
    if (rightOfRmv == nullptr && leftOfRmv == nullptr)
    {
        if (nodeToRmv == root)
        {
            root = nullptr;
        }
        else
        {
            if (nodeToRmv->child == 0) 
            {
                parentOfRmv->l_child = nullptr;
            }
            else if (nodeToRmv->child == 1)  
            {
                parentOfRmv->r_child = nullptr;
            }
        }
        return parentOfRmv;
    }
    
    else
    {
        node* successor = nullptr;
        
        
        if (leftOfRmv != nullptr)
        {
            successor = leftOfRmv;
            
            while (successor->r_child != nullptr)
            {
                successor = successor->r_child;
            }
        }
        else
        {
            successor = p1->r_child;
        }
        
        node* preParentOfSucc = successor->parent;
        node* leftOfSucc = successor->l_child;
        
        
        if (nodeToRmv == root) 
        {
            root = successor;
            successor->parent = nullptr;
            successor->child = -1;
        }
        else 
        {
            successor->parent = parentOfRmv;
            if (nodeToRmv->child == 0) 
            {
                parentOfRmv->l_child = successor;
            }
            else if (nodeToRmv->child == 1)  
            {
                parentOfRmv->r_child = successor;
                successor->child = 1;
            }
        }
        
        
        if (leftOfRmv == nullptr)
        {
            return successor;
        }
        
        else
        {
            
            if (rightOfRmv != nullptr)
            {
                successor->r_child = rightOfRmv;
                rightOfRmv->parent = successor;
            }
            
            
            if (successor != leftOfRmv)
            {
                successor->l_child = leftOfRmv;
                leftOfRmv->parent = successor;
                
                if (leftOfSucc != nullptr)
                {
                    leftOfSucc->parent = preParentOfSucc;
                    preParentOfSucc->r_child = leftOfSucc;
                    leftOfSucc->child = 1;
                    return leftOfSucc;
                }
                else
                {
                    preParentOfSucc->r_child = nullptr;
                    return preParentOfSucc;
                }
            }
            else return successor;
        }
    }
}

void  avl_tree::L_Rotate(node *p)
{
    node * parentOfP = p->parent;
    node * tempRight = p->r_child;
    node * LeftOfRight = p->r_child->l_child;
    
    if (p == root)
    {
        tempRight->parent = nullptr;
        root = tempRight;
        tempRight->child = -1;
        
        tempRight->l_child = p;
        p->parent = tempRight;
        p->child = 0;
    }
    else
    {
        if (p->child == 0) 
        {
            parentOfP->l_child = tempRight;
        }
        else if (p->child == 1) 
        {
            parentOfP->r_child = tempRight;
            tempRight->child = 1;
        }
        tempRight->parent = parentOfP;
        
        p->parent = tempRight;
        tempRight->l_child = p;
    }
    
    if (LeftOfRight != nullptr)
    {
        p->r_child = LeftOfRight;
        LeftOfRight->parent = p;
        LeftOfRight->child = 1;
    }
    else p->r_child = nullptr;
    
}

void  avl_tree::R_Rotate(node *p)
{
    node * parentOfP = p->parent;
    node * tempLeft = p->l_child;
    node * rightOfLeft = p->l_child->r_child;
    
    if (p == root)
    {
        tempLeft->parent = nullptr;
        root = tempLeft;
        tempLeft->child = -1;
        
        tempLeft->r_child = p;
        p->parent = tempLeft;
        p->child = 1;
    }
    else
    {
        if (p->child == 0) 
        {
            parentOfP->l_child = tempLeft;
        }
        else if (p->child == 1) 
        {
            parentOfP->r_child = tempLeft;
            tempLeft->child = 1;
        }
        tempLeft->parent = parentOfP;
        
        p->parent = tempLeft;
        tempLeft->r_child = p;
    }
    
    if (rightOfLeft != nullptr)
    {
        p->l_child = rightOfLeft;
        rightOfLeft->parent = p;
        rightOfLeft->child = 0;
    }
    else p->l_child = nullptr;
}

void  avl_tree::add_node(int i)
{
    int pattern = 0;
    node * newNode = new node(i);
    node * next = root;
    int flag = -1;
    
    
    if (root == nullptr) 
    {
        root = newNode;
        root->child = -1;
        newNode = root;
        next = root;
    }
    else 
    {
        while (next != nullptr)  
        {
            
            if (i < next->value)
            {
                if (next->l_child == nullptr)
                {
                    flag = 0;
                    break;
                }
                else next = next->l_child;
            }
            
            else if (i > next->value)
            {
                if (next->r_child == nullptr)
                {
                    flag = 1;
                    break;
                }
                else next = next->r_child;
            }
        }
        
        
        if (flag == 0) 
        {
            newNode->child = 0;
            next->l_child = newNode;
            newNode->parent = next;
        }
        else if (flag == 1) 
        {
            newNode->child = 1;
            next->r_child = newNode;
            newNode->parent = next;
        }
    }
    
    
    node * actionNode = height_adjustment(newNode, pattern);
    if (actionNode != nullptr)
    {
        switch (pattern)
        {
            case 1:  
            {
                R_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
            case 2:  
            {
                node * preLeftOfAN = actionNode->l_child; 
                L_Rotate(actionNode->l_child); 
                height_adjustment(preLeftOfAN, pattern);
            
                R_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                
                break;
            }
            case 3: 
            {
                node * preRightOfAN = actionNode->r_child; 
                R_Rotate(actionNode->r_child); 
                height_adjustment(preRightOfAN, pattern);
            
                L_Rotate(actionNode);
                height_adjustment(actionNode, pattern);
                break;
            }
            case 4: 
            {
                L_Rotate(actionNode); 
                height_adjustment(actionNode, pattern);
                break;
            }
        }
    }
}

node * avl_tree::height_adjustment(node *p, int &pattern)
{
    int flag = -1; 
    
    
    while (p != nullptr)
    {
        
        if (p->l_child == nullptr && p->r_child == nullptr)
        {
            p->height = 1;
        }
        
        else if (p->l_child == nullptr && p->r_child != nullptr)
        {
            p->height = p->r_child->height + 1;
            
            if (p->r_child->height > 1) 
            {
                flag = 1;
                break;
            }
        }
        
        else if (p->l_child != nullptr&& p->r_child == nullptr)
        {
            p->height = p->l_child->height + 1;
            
            if (p->l_child->height > 1) 
            {
                flag = 0;
                break;
            }
        }
        
        else if (p->l_child != nullptr && p->r_child != nullptr)
        {
            p->height = max(p->r_child->height, p->l_child->height) + 1;
            
            
            if (p->l_child->height - p->r_child->height > 1) 
            {
                flag = 0;
                break;
            }
            else if (p->r_child->height - p->l_child->height > 1) 
            {
                flag = 1;
                break;
            }
        }
        
        if (p->parent == nullptr) break;
        p = p->parent;
    }
    
    
    if (flag != -1)
    {
        if (flag == 0) 
        {
            if (p->l_child->l_child != nullptr && p->l_child->r_child != nullptr)
            {
                if (p->l_child->l_child->height >= p->l_child->r_child->height) pattern = 1; 
                else pattern = 2; 
            }
            else if (p->l_child->l_child == nullptr && p->l_child->r_child != nullptr) pattern = 2; 
            else if (p->l_child->l_child != nullptr && p->l_child->r_child == nullptr) pattern = 1; 
        }
        else if (flag == 1) 
        {
            if (p->r_child->l_child != nullptr && p->r_child->r_child != nullptr)
            {
                if (p->r_child->l_child->height > p->r_child->r_child->height) pattern = 3; 
                else pattern = 4; 
            }
            else if (p->r_child->l_child == nullptr && p->r_child->r_child != nullptr) pattern = 4; 
            else if (p->r_child->l_child != nullptr && p->r_child->r_child == nullptr) pattern = 3; 
        }
        return p;
    }
    else return nullptr;
}

void avl_tree::in_order_traversal(node * p) {
    if (p == nullptr)  return;
    in_order_traversal(p->l_child);
    cout << "value = " << p->value << " " << "height = " << p->height << "   ";
    in_order_traversal(p->r_child);
}

int main() {
    avl_tree t1;
    t1.add_node(45);
    t1.in_order_traversal(t1.root);
    t1.remove_node(45);
    t1.in_order_traversal(t1.root);
    t1.add_node(50);
    t1.add_node(47);
    t1.add_node(30);
    t1.add_node(35);
    t1.in_order_traversal(t1.root);
    t1.remove_node(47);
    t1.in_order_traversal(t1.root);
    getchar();
    getchar();
    return 0;
}

