/*
 * Assignment #12: Compare sorting algorithms
 *
 * CMPE 180-92 Data Structures and Algorithms in C++
 * Department of Computer Engineering
 * R. Mak, Nov. 20, 2016
 */
#include <string>
#include "MergeSort.h"
#include <iostream>
/**
 * Default constructor.
 */
MergeSort::MergeSort() : ListSorter() {}

/**
 * Destructor.
 */
MergeSort::~MergeSort() {}

/**
 * Get the name of this sorting algorithm.
 * @return the name.
 */
string MergeSort::name() const { return "Mergesort"; }

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
    //reference: http://stackoverflow.com/questions/5630994/merge-sorting-a-linked-list
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

/**
 * Merge two sublists back into a single list.
 * @param list the merged list.
 * @param sublist1 the first sublist.
 * @param sublist2 the second sublist.
 */
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

/**
 * Clear the data.
 */
void MergeSort::clear() { data.clear(); }
