package redblacktree;

import java.io.*;

/*------���δ���ʵ�ֵĹ����ǲ��루������漰���ĵ����������������ȣ���ɾ����������ָ��Keyֵ�ڵ㣩-----*/

public class redblacktree{
	
	public Node root;
	public Node nil= new Node();
	
	//��ʼ��Ҷ��
	private  void InitNil(){
		 nil.NData=0;
		 nil.color=true;  //Ҷ�ӽڵ㶼�����Ǻڵ�
		 nil.leftChild=null;
		 nil.rightChild=null;
		 
	}
	
	
	//���ø��ڵ�
	private void setRoot(Node node){
    this.root=node;		
	}
	
	
	
	
	
	
	private Node getMin(Node node){
		while(node.leftChild !=nil)
			node=node.leftChild ;
		return node;
	}
	
	
	/*----------------------С��public---------------*/
	public  Node getRoot(){
		return this.root;
		
	}
	
	public void preOrder(){
		preOrderRBTree(this.root,1);
		
	}
	//��������ֵ
	public void rbInsert(int i)
	{
		InitNil();
		Node node=new Node();
		node.NData =i;
		Insert(node);
		node.color=false;  //Ĭ��ִred
		node.leftChild =nil;
		node.rightChild =nil;
		rbInsertAdjustment(node);
		
		
	}
	
	//����ʵ��rank��T��x������ش���
	public int size(Node node)
	{ if(node==nil) return 0;
	else  return size(node.leftChild )+size(node.rightChild )+1;
	
	}
	public int OSRank(int x)
	{ int r;
	Node y;
	r=size(search(x).leftChild )+1;
	y=search(x);
	while(y!=this.root)
	{ if(y==y.parent.rightChild)
		 r=r+size(y.parent.leftChild )+1;
	    y=y.parent ;
	}
	    return r;
	}
	
	
	/*-----------------------������ֵ�ҽڵ�---------------*/
	public Node search(int key){
		if(root==null) return null;
		else {
			Node temp=root;
			while(temp.NData !=key)
			{if(key<temp.NData )
				temp=temp.leftChild ;
			else
				temp=temp.rightChild ;
			if(temp==nil)
				return null;
			}
			return temp;
		}
	}
	
	
	public Node rbDelete(int i){
		Node node;
		node=search(i);
		if(node==null) return null;
		else return (rbDelete(node));
	}
	
	
	
	
	
	
	
	
	
	/*--------------------------------------------*/
	//������Ķ��ڵ�Ĳ������
	public void Insert(Node node)
	{
		//������ʱ��
		if(root==null){
			root=node;
			root.parent=nil;
			
		}
		else
		{
			Node begin =root;
			Node parent;
			while(true){
			parent=begin;
			if(node.NData< begin.NData)
			{ //��Ҫ����ڵ������ֵ�ȵ�ǰ��ͷ�ڵ������ֵС��ʱ����������߲���
				begin=begin.leftChild;
				if(begin==nil)
				{ //�Ѿ����Ƶ����������
					begin.leftChild=node;
					node.parent=parent;
					return ;
				}
				
			} 
			else{
				//��Ҫ��������ұ�ʱ��
				begin=begin.rightChild;
				if(begin==nil)
				{ 
					parent.rightChild=node;
				node.parent=parent;
				return ;
				}
			}
			}//end of while
			
			
		}//end of else
		
	}
	
	
	
	
	//ǰ����������
	private void preOrderRBTree(Node root,int level){
		
	if(root != null)
		
		System.out.println("(" + root.NData + root.getColor() + ",");
	        if(root.leftChild == nil) 
	        { for(int i=0;i<level;i++) System.out.print("  "); 
	        	System.out.println("NIL,");
	        }
	        else {
	           preOrderRBTree(root.leftChild,level++);
	           for(int i=0;i<level;i++) System.out.print("  "); 
	           System.out.println(",");
	           }
	        for(int i=0;i<level;i++) System.out.print("  "); 
	        if(root.rightChild == nil) 
	        {	 for(int i=0;i<level;i++) System.out.print("  "); 
	        	System.out.println("NIL)");
	        }
	        else{
	           preOrderRBTree(root.rightChild,level++);
	           for(int i=0;i<level;i++) System.out.print("  "); 
	           System.out.println(")");
	           }
	    
	    
	         }//end of preOrderRBTree
	
	
	//�������������ת
	private void leftRotate(Node node){
		Node temp;
       temp=node.rightChild ;
       
       node.rightChild =temp.leftChild ;
       /*------------1---------------*/
       if(temp.leftChild !=nil)
    	   temp.leftChild .parent =node;
           temp.parent =node.parent ;
       /*------------2��ǰ�ڵ�û�и�ĸ�ڵ㣬�����Լ����²���ĵ�һ��������ǰ����ɾ����--------------*/
       if(node.parent ==nil) this.setRoot(temp);
       else if(node==node.parent .leftChild )
    	      node.parent .leftChild =temp;
       else node.parent .rightChild =temp;
       temp.leftChild =node;
       node.parent =temp;
                    }
	
	private void rightRotate(Node node){
		Node tempa;
		tempa=node.leftChild ;
		
		node.leftChild =tempa.rightChild ;
		if(tempa.rightChild !=nil) tempa.rightChild .parent =node;
		tempa.parent=node.parent ;
		
		if(node.parent ==nil) this.setRoot(tempa);
		else if (node==node.parent .leftChild ) node.parent .leftChild =tempa;
		else node.parent .rightChild =tempa;
		tempa.rightChild =node;
		node.parent =tempa;
	}

	//����������ĵ���
	private void rbInsertAdjustment(Node node){
		while(node.parent .color == false)
		{
			if(node.parent ==node.parent .parent .leftChild )
			{ Node temp=node.parent .parent .rightChild ;
			if(temp.color ==false){
				node.parent.color =true;
				temp.color =true;
				node.parent .parent .color =false;
				node=node.parent .parent ;
                        		}
			else          {
				if(node==node.parent .rightChild ){
					node=node.parent ;
					leftRotate(node);
				                                  }
				node.parent .color =true;
				node.parent .parent .color =false;
				rightRotate(node.parent .parent );
				
			              }
			                 }
			else {
				Node temp=node.parent .parent .leftChild ;
				if(temp.color ==false){
					node.parent .color =true;
					temp.color =true;
					node.parent .parent .color =false;
					node=node.parent .parent ;
				}
				else{
					if(node==node.parent.leftChild ){
						node=node.parent ;
						rightRotate(node);
					}
					node.parent .color =true;
					node.parent .parent .color =false;
					leftRotate(node.parent .parent );
				}
			}
		}
		this.getRoot().color=true;
	}
	//���Һ��
	private Node getSuccessor(Node node){
        if (node.rightChild != nil) return getMin(node.rightChild);
        Node y = node.parent;
        while((y != nil) && (y.rightChild == node)){
            node = y;
            y = y.parent;
        }
        return y;
    }
	
	
	//�ڵ�ɾ��
	private Node rbDelete(Node node){
        Node y, x;
        if ((node.leftChild == nil) || (node.rightChild == nil))
            y = node;
        else y = getSuccessor(node);
        if (y.leftChild != nil) x = y.leftChild;
        else x = y.rightChild;
        x.parent = y.parent;
        if (y.parent == nil) setRoot(x);
        else if (y == y.parent.leftChild) y.parent.leftChild = x;
        else y.parent.rightChild = x;
        if(y != node) node.NData  = y.NData;
        if (y.color == true) rbDeleteAdjust(x);
        return y;
    }
	
	
	
	
	//ɾ�������Ϊ�����
	 private void rbDeleteAdjust(Node node){
	        while(node != getRoot() && node.color == true)
	            if(node == node.parent.leftChild){
	                Node y = node.parent.rightChild;
	                if(y.color == false){
	                    y.color = true;
	                    node.parent.color = false;
	                    leftRotate(node.parent);
	                    y = node.parent.rightChild;
	                }
	                if ((y.leftChild.color == true) && (y.rightChild.color == true)){
	                    y.color = false;
	                    node = node.parent;
	                }
	                else if(y.rightChild.color == true){
	                    y.leftChild.color = true;
	                    y.color = false;
	                    rightRotate(y);
	                    y = node.parent.rightChild;
	                    }
	                y.color = node.parent.color;
	                node.parent.color = true;
	                y.rightChild.color = true;
	                leftRotate(node.parent);
	                node = getRoot();
	            }
	            else{
	                Node y = node.parent.leftChild;
	                if(y.color == false){
	                    y.color = true;
	                    node.parent.color = false;
	                    rightRotate(node.parent);
	                    y = node.parent.leftChild;
	                }
	                if ((y.rightChild.color == true) && (y.leftChild.color == true)){
	                    y.color = false;
	                    node = node.parent;
	                }
	                else if(y.leftChild.color == true){
	                    y.rightChild.color = true;
	                    y.color = false;
	                    leftRotate(y);
	                    y = node.parent.leftChild;
	                    }
	                y.color = node.parent.color;
	                node.parent.color = true;
	                y.leftChild.color = true;
	                rightRotate(node.parent);
	                node = getRoot();
	            }
	        node.color = true;
	    }
	 
	 
	//���������ĺڸ߶�
	public int bDepth(){
		Node mynode=this.root ;
		Node p=mynode;
		Node[] Stack1;
		Stack1=new Node[10];
		int[] Stack2;
		Stack2=new int[10];
		
		int curdepth,maxdepth=0,top=-1;
		if(mynode!=null){
	  curdepth=1;
	  do{
		  while(p!=null)
		  {Stack1[++top]=p;
		  Stack2[top]=curdepth;
		  
		  if(p.color==true)
		  {p=p.leftChild ;
		   curdepth++;
		  }
		  else p=p.leftChild ;
		   
		  } //end of WHILE
		  p=Stack1[top];
		  curdepth=Stack2[top--];
		  if(p.leftChild ==null && p.rightChild ==null)
			   if(curdepth>maxdepth)
				   maxdepth=curdepth;
		  if(p.color==true)
		  {
		  p=p.rightChild ;
		  curdepth++;
		  }
		  else p=p.rightChild ;
	  
		  
	  }while(!(p==null && top==-1));//end of DO
		}// end of IF 
  return(maxdepth);
	
	} //end of BLACK Height
	
	
	

	
}//end of the whole red-black tree class


















































	
	
	
	