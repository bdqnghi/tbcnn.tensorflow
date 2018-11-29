import java.util.Vector;

/* 
 * Mergesort using vectors (smaller compact version of LL)
 * Created by sjlu - steven lu on 5/8/2011
 */

public class mergesort
{
	public static void main(String[] args)
	{
		Vector<Integer> numbers = new Vector<Integer>();
		numbers.add(14);
		numbers.add(4);
		numbers.add(55);
		numbers.add(32);
		numbers.add(17);
		
		System.out.println(numbers);
		System.out.println(sort(numbers));
	}
		
	public static Vector<Integer> sort(Vector<Integer> numbers)
	{
		// the smallest partition we can contain is 1 element
		if (numbers.size() <= 1)
		{
			return numbers;
		}
		
		int middle = numbers.size()/2;
		// we partition this in half, left and right
		Vector<Integer> left_partition = partition(numbers, 0, middle);
		Vector<Integer> right_partition = partition(numbers, middle, numbers.size());
		
		// and then we send it back to ourself to partition the partitions
		// the recursion will stop when we reach the smallest partition
		left_partition = sort(left_partition);
		right_partition = sort(right_partition);
		
		// then we merge the left and right partitions accordingly
		return merge(left_partition, right_partition);
	}
	
	// this is just giving us a partition from beg index to end index 
	public static Vector<Integer> partition(Vector<Integer> vector, int begIndex, int endIndex)
	{
		Vector<Integer> tmp_vector = new Vector<Integer>();
		for (int i = begIndex; i < endIndex; i++)
		{
			tmp_vector.add(vector.get(i));
		}
		return tmp_vector;
	}
	
	public static Vector<Integer> merge(Vector<Integer> v1, Vector<Integer> v2)
	{
		Vector<Integer> tmp_vector = new Vector<Integer>();
		
		int v1c = 0;
		int v2c = 0;
		
		while (v1c < v1.size() || v2c < v2.size())
		{
			// if we iterated through one vector already
			// we can just add the other now
			if (v1c == v1.size())
			{
				tmp_vector.add(v2.get(v2c));
				v2c++;
				continue;
			}
			else if (v2c == v2.size())
			{
				tmp_vector.add(v1.get(v1c));
				v1c++;
				continue;
			}
			
			// we will see which element is greatest
			// add it, and then up its count
			if (v1.get(v1c) <= v2.get(v2c))
			{
				tmp_vector.add(v1.get(v1c));
				v1c++;
			}
			else
			{
				tmp_vector.add(v2.get(v2c));
				v2c++;
			}
		}
		
		return tmp_vector;
	}
}