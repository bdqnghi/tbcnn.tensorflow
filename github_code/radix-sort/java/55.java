package apps;

import java.io.IOException;
import java.util.Scanner;

import structures.Node;

/**
 * This class sorts a given list of strings which represent numbers in the given
 * radix system. For instance, radix=10 means decimal numbers; radix=16 means
 * hexadecimal numbers.
 * 
 * @author ru-nb-cs112
 */
public class Radixsort
{

	/**
	 * Master list that holds all items, starting with input, and updated after
	 * every pass of the radixsort algorithm. Holds sorted result after the
	 * final pass. This is a circular linked list in which every item is stored
	 * in its textual string form (even though the items represent numbers).
	 * This masterListRear field points to the last node in the CLL.
	 */
	Node<String> masterListRear;

	/**
	 * Array of linked lists that holds the digit-wise distribution of the items
	 * during each pass of the radixsort algorithm.
	 */
	Node<String>[] buckets;

	/**
	 * The sort radix, defaults to 10.
	 */
	int radix = 10;

	/**
	 * Initializes this object with the given radix (10 or 16)
	 * 
	 * @param radix
	 */
	public Radixsort()
	{
		masterListRear = null;
		buckets = null;
	}

	/**
	 * Sorts the items in the input file, and returns a CLL containing the
	 * sorted result in ascending order. The first line in the input file is the
	 * radix. Every subsequent line is a number, to be read in as a string.
	 * 
	 * The items in the input are first read and stored in the master list,
	 * which is a CLL that is referenced by the masterListRear field. Next, the
	 * max number of digits in the items is determined. Then, scatter and gather
	 * are called, for each pass through the items. Pass 0 is for the least
	 * significant digit, pass 1 for the second-to-least significant digit, etc.
	 * After each pass, the master list is updated with items in the order
	 * determined at the end of that pass.
	 * 
	 * NO NEW NODES are created in the sort process - the nodes of the master
	 * list are recycled through all the intermediate stages of the sorting
	 * process.
	 * 
	 * @param sc
	 *            Scanner that points to the input file of radix + items to be
	 *            sorted
	 * @return Sorted (in ascending order) circular list of items
	 * @throws IOException
	 *             If there is an exception in reading the input file
	 */
	@SuppressWarnings("unchecked")
	public Node<String> sort(Scanner sc) throws IOException
	{
		// first line is radix
		if (!sc.hasNext())
		{ // empty file, nothing to sort
			return null;
		}

		// read radix from file, and set up buckets for linked lists
		radix = sc.nextInt();
		buckets = (Node<String>[]) new Node[radix];

		// create master list from input
		createMasterListFromInput(sc);

		// find the string with the maximum length
		int maxDigits = getMaxDigits();

		for (int i = 0; i < maxDigits; i++)
		{
			scatter(i);
			gather();
		}
		return masterListRear;
	}

	/**
	 * Reads entries to be sorted from input file and stores them as strings in
	 * the master CLL (pointed by the instance field masterListRear, in the
	 * order in which they are read. In other words, the first entry in the
	 * linked list is the first entry in the input, the second entry in the
	 * linked list is the second entry in the input, and so on.
	 * 
	 * @param sc
	 *            Scanner pointing to the input file
	 * @throws IOException
	 *             If there is any error in reading the input
	 */
	public void createMasterListFromInput(Scanner sc) throws IOException
	{
		String readLine = null;
		Node<String> tmp = null;
		while (sc.hasNext())
		{
			readLine = sc.next();
			if (!readLine.isEmpty())
			{
				if (null == masterListRear)
				{
					masterListRear = new Node<String>(readLine, masterListRear);
					tmp = masterListRear;
				} else
				{
					tmp.setNext(new Node<String>(readLine, masterListRear));
					tmp = tmp.getNext();
				}
			}
		}
		setListAsRequired();
	}

	/**
	 * Determines the maximum number of digits over all the entries in the
	 * master list
	 * 
	 * @return Maximum number of digits over all the entries
	 */
	public int getMaxDigits()
	{
		int maxDigits = masterListRear.getData().length();
		Node<String> ptr = masterListRear.getNext();
		while (ptr != masterListRear)
		{
			int length = ptr.getData().length();
			if (length > maxDigits)
			{
				maxDigits = length;
			}
			ptr = ptr.getNext();
		}
		return maxDigits;
	}

	/**
	 * Scatters entries of master list (referenced by instance field
	 * masterListReat) to buckets for a given pass.
	 * 
	 * Passes are digit by digit, starting with the rightmost digit - the
	 * rightmost digit is the "0-th", i.e. pass=0 for rightmost digit, pass=1
	 * for second to rightmost, and so on.
	 * 
	 * Each digit is extracted as a character, then converted into the
	 * appropriate numeric value in the given radix using the
	 * java.lang.Character.digit(char ch, int radix) method
	 * 
	 * @param pass
	 *            Pass is 0 for rightmost digit, 1 for second to rightmost, etc
	 */
	public void scatter(int pass)
	{
		int position = -1, count = 0;
		char[] tmpData = null;
		String tmpBucketData = null;
		Node<String> tmpNode = null;

		while (null != masterListRear)
		{
			/**
			 * IMPORTANT: According to the instructions, every time the REAR of 
			 * the list, in stead of the front.
			 * Now , get to the 1st node from the last one.
	 		 */
			if(0 == count)
			{
				masterListRear = masterListRear.getNext();
				++count;
			}
			
			tmpData = masterListRear.getData().toCharArray();
			if(0 <= tmpData.length - 1 - pass)
			{
				position = Character.digit(tmpData[tmpData.length - 1 - pass], radix);
			}
			else
			{
				position = 0;
			}

			if (-1 == position)
			{
				return;
			}

			if (null == buckets[position])
			{
				buckets[position] = masterListRear;
				setListRearToNextOne();
				buckets[position].setNext(buckets[position]);

			} else
			{
				tmpBucketData = buckets[position].getData();
				tmpNode = buckets[position];
				
				//find the tail
				while(!tmpBucketData.equals(tmpNode.getNext().getData()))
				{
					tmpNode = tmpNode.getNext();
				}
				
				tmpNode.setNext(masterListRear);
				setListRearToNextOne();
				tmpNode.getNext().setNext(buckets[position]);
			}
		}
	}

	/**
	 * This function will delete the node that is currently pointed by
	 * masterListRear. And masterListRear will be automatically set to the next
	 * node that is next to the current node.
	 */
	private void setListRearToNextOne()
	{
		// 0 node
		if (null == masterListRear)
		{
			return;
		}

		String tmpData = masterListRear.getData();

		// 1 node
		if (tmpData.equals(masterListRear.getNext().getData()))
		{
			masterListRear = null;
		}
		// > 1 node
		else
		{
			while (!tmpData.equals(masterListRear.getNext().getData()))
			{
				masterListRear = masterListRear.getNext();
			}
			masterListRear.setNext(masterListRear.getNext().getNext());

			masterListRear = masterListRear.getNext();
		}
	}

	/**
	 * Gathers all the CLLs in all the buckets into the master list, referenced
	 * by the instance field masterListRear
	 * 
	 * @param buckets
	 *            Buckets of CLLs
	 */
	public void gather()
	{
		String tmpData = null;
		Node<String> tmpNode = null;
		
		for (int i = 0; i < buckets.length; ++i)
		{
			if (null == buckets[i])
			{
				continue;
			} else if (null == masterListRear)
			{
				masterListRear = buckets[i];
			} else
			{
				tmpData = masterListRear.getData();
				tmpNode = masterListRear;
				
				while(!tmpData.equals(tmpNode.getNext().getData()))
				{
					tmpNode = tmpNode.getNext();
				}
				
				tmpNode.setNext(buckets[i]);
				
				tmpData = buckets[i].getData();
				tmpNode = tmpNode.getNext();
				
				while(!tmpData.equals(tmpNode.getNext().getData()))
				{
					tmpNode = tmpNode.getNext();
				}
				tmpNode.setNext(masterListRear);
				tmpNode = null;
				tmpData = null;
			}

			buckets[i] = null;
		}
		
		/**
		 * IMPORTANT: According to the instructions, every time the REAR of 
		 * the list, in stead of the front.
		 * So now get to the last node.
		 */
		setListAsRequired();
	}

	/**
	 * <p>
	 * IMPORTANT: According to the instructions, every time the REAR of 
	 * the list, in stead of the front.
	 * </p>
	 * <p>
	 * This function will set the masterListRear as required, i.e.,
	 * the front of masterListRear is actually the last one of it.
	 * </p>
	 */
	private void setListAsRequired()
	{
		String tmp = masterListRear.getData();
		
		while(!tmp.equals(masterListRear.getNext().getData()))
		{
			masterListRear = masterListRear.getNext();
		}
	}

}
