

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;


template <class T>
class Element {
public:
    int id;
    T info;

    Element(){ this->id = 0;}
    Element(int id, T info){
        this->id = id;
        this->info = info;
    }

    void print_element(){ cout << "(" << id << ", " << info << ") ";}

    
    Element<T> operator= (const Element<T> &e){ id = e.id; info = e.info;}
    bool operator < (const Element<T> &e){ return id < e.id;}
    bool operator <=(const Element<T> &e){ return id <= e.id;}
    bool operator > (const Element<T> &e){ return id > e.id;}
    bool operator >=(const Element<T> &e){ return id >= e.id;}
    bool operator ==(const Element<T> &e){ return id == e.id && info == e.info;}
    bool operator !=(const Element<T> &e){ return id != e.id || info != e.info;}
};


template <class T>
class Node {
public:
    short unsigned int size;    
    bool is_leaf;               
    Element<T>* elements;       
    Node<T>** p_sons;           

    static const short unsigned int max_size = 5; 

    
    Node();
    Node(int, Element<T>*, Node<T>** = NULL);

    
    Element<T>* find_element_by_id_in_node(int);
    bool insert_element(Element<T>);            
    bool remove_element(int);                   
    void clear_elements() { this->size=0; }     
    void print_elements();                      
    void shift_left_pointers(int); 
    void shift_right_pointers(int); 

    
    inline void set_is_leaf(bool a) { this->is_leaf = a; }

    
    Node<T>& operator ++();             
    Node<T>& operator --();             
    Node<T>& operator >> (const int);   
    Node<T>& operator << (const int);   
};

template <class T>
Node<T>& Node<T>::operator++() {
    this->size += 1;
    return *this;
}

template <class T>
Node<T>& Node<T>::operator--() {
    this->size -= 1;
    return *this;
}

template <class T>
Node<T>& Node<T>::operator>> (const int index){
    int j = size, i = index;
    while(j > i){
        elements[j] = elements[j-1]; 
        j--;
    }
    ++(*this); 
    return *this;
}

template <class T>
Node<T>& Node<T>::operator<< (const int index){
    int i = index; 
    while(i < this->size){
        elements[i] = elements[i+1]; 
        i++;
    }
    --(*this); 
    return *this;
}

template <class T>
Node<T>::Node(int size, Element<T>* elements, Node<T>** p_nodes){
    this->size = size;
    this->is_leaf = p_nodes[0] == NULL;
    this->elements = new Element<T>[max_size];
    for(int i=0; i<size; i++) this->elements[i] = elements[i];
    this->p_sons = new Node<T>*[max_size+1];
    for(int i=0; i<size+1; i++) this->p_sons[i] = p_nodes[i];
}

template <class T>
Node<T>::Node(){
    this->size = 0;
    this->is_leaf = true;
    this->elements = new Element<T>[max_size];
    this->p_sons = new Node<T>*[max_size+1];
}

template <class T>
void Node<T>::shift_left_pointers(int i){
    while(i <= this->size) this->p_sons[i] = this->p_sons[++i];
}

template <class T>
void Node<T>::shift_right_pointers(int i){
    int j = size+1; 
    while(j >= i) p_sons[j] = p_sons[--j];
}

template <class T>
Element<T>* Node<T>::find_element_by_id_in_node(int id){
    int i=0;
    while(i < size && elements[i].id != id) i++; 
    if (i != size) 
        return &(elements[i]);
    else 
        return NULL;
}

template <class T>
bool Node<T>::insert_element(Element<T> element){
    if(size < max_size){
        
        int i=0, j = size;
        while(i < size && elements[i] < element) i++; 
        *this >> i; 
        elements[i] = element; 
        return true;
    } else
        return false;
}

template <class T>
void Node<T>::print_elements(){
    int i;
    for(i=0; i<size; i++)
        elements[i].print_element();
    cout << endl;
}

template <class T>
bool Node<T>::remove_element(int id){
    int i=0;
    while(i < size && elements[i].id != id) i++; 
    if (i != size) 
        *this << i;
    else 
        return false;
    return true;
}


template <class T>
class BTree {
private:
    Node<T>* root;          

    
    void rotate_left(Node<T>*, Node<T>*, int);
    void rotate_right(Node<T>*, Node<T>*, int);
    void rotate(Node<T>*, Node<T>*, int, int);
    int binary_search_by_id(Node<T>*, int, bool);
    int get_index_to_insertion(Node<T>*, Element<T>);
    Node<T>* insertion(Node<T>*, Node<T>*, int);

public:
    
    BTree() { root = new Node<T>;}

    
    Element<T>* find_element_by_id(int, Node<T>* = NULL, bool = true);
    Node<T>* insert_element(Element<T>, Node<T>* = NULL, bool = true);
    Node<T>* split(Element<T>, Node<T>*, Node<T>* = NULL, Node<T>* = NULL);
    Node<T>* remove_element(int, Node<T>* = NULL, bool = true);
    Node<T>* fusion(Node<T>*, Node<T>*, Node<T>*, int);
    void print_tree(Node<T>* = NULL, bool = true, int = 0);
};

template <class T>
int BTree<T>::get_index_to_insertion(Node<T>* root, Element<T> element){
    int i = 0;
    while(i < root->size && root->elements[i] < element) ++i;
    return i;
}

template <class T>
int BTree<T>::binary_search_by_id(Node<T>* root, int id, bool exact){
    int i = 0;
    while(i < root->size && root->elements[i].id < id) ++i;
    return ((root->elements[i].id == id && exact) || !exact) ? i : -1;
}

template <class T>
Element<T>* BTree<T>::find_element_by_id(int id, Node<T>* root, bool is_first){
    if(is_first) root = this->root;
    int i = binary_search_by_id(root, id, true);
    if(i != -1) 
        return &(root->elements[i]);
    else if(root->is_leaf) 
        return NULL;
    else { 
        i = binary_search_by_id(root, id, false);
        return find_element_by_id(id, root->p_sons[i], false);
    }
}

template <class T>
Node<T>* BTree<T>::insert_element(Element<T> element, Node<T>* root, bool is_first){
    if (is_first) root = this->root;
    if (root == NULL) root = new Node<T>;
    if (root->is_leaf)
        if (root->max_size > root->size){ 
            root->insert_element(element);
            return root;
        }
        else 
            return split(element, root);
    else {
        
        int i = get_index_to_insertion(root, element);
        Node<T>* temp = insert_element(element, root->p_sons[i], false);
        if (temp->size == 1){ 
            if(root->size == root->max_size) 
                return split(temp->elements[0], root, temp->p_sons[0], temp->p_sons[1]);
            root = insertion(root, temp, i); 
        }
    }
    return root;
}

template <class T>
Node<T>* BTree<T>::insertion(Node<T>* root, Node<T>* temp, int i){
    root->shift_right_pointers(i); 
    *root >> i; 
    root->elements[i] = temp->elements[0]; 
    root->p_sons[i] = temp->p_sons[0]; 
    root->p_sons[i+1] = temp->p_sons[1]; 
    return root;
}


template <class T>
Node<T>* BTree<T>::split(Element<T> element, Node<T>* root, Node<T>* left_son, Node<T>* right_son){
    root->set_is_leaf(false); 
    
    Element<T> temp_elements [root->size+1]; 
    bool in_temp = false;
    int i, j;
    for(i=0, j=0; i<root->size+1; i++)
        if(root->elements[i] > element && !in_temp){
            temp_elements[i] = element;
            in_temp = true;
        } else
            temp_elements[i] = root->elements[j++];
    if(!in_temp) temp_elements[i-1] = element; 

    
    Node<T>* temp_p [root->size+2]; 
    for(int k=0, l=0; k<root->size+2; k++)
        if(temp_elements[k] == element){
            temp_p[k++] = left_son;
            temp_p[k] = right_son;
        } else
            temp_p[k] = root->p_sons[l++];

    
    int new_size = root->size+1;
    int size_left = (new_size % 2 == 0) ? new_size/2-1 : new_size/2;
    int size_right = new_size/2;
    root->clear_elements();
    root->insert_element(temp_elements[size_left]); 
    
    root->p_sons[0] = new Node<T>(size_left, temp_elements, temp_p);
    root->p_sons[1] = new Node<T>(size_right, temp_elements+size_left+1, temp_p+size_left+1);

    return root;
}




template <class T>
void BTree<T>::rotate_right(Node<T>* root, Node<T>* node, int i){
    Node<T>* giver = root->p_sons[i-1]; 
    node->insert_element(root->elements[i-1]);
    int j, tam = (giver->size - root->max_size/2)/2 -
                 (giver->size % 2 == 0) ? 1 : 0;
    for (j=giver->size-1; j<giver->size-tam-1; j--){
        
        node->insert_element(giver->elements[j]);
        giver->remove_element(giver->elements[j].id); 
    }
    root->elements[i-1] = giver->elements[j]; 
    giver->remove_element(giver->elements[j].id); 
}

template <class T>
void BTree<T>::rotate_left(Node<T>* root, Node<T>* node, int i){
    Node<T>* giver = root->p_sons[i+1];
    node->insert_element(root->elements[i]);
    int j, tam = (giver->size - root->max_size/2)/2 -
                 (giver->size % 2 == 0) ? 1 : 0;
    for (j=0; j<tam; j++){
        
        node->insert_element(giver->elements[j]);
        giver->remove_element(giver->elements[j].id); 
    }
    root->elements[i] = giver->elements[j];
    giver->remove_element(giver->elements[j].id); 
}


template <class T>
Node<T>* BTree<T>::fusion(Node<T>* root, Node<T>* l_node, Node<T>* r_node, int i){
    
    int index_p = l_node->size+1;
    Element<T> insertion = root->elements[i];

    
    *root << i; root->shift_left_pointers(i+1);
    l_node->insert_element(insertion);

    
    for (int i=0; i<r_node->size; i++)
        l_node->insert_element(r_node->elements[i]);

    
    for(int i=0; i<=r_node->size; i++)
        l_node->p_sons[index_p++] = r_node->p_sons[i];


    return l_node;
}

template <class T>
Node<T>* BTree<T>::remove_element(int id, Node<T>* root, bool is_first){
    if (is_first) root = this->root;
    if (!root) return NULL;
    int i = binary_search_by_id(root, id, true); 
    Node<T>* node = NULL; 
    if(i != -1) { 
        if(root->is_leaf)
            root->remove_element(id);
        else {
            
            node = root->p_sons[i+1]; 
            
            while (node && !node->is_leaf)
                node = node->p_sons[0];

            Element<T> son = node->elements[0];
            root->elements[i] = son;
            
            remove_element(son.id, root->p_sons[i+1], false);
        }
    } else { 
        i = binary_search_by_id(root, id, false); 
        node = remove_element(id, root->p_sons[i], false);
        if (root->p_sons[i] != node)
            root = root->p_sons[i]; 
    }
    
    
    if (node && node->size < node->max_size/2) {
        
        
        i=0; while(root->p_sons[i] != node) i++; 
        
        if (i > 0 && root->p_sons[i-1]->size > root->max_size/2){
            
            rotate_right(root, node, i);
        
        } else if (i < root->size && root->p_sons[i+1]->size > root->max_size/2){
            
            rotate_left(root, node, i);
        } else if (i > 0 && root->p_sons[i-1]->size == root->max_size/2){
            
            node = fusion(root, root->p_sons[i-1], node, i-1);
        } else if (i < root->size && root->p_sons[i+1]->size == root->max_size/2){
            
            node = fusion(root, node, root->p_sons[i+1], i);
        }
        if (root->size == 0) this->root = node;
    }
    return root;
}

template <class T>
void BTree<T>::print_tree(Node<T>* node, bool is_first, int k){
    if(is_first) node = this->root;
    if(node != NULL){
        int j=0;
        cout << endl;
        while(k > j){ cout << "    "; j++;}
        node->print_elements();
        for(int i=0; i<node->size+1; i++){ 
            print_tree(node->p_sons[i], false, k+1);
        }
    }
}

Element<int> create_element(int id){
    Element<int> e(id, rand()%100+1);
    return e;
}

int main(){
    BTree<int> node;
    srand(time(NULL));

    cout << endl << "===== Inserindo 1, 3, 4, 5, 7 =====" << endl;
    node.insert_element(create_element(1));
    node.insert_element(create_element(3));
    node.insert_element(create_element(4));
    node.insert_element(create_element(5));
    node.insert_element(create_element(7));
    node.print_tree();
    cout << endl << "===== Inserindo 10, 11, 13 =====" << endl;
    node.insert_element(create_element(10));
    node.insert_element(create_element(11));
    node.insert_element(create_element(13));
    node.print_tree();
    cout << endl << "===== Inserindo 14, 15, 16 =====" << endl;
    node.insert_element(create_element(14));
    node.insert_element(create_element(15));
    node.insert_element(create_element(16));
    node.print_tree();
    cout << endl << "===== Inserindo 18, 19, 20 =====" << endl;
    node.insert_element(create_element(18));
    node.insert_element(create_element(19));
    node.insert_element(create_element(20));
    node.print_tree();
    cout << endl << "===== Inserindo 21, 22, 24 =====" << endl;
    node.insert_element(create_element(21));
    node.insert_element(create_element(22));
    node.insert_element(create_element(24));
    node.print_tree();
    cout << endl << "===== Inserindo 25, 26, 27 =====" << endl;
    node.insert_element(create_element(25));
    node.insert_element(create_element(26));
    node.insert_element(create_element(27));
    node.print_tree();
    cout << endl << "===== Inserindo 28 =====" << endl;
    node.insert_element(create_element(28));
    node.print_tree();
    cout << endl << "===== Removendo 14 =====" << endl;
    node.remove_element(14);
    node.print_tree();
    cout << endl << "===== Removendo 5 =====" << endl;
    node.remove_element(5);
    node.print_tree();
    cout << endl << "===== Removendo 4 =====" << endl;
    node.remove_element(4);
    node.print_tree();
    cout << endl << "===== Removendo 3 =====" << endl;
    node.remove_element(3);
    node.print_tree();
    cout << endl << "===== Removendo 1 =====" << endl;
    node.remove_element(1);
    node.print_tree();
}
