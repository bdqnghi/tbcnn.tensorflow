
#include <string>
#include "MergeSort.h"
#include <iostream>

MergeSort::MergeSort() : ListSorter() {}


MergeSort::~MergeSort() {}


string MergeSort::name() const { return "Mergesort"; }


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
    
    if(list.get_size() > 1){
        LinkedList *list1 = new LinkedList();
        LinkedList *list2 = new LinkedList();
        list.split(*list1, *list2);
        move_count += 2;
        mergesort(*list1);
        mergesort(*list2);
        merge(list, *list1, *list2);
    }
}


void MergeSort::merge(LinkedList& list,
                      LinkedList& sublist1, LinkedList& sublist2)
{
    move_count++;
    if(sublist1.get_size() == 0 && sublist2.get_size() == 0){
        sublist1.clear();
        sublist2.clear();
    }
    else if(sublist1.get_size() == 0) list.concatenate(sublist2);
    else if(sublist2.get_size() == 0) list.concatenate(sublist1);
    else if(sublist1.get_head()->value > sublist2.get_head()->value){
        compare_count++;
        list.add(sublist2.remove_head());
        merge(list, sublist1, sublist2);
    }else{
        compare_count++;
        list.add(sublist1.remove_head());
        merge(list, sublist1, sublist2);
    }
}


void MergeSort::clear() { data.clear(); }
