// Merge Sort

// divide list into even indices list and odd indices list
// and merge them.

//;; merge : SortedList SortedList -> SortedList
//;; merges its two arguments
//;; strategy: recur on (rest lst1) or (rest lst2)
//;; HALTING MEASURE: (length lst1) + (length lst2) 
//(define (merge lst1 lst2)
//  (cond
//    [(empty? lst1) lst2]
//    [(empty? lst2) lst1]
//    [(< (first lst1) (first lst2))
//     (cons (first lst1) (merge (rest lst1) lst2))]
//    [else
//     (cons (first lst2) (merge lst1 (rest lst2)))]))
//
//
//;; merge-sort : RealList -> SortedList
//(define (merge-sort lst)
//  (cond
//    [(empty? lst) lst]
//    [(empty? (rest lst)) lst]
//    [else
//      (local
//       ((define evens (even-elements lst))
//        (define odds  (odd-elements lst)))
//       (merge 
//        (merge-sort evens)
//        (merge-sort odds)))]))



package leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MergeSort {

  public static void main(String[] args) {
    MergeSort m = new MergeSort();
    List<Integer> list = Arrays.asList(1, 4, 8, 10, -24, -6, 9, 21, 45, 1234, 20, 58, 77,14);
    for (int i : m.mergeSort(list))
      System.out.print(i + " ");
  }

  public List<Integer> mergeSort(List<Integer> list) {
    if (list.size() < 2) // if the list has 1 or no elements, stop recursing and start merging.
      return list;
    return merge(mergeSort(evenList(list)), mergeSort(oddList(list)));
  }

  public List<Integer> evenList(List<Integer> list) {
    List<Integer> evenList = new ArrayList<Integer>();
    for (int i = 0; i < list.size(); i++)
      if (i % 2 == 0)
        evenList.add(list.get(i));
    return evenList;
  }

  public List<Integer> oddList(List<Integer> list) {
    List<Integer> oddList = new ArrayList<Integer>();
    for (int i = 0; i < list.size(); i++)
      if (i % 2 != 0)
        oddList.add(list.get(i));
    return oddList;
  }

  public List<Integer> merge(List<Integer> list1, List<Integer> list2) {
    if (list1.isEmpty())
      return list2;
    else if (list2.isEmpty())
      return list1;
    else if (list1.get(0) < list2.get(0))
      return cons(list1.get(0), merge(rest(list1), list2));
    else
      return cons(list2.get(0), merge(list1, rest(list2)));
  }

  public List<Integer> rest(List<Integer> list) {
    List<Integer> restList = new ArrayList<Integer>(list);
    restList.remove(0);
    return (restList);
  }

  public List<Integer> cons(int a, List<Integer> list) {
    List<Integer> consedList = new ArrayList<Integer>(list);
    consedList.add(0, a);
    return (consedList);
  }

}
