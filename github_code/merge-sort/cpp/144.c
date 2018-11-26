#include <string>
#include "MergeSort.h"

MergeSort::MergeSort() : ListSorter("Mergesort") {}

MergeSort::~MergeSort() {}

void MergeSort::run_sort_algorithm() throw(string)
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

void MergeSort::mergesort(LinkedList& list) //algorithm recursively splits and merges data lists.
{

	if (list.get_size() != 0 && list.get_size() != 1) {
		LinkedList list1;
		LinkedList list2;
		//move_count++;
		list.split(list1, list2);

		mergesort(list1);  // recursively sort the first sublist
		mergesort(list2);  // recursively sort the second sublist
		//move_count++;
		merge(list, list1, list2);  // merge the two sublists back together
	}
}

void MergeSort::merge(LinkedList& list,
		LinkedList& sublist1, LinkedList& sublist2)
{
	list.reset();
	Node *list1 = sublist1.get_head(); //pointer to the head node 1st List

	Node *list2 = sublist2.get_head(); //pointer to the head node 2nd List

	while (list1 != nullptr && list2 != nullptr) {

		if (list1->element.get_value() <= list2->element.get_value()) //compare the first nodes
		{
			list.add(sublist1.remove_head());
			list1 = sublist1.get_head();
		} else
		{
			list.add(sublist2.remove_head());
			list2 = sublist2.get_head();
		}
		//move_count++;
		compare_count++;
	}

	if (list1 != nullptr) {
		list.concatenate(sublist1);
		//move_count++;
	}

	if (list2 != nullptr) {
		list.concatenate(sublist2);
		//move_count++;
	}
}


/**
 * Clear the data.
 */
void MergeSort::clear() { data.clear(); }
