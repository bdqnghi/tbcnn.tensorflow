/*
 * Assignment #12: Compare sorting algorithms
 *
 * CMPE 180-92 Data Structures and Algorithms in C++
 * Department of Computer Engineering
 * R. Mak, Nov. 20, 2016
 */
#include <string>
#include "MergeSort.h"

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
   if(list.get_size()<2)
   {
      return;
  }
       LinkedList list1;
    LinkedList list2;
    list.split(list1, list2);
    
    mergesort(list1);
    mergesort(list2);
    merge(list, list1, list2 );
    
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
    list.clear();
    int i=0;
    int j=0;
    int list1_len= sublist1.get_size();
    int list2_len= sublist2.get_size();
    Node *temp1 = sublist1.get_head();
    Node *temp2 = sublist2.get_head();
    
    
    
    while(i<list1_len && j<list2_len)
  {
        
        compare_count++;
        if(temp1->value <= temp2->value)
        {
            list.add(temp1->value);
            sublist1.remove_head();
            i++;
            move_count++;
            
        }
        else 
        {
            list.add(temp2->value);            sublist2.remove_head();
            j++;
            move_count++;
        }
            }
    
while (i<list1_len)
{
    
      list.add(temp1->value);
 i++;   
 move_count++;
     
   
}

while (j<list2_len)
{
 
     list.add(temp2->value);
 
 j++;
     move_count++;
 
    
}
    
}

/**
 * Clear the data.
 */
void MergeSort::clear() 
{ 
    data.clear(); 
    
}
