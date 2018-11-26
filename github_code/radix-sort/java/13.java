package apps;

import java.io.IOException;
import java.util.Scanner;

import structures.Node;

/**
 * This class sorts a given list of strings which represent numbers in
 * the given radix system. For instance, radix=10 means decimal numbers;
 * radix=16 means hexadecimal numbers. 
 * 
 * @author ru-nb-cs112
 */
public class Radixsort {

	/**
	 * Master list that holds all items, starting with input, and updated after every pass
	 * of the radixsort algorithm. Holds sorted result after the final pass. This is a
	 * circular linked list in which every item is stored in its textual string form (even
	 * though the items represent numbers). This masterListRear field points to the last 
	 * node in the CLL.
	 */
	Node<String> masterListRear;
	
	/**
	 * Array of linked lists that holds the digit-wise distribution of the items during
	 * each pass of the radixsort algorithm. 
	 */
	Node<String>[] buckets;
	
	/** 
	 * The sort radix, defaults to 10.
	 */
	int radix=10;
	
	/**
	 * Initializes this object with the given radix (10 or 16)
	 * 
	 * @param radix
	 */
	public Radixsort() {
		masterListRear = null;
		buckets = null;
	}
	
	/**
	 * Sorts the items in the input file, and returns a CLL containing the sorted result
	 * in ascending order. The first line in the input file is the radix. Every subsequent
	 * line is a number, to be read in as a string.
	 * 
	 * The items in the input are first read and stored in the master list, which is a CLL that is referenced
	 * by the masterListRear field. Next, the max number of digits in the items is determined. Then, 
	 * scatter and gather are called, for each pass through the items. Pass 0 is for the least
	 * significant digit, pass 1 for the second-to-least significant digit, etc. After each pass,
	 * the master list is updated with items in the order determined at the end of that pass.
	 * 
	 * NO NEW NODES are created in the sort process - the nodes of the master list are recycled
	 * through all the intermediate stages of the sorting process.
	 * 
	 * @param sc Scanner that points to the input file of radix + items to be sorted
	 * @return Sorted (in ascending order) circular list of items
	 * @throws IOException If there is an exception in reading the input file
	 */
	public Node<String> sort(Scanner sc) 
	throws IOException {
		// first line is radix
		if (!sc.hasNext()) 
		{ // if it is an empty file, nothing to sort
			return null;
		}
		
		// read radix from file, and set up buckets for linked lists
		radix = sc.nextInt();
		buckets = (Node<String>[])new Node[radix];
		
		// create master list from input 
		createMasterListFromInput(sc);
		
		// find the string with the maximum length
		int maxDigits = getMaxDigits();
		
		for (int i=0; i < maxDigits; i++)  
		{
			scatter(i);
			gather();
		}
		
		return masterListRear;
	} 
	
	/**
	 * Reads entries to be sorted from input file and stores them as 
	 * strings in the master CLL (pointed by the instance field masterListRear, 
	 * in the order in which they are read. In other words, the first entry in the linked 
	 * list is the first entry in the input, the second entry in the linked list is the 
	 * second entry in the input, and so on. 
	 * 
	 * @param sc Scanner pointing to the input file
	 * @throws IOException If there is any error in reading the input
	 */
	public void createMasterListFromInput(Scanner sc) 
	throws IOException 
	{
		// WRITE YOUR CODE HERE		
				Node<String> front = new Node<String>(sc.next(),null); //Adds the very first node to the beginning of the linked list 
				Node<String> ptr=front;
				Node<String> cLL=null; 
				
					while(sc.hasNext()) //if sc.hasNextLine() == true then we use nextLine() to increment to the next line of the scanner
						{
						 cLL = new Node<String>(sc.next(),null);
						 ptr.next=cLL;
						 ptr=ptr.next; 
	 				    }
					 
					masterListRear=cLL; 
					masterListRear.next=front;
	}
	
	/**
	 * Determines the maximum number of digits over all the entries in the master list
	 * 
	 * @return Maximum number of digits over all the entries
	 */
	public int getMaxDigits() {
		int maxDigits = masterListRear.data.length();
		Node<String> ptr = masterListRear.next;
		while (ptr != masterListRear) {
			int length = ptr.data.length();
			if (length > maxDigits) {
				maxDigits = length;
			}
			ptr = ptr.next;
		}
		return maxDigits;
	}
	
	/**
	 * Scatters entries of master list (referenced by instance field masterListReat) 
	 * to buckets for a given pass.
	 * 
	 * Passes are digit by digit, starting with the rightmost digit -
	 * the rightmost digit is the "0-th", i.e. pass=0 for rightmost digit, pass=1 for 
	 * second to rightmost, and so on. 
	 * 
	 * Each digit is extracted as a character, 
	 * then converted into the appropriate numeric value in the given radix
	 * using the java.lang.Character.digit(char ch, int radix) method
	 * 
	 * @param pass Pass is 0 for rightmost digit, 1 for second to rightmost, etc
	 */
	public void scatter(int pass) 
	{
		// WRITE YOUR CODE HERE 
				Node<String> temp=null;//what we're using to iterate through the cLL 
				
				do 
					{ 
					  temp = masterListRear.next; //declaring and initializing a temp to the front of the cLL 
			 		  int index=temp.data.length()-1-pass;//Gets the index of the character we are accessing in the string node 
					  char tempCh;
					  int tempInt=0;
					  if(index>=0)
					  { 
						tempCh=temp.data.charAt(index); //Gets the character at index size 
					    tempInt=Character.digit(tempCh,radix); 
					  }
			 	  
				 for(int x=0; x<buckets.length;x++) //Goes through the entire array's indexes 
				    {  	   
					  if(index>=0) 
			           { 
						   if(tempInt == x)
						   {
							   if(buckets[x]==null) //if index x of array buckets is empty then we populate it 
							   { 
								
								 Node<String> nextPtr=temp.next; //We make the nextPtr point to the one after front so it does not get garbage collected
								 temp.next=temp; //We set the node equal to itself in the circular linked list 
								 System.out.println("When we add to an empty bucket " + temp.data);
								 buckets[x]=temp; //We set buckets equal to the node in the linked list 
								 masterListRear.next=nextPtr;
								 temp=nextPtr;  
								
								 break; 
							   }
							   
							   else //else if index x of array buckets is not empty then we add to the end of the cLL 
							   {
							     Node<String> nextPtr=temp.next;  
								 temp.next=buckets[x].next;
								 System.out.println("When we add to a non empty bucket " + temp.data);
								 buckets[x].next=temp;
								 buckets[x]=temp; 								 
								 masterListRear.next=nextPtr; 
								 temp=nextPtr; 
								 break;
						       }  
						   }
						   
			          }
					
					  else//if index is negative  
						{
						   if(buckets[0]==null) //if index x of array buckets is empty if so then we populate it 
						   {
							Node<String> nextPtr=temp.next;
							temp.next=temp;
							System.out.println("Add to bucket 0 when index is negative " + temp.data);
							buckets[0]=temp; 
							masterListRear.next=nextPtr;  
							temp=nextPtr;
							break; 
						   }
						   else //else if index x of array buckets is not empty then we add to the end of the cLL 
						   {
							 Node<String> nextPtr=temp.next;
							 temp.next=buckets[x].next;
							 System.out.println("Add to bucket 0 when index is negative and populated " + temp.data);
							 buckets[0].next=temp;
							 buckets[0]=temp;
							 masterListRear.next=nextPtr;
							 temp=nextPtr;
						     break; 
						   }
					   }	     
			     
				 }
			  } 
				
			 while(temp!=masterListRear); 
				
		     if(temp==masterListRear)  
		     {  
		       int tempIndex=temp.data.length()-1-pass;
		       int tempInt=0; 
		       
		       if(tempIndex>=0)
		       {     
			        if(tempIndex>=0)  
			    	{	
			        char tempCh=temp.data.charAt(tempIndex); //Gets the character at index size 
				    tempInt=Character.digit(tempCh,radix); 
			    	}
				   for(int x=0; x<buckets.length;x++)
			    	{
				      if(tempInt==x)
			    	  {
			    		 if(buckets[x]==null)
			    		 {
			    			 temp.next=temp;
			    			 buckets[x]=temp;
			    			 System.out.println("The index is " + x);
			    			 System.out.println("Temp is " + temp.data + "Temp.next is " + temp.next.data); 
			    			 System.out.println("buckets[x] is " + buckets[x].data);
			    			 masterListRear=null;
			    			 break;
			    			 
			    		 }
			    		 else
			    		 {
			    			 System.out.println("The index is " + x);
			    			 temp.next=buckets[x].next; 
			    			 System.out.println("Temp is " + temp.data + " Temp.next is " + temp.next.data);
			    			 buckets[x].next=temp;
			    			 buckets[x]=temp; 
			    			 System.out.println("buckets[x] is " + buckets[x].data);
			    			 masterListRear=null;
			    			 break;  
			    		 }
			    	  }
				      
			    	}
		       } 
		       else 
		       {
		    	   if(buckets[0]==null)
			    	 {
		    		     temp.next=temp;
			   			 buckets[0]=temp;
			   			 System.out.println("Temp is " + temp.data + "Temp.next is " + temp.next.data);
			   			 temp.next=buckets[0]; 
			   			 masterListRear=null;
		    			 
			    	 }
			       else
			         {
			    		 temp.next=buckets[0].next; 
			    		 System.out.println("Temp is " + temp.data + " Temp.next is " + temp.next.data);
			    		 buckets[0].next=temp;
			    		 buckets[0]=temp;
			    		 masterListRear=null;
			    			 
			    	 }
			      }
		       	}
		      
		}
						
	
	 
   

	/**
	 * Gathers all the CLLs in all the buckets into the master list, referenced
	 * by the instance field masterListRear
	 * 
	 * @param buckets Buckets of CLLs
	 */
	public void gather() 
	{// WRITE YOUR CODE HERE
	    
		   Node<String> tempPtrFront=null;
		   Node<String> begin=null; 
		   for(int x=0; x<buckets.length;x++) //Going through the entire array of buckets[] 
		   {   
			   if(buckets[x]!=null) //if the array at index x is not empty 
			   {
				 begin=buckets[x].next; //the front of the first node in the bucket list 
				 tempPtrFront=buckets[x]; //the last node of the bucket index    
				 buckets[x]=null;  
				 break;
			   }
		   }

		   //Populating the rest of the circular linked lists with buckets
		   Node<String> tempPtr=null; 
		   Node<String> tempPtrFront2=tempPtrFront; //tempPtrFront2 is now point to the last node of the first index 
		   for(int x=0; x<buckets.length;x++)
		   {
			   if(buckets[x]!=null) 
			   {
				  tempPtr=buckets[x]; //tempPtr is now pointing to the last node in bucket[x]
				  tempPtrFront2.next=tempPtr.next;  //the last node of the first bucket index is now pointing to the front of the current bucket index
				  tempPtrFront2=tempPtr; 
				  buckets[x]=null; 
			   }
		   }
		 
		 masterListRear=tempPtrFront2; 
		 masterListRear.next=begin;  
		  
		
    }
	
}

