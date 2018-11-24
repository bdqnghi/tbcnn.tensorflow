// Author: Beier Chen, bchen22@syr.edu
// Source: Roger Chen
// Application: 674 HW6  AVL Tree
// Due: Saturday (Nov. 18) at 11:59PM

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
    int value;
    int height;
    int child; //0: this node is a left child of its parent; 1: right child; -1 this node is the tree root
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
    void add_node(int i);//You need to implement this.
    void in_order_traversal(node *p);  //provided.
    node * height_adjustment(node *p, int &pattern); //You need to implement this
    void L_Rotate(node *p); //You need to implement this.
    void R_Rotate(node *p); //You need to implement this.
    void remove_node(int i);// You need to implement this.
    node * replace(node * p1);// You need to implement this.
};

void avl_tree::remove_node(int i)
{
    node* nodeToRmv = root; // the node to be removed
    int pattern = 0;
    node * actionNode = nullptr;
    bool rmvExist = true;
    
    /* ----- < locates the nodeToRmv > ----- */
    while(nodeToRmv->value != i)
    {
        if (i < nodeToRmv->value) // go to left subtree
        {
            nodeToRmv = nodeToRmv->l_child;
        }
        else if (i > nodeToRmv->value) // go to right subtree
        {
            nodeToRmv = nodeToRmv->r_child;
        }
        
        if(nodeToRmv == nullptr)
        {
            rmvExist = false;
            break;
        }
    }
    
    /* ----- < remove the nodeToRmv > ----- */
    if(rmvExist)
    {
        node * nodeToUpdate = replace(nodeToRmv);// the first node we need to check for possible height update after a node replcement.
        actionNode = height_adjustment(nodeToUpdate, pattern);
    }

    
    /* ----- < after removing the nodeToRmv, if violation occurs, rebalance the tree > ----- */
    if (actionNode != nullptr)
    {
        switch (pattern)
        {
            case 1:  // LL pattern
            {
                R_Rotate(actionNode); //perform R_Rotate around Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
            case 2:  // LR pattern
            {
                node * preLeftOfAN = actionNode->l_child; // before L_Rotate, the left child of the Action Node
                L_Rotate(actionNode->l_child); // first perform L_Rotate around the left child of Action Node
                height_adjustment(preLeftOfAN, pattern);

                R_Rotate(actionNode); // then perform R_Rotate around the Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
            case 3: // RL pattern
            {
                node * preRightOfAN = actionNode->r_child; // before R_Rotate, the right child of the Action Node
                R_Rotate(actionNode->r_child);
                height_adjustment(preRightOfAN, pattern); // first perform R_Rotate around the right child of Action Node
                
                L_Rotate(actionNode); // then perform L_Rotate around the Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
            case 4: // RR pattern
            {
                L_Rotate(actionNode); //perform L_Rotate around Action Node
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
    
    // --- < if nodeToRmv is the root without subtree or a terminal node
    if (rightOfRmv == nullptr && leftOfRmv == nullptr)
    {
        if (nodeToRmv == root)
        {
            root = nullptr;
        }
        else
        {
            if (nodeToRmv->child == 0) // nodeToRmv is left child of its parent
            {
                parentOfRmv->l_child = nullptr;
            }
            else if (nodeToRmv->child == 1)  // nodeToRmv is right child of its parent
            {
                parentOfRmv->r_child = nullptr;
            }
        }
        return parentOfRmv;
    }
    // --- < if nodeToRmv is the root with subtrees or a non-terminal node
    else
    {
        node* successor = nullptr;
        
        // locate the successor node to replace nodeToRmv
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
        
        // update successor's parent
        if (nodeToRmv == root) // if nodeToRmv is the root
        {
            root = successor;
            successor->parent = nullptr;
            successor->child = -1;
        }
        else // if nodeToRmv is not the root
        {
            successor->parent = parentOfRmv;
            if (nodeToRmv->child == 0) // nodeToRmv is left child of its parent
            {
                parentOfRmv->l_child = successor;
            }
            else if (nodeToRmv->child == 1)  // nodeToRmv is right child of its parent
            {
                parentOfRmv->r_child = successor;
                successor->child = 1;
            }
        }
        
        // if nodeToRmv doesn't have left child, replace it with its right child
        if (leftOfRmv == nullptr)
        {
            return successor;
        }
        // if nodeToRmv has left child, replace it with the largest node of its left subtree
        else
        {
            // update successor's right child
            if (rightOfRmv != nullptr)
            {
                successor->r_child = rightOfRmv;
                rightOfRmv->parent = successor;
            }
            
            // if successor is not the left child of nodeToRmv, update successor's left child
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
        if (p->child == 0) // p is left child of its parent
        {
            parentOfP->l_child = tempRight;
        }
        else if (p->child == 1) // p is right child of its parent
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
        if (p->child == 0) // p is left child of its parent
        {
            parentOfP->l_child = tempLeft;
        }
        else if (p->child == 1) // p is right child of its parent
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
    
    // ----< add a new node to the tree
    if (root == nullptr) // if the tree is empty
    {
        root = newNode;
        root->child = -1;
        newNode = root;
        next = root;
    }
    else // if the tree is not empty
    {
        while (next != nullptr)  // find the position to add the new node
        {
            // go to left subtree
            if (i < next->value)
            {
                if (next->l_child == nullptr)
                {
                    flag = 0;
                    break;
                }
                else next = next->l_child;
            }
            // go to right subtree
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
        
        // add the node to the tree
        if (flag == 0) // the new node will be the left child of its parent
        {
            newNode->child = 0;
            next->l_child = newNode;
            newNode->parent = next;
        }
        else if (flag == 1) // the new node will be the right child of its parent
        {
            newNode->child = 1;
            next->r_child = newNode;
            newNode->parent = next;
        }
    }
    
    // ----< update the height. If violation occurs, rebalance the tree
    node * actionNode = height_adjustment(newNode, pattern);
    if (actionNode != nullptr)
    {
        switch (pattern)
        {
            case 1:  // LL pattern
            {
                R_Rotate(actionNode); // perform R_Rotate around Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
            case 2:  // LR pattern
            {
                node * preLeftOfAN = actionNode->l_child; // before L_Rotate, the left child of the Action Node
                L_Rotate(actionNode->l_child); // first perform L_Rotate around the left child of Action Node
                height_adjustment(preLeftOfAN, pattern);
            
                R_Rotate(actionNode); // then perform R_Rotate around the Action Node
                height_adjustment(actionNode, pattern);
                
                break;
            }
            case 3: // RL pattern
            {
                node * preRightOfAN = actionNode->r_child; // before R_Rotate, the right child of the Action Node
                R_Rotate(actionNode->r_child); // first perform R_Rotate around the right child of Action Node
                height_adjustment(preRightOfAN, pattern);
            
                L_Rotate(actionNode);// then perform L_Rotate around the Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
            case 4: // RR pattern
            {
                L_Rotate(actionNode); // perform L_Rotate around Action Node
                height_adjustment(actionNode, pattern);
                break;
            }
        }
    }
}

node * avl_tree::height_adjustment(node *p, int &pattern)
{
    int flag = -1; // help to find the violation pattern
    
    // -----< update height
    while (p != nullptr)
    {
        // 1. leaf node, height = 1
        if (p->l_child == nullptr && p->r_child == nullptr)
        {
            p->height = 1;
        }
        // 2. only right child exists
        else if (p->l_child == nullptr && p->r_child != nullptr)
        {
            p->height = p->r_child->height + 1;
            
            if (p->r_child->height > 1) // violation occurs
            {
                flag = 1;
                break;
            }
        }
        // 3. only left child exists
        else if (p->l_child != nullptr&& p->r_child == nullptr)
        {
            p->height = p->l_child->height + 1;
            
            if (p->l_child->height > 1) // violation occurs
            {
                flag = 0;
                break;
            }
        }
        // 4. has both right and left child
        else if (p->l_child != nullptr && p->r_child != nullptr)
        {
            p->height = max(p->r_child->height, p->l_child->height) + 1;
            
            // violation occurs
            if (p->l_child->height - p->r_child->height > 1) // L
            {
                flag = 0;
                break;
            }
            else if (p->r_child->height - p->l_child->height > 1) // R
            {
                flag = 1;
                break;
            }
        }
        
        if (p->parent == nullptr) break;
        p = p->parent;
    }
    
    // -----< find the violation pattern
    if (flag != -1)
    {
        if (flag == 0) // L
        {
            if (p->l_child->l_child != nullptr && p->l_child->r_child != nullptr)
            {
                if (p->l_child->l_child->height >= p->l_child->r_child->height) pattern = 1; //LL
                else pattern = 2; // LR
            }
            else if (p->l_child->l_child == nullptr && p->l_child->r_child != nullptr) pattern = 2; //LR
            else if (p->l_child->l_child != nullptr && p->l_child->r_child == nullptr) pattern = 1; // LL
        }
        else if (flag == 1) // R
        {
            if (p->r_child->l_child != nullptr && p->r_child->r_child != nullptr)
            {
                if (p->r_child->l_child->height > p->r_child->r_child->height) pattern = 3; //RL
                else pattern = 4; // RR
            }
            else if (p->r_child->l_child == nullptr && p->r_child->r_child != nullptr) pattern = 4; //RR
            else if (p->r_child->l_child != nullptr && p->r_child->r_child == nullptr) pattern = 3; // RL
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

