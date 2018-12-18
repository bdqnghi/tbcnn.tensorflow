


import java.io.*;
import java.util.*;


class listNode {
	
	protected String data; 
	protected listNode next;
	
	public listNode(){
		this(null);
	} 
	
	public listNode(String data){
		this.data = data;
	} 
}


class linkedList {

	protected listNode listHead, walker;
	
	public linkedList(){
		listHead = new listNode("dummy");
	} 
	
	public void listInsert(String ndata){
		listNode newNode;
		walker = listHead;
		if(walker.next != null && ndata.length() > walker.next.data.length()){
			walker = walker.next;
		}
		newNode = new listNode(ndata);
		newNode.next = walker.next;
		walker.next = newNode;
	}
	
	public boolean isEmpty(){
		return listHead == null;
	}
	
	public String printList(){
		listNode curr = listHead;
		String Llist = "listHead";
		while(curr != null && curr.next != null){
			Llist += " --> (";
			Llist += curr.data;
			Llist += ", ";
			Llist += curr.next.data;
			Llist += ")";
		
			curr = curr.next;
		}
		Llist += System.lineSeparator();
		return Llist;
	}	
}


public class Project1Java {

	public static void main(String[] args) throws FileNotFoundException{
		
		linkedList sList = new linkedList();
		Scanner inFile = new Scanner(new FileReader(args[0]));
		PrintWriter outFile = new PrintWriter(args[1]);
		
		String word;
		String output;
		while(inFile.hasNext()){
			word = inFile.next();
			
			sList.listInsert(word);
			output = sList.printList();
			outFile.print(output);
		}
		
		inFile.close();
		outFile.close();
	}
}
