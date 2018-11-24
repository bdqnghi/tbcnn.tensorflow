
#include "stdafx.h"
#include "B-Tree.h"

//Global 
 extern  FILE  * fBTree ;


//B_TREE operation function 
int  Search_B_NODE(const B_TreeNode & TreeNode ,KEY k)
 //��һ��B_TreeNode�в���
 //����ֵ -1,û�ҵ�
 //       >=0, �ҵ�   
{
  int num=TreeNode.iNumOfKey ;
  int ret=0 ;
  if(k<TreeNode.KeyArray[0]) return (-1); 
   else 
	   if(k>TreeNode.KeyArray[num]) return (num);
	   //num(�ؼ�����Ŀ)���ΪB���Ľ���-1
   else // Key is arrange this node .
   { 
	   while(ret<num && k>=TreeNode.KeyArray[ret])
		   ret++ ;
	   return (ret-1);
   }  
}

SearchResult  Search(const B_Tree & B_root,KEY  kValue)
{
  	B_Tree   p/*,q ,pRetTreeNode */ ;
	B_TreeNode RetTreeNode;
	static int i,n ;
	BOOL bFinished=FALSE ;	
    p=B_root ;
	/*pRetTreeNode=q=NULL ;*/
	SearchResult ret ;
	memset((void*)&ret,0,sizeof(SearchResult));
	
	while(p&&(!bFinished)){
		//TreeNode=*p;	
        n=p->iNumOfKey ; 
	    i=Search_B_NODE(*p,kValue) ;
		// p->KeyArray[i]<kVaLUE 
		// if not found ,then  i=-1 || p->iNumOfKey  
		// else (among the node key value range)
		//    p->KeyArray[i]<kVaLUE 
	   if(i>=0 &&(i<p->iNumOfKey)&& p->KeyArray[i]==kValue) 
	   {
		   bFinished=TRUE ; //exactly match
		   	ret.IsMatch =TRUE ; //exactly match  
	   }
	   else {
		   /*
		   if(!pRetTreeNode)
			   pRetTreeNode=(B_Tree)malloc(sizeof(B_TreeNode)); 
		   //may be a leak
		   */

		   if(!p->pChild[i+1]) 
			  //next layer is leaves ,search end but not match 
			   bFinished=TRUE  ; 
		   else {
		   /*q=p ;*/
		   fseek(fBTree,((p->pChild[i+1])*SIZEOF_BTREE_NODE),SEEK_SET); 
		   fread((void*)(&RetTreeNode),SIZEOF_BTREE_NODE,1,fBTree);
		   p=&RetTreeNode;
		   }
	   }	   
	}//end of while 

	if(bFinished) 
	{ 
		ret.retNode = *p ;

		//May be not NULL , !!! free when return ;		
		ret.recordKeyAdd=i;
	}
	 else  // p==NULL 		
		 ret.IsFailed =TRUE ;
		return  ret;  
}


BOOL    Insert_B_NODE(B_TreeNode * pNode , KEY kValue, int iPos)
{
	return FALSE ;

}

BOOL  Insert(B_Tree * B_root,KEY  kValue ,B_TreeNode *TreeNode,int i ) 
{ //insert in (*TreeNode) , between key[i] and key[i+1] 
  //before insert ,search it 
	 
	
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

