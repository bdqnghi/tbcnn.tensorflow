

#ifndef ST_B__TREE_CPP_H_
#define ST_B__TREE_CPP_H_




class BTree
{
public:
	int n;       								
	BTree *father;
	static int number;							
	static BTree *root;
	BTree();
	int *data;
	BTree **down;

	static bool inserttree(int t);				
	static	BTree* searchinsert(int t);			
	bool insertpoint(int t,BTree *p);			
	void split(int t,BTree *p);  				

	static void treedel(int t);
	void  delpoint(int t);
	static BTree*searchdel(int t);				
	void combine();

	static int deep;  							
	static void deletetree();
};


class dui					
{
public :
	BTree * data[200];  	
	int   num[200];    		
	int tp,tl;				
	dui(){tp=0;tl=0;}		
	BTree* pop();
	void push(BTree*,int);
	bool empty();
};

struct node
{
   BTree* q;
   node *next;
};


extern void Create(int m) ;
extern void searchlink(int t) ;
extern void searchroot(int t) ;
extern void st_bb_tree_cpp_test(void);
extern void bbprinttree(BTree *q);





#endif 
