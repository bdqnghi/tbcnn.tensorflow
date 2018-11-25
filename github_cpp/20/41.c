







#ifndef red_black_tree_hpp
#define red_black_tree_hpp

struct node{
    int ID;         
    int count;      
    char color;     
    node *p;        
    node *l;        
    node *r;        
    
    
    node(int i, int c){
        ID=i;
        count=c;
        color='b';  
        p=NULL;
        l=NULL;
        r=NULL;
    }
};

class red_black_tree{
    
private:
    node *root;
    
public:
    
    red_black_tree();                       
    void insert_from_sorted_list(int id[],int count[],int start,int end,int height); 
    int increase(int id,int m);             
    int reduce(int id,int m);               
    int count(int id);                      
    int inrange(int id1,int id2);           
    node* search(int id);                   
    node* search_next(int id);              
    node* search_previous(int id);          
    
    
    void insert(node *t);                   
    void remove(node *t);                   
    node* next(node *t);                    
    node* previous(node *t);                
    node* getroot();                        
    node* sorted_insert(int i[],int c[],int s,int e,int h); 
    int inrange_recursive(node *t,int i1,int i2);   
    
    
    void display(node *t,int n,char c);     
    int max_height(node *t);                
    void color(node *t,int h);              
};

#endif 
