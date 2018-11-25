#include <string>
#include "MergeSort.h"


MergeSort::MergeSort(string name) : ListSorter(name) {}


MergeSort::~MergeSort() {}


void MergeSort::run_sort_algorithm()
    throw (string)
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





void MergeSort::merge(LinkedList& list,
                      LinkedList& sublist1, LinkedList& sublist2)
{
    
	

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


void MergeSort::clear() { data.clear(); }
