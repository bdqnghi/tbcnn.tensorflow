#include <string>
#include "MergeSort.h"

/**
 * Constructor.
 * @param name the name of the algorithm.
 */
MergeSort::MergeSort(string name) : ListSorter(name) {}

/**
 * Destructor.
 */
MergeSort::~MergeSort() {}

/**
 * Run the mergesort algorithm.
 * @throws an exception if an error occurred.
 */
void MergeSort::run_sort_algorithm()
    throw (string)
{
    // Defensive programming: Make sure we end up
    // with the same size list after sorting.
    int size_before = data.get_size();

    mergesort(data);

    // Check sizes.
    int size_after = data.get_size();
    if (size_before != size_after)
    {
        string message = "***** Size mismatch: before " +
                         to_string(size_before) + ", size after " +
                         to_string(size_after);
        throw message;
    }
}

/**
 * The mergesort algorithm recursively splits and merges data lists.
 * @param list the list of data to sort.
 */
void MergeSort::mergesort(LinkedList& list)
{
    /***** Complete this member function. *****/

	// Reference D S Malik

	LinkedList sublist1, sublist2;

	if (list.get_head() != list.get_tail())
	{
		list.split(sublist1, sublist2);

		if (sublist1.get_head() != nullptr)
		{
			mergesort(sublist1);
		}

		if (sublist2.get_head() != nullptr)
		{
			mergesort(sublist2);
		}

		merge(list, sublist1, sublist2);
	}

}

/**
 * Merge two sublists back into a single list.
 * @param list the merged list.
 * @param sublist1 the first sublist.
 * @param sublist2 the second sublist.
 */



void MergeSort::merge(LinkedList& list,
                      LinkedList& sublist1, LinkedList& sublist2)
{
    /***** Complete this member function. *****/
	// Reference D S Malik 2nd Edition

	if (sublist1.get_head() == nullptr)
	{
		if (sublist2.get_head() != nullptr)
		{
			list.concatenate(sublist2);
		}
	}
	else if (sublist2.get_head() == nullptr)
	{
		if (sublist1.get_head() != nullptr)
		{
			list.concatenate(sublist1);
		}
	}
	else if (sublist1.get_head() != nullptr and sublist2.get_head() != nullptr)
	{
		move_count++;
		while (sublist1.get_head() != nullptr && sublist2.get_head() != nullptr)
		{
			move_count++;
			compare_count++;
			if (sublist1.get_head()->element.get_value() < sublist2.get_head()->element.get_value())
			{
				list.add(sublist1.remove_head());
			}
			else
			{
				list.add(sublist2.remove_head());
			}
		}

		if (sublist1.get_head() == nullptr)
		{
			list.concatenate(sublist2);
		}

		if (sublist2.get_head() == nullptr)
		{
			list.concatenate(sublist1);
		}
	}

}

/**
 * Clear the data.
 */
void MergeSort::clear() { data.clear(); }
