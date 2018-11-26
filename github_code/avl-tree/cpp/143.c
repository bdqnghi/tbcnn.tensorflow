#include "avltree.h"
#include <QDebug>
//template<class T>

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

//Máximo
int AVLtree::Max(int cmpa,int cmpb)
{
    return cmpa>cmpb?cmpa:cmpb;
}

//Rotacion izquierda
void AVLtree::SingRotateLeft(TreeNode* &k2)
{
    TreeNode* k1;
    k1=k2->lson;
    k2->lson=k1->rson;
    k1->rson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->lson),k2->hgt)+1;
}

//En el caso de la rotación de la derecha
void AVLtree::SingRotateRight(TreeNode* &k2)
{
    TreeNode* k1;
    k1=k2->rson;
    k2->rson=k1->lson;
    k1->lson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->rson),k2->hgt)+1;
}

//Rotacion doble izquierda-derecha.
void AVLtree::DoubleRotateLR(TreeNode* &k3)
{
    SingRotateRight(k3->lson);
    SingRotateLeft(k3);
}

//La rotación de la izquierda a la derecha
void AVLtree::DoubleRotateRL(TreeNode* &k3)
{
    SingRotateLeft(k3->rson);
    SingRotateRight(k3);
}

void AVLtree::insertpri(TreeNode* &node,Persona *x)
{
    if(node == nullptr)//Si los nodos vacío, con la información de este nodo X
    {
        node = new TreeNode();
        node->ptHumano = x;
        return;
    }
    if(node->ptHumano->id>x->id)//Si X es inferior al valor del nodo, sigue en el árbol de la izquierda inserción de nodo X
    {
        insertpri(node->lson,x);
        if(2==(height(node->lson)-height(node->rson))){
            if(x->id<node->lson->ptHumano->id)
                SingRotateLeft(node);
            else
                DoubleRotateLR(node);
        }
    }
    else if(node->ptHumano->id<x->id)//Si X es mayor que el valor del nodo, sigue en la inserción de nodo X subárbol
    {
        insertpri(node->rson,x);
        if(2==(height(node->rson)-height(node->lson))){//Si la altura de la diferencia es de 2 palabras, perdió el equilibrio y la necesidad de rotación
            if(x->id>node->rson->ptHumano->id)
                SingRotateRight(node);
            else
                DoubleRotateRL(node);
        }
    }
    else ++(node->freq);//Si son iguales, con frecuencia 1
    node->hgt=Max(height(node->lson),height(node->rson));
}

//La inserción de la interfaz
void AVLtree::insert(Persona *x)
{
    insertpri(root,x);
    listaPersonas.append(x);
}


//Buscar
TreeNode* AVLtree::findpri(TreeNode* node, Persona *x)
{
    if(node==nullptr)//Si los nodos vacío que no encontrar, devuelve null
    {
        return nullptr;
    }
    if(node->ptHumano->id>x->id)//Si X es inferior al valor del nodo, continuar la búsqueda de X en el árbol de la izquierda del nodo
    {
        return findpri(node->lson,x);
    }
    else if(node->ptHumano->id<x->id)//Si X es mayor que el valor del nodo, continuar la búsqueda de X en el árbol de la izquierda del nodo
    {
        return findpri(node->rson,x);
    }
    else return node;//Si son iguales, de encontrar este nodo
}

//Interfaz de búsqueda
TreeNode* AVLtree::find(Persona *x)
{
    return findpri(root,x);
}

//Borrar
void AVLtree::Deletepri(TreeNode* &node,Persona *x)
{
    if(node==nullptr) return ;//No es encontrar el valor X de los nodos
    if(x->id <node->ptHumano->id)
    {
         Deletepri(node->lson,x);//Si X es inferior al valor del nodo, sigue en el árbol de la izquierda elimina el nodo X
         if(2==height(node->rson)-height(node->lson))
            if(node->rson->lson!=nullptr && (height(node->rson->lson)>height(node->rson->rson)) )
                DoubleRotateRL(node);
            else
                SingRotateRight(node);
    }

    else if(x->id > node->ptHumano->id)
    {
         Deletepri(node->rson,x);//Si X es mayor que el valor del nodo, sigue en el nodo eliminar X subárbol
         if(2==height(node->lson)-height(node->rson))
            if(node->lson->rson!=nullptr && (height(node->lson->rson)>height(node->lson->lson) ))
                DoubleRotateLR(node);
            else
                SingRotateLeft(node);
    }

    else//Si son iguales, el nodo es eliminar nodo
    {
        if(node->lson&&node->rson)//El nodo tiene dos hijos
        {
            TreeNode* temp=node->rson;//Nodos hijo temp hacia la derecha
            while(temp->lson != nullptr) temp=temp->lson;//Encontrar un mínimo de nodos subárbol mediana
            //A la derecha en el valor mínimo de nodos subárbol de asignar a este nodo
            node->ptHumano->id=temp->ptHumano->id;
            node->freq=temp->freq;
            Deletepri(node->rson,temp->ptHumano);//Eliminar nodos en el valor mínimo de la derecha subárbol
            if(2==height(node->lson)-height(node->rson))
            {
                if(node->lson->rson != nullptr && (height(node->lson->rson)>height(node->lson->lson) ))
                    DoubleRotateLR(node);
                else
                    SingRotateLeft(node);
            }
        }
        else//El nodo tiene un hijo o 1 0
        {
            TreeNode* temp=node;
            if(node->lson == nullptr)//Hijo o no, el hijo de la derecha
            node=node->rson;
            else if(node->rson == nullptr)//A la izquierda, hijo
            node=node->lson;
            delete(temp);
            temp = nullptr;
        }
    }
    if(node==nullptr) return;
    node->hgt=Max(height(node->lson),height(node->rson))+1;
    return;
}

//Agrega
void AVLtree::agregar(QVector<Persona*>* l, string pais){
    agregar(root, l, pais);
}

//Agrega_2.0
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

