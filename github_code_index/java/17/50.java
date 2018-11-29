/*
class RedBlackTree
contains the definitions and constructors to create a Red Black Tree.
contains the following functions:
1) HELPER FUNCTIONS
-int insert(Node n)
-void rbInsertFix(Node z)
-void transplant(Node u,Node v)
-void delete(Node z)
-void deleteFixup(Node x)
-Node treeMinimum(Node n)
-void prettyPrint()\
-void leftRotate(Node x)
-void rightRotate(Node x)



2) PROJECT FUNCTIONS
-Node search(int theid) : returns the node with id theid
-void Increase(int theid,int m) : Increase the count of the event theID by m. If theID is not present, insert it. Print the count of theID after the addition.
-void Reduce(int theid,int m) : Decrease the count of theID by m. If theID’s count becomes less than or equal to 0, remove theID from the counter. Print the count of theID after the deletion, or 0 if theID is removed or not present.
-void Count(int theid) : Print the count of theID. If not present, print 0.
-void InRange(int id1,int id2) : Print the total count for IDs between ID1 and ID2 inclusively. Note, ID1 ≤ ID2
-void recAdd(int id1,int id2,Node n) : InRange uses recAdd to recursively calculate the sum of count in between id1 and id2
-void Next(int theid) : Print the ID and the count of the event with the lowest ID that is greater that theID. Print “0 0”, if there is no next ID.
-void Previous(int theid) : Print the ID and the count of the event with the greatest key that is less that theID. Print “0 0”, if there is no previous ID.
-Node Successor(int theid) : Returns the successor of node with id theid
-Node genTree(int[][]arr,int start,int end,Node par) : used to generate tree initially in O(n) time by recursively adding the middle element from the sorted input array.
*/

public class RedBlackTree implements Sentinel
{
	
	Node root;
	
	int sum;
	/////////////////////
	///CONSTRUCTORS////
	///////////////////
	RedBlackTree(Node r)
	{
		root=r;
		sum=0;
		root.left=nil;
		root.right=nil;
		root.parent=nil;
		root.color="black";
	}
	
	RedBlackTree()
	{
		root=nil;
		sum=0;
		root.left=nil;
		root.right=nil;
		root.parent=nil;
		root.color="black";
	}

    ///////////////////////
	///INSERT FUNCTIONS////
	//////////////////////

	//inserts node in RBT
	int insert(Node n) 
	{
		Node y=null;
		Node x=root;
		while(x!=nil)
		{
			y=x;
			if(n.id < x.id)
			{
				x=x.left;
			}
			else
			{
				x=x.right;
			}
			
		}
		n.parent=y;
		if(y==nil)
		{
			root=n;
		}
		else if(n.id<y.id)
		{
			y.left=n;
		}
		else
		{
			y.right=n;
		}
		n.left=nil;
		n.right=nil;
		n.color="red";
		rbInsertFix(n);
		
		return 1;
	}
	
	//fixes any violations in RBT after insert
	void rbInsertFix(Node z)
	{
		Node y=null;
		
		while(z.parent.color=="red")
		{
			if(z.parent==z.parent.parent.left)
			{
				y=z.parent.parent.right;
				if(y.color=="red")
				{
					z.parent.color="black";
					y.color="black";
					z.parent.parent.color="red";
					z=z.parent.parent;
				}
				else 
				{
					if(z==z.parent.right)
					{
						z=z.parent;
						this.leftRotate(z);
					}		
					z.parent.color="black";
					z.parent.parent.color="red";
					this.rightRotate(z.parent.parent);
					
				}
			}
			else
			{
					y=z.parent.parent.left;
				
				if(y.color=="red")
				{
					z.parent.color="black";
					y.color="black";
					z.parent.parent.color="red";
					z=z.parent.parent;
				}
				else 
				{
					if(z==z.parent.left)
					{
						z=z.parent;
						this.rightRotate(z);
					}
					
					z.parent.color="black";
					z.parent.parent.color="red";
					this.leftRotate(z.parent.parent);
					
				}
			}
			
				
			
		}
		root.color="black";
	}
	///////////////////////
	///DELETE FUNCTIONS////
	//////////////////////

	//replaces the subtree rooted at node u with the subtree rooted at node v. Used for RBT delete.
	void transplant(Node u,Node v)
	{
		if(u.parent==nil)
		{
			root=v;
		}
		else if(u==u.parent.left)
		{
			u.parent.left=v;
		}
		else
		{
			u.parent.right=v;
		}
		v.parent=u.parent;
	} 
	
	//Performs the RBT delete node operation. Calls the deleteFixup (Node x) function to check whether any RBT violations have occurred and fix them.
	void delete(Node z)
	{
		Node x=null;
		Node y=z;
		String y_original_color=y.color;
		if(z.left==nil)
		{
			x=z.right;
			transplant(z,z.right);
		}
		else if(z.right==nil)
		{
			x=z.left;
			transplant(z,z.left);
		}
		else
		{
			y=treeMinimum(z.right);
			y_original_color=y.color;
			x=y.right;
			if(y.parent==z)
			{
				x.parent=y;
			}
			else
			{
				transplant(y,y.right);
				y.right=z.right;
				y.right.parent=y;
			}
			transplant(z,y);
			y.left=z.left;
			y.left.parent=y;
			y.color=z.color;
		}
		if(y_original_color=="black")
		{
			
			deleteFixup(x);
		}
	}
	
	//Fixes all the RBT violations that occurred after deleting by using left rotations, right rotations and colorings.
	void deleteFixup(Node x)
	{
		Node w=null;
		while(x!=root && x.color=="black")
		{
			if(x==x.parent.left)
			{
				w=x.parent.right;
				if(w.color=="red")
				{
					w.color="black";
					x.parent.color="red";
					leftRotate(x.parent);
					w=x.parent.right;
				}
				if(w.left.color=="black" && w.right.color=="black")
				{
					w.color="red";
					x=x.parent;
				}
				else 
				{
					if(w.right.color=="black")
					{
						w.left.color="black";
						w.color="red";
						rightRotate(w);
						w=x.parent.right;
					}
					w.color=x.parent.color;
					x.parent.color="black";
					w.right.color="black";
					leftRotate(x.parent);
					x=root;
				}
			}
			else
			{
				w=x.parent.left;
				if(w.color=="red")
				{
					w.color="black";
					x.parent.color="red";
					rightRotate(x.parent);
					w=x.parent.left;
				}
				if(w.right.color=="black" && w.left.color=="black")
				{
					w.color="red";
					x=x.parent;
				}
				else 
				{
					if(w.left.color=="black")
					{
						w.right.color="black";
						w.color="red";
						leftRotate(w);
						w=x.parent.left;
					}
					w.color=x.parent.color;
					x.parent.color="black";
					w.left.color="black";
					rightRotate(x.parent);
					x=root;
				}
			}
		}
		x.color="black";
	}

	///////////////////////
	///HELPER FUNCTIONS////
	//////////////////////

	//Returns the node with the minimum id value in the tree rooted at Node n.
	Node treeMinimum(Node n)
	{
		Node y=n;
		
		while(y.left!=nil)
		{
			
			y=y.left;
		}
		return y;
	}
	
	//Prints the RBT by calling the recursive function pretty().
	void prettyPrint()
	{
		root.pretty(0);
	}
	
	//It performs a left rotate operation at Node x.
	void leftRotate(Node x)
	{
		Node y=x.right;
		x.right=y.left;
		if(y.left!=nil)
		{
			y.left.parent=x;
		}
		y.parent=x.parent;
		if(x.parent==nil)
		{
			root=y;
		}
		else if(x==x.parent.left)
		{
			x.parent.left=y;
		}
		else
		{
			x.parent.right=y;
		}
		y.left=x;
		x.parent=y;
	}

	//It performs a right rotate operation at Node x.
	void rightRotate(Node x)
	{
		Node y=x.left;
		x.left=y.right;
		if(y.right!=nil)
		{
			y.right.parent=x;
		}
		y.parent=x.parent;
		if(x.parent==nil)
		{
			root=y;
		}
		else if(x==x.parent.right)
		{
			x.parent.right=y;
		}
		else
		{
			x.parent.left=y;
		}
		y.right=x;
		x.parent=y;
	}
	
	//Returns the node from RBT with id “theid”.
	Node search(int theid)
	{
		Node x=root;
		while(x!=nil)
		{
			if(theid<x.id)
			{
				x=x.left;
			}
			else if(theid>x.id)
			{
				x=x.right;
			}
			else
			{
				return x;
			}
		}
		return null;
	}

	///////////////////////
	///INCREASE////////////
	//////////////////////

	// Increases the count of the event “theid” by “m”.
	void Increase(int theid,int m)
	{
		
		Node n=search(theid);
		if(n==null)
		{
			Node x=new Node(theid,m);
			insert(x);
			System.out.println(x.count);
		}
		else
		{
			n.count=n.count+m; //increasing the count
			System.out.println(n.count);
		}
	}
	///////////////////////
	///REDUCE/////////////
	//////////////////////

	//Decreases the count of “theid” by “m”.
	void Reduce(int theid,int m)
	{
		Node n=search(theid);
		if(n==null)
		{
			System.out.println(0);
		}
		else
		{
			if(n.count-m<=0)
			{
				delete(n);
				System.out.println(0);
			}
			else
			{
				n.count=n.count-m;
				System.out.println(n.count);
			}
		}
	}
	///////////////////////
	///COUNT//////////////
	//////////////////////

	//Prints the count of “theid”.
	void Count(int theid)
	{
		Node n=search(theid);
		if(n==null)
		{
			System.out.println(0);
		}
		else
		{
			System.out.println(n.count);
		}
	}
	///////////////////////
	///INRANGE/////////////
	//////////////////////

	//Prints the total count for id’s between “id1” and “id2” inclusively.
	void InRange(int id1,int id2)
	{
		sum=0;
		recAdd(id1,id2,root);
		System.out.println(sum);
	}
	
	//InRange uses recAdd to recursively calculate the sum of count in between “id1” and “id2”.
	void recAdd(int id1,int id2,Node n)
	{
		Node x=n;
		if(x==nil)
		{
			return;
		}
		if(x.id>=id1 && x.id<=id2)
		{
			sum=sum+x.count;
			recAdd(id1,id2,n.left);
			recAdd(id1,id2,n.right);
		}
		else if(x.id<id1)
		{
			recAdd(id1,id2,n.right);
		}
		else if(x.id>id2)
		{
			recAdd(id1,id2,n.left);
		}
	}
	///////////////////////
	///NEXT///////////////
	//////////////////////

	//Prints the id and the count of the event with the lowest id that is greater than “theid”. 
	 void Next(int theid)
	{
		Node next=null;
		Node x=root;
		while(x!=nil)
		{
			if(theid<x.id)
			{
				next=x;
				x=x.left;
			}
			else
			{
				x=x.right;
			}
		}
		if(next==null)
		{
			System.out.println("0 0");
		}
		else
		{
			System.out.println(next.id +" "+next.count );
		}
	}
	///////////////////////
	///PREVIOUS/////////////
	//////////////////////

	//Prints the id and the count of the event with the greatest key that is less that “theid”.
	void Previous(int theid)
	{
		Node prev=null;
		Node x=root;
		while(x!=nil)
		{
			if(theid<=x.id)
			{
				
				x=x.left;
			}
			else if(theid>x.id)
			{
				prev=x;
				x=x.right;
			}
			
		}
		if(prev==null)
		{
			System.out.println("0 0");
		}
		else
		{
			System.out.println(prev.id +" "+prev.count);
		}
	}
	////////////////////////
	///SUCCESSOR/////////////
	///////////////////////

	//Returns the inorder successor of node with id “theid”.
	Node Successor(int theid)
	{
		Node x=search(theid);
		Node suc;
		Node y;
		if(x.right!=nil)
		{
			 suc=treeMinimum(x.right);
			 
		}
		else
		{
			y=x.parent;
			while(y!=nil && x==y.right)
			{
				x=y;
				y=y.parent;
			}
			suc=y;
		}
		if(suc==nil)
		{
			System.out.println("0 0");
		}
		else
		{
			System.out.println(suc.id);
		}
		return suc;
	}

 	///////////////////////
	///GENERATE TREE///////
	//////////////////////
	//used to generate tree initially in O(n) time by recursively adding the middle element from the sorted input array.
	Node genTree(int[][]arr,int start,int end,Node par) 
    {
		if(start>end)
		{
			return nil;
		}
		int middle=(start+end)/2;
		Node n=new Node(arr[middle][0],arr[middle][1]);
		n.parent=par;
		n.color="black";
		
		n.left=genTree(arr,start,middle-1,n);
		n.right=genTree(arr,middle+1,end,n);
		return n;
    }
}
