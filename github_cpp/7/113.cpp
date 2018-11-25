





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
    LinkedList list1,list2;
	if(list.get_head()==nullptr||list.get_head()->next==NULL)
		return;
	else{
		list.split(list1,list2);
		mergesort(list1);
		mergesort(list2);
		merge(list,list1,list2);
	}
}

void MergeSort::merge(LinkedList& list,
                      LinkedList& sublist1, LinkedList& sublist2)
{

	LinkedList buffer;

	    while(!(sublist1.get_head()==nullptr  || sublist2.get_head()==nullptr)){
	         this->compare_count++;
	        if((sublist1.get_head()->element.get_value()<sublist2.get_head()->element.get_value())||
	            (sublist1.get_head()->element.get_value()==sublist2.get_head()->element.get_value()))
	        {
	            buffer.add(sublist1.remove_head());
	        }
	        else
	        {
	            buffer.add(sublist2.remove_head());
	        }
	    }
	    if(sublist1.get_head()==nullptr){
	        buffer.concatenate(sublist2);
	    }
	    else if(sublist2.get_head()==nullptr){
	        buffer.concatenate(sublist1);
	    }
	    list.set(buffer.get_head(),buffer.get_tail(),buffer.get_size());
}

void MergeSort::clear() { data.clear(); }
