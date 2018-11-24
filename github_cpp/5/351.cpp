#include "avl-tree.h"

AVL_tree::AVL_tree(int k){
    key=k;
    height=1;
    left=0;
    right=0;
}

AVL_tree::AVL_tree(AVL_tree* p){
    this->key=p->key;
    this->left=p->left;
    this->right=p->right;
    this->height=p->get_height();
}

//Поиск элемента.
AVL_tree* AVL_tree::find (int k){
    if (this==0){
        return 0;
    }
    if (k==this->key){
        return this;
    }
    if (k<this->key){
        return (this->left)->find(k);
    } else{
        return (this->right)->find(k);
    }
}

//Размеры дерева.
unsigned int AVL_tree::get_height(){
    if (this==0){
        return 0;
    }
    return this->height;
}

void AVL_tree::fix_height(){
    unsigned int hl=this->left->get_height();
    unsigned int hr=this->right->get_height();
    this->height =( (hl>hr?hl:hr) + 1 );
}

int AVL_tree::balance_factor(){
    return (this->right->get_height() - this->left->get_height());
}

//Балансировка.
AVL_tree* AVL_tree::turn_right(){
    AVL_tree* q=this->left;
    if (q==0){
        return this;
    }
    this->left=q->right;
    q->right=this;
    this->fix_height();
    q->fix_height();

    return q;
}

AVL_tree* AVL_tree::turn_left(){
    AVL_tree* q=this->right;
    if (q==0){
        return this;
    }
    this->right=q->left;
    q->left=this;
    this->fix_height();
    q->fix_height();

    return q;
}

AVL_tree* AVL_tree::balance(){
    this->fix_height();
    if (this->balance_factor()==2){
        if ( this->right->balance_factor() < 0){
            this->right=this->right->turn_right();
        }
        return this->turn_left();
    }
    if (this->balance_factor()==-2){
        if ( this->left->balance_factor() > 0){
            this->left=this->left->turn_left();
        }
        return this->turn_right();
    }
    return this;
}

//Вставка элемента.
AVL_tree* AVL_tree::insert_key(int k){
    if (this->find(k) != 0){
        cout<<"This key ("<< (this->find(k))->key <<") is already in tree.\n";
        return this->find(k);
    } else{
        if (this==0){
            return new AVL_tree(k);
        }
        if (k<this->key){
            this->left=this->left->insert_key(k);
        } else{
            this->right=this->right->insert_key(k);
        }
        return this->balance();
    }
}

//Печать дерева. Дерево как бы лежит на боку (растет слева направо).
void AVL_tree::print_tree(int level){
    if(this){
        this->right->print_tree(level+1);
        for (int i=0; i<level; i++)
            cout<<"   ";
        cout<<this->key<<endl;
        this->left->print_tree(level+1);
    }
}

//Обходы деревьев.
//Прямой.
vector<int> AVL_tree::PreOrder(vector<int> path){
    path.push_back(this->key);
    if(this->left)
        path=this->left->PreOrder(path);
    if(this->right)
        path=this->right->PreOrder(path);
    return path;
}

//Обратный.
vector<int> AVL_tree::PostOrder(vector<int> path){
    if(this->left){
        path=this->left->PostOrder(path);
    }
    if(this->right){
        path=this->right->PostOrder(path);
    }
    path.push_back(this->key);
    return path;
}

//Симметричный
vector<int> AVL_tree::InOrder(vector<int> path){
    if(this->left){
        path=this->left->InOrder(path);
    }
    path.push_back(this->key);
    if(this->right){
        path=this->right->InOrder(path);
    }
    return path;
}

//В ширину.
vector<int> AVL_tree::LevelOrder(){
    vector<int> path;
    queue<AVL_tree> q;
    q.push(this);
    while(!q.empty()){
        AVL_tree* p=&q.front();
        path.push_back(p->key);

        if (p->left && p->right){
            q.push(p->left);
            q.push(p->right);
        } else
        if (p->left){
            q.push(p->left);
        } else
        if (p->right){
            q.push(p->right);
        }

        q.pop();
    }
    return path;
}

//Объединение деревьев.
AVL_tree* AVL_tree::union_tree(AVL_tree A){
    vector<int> vec;
    vec=A.PreOrder(vec);
    AVL_tree* t=this->insert_key(vec[0]);
    for(unsigned int i=1; i<vec.size(); i++){
        if(t->find(vec[i])==0)
            t=t->insert_key(vec[i]);
    }
    return t;
}

//Удаление элемента.
AVL_tree* AVL_tree::del_minus1234(){
    if ( this->right->key==-1234 ){
        this->right=0;
        return this;
    } else
        return this->right->del_minus1234();
}

int AVL_tree::find_max(){
    if (this->right){
        return this->right->find_max();
    }
    else{
        return this->key;
    }
}

vector<int> AVL_tree::subtree_max(){
    int max=this->find_max();
    AVL_tree* Max=this->find(max);
    vector<int> subtree_m=Max->LevelOrder();
    vector<int> subtree;
    for (unsigned int i=1; i<subtree_m.size(); i++){
        subtree.push_back(subtree_m[i]);
    }
    return subtree;
}

AVL_tree* AVL_tree::delete_key(int k){
    if (this==0) return 0;
    if (this->find(k) != 0){                                //Проверяем, есть ли элемент в дереве.
        if (k < this->key)                                  //Поиск элемента.
            this->left= this->left->delete_key(k);
        else if (k > this->key)
            this->right= this->right->delete_key(k);
        else if(k==this->key){                              //Элемент найден.
            AVL_tree* Left=this->left;
            AVL_tree* Right=this->right;

            if (Left!=0 && Right!=0){                       //Если существуют оба поддерева.
                int new_root=Left->find_max();              //Максимальный элемент левого поддерева (new_root) - новый корень вместо удаляемого.

                vector<int> subtree=Left->subtree_max();    //Запоминаем элементы поддерева с корнем new_root (они есть только слева, т.к. элемент максимальный справа ничего быть не может)

                Left->find(new_root)->key=-1234;            //Удаляем элемент new_root из дерева.
                if (Left->key == -1234){
                    this->left=0;
                } else{
                    this->left->del_minus1234();
                }

                this->key=new_root;

                AVL_tree* Tree=this->balance();           //Сбалансируем дерево.

                for (unsigned int i=0; i<subtree.size(); i++){
                    Tree=Tree->insert_key(subtree[i]);      //Добавим в дерево недостающие элементы, которые мы запомнили раннее и сбалансируем дерево.
                }

                return Tree;
            } else if (Left==0 && Right==0){
                delete this;
                return 0;
            } else if (Right==0 && Left!=0){
                this->key=Left->key;
                this->right=Left->right;
                this->left=Left->left;
                delete Left;
                return this->balance();

            } else if (Left==0 && Right!=0){
                this->key=Right->key;
                this->left=Right->left;
                this->right=Right->right;
                delete Right;
                return this->balance();
            }
        }
        return this->balance();
    }
    else return 0;
}
