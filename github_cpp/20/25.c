







#include <iostream>

#include "red_black_tree.hpp"           

using namespace std;




red_black_tree::red_black_tree(){
    root=NULL;
};


void red_black_tree::insert_from_sorted_list(int id[],int count[],int start,int end,int height){
    root=sorted_insert(id,count,start,end,height);
    
    
    if(root)
        root->color='b';
};


node* red_black_tree::sorted_insert(int i[],int c[],int s,int e,int h){
    node *t=NULL;
    if(s<=e){
        int m=(s+e)/2;                      
        t=new node(i[m],c[m]);              
        if(h==1)                            
            t->color='r';
        t->l=sorted_insert(i,c,s,m-1,h-1);  
        if(t->l)                            
            t->l->p=t;
        t->r=sorted_insert(i,c,m+1,e,h-1);  
        if(t->r)                            
            t->r->p=t;
    }
    return t;
};


int red_black_tree::increase(int id,int m){
    node *t=search(id);             
    int count=m;                    
    if(t){                          
        t->count+=m;                
        count=t->count;             
    }
    else{                           
        node *temp=new node(id,m);  
        temp->color='r';            
        insert(temp);               
    }
    return count;                   
};


void red_black_tree::insert(node *t){
    if(!root){                      
        root=t;
        root->color='b';
    }
    else{
        
        
        node *next=root;
        node *prev;
        do{                     
            prev=next;
            if(next->ID>t->ID)
                next=next->l;
            else
                next=next->r;
        }while(next);
        if(prev->ID>t->ID)      
            prev->l=t;
        else
            prev->r=t;
        t->p=prev;              
        
        
        
        if(t->p->color=='r'){
            char c;                 
            node *parent,*gparent;  
            parent=t->p;
            gparent=parent->p;
            if(gparent->l==parent){ 
                if(gparent->r!=NULL)
                    c=gparent->r->color;
                else
                    c='b';
            }
            else{
                if(gparent->l!=NULL)
                    c=gparent->l->color;
                else
                    c='b';
            }
            
            
            
            
            
            while(c=='r'&&parent&&gparent){
                parent->color='b';      
                gparent->color='r';     
                if(gparent->l==parent&&gparent->r!=NULL)    
                    gparent->r->color='b';
                else if(gparent->r==parent&&gparent->l!=NULL)
                    gparent->l->color='b';
                root->color='b';
                
                
                if(gparent->p&&gparent->p->color=='r'){
                    t=gparent;
                    parent=t->p;
                    gparent=parent->p;
                    if(gparent->l==parent){
                        if(gparent->r!=NULL)
                            c=gparent->r->color;
                        else
                            c='b';
                    }
                    else{
                        if(gparent->l!=NULL)
                            c=gparent->l->color;
                        else
                            c='b';
                    }
                }
                else    
                    gparent=NULL;
            }
            
            
            if(gparent&&c=='b'){
                
                if(parent->l==t&&gparent->l==parent){
                    if(gparent->p){                 
                        if(gparent->p->l==gparent)
                            gparent->p->l=parent;
                        else
                            gparent->p->r=parent;
                        parent->p=gparent->p;
                    }
                    else{
                        root=parent;
                        parent->p=NULL;
                    }
                    gparent->l=parent->r;
                    if(parent->r)
                        parent->r->p=gparent;
                    gparent->p=parent;
                    parent->r=gparent;
                    parent->color='b';
                    gparent->color='r';
                }
                
                else if(parent->r==t&&gparent->r==parent){
                    if(gparent->p){                 
                        if(gparent->p->l==gparent)
                            gparent->p->l=parent;
                        else
                            gparent->p->r=parent;
                        parent->p=gparent->p;
                    }
                    else{
                        root=parent;
                        parent->p=NULL;
                    }
                    gparent->r=parent->l;
                    if(parent->l)
                        parent->l->p=gparent;
                    gparent->p=parent;
                    parent->l=gparent;
                    parent->color='b';
                    gparent->color='r';
                }
                
                else if(parent->r==t&&gparent->l==parent){
                    if(gparent->p){                 
                        if(gparent->p->l==gparent)
                            gparent->p->l=t;
                        else
                            gparent->p->r=t;
                        t->p=gparent->p;
                    }
                    else{
                        root=t;
                        t->p=NULL;
                    }
                    gparent->l=t->r;
                    if(t->r)
                        t->r->p=gparent;
                    gparent->p=t;
                    t->r=gparent;
                    parent->r=t->l;
                    if(t->l)
                        t->l->p=parent;
                    parent->p=t;
                    t->l=parent;
                    t->color='b';
                    gparent->color='r';
                }
                
                else{
                    if(gparent->p){                 
                        if(gparent->p->l==gparent)
                            gparent->p->l=t;
                        else
                            gparent->p->r=t;
                        t->p=gparent->p;
                    }
                    else{
                        root=t;
                        t->p=NULL;
                    }
                    gparent->r=t->l;
                    if(t->l)
                        t->l->p=gparent;
                    gparent->p=t;
                    t->l=gparent;
                    parent->l=t->r;
                    if(t->r)
                        t->r->p=parent;
                    parent->p=t;
                    t->r=parent;
                    t->color='b';
                    gparent->color='r';
                }
            } 
        } 
    } 
};


int red_black_tree::reduce(int id,int m){
    node *t=search(id);             
    int count=0;                    
    if(t){                          
        if(t->count>m){             
            t->count-=m;
            count=t->count;         
        }
        else                        
            remove(t);
    }
    return count;                   
};


void red_black_tree::remove(node *t){
    if(!t)                          
        return;
    
    
    if(t->l&&t->r){
        node *n=next(t);
        int x,y;
        x=n->ID;
        y=n->count;
        n->ID=t->ID;
        n->count=t->count;
        t->ID=x;
        t->count=y;
        t=n;
    }
    
    
    if(t==root){
        if(root->l)
            root=root->l;
        else
            root=root->r;
        root->p=NULL;
        if(root)
            root->color='b';
        return;
    }
    
    
    node *parent,*y,*s;
    parent=t->p;
    if(parent->l==t)
        s=parent->r;
    else
        s=parent->l;
    if(t->l){               
        if(parent->l==t)
            parent->l=t->l;
        else
            parent->r=t->l;
        y=t->l;
        y->p=parent;
    }
    else if(t->r){          
        if(parent->l==t)
            parent->l=t->r;
        else
            parent->r=t->r;
        y=t->r;
        y->p=parent;
    }
    else{                   
        if(parent->l==t)
            parent->l=NULL;
        else
            parent->r=NULL;
        y=NULL;
    }
    
    
    if(t->color=='r')
        return;
    
    
    if(t->color=='b'&&y&&y->color=='r'){
        y->color='b';
        return;
    }
    
    
    
    
    int n=0;
    if(s->l&&s->l->color=='r')
        ++n;
    if(s->r&&s->r->color=='r')
        ++n;
    
    
    while(s->color=='b'&&n==0&&parent->color=='b'){
        s->color='r';
        
        
        y=parent;
        if(y->p)
            parent=y->p;
        else
            return;
        if(parent->l==y)
            s=parent->r;
        else
            s=parent->l;
        if(!s)
            return;
        n=0;
        if(s->l&&s->l->color=='r')
            ++n;
        if(s->r&&s->r->color=='r')
            ++n;
    }
    
    
    if(s->color=='b'&&n==0&&parent->color=='r'){
        parent->color='b';
        s->color='r';
        return;
    }
    
    
    if(s->color=='b'&&n!=0){
        if(s->p->l==s){
            
            if(s->r&&s->r->color=='r'){
                node *w=s->r;
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=w;
                    else
                        parent->p->r=w;
                    w->p=parent->p;
                }
                else{
                    root=w;
                    w->p=NULL;
                }
                w->color=parent->color;
                parent->color='b';
                parent->l=w->r;
                if(w->r)
                    w->r->p=parent;
                w->r=parent;
                parent->p=w;
                s->r=w->l;
                if(w->l)
                    w->l->p=s;
                w->l=s;
                s->p=w;
            }
            
            else{
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=s;
                    else
                        parent->p->r=s;
                    s->p=parent->p;
                }
                else{
                    root=s;
                    s->p=NULL;
                }
                parent->l=s->r;
                if(s->r)
                    s->r->p=parent;
                parent->p=s;
                s->r=parent;
                s->color=parent->color;
                parent->color='b';
                s->l->color='b';
            }
        }
        else{
            
            if(s->l&&s->l->color=='r'){
                node *w=s->l;
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=w;
                    else
                        parent->p->r=w;
                    w->p=parent->p;
                }
                else{
                    root=w;
                    w->p=NULL;
                }
                w->color=parent->color;
                parent->color='b';
                parent->r=w->l;
                if(w->l)
                    w->l->p=parent;
                w->l=parent;
                parent->p=w;
                s->l=w->r;
                if(w->r)
                    w->r->p=s;
                w->r=s;
                s->p=w;
            }
            
            else{
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=s;
                    else
                        parent->p->r=s;
                    s->p=parent->p;
                }
                else{
                    root=s;
                    s->p=NULL;
                }
                parent->r=s->l;
                if(s->l)
                    s->l->p=parent;
                parent->p=s;
                s->l=parent;
                s->color=parent->color;
                parent->color='b';
                s->l->color='b';
            }
        }
        return;
    }
    
    
    
    
    node *w;
    if(parent->l==s)
        w=s->r;
    else
        w=s->l;
    
    
    n=0;
    if(w->l&&w->l->color=='r')
        ++n;
    if(w->r&&w->r->color=='r')
        ++n;
    
    
    if(n==0){
        
        if(parent->l==s){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=s;
                else
                    parent->p->r=s;
                s->p=parent->p;
            }
            else{
                root=s;
                s->p=NULL;
            }
            parent->l=s->r;
            if(s->r)
                s->r->p=parent;
            parent->p=s;
            s->r=parent;
            s->color='b';
            if(parent->l)
                parent->l->color='r';
        }
        
        else if(parent->r==s){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=s;
                else
                    parent->p->r=s;
                s->p=parent->p;
            }
            else{
                root=s;
                s->p=NULL;
            }
            parent->r=s->l;
            if(s->l)
                s->l->p=parent;
            parent->p=s;
            s->l=parent;
            s->color='b';
            if(parent->r)
                parent->r->color='r';
        }
        return;
    }
    
    if(n==1){
        
        if(parent->l==s&&(!w->r||w->r->color=='b')){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=w;
                else
                    parent->p->r=w;
                w->p=parent->p;
            }
            else{
                root=w;
                w->p=NULL;
            }
            parent->l=w->r;
            if(w->r)
                w->r->p=parent;
            w->r=parent;
            parent->p=w;
            s->r=w->l;
            if(w->l){
                w->l->p=s;
                w->l->color='b';
            }
            w->l=s;
            s->p=w;
        }
        
        else if(parent->r==s&&(!w->l||w->l->color=='b')){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=w;
                else
                    parent->p->r=w;
                w->p=parent->p;
            }
            else{
                root=w;
                w->p=NULL;
            }
            parent->r=w->l;
            if(w->l)
                w->l->p=parent;
            w->l=parent;
            parent->p=w;
            s->l=w->r;
            if(w->r){
                w->r->p=s;
                w->r->color='b';
            }
            w->r=s;
            s->p=w;
        }
        return;
    }
    
    
    if(parent->l==s&&(!w->r||w->r->color=='r')){
        node *x=w->r;
        if(parent->p){
            if(parent->p->l==parent)
                parent->p->l=x;
            else
                parent->p->r=x;
            x->p=parent->p;
        }
        else{
            root=x;
            x->p=NULL;
        }
        w->r=x->l;
        if(x->l)
            x->l->p=w;
        parent->l=x->r;
        if(x->r)
            w->r->r->p=parent;
        x->l=s;
        s->p=x;
        x->r=parent;
        parent->p=x;
    }
    
    else if(parent->r==s&&(!w->l||w->l->color=='r')){
        node *x=w->l;
        if(parent->p){
            if(parent->p->l==parent)
                parent->p->l=x;
            else
                parent->p->r=x;
            x->p=parent->p;
        }
        else{
            root=x;
            x->p=NULL;
        }
        w->l=x->r;
        if(x->r)
            x->r->p=w;
        parent->r=x->l;
        if(x->l)
            x->l->p=parent;
        x->r=s;
        s->p=x;
        x->l=parent;
        parent->p=x;
    }
};


int red_black_tree::count(int id){
    node *t=search(id);         
    if(t)                       
        return t->count;
    return 0;                   
};


int red_black_tree::inrange(int id1,int id2){
    return inrange_recursive(root,id1,id2);     
};


int red_black_tree::inrange_recursive(node *t,int i1,int i2){
    int sum=0;                  
    if(t){
        if(t->ID>i1)            
            sum+=inrange_recursive(t->l,i1,i2);
        if(t->ID>=i1&&t->ID<=i2)
            sum+=t->count;
        if(t->ID<i2)            
            sum+=inrange_recursive(t->r,i1,i2);
    }
    return sum;
};


node* red_black_tree::search(int id){
    if(root){
        node *t=root;
        do{
            if(t->ID==id)           
                return t;
            if(t->ID>id&&t->l)      
                t=t->l;
            else if(t->ID>id)       
                break;
            else if(t->ID<id&&t->r) 
                t=t->r;
            else if(t->ID<id)       
                break;
        }while(t);
    }
    return NULL;                    
};


node* red_black_tree::search_next(int id){
    node *t=root;
    if(root){
        do{
            if(t->ID>id&&t->l)      
                t=t->l;
            else if(t->ID>=id)       
                break;
            else if(t->ID<id&&t->r) 
                t=t->r;
            else if(t->ID<=id)       
                break;
        }while(t);
    }
    if(t&&t->ID<id)                 
        t=next(t);
    if(t->ID==id)
        t=NULL;
    return t;
};


node* red_black_tree::search_previous(int id){
    node *t=root;
    if(root){
        do{
            if(t->ID>id&&t->l)      
                t=t->l;
            else if(t->ID>=id)       
                break;
            else if(t->ID<id&&t->r) 
                t=t->r;
            else if(t->ID<=id)       
                break;
        }while(t);
    }
    if(t&&t->ID>id)                 
        t=previous(t);
    if(t->ID==id)
        t=NULL;
    return t;
};


node* red_black_tree::getroot(){
    return root;
};


node* red_black_tree::next(node *t){
    if(t&&t->r!=NULL){              
        t=t->r;                     
        while(t->l!=NULL)
            t=t->l;
        return t;
    }
    else if(t){                     
        while(t->p&&t->p->r==t)     
            t=t->p;
        if(t->p)
            return t->p;
    }
    return NULL;
};


node* red_black_tree::previous(node *t){
    if(t&&t->l!=NULL){         
        t=t->l;                
        while(t->r!=NULL)
            t=t->r;
        return t;
    }
    else if(t){                
        while(t->p&&t->p->l==t)
            t=t->p;
        if(t->p)
            return t->p;
    }
    return NULL;
};




void red_black_tree::display(node *t,int n,char c){
    if(!t)
        return;
    for(int i=0;i<n;++i)
        cout<<".";
    cout<<t->ID<<"("<<c<<","<<t->count<<","<<t->color<<") has";
    if(t->p)
        cout<<" "<<t->p->ID<<" as parent ";
    if(t->l)
        cout<<" "<<t->l->ID<<" as left child ";
    if(t->r)
        cout<<" "<<t->r->ID<<" as right child ";
    cout<<"\n";
    
    display(t->l,n+1,'L');
    display(t->r,n+1,'R');
};


int red_black_tree::max_height(node *t){
    int h=0;
    if(t){
        h=1+max(max_height(t->l),max_height(t->r));
    }
    return h;
};


void red_black_tree::color(node *t,int h){
    if(t){
        if(h==1)
            t->color='r';
        else
            t->color='b';
        color(t->l,h-1);
        color(t->r,h-1);
    }
};
