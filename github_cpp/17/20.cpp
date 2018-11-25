
#include "stdafx.h"
#include "B-Tree.h"


 extern  FILE  * fBTree ;



int  Search_B_NODE(const B_TreeNode & TreeNode ,KEY k)
 
 
 
{
  int num=TreeNode.iNumOfKey ;
  int ret=0 ;
  if(k<TreeNode.KeyArray[0]) return (-1); 
   else 
	   if(k>TreeNode.KeyArray[num]) return (num);
	   
   else 
   { 
	   while(ret<num && k>=TreeNode.KeyArray[ret])
		   ret++ ;
	   return (ret-1);
   }  
}

SearchResult  Search(const B_Tree & B_root,KEY  kValue)
{
  	B_Tree   p ;
	B_TreeNode RetTreeNode;
	static int i,n ;
	BOOL bFinished=FALSE ;	
    p=B_root ;
	
	SearchResult ret ;
	memset((void*)&ret,0,sizeof(SearchResult));
	
	while(p&&(!bFinished)){
		
        n=p->iNumOfKey ; 
	    i=Search_B_NODE(*p,kValue) ;
		
		
		
		
	   if(i>=0 &&(i<p->iNumOfKey)&& p->KeyArray[i]==kValue) 
	   {
		   bFinished=TRUE ; 
		   	ret.IsMatch =TRUE ; 
	   }
	   else {
		   

		   if(!p->pChild[i+1]) 
			  
			   bFinished=TRUE  ; 
		   else {
		   
		   fseek(fBTree,((p->pChild[i+1])*SIZEOF_BTREE_NODE),SEEK_SET); 
		   fread((void*)(&RetTreeNode),SIZEOF_BTREE_NODE,1,fBTree);
		   p=&RetTreeNode;
		   }
	   }	   
	}

	if(bFinished) 
	{ 
		ret.retNode = *p ;

		
		ret.recordKeyAdd=i;
	}
	 else  
		 ret.IsFailed =TRUE ;
		return  ret;  
}


BOOL    Insert_B_NODE(B_TreeNode * pNode , KEY kValue, int iPos)
{
	return FALSE ;

}

BOOL  Insert(B_Tree * B_root,KEY  kValue ,B_TreeNode *TreeNode,int i ) 
{ 
  
	 
	
	return FALSE ;
}

BOOL  Delete_B_NODE(B_Tree * B_root, KEY  kValue) 
{
 return FALSE ; 
}

int CompareKey(int key1 ,int key2 ) 
{
 return 1;
}

