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
	if (!sc.hasNext()) { // empty file, nothing to sort
		return null;
	}

	// read radix from file, and set up buckets for linked lists
	radix = sc.nextInt();
	buckets = (Node<String>[]) new Node[radix];

	// create master list from input
	createMasterListFromInput(sc);

	// find the string with the maximum length
	int maxDigits = getMaxDigits();

	for (int i=0; i < maxDigits; i++) {
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
public void createMasterListFromInput(Scanner sc) throws IOException
{// WRITE YOUR CODE HERE

	Node<String> ptr = null;
	Node<String> prev = null;
	Node<String> holder = null;
	String RADIX = sc.next();

	for(int i = 0; i < RADIX.length(); i++)
	{
		if(Character.isLetter(RADIX.charAt(i)) )
		{        
			while(sc.hasNext())
			{
				if(masterListRear == null)
				{
					ptr = new Node<String>(RADIX,null);

					masterListRear = ptr;

					ptr.next = ptr;
				}
				else if(masterListRear != null)
				{
				ptr = new Node<String>(sc.next(),null);

				ptr.next = masterListRear.next;

				masterListRear.next = ptr;

				masterListRear = ptr;
				}
			}
		}
		else if(Character.isDigit(RADIX.charAt(i)))
		{
			while(sc.hasNext())
			{         
				if(masterListRear == null)
				{
					ptr = new Node<String>(RADIX,null);

					masterListRear = ptr;

					masterListRear.next = masterListRear;
				}
				else if(masterListRear != null)
				{
					ptr = new Node<String>(sc.next(),null);

					ptr.next = masterListRear.next;

					masterListRear.next = ptr;

					masterListRear = ptr;
				}

			}	
		}
	}
	//Sorter.printCLL(masterListRear);
}

/**
 * Determines the maximum number of digits over all the entries in the master list
 * 
 * @return Maximum number of digits over all the entries
 */
public int getMaxDigits() {
	if (masterListRear == null){
		System.out.println("Here");
	} 
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
 * Scatters entries of master list (referenced by instance field masterListRear) 
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
	Node<String> head = masterListRear.next;
	Node<String> ptr = masterListRear.next;

	int x;

	do {
		Node<String> temp = null;
		if (pass >= head.data.length() )
		{
			x = 0;	
		}
		else
		{
			x = Character.digit(head.data.charAt(head.data.length()-pass - 1), radix);
		}
		if (buckets[x] == null) 
		{
			temp = head;

			head = head.next;

			buckets[x] = temp;

			temp.next = temp;
		} 
		else
		{
			temp = head;

			Node<String> holder = buckets[x].next; // Holds value of bucket at position x's next, to not lose any items 
							       // when passing.
			head = head.next;

			buckets[x].next = temp;

			temp.next = holder;

			buckets[x] = temp;

		}
	}while(head != ptr);
}
/**
 * Gathers all the CLLs in all the buckets into the master list, referenced
 * by the instance field masterListRear
 * 
 * @param buckets Buckets of CLLs
 */
public void gather() 
{
	boolean val = false;
	masterListRear = null;
	Node<String> start = null;

	for(int i = 0; i < buckets.length ; i++)
	{

	if(buckets[i] == null) // checks if the bucket at position i is null.
	{
		continue;
	}
	else if(buckets[i] != null) 
	{
		val = true;
	}
	do{
		Node<String> holder = buckets[i];
		Node<String> check = buckets[i];
		
		if(masterListRear == null)
		{
			start = holder;

			holder = holder.next;

			start.next = holder.next;

			masterListRear = holder;

			holder.next = holder;

		}
		else if(masterListRear != null)
		{

		holder = check.next; 

		check.next = holder.next;

		holder.next = masterListRear.next;

		masterListRear.next = holder;

		masterListRear = holder;
		}

		if(check == holder)
		{
			val = false;
		}

		else if(check != holder)
		{
			continue;
		}
	} while(val);
    }
clear();
}
/*Clears all the buckets containing information
*setting each individual bucket to null.
*/
private void clear()
{
	for(int i = 0; i < buckets.length; i++)
	{
		if (buckets[i] == null)
		{
			continue;
		}
		if(buckets[i] != null)
		{
		buckets[i] = null;
		}
	}
     }
}

