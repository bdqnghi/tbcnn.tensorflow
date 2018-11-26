#include<iostream>
#include<string>
using namespace std;

#define M 4

//test
typedef struct{
    int num;
    string name;
    string auth;
    int current;
    int total;
}book;

typedef struct node{
    int coun;
    book  key[M];
    struct node *child[M+1];
    struct node *prt;
}BTNode;

typedef struct{
    int inpoint;
    BTNode *pono;
    int _findit;
}Dest;

Dest *findtree(BTNode *tree,int a)
{
    int  i ;
    Dest *p = NULL;

    if(tree != NULL){
        for(i = 0; i < tree->coun ;i++){
            if(a == tree ->key[i].num){
                p = new Dest;
                p ->inpoint = i;
                p ->pono = tree;
                p ->_findit = 1;
                cout <<"find it"<<endl;
                //p ->_findit = 1;
                return p;
            }
            else if(a < tree ->key[i].num){
                        if(tree ->child[i] != NULL){
                            p = findtree(tree ->child[i],a);
                            break;
                        }
                        else{
                            p = new Dest;
                            p ->pono = tree;
                            p ->inpoint = i;
                            p ->_findit = 0;
                            return p;
                        }
                 }
    }
    if(i == tree ->coun){
        if(tree ->child[i] != NULL)
            p = findtree(tree ->child[i],a);
        else{
                p = new Dest;
                p ->inpoint = i;
                p ->pono = tree;
                p ->_findit = 0;
        }
        }
    }
    return p;
}

void splittree(BTNode *p)
{
    BTNode *q,*h;
    if(p ->prt != NULL){
            //cout<<p ->prt->coun<<"  "<<p ->prt->key[0].num<<endl;
        int i;
        for(i =0;i < p ->prt ->coun;i++)
            if(p ->key[M/2].num < p ->prt ->key[i].num)
                break;
        for(int a = p ->prt->coun; a > i; a--){

            p ->prt ->key[a] = p ->prt ->key[a-1];
            p ->prt ->child[a+1] = p ->prt ->child[a];

        }
        p ->prt ->key[i] = p ->key[M/2];

        h = new BTNode;
        h ->coun = M-1-M/2;
        h ->key[0] = p ->key[M-1];
        h ->child[0] = p ->child[M-1];
        h ->child[1] = p ->child[M];
        if(h ->child[0] != NULL)
        {
            h ->child[0] ->prt = h;
            h ->child[1] ->prt = h;
        }
        h ->prt  = p ->prt;

        q = new BTNode;
        for(int i = 0;i < M/2;i++){
            q ->key[i] = p ->key[i];
            q ->child[i] = p ->child[i];
            if(q ->child[i] != NULL)
                q ->child[i] ->prt = q;
        }
        q ->coun =  M/2;
        q ->child[M/2] = p ->child[2];
        if(q ->child[M/2] != NULL)
            q ->child[M/2] ->prt = q;
        q ->prt = p ->prt;

        p ->prt ->coun++;
        p ->prt ->child[i] = q;
        p ->prt ->child[i+1]    = h;
        //cout << q ->prt ->key[0].num<<"  "<<h ->prt ->key[0].num<<endl;
        //delete p;

        if(p ->prt ->coun == M)
            splittree(p  ->prt);
        delete p;
    }
    else{
            h = new BTNode;
            q = new BTNode;
            q ->coun = M/2;
            for(int i = 0;i < M/2;i++){
                q ->key[i] = p ->key[i];
                q ->child[i] = p ->child[i];
            }

            q ->child[M/2] = p ->child[2];
            if(q ->child[0] != NULL)
                for(int i = 0; i<= q ->coun ;i++)
                    q ->child[i] ->prt =q;

            q ->prt = p ;
            h ->coun = M-1-M/2;
            h ->key[0] = p ->key[M-1];
            h ->child[0] = p ->child[M-1];
            h ->child[1] = p ->child[M];
            h ->prt  = p ;
            if(h ->child[0] != NULL)
            {
                h ->child[0] ->prt = h;
                h ->child[1] ->prt = h;
            }
            if(h ->child[0] != NULL)
                for(int i = 0; i<= h ->coun ;i++)
                    h ->child[i] ->prt =h;

            p ->coun = 1;
            //p ->prt = NULL;
            p ->key[0] = p ->key[M/2];
            p ->child[0] = q;
            p ->child[1] = h;
            //cout << q ->prt ->key[0].num<<"  "<<h ->prt ->key[0].num<<endl;
    }
}

void show(BTNode *p,int n)
{
    int a;
    if(p  == NULL)
    {
        cout <<"EMPTY!"<<endl<<endl;
        return;
    }
    if(p ->child[0] != NULL){

        for(int i = p ->coun;i >= 0;i--){
            a = n+1;
            show(p ->child[i],a);
            if(i != 0){
                for(int b = 0;b < n-1;b++)
                    cout <<"     ";
                cout<<p ->key[i-1].num<<endl;
            }
        }
    }
    else{
        for(int i = 0;i < n-1;i++)
            cout <<"     ";
        cout <<"--";
        for(int i = 0;i < p ->coun;i++)
            cout << p ->key[i].num<<" ";
        cout <<endl;
    }
}

int insertbtree(BTNode **tree,book a)
{
    BTNode *p;
    Dest *w;
    if(*tree == NULL){
        p = new BTNode;
        if(NULL == p)
            return 1;
        p ->coun = 1;
        p ->prt = NULL;
        p ->key[0] = a;
        for(int i = 0 ;i < M ;i++)
           p ->child[i] = NULL;
        *tree = p;
        return 0;
    }
    else{
            w = findtree(*tree,a.num);
            if(w ->_findit == 1 ){
                cout << "This book has been existed."<<endl<<endl;
                return -1;
            }
            w ->pono ->coun++;
            for(int i = w ->pono ->coun; i > w ->inpoint; i--){
                if(i < w ->pono ->coun)
                    w ->pono ->key[i] = w ->pono ->key[i-1];
                w ->pono ->child[i] = w ->pono ->child[i-1];
            }
            w ->pono ->key[w ->inpoint] = a;
            w ->pono ->child[w ->inpoint] = NULL;
            //for(int i = 0;i < 4;i++)
            if(w ->pono ->coun == M)
                splittree(w ->pono);
        }
    return 0;
}

void borroewBTtree(Dest *w){
    int i;
    //Dest *w = p;
    for(i = 0;i <= w ->pono ->prt ->coun;i++){
        if(w ->pono ->prt ->child[i] == w ->pono)
            break;
    }
    if(i == w ->pono ->prt ->coun)
    {
        if(w ->pono ->prt ->child[i-1]->coun > M/2-1)
        {
            w ->pono ->key[0] = w ->pono ->prt ->key[i-1];
            w ->pono ->coun ++;
            w ->pono ->prt ->key[i-1] = w ->pono ->prt ->child[i-1]->key[w ->pono ->prt ->child[i-1] ->coun-1];
            if(w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1] ->coun] != NULL && w ->pono ->child[0] != NULL)
            {
                if(w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1] ->coun] ->key[0].num < w ->pono ->child[0] ->key[0].num)
                {
                    w ->pono ->child[1] = w ->pono ->child[0];
                    w ->pono ->child[0] = w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1] ->coun];
                    w ->pono ->child[0] ->prt = w ->pono;
                }
                else
                    w ->pono ->child[1] = w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1] ->coun];
            }
            else
                w ->pono ->child[w ->pono ->coun-1] = w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1] ->coun];
            w ->pono ->prt ->child[i-1] ->coun--;
        }
        else
            if(w ->pono ->prt ->child[i-1]->coun == M/2-1)
        {

            if(w ->pono ->prt ->prt == NULL && w ->pono ->prt ->coun == 1){
                BTNode *b;
                w ->pono ->prt ->coun = w ->pono ->prt ->coun + w ->pono ->prt ->child[0] ->coun;

                w ->pono ->prt ->key[w ->pono ->prt ->coun-1] = w ->pono ->prt ->key[0];

                b = w ->pono ->prt ->child[0];
                for(int i = 0;i < b ->coun;i++){
                    w ->pono ->prt ->key[i] = b ->key[i];
                    w ->pono ->prt ->child[i] = b ->child[i];
                    if(w ->pono ->prt ->child[i] != NULL)
                        w ->pono ->prt ->child[i] ->prt = w ->pono ->prt;
                }
                w ->pono ->prt ->child[b ->coun] = b ->child[b ->coun];
                if(w ->pono ->prt ->child[b ->coun] != NULL)
                    w ->pono ->prt ->child[b ->coun] ->prt = w ->pono ->prt;
                w ->pono ->prt ->child[w ->pono ->prt ->coun] = w ->pono ->child[0];
                if(w ->pono ->prt ->child[w ->pono ->prt ->coun] != 0)
                    w ->pono ->prt ->child[w ->pono ->prt ->coun] ->prt = w ->pono ->prt ;
            }

        else{
            w ->pono ->prt ->child[i-1]->key[M/2-1] = w ->pono ->prt ->key[w ->pono ->prt ->coun -1];
            w ->pono ->prt ->child[i-1]->coun ++;
            w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1]->coun] = w ->pono ->child[0];
            if(w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1]->coun] != NULL)
                w ->pono ->prt ->child[i-1]->child[w ->pono ->prt ->child[i-1]->coun] ->prt = w ->pono ->prt ->child[i-1];

            w ->pono ->prt ->coun --;
            if(w ->pono ->prt ->coun == 0){
                Dest *l = new Dest;
                l ->pono = w ->pono ->prt;
                l ->inpoint = w ->pono ->coun;
                borroewBTtree(l);
            }
        }

        }
    }
    else {
            if(w ->pono ->prt ->child[i+1]->coun > M/2-1)
            {
                w ->pono ->key[0] = w ->pono ->prt ->key[i];
                w ->pono ->coun ++;
                w ->pono ->prt ->key[i] = w ->pono ->prt ->child[i+1] ->key[0];
                w ->pono ->child[w ->pono ->coun] = w ->pono ->prt ->child[i+1] ->child[0];
                if(w ->pono ->child[w ->pono ->coun] != 0)
                    w ->pono ->child[w ->pono ->coun] ->prt = w ->pono;

                w ->pono ->prt ->child[i+1]->coun--;

                for(int a = 0;a < w ->pono ->prt ->child[i+1]->coun;a++)
                {
                    w ->pono ->prt ->child[i+1] ->key[a]   = w ->pono ->prt ->child[i+1]->key[a+1];
                    w ->pono ->prt ->child[i+1] ->child[a] = w ->pono ->prt ->child[i+1] ->child[a+1];
                }
                w ->pono ->prt ->child[i+1] ->child[w ->pono ->prt ->child[i+1] ->coun] = w ->pono ->prt ->child[i+1] ->child[w ->pono ->prt ->child[i+1] ->coun+1];
            }
            else
                if(w ->pono ->prt ->child[i+1]->coun == M/2-1)
                {
                    cout << w ->pono ->key[w ->inpoint].num <<"  "<< w ->pono ->prt ->key[0].num  <<endl;//---------test
                    if(w ->pono ->prt ->prt == NULL && w ->pono ->prt ->coun == 1)
                    {
                        BTNode *b;

                        w ->pono ->prt ->coun = w ->pono ->prt ->coun + w ->pono ->prt ->child[1] ->coun;

                        b = w ->pono ->prt ->child[1];

                        for(int a = 1;a < b ->coun+1;a++){
                            w ->pono ->prt ->key[a] = b ->key[a-1];
                            w ->pono ->prt ->child[a] = b ->child[a-1];
                            if(w ->pono ->prt ->child[a] != NULL)
                                w ->pono ->prt ->child[a] ->prt = w ->pono ->prt;
                        }
                        w ->pono ->prt ->child[w ->pono ->prt ->coun] = b ->child[b ->coun];
                        if(w ->pono ->prt ->child[w ->pono ->prt ->coun] != NULL)
                            w ->pono ->prt ->child[w ->pono ->prt ->coun] ->prt = w ->pono ->prt;
                        w ->pono ->prt ->child[0] = w ->pono ->child[0];
                        if(w ->pono ->prt ->child[0] != NULL)
                            w ->pono ->prt ->child[0] ->prt = w ->pono ->prt;



                    }
                    else{
                        w ->pono ->key[0] = w ->pono ->prt ->key[i] ;
                        w ->pono ->coun ++;
                        w ->pono ->key[w ->pono ->coun] = w ->pono ->prt ->child[i+1] ->key[w ->pono ->prt ->child[i+1] ->coun-1];
                        w ->pono ->coun ++;
                        w ->pono ->child[w ->pono ->coun-1] = w ->pono ->prt ->child[i+1] ->child[0];
                        w ->pono ->child[w ->pono ->coun] = w ->pono ->prt ->child[i+1] ->child[1];
                        if(w ->pono ->child[w ->pono ->coun] != NULL){
                            w ->pono ->child[w ->pono ->coun] ->prt = w ->pono;
                            w ->pono ->child[w ->pono ->coun-1] ->prt = w ->pono;
                        }
                        //cout <<i<<endl;
                        for(int a = i;a < w ->pono ->prt ->coun-1;a++){
                            w ->pono ->prt ->key[a]     = w ->pono ->prt ->key[a+1];
                            w ->pono ->prt ->child[a+1] = w ->pono ->prt ->child[a+2];

                        }
                        w ->pono ->prt ->coun --;
                        if(w ->pono ->prt ->coun == 0){
                            Dest *l = new Dest;
                            l ->pono = w ->pono ->prt;
                            l ->inpoint = w ->pono ->prt ->coun;
                            borroewBTtree(l);
                        }
                    }
                }
    }

}

int deleteBTtree(BTNode *tree,int a)
{
    BTNode *p;
    Dest *w;
    if(tree == NULL){
        cout <<"EMPTY!"<<endl<<endl;
        return -1;
    }
    w = findtree(tree ,a);
    if(w ->_findit == 0){
        cout << "This book dose not exist."<<endl <<endl;
        return -1;
    }
    if(w ->pono ->child[0] == NULL){
        if(w ->pono ->prt == NULL&&w ->pono ->coun > 0)
        {

            for(int i = w ->inpoint;i < w ->pono ->coun-1;i++)
                w ->pono ->key[i] = w ->pono ->key[i+1];
            w ->pono ->coun--;
            cout <<"success"<<endl<<endl;
            return 0;
        }

        for(int i = w ->inpoint;i < w ->pono ->coun-1;i++)
            w ->pono ->key[i] = w ->pono ->key[i+1];
        w ->pono ->coun--;
        if(w ->pono ->coun == 0)
            borroewBTtree(w);

    }
    else {
            p = w ->pono ->child[w ->inpoint+1];
            while(1){
                if(p ->child[0] == NULL)
                    break;
                p = p ->child[0];
            }
            cout<<p ->key[0].num<<endl;//---------------
            w ->pono ->key[w ->inpoint] = p ->key[0];
            for(int i = 0;i < p ->coun-1;i++){
                p ->key[i] = p ->key[i+1];
            }
            p ->coun --;
            if(p ->coun == 0){
                Dest *l = new Dest;
                l ->inpoint = 0;
                l ->pono = p;
                borroewBTtree(l);
            }
    }
    return 0;
}

void Borrow(BTNode *tree)
{
    Dest *w;
    int n = 0,a;
    if(tree == NULL){
        cout <<"EMPTY!"<<endl<<endl;
        return;
    }
    cout <<"print the number of the book:"<<endl;
    cin >>a;
    w = findtree(tree,a);
    if(w ->_findit == 1){
        cout << w ->pono ->key[w ->inpoint].name<<" "<<w ->pono ->key[w ->inpoint].auth<<"  "<<w ->pono ->key[w ->inpoint].current<<"   "<<w ->pono ->key[w ->inpoint].total<<endl;
        if(w ->pono ->key[w ->inpoint].current > 0)
        {
            cout <<"Are you sure borrow this book? 1.ture 2.cancel"<<endl;
            cin >>n;
            if(n == 1)
            {
                w ->pono ->key[w ->inpoint].current--;
                cout <<"success"<<endl<<endl;
                return;
            }

        }
        else
            cout <<"Out of stock!"<<endl<<endl;
    }
    else
        cout <<"This book dose not exist."<<endl<<endl;

}

void revert(BTNode *tree)
{
    Dest *w;
    int a;
    if(tree == NULL){
        cout <<"EMPTY!"<<endl<<endl;
        return;
    }
    cout <<"print the number of the book:"<<endl;
    cin >>a;
    w = findtree(tree,a);
    if(w ->_findit == 1){
        if(w ->pono ->key[w ->inpoint].current < w ->pono ->key[w ->inpoint].total){
            w ->pono ->key[w ->inpoint].current++;
            cout <<"success"<<endl<<endl;
        }
        else cout <<"This book has not yet been borrowed!"<<endl<<endl;
    }
    else
        cout <<"This book dose not exist."<<endl<<endl;
}



int main()
{
    book data[20]={{40,"Harry Potter and the Goblet of Fire","JK Rowling",2,3},{45,"The Bible","frost",1,3},{1002,"The Da Vinci Code","Dan Brown",3,3},{41,"Harry Potter and the Prisoner of Azkaban","JK Rowling",0,3},{30,"The Official Highway Code","Department for Transport",1,3},
    {23,"dgdfg","sdfsdf",2,4},{32,"dfs","cxvkwkr",1,5},{39,"asdad","adfghrth",2,2},{24,"ivbd9g","ihgdif98",4,5},{25,"sfdhiyet","ufu",5,5},{26,"afutr","fdut",1,4},{27,"556ytre0","gfgdr",3,7},{28,"ddfsdfw","dfrw",5,8},{13,"adae","dfweg",4,6},{15,"dwfsxv","ffgevvc",1,8}};
    int n = 0,a;
    //BTNode *p,*l;
    //Dest *w;
    BTNode *root;
    root = NULL;
    while(1){
        cout<<"---book manage system---"<<endl;
        cout <<"    1.print"<<endl<<"    2.delete"<<endl<<"    3.borrow"<<endl<<"    4.restitution"<<endl<<"    5.dispaly"<<endl;
        cout <<"print your choose:"<<endl;
        cin >> a;
        switch(a){

        case 1:
            for(int i = 0;i < 15;i++){
                if(insertbtree(&root,data[i]) == 0)
                    cout <<"successfully!"<<endl;
                    show(root,1);
            }
            cout <<root ->coun;
            cout <<"finish input"<<endl<<endl;
            break;
        case 2:
            cout <<"print the number of the book:"<<endl;
            cin >>n;
            deleteBTtree(root,n);show(root,1);break;
        case 3:Borrow(root);break;
        case 4:revert(root);break;
        case 5: cout <<"the information of books:"<<endl;show(root,1);break;
        default :cout <<"!!!!!"<<endl;break;

    }

    }

    return 0;
}
                    
