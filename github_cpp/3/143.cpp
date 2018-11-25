#include "avltree.h"
#include <QDebug>


AVLtree::AVLtree()
{
    root = nullptr;
}

int AVLtree::height(TreeNode* node)
{
    if(node!=nullptr)
        return node->hgt;
    return -1;
}


int AVLtree::Max(int cmpa,int cmpb)
{
    return cmpa>cmpb?cmpa:cmpb;
}


void AVLtree::SingRotateLeft(TreeNode* &k2)
{
    TreeNode* k1;
    k1=k2->lson;
    k2->lson=k1->rson;
    k1->rson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->lson),k2->hgt)+1;
}


void AVLtree::SingRotateRight(TreeNode* &k2)
{
    TreeNode* k1;
    k1=k2->rson;
    k2->rson=k1->lson;
    k1->lson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->rson),k2->hgt)+1;
}


void AVLtree::DoubleRotateLR(TreeNode* &k3)
{
    SingRotateRight(k3->lson);
    SingRotateLeft(k3);
}


void AVLtree::DoubleRotateRL(TreeNode* &k3)
{
    SingRotateLeft(k3->rson);
    SingRotateRight(k3);
}

void AVLtree::insertpri(TreeNode* &node,Persona *x)
{
    if(node == nullptr)
    {
        node = new TreeNode();
        node->ptHumano = x;
        return;
    }
    if(node->ptHumano->id>x->id)
    {
        insertpri(node->lson,x);
        if(2==(height(node->lson)-height(node->rson))){
            if(x->id<node->lson->ptHumano->id)
                SingRotateLeft(node);
            else
                DoubleRotateLR(node);
        }
    }
    else if(node->ptHumano->id<x->id)
    {
        insertpri(node->rson,x);
        if(2==(height(node->rson)-height(node->lson))){
            if(x->id>node->rson->ptHumano->id)
                SingRotateRight(node);
            else
                DoubleRotateRL(node);
        }
    }
    else ++(node->freq);
    node->hgt=Max(height(node->lson),height(node->rson));
}


void AVLtree::insert(Persona *x)
{
    insertpri(root,x);
    listaPersonas.append(x);
}



TreeNode* AVLtree::findpri(TreeNode* node, Persona *x)
{
    if(node==nullptr)
    {
        return nullptr;
    }
    if(node->ptHumano->id>x->id)
    {
        return findpri(node->lson,x);
    }
    else if(node->ptHumano->id<x->id)
    {
        return findpri(node->rson,x);
    }
    else return node;
}


TreeNode* AVLtree::find(Persona *x)
{
    return findpri(root,x);
}


void AVLtree::Deletepri(TreeNode* &node,Persona *x)
{
    if(node==nullptr) return ;
    if(x->id <node->ptHumano->id)
    {
         Deletepri(node->lson,x);
         if(2==height(node->rson)-height(node->lson))
            if(node->rson->lson!=nullptr && (height(node->rson->lson)>height(node->rson->rson)) )
                DoubleRotateRL(node);
            else
                SingRotateRight(node);
    }

    else if(x->id > node->ptHumano->id)
    {
         Deletepri(node->rson,x);
         if(2==height(node->lson)-height(node->rson))
            if(node->lson->rson!=nullptr && (height(node->lson->rson)>height(node->lson->lson) ))
                DoubleRotateLR(node);
            else
                SingRotateLeft(node);
    }

    else
    {
        if(node->lson&&node->rson)
        {
            TreeNode* temp=node->rson;
            while(temp->lson != nullptr) temp=temp->lson;
            
            node->ptHumano->id=temp->ptHumano->id;
            node->freq=temp->freq;
            Deletepri(node->rson,temp->ptHumano);
            if(2==height(node->lson)-height(node->rson))
            {
                if(node->lson->rson != nullptr && (height(node->lson->rson)>height(node->lson->lson) ))
                    DoubleRotateLR(node);
                else
                    SingRotateLeft(node);
            }
        }
        else
        {
            TreeNode* temp=node;
            if(node->lson == nullptr)
            node=node->rson;
            else if(node->rson == nullptr)
            node=node->lson;
            delete(temp);
            temp = nullptr;
        }
    }
    if(node==nullptr) return;
    node->hgt=Max(height(node->lson),height(node->rson))+1;
    return;
}


void AVLtree::agregar(QVector<Persona*>* l, string pais){
    agregar(root, l, pais);
}


bool AVLtree::agregar(TreeNode *r,QVector<Persona*>* l,string pais){
    if(r == nullptr){
        return true;
    }else if(!r->isSon && pais == r->ptHumano->pais){
        l->append(r->ptHumano);
        r->isSon = true;
        return false;
    }
    return agregar(r->lson, l, pais) && agregar(r->rson, l, pais);
}

