import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;


public class BTree {

	public BNode addRecurse(int k, int val, BNode node){
		if(node == null){	//if key exists. ignore
			System.out.println("Repeated Entry. Ignored ");
			return null;
		}
		else{
			int index = node.find(k);	//find the the position where the new key has to be inserted into current node 
			if(index >= 0){
				return null;	//ie key already exits
			}
			else{
				index = -(index + 1);	//negative index is returned when the key does not exit
				if(node.getChild(index)!=null){	//if this node is not a leaf node:
					BNode node2 = addRecurse(k,val,node.getChild(index));	//then keep moving down the tree
					if(node2.getWeight() > (node2.getOrder() -2)){	//If number of keys in node == order
						BNode middle= node2.split();	//then split
						node.merge(middle);	//and merge
						return node;
					}else
					return node;
				}
				else{
					node.insertIntoLeaf(k, val);	//insert key value pair to this node
					return node;
				}
			}
		}
	}
	
	public BNode add(int k, int val, BNode node){
		BNode node2 = addRecurse(k,val,node);		//calls addRecurse, which adds the key value pair to tree and returns the root
		if(node2 == null)
			return node;	//in case key already exists, same root is returned without chnages
		if(node2.getWeight() > (node2.getOrder() -2)){	//if number of keys in the root is equal to order:
			BNode middle= node2.split();	//then split the root
			middle.addChild(node2,"start");	//and form a new root
			return middle;	//new root
		}else{
			return node2;
		}
	}
	
	public BNode search(int k, BNode node){
		int index = node.find(k);	
		if (index < 0){	
			index = -(index + 1);
			if(node.getChild(index)!=null){
				return search(k, node.getChild(index));	//if value is not found in this node, then recursively go down the tree
			}
			else
				return null;
		}else{
			return node;	//if the value is found in this node, this node is return
		}
	}
	
	//Print to console in as sorted
	public int sorted(BNode node){
		if(node == null)
			return 1;
		for(int i = 0;i<=node.getWeight() + 1;i++){	//traverse through the child nodes of the current node
		sorted(node.getChild(i));	//recursively traverse each of them
		if(node.getWeight()+1!=i)
			System.out.println(node.getKey(i) + " " + node.getValue(i));	//print the key value
		}
		return 1;
	}
	
	//Print to Arraylist as sorted. That Array list of then written to file
	public int sortedWrite(BNode node, ArrayList<String> output){
		if(node == null)
			return 1;
		for(int i = 0;i<=node.getWeight() + 1;i++){//traverse through the child nodes of the current node
		sortedWrite(node.getChild(i),output);	//recursively traverse each of them
		if(node.getWeight()+1!=i)
			output.add(node.getValue(i)+" ");	//print the value to Array List
		}
		return 1;
	}
	
	//Print to console in in level
	public void level(BNode B){
		Queue<BNode> qe = new LinkedList<BNode>(); 
		qe.add(B);	// add the current node to a queue
		BNode node2 = null;
		while(qe.peek() != null){
			node2 = qe.poll();	//deque a node from the queue
		for(int i=0;i<=node2.getWeight();i++)
		{
			System.out.println(node2.getKey(i)+" "+node2.getValue(i));	//print all the values in the deque-ed node
			qe.add(node2.getChild(i));	//enque all the child nodes of the deque-ed node
		}
			qe.add(node2.getChild(node2.getWeight()+1));			
		}
	}
	
	//Print to Arraylist in level. That Array list of then written to file
	public void levelWrite(BNode B, ArrayList<String> output){
		Queue<BNode> qe = new LinkedList<BNode>(); 
		qe.add(B);	// add the current node to a queue
		BNode node2 = null;
		while(qe.peek() != null){
			node2 = qe.poll();	//deque a node from the queue
		for(int i=0;i<=node2.getWeight();i++)
		{
			output.add(node2.getValue(i)+" ");	//print all the values, in the deque-ed node, to the ArrayList
			qe.add(node2.getChild(i));		//enque all the child nodes of the deque-ed node
		}
			qe.add(node2.getChild(node2.getWeight()+1));			
		}
	}
}
