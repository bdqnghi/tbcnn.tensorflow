#include <string>
#include "MergeSort.h"

MergeSort::MergeSort() : ListSorter("Mergesort") {}

MergeSort::~MergeSort() {}

void MergeSort::run_sort_algorithm() throw(string)
					{
	
	
	int size_before = data.get_size();

	mergesort(data);

	
	int size_after = data.get_size();
	if (size_before != size_after)
	{
		string message = "***** Size mismatch: before " +
				to_string(size_before) + ", size after " +
				to_string(size_after);
		throw message;
	}
					}

void MergeSort::mergesort(LinkedList& list) 
{

	if (list.get_size() != 0 && list.get_size() != 1) {
		LinkedList list1;
		LinkedList list2;
		
		list.split(list1, list2);

		mergesort(list1);  
		mergesort(list2);  
		
		merge(list, list1, list2);  
	}
}

void MergeSort::merge(LinkedList& list,
		LinkedList& sublist1, LinkedList& sublist2)
{
	list.reset();
	Node *list1 = sublist1.get_head(); 

	Node *list2 = sublist2.get_head(); 

	while (list1 != nullptr && list2 != nullptr) {

		if (list1->element.get_value() <= list2->element.get_value()) 
		{
			list.add(sublist1.remove_head());
			list1 = sublist1.get_head();
		} else
		{
			list.add(sublist2.remove_head());
			list2 = sublist2.get_head();
		}
		
		compare_count++;
	}

	if (list1 != nullptr) {
		list.concatenate(sublist1);
		
	}

	if (list2 != nullptr) {
		list.concatenate(sublist2);
		
	}
}



void MergeSort::clear() { data.clear(); }
