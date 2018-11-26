  /**
   * Sort the elements of sequence S in nondecreasing order according
   * to comparator c, using the merge-sort algorithm.
   **/
  public static void mergeSort (Sequence S, Comparator c) {
    int n = S.size();
    // a sequence with 0 or 1 element is already sorted
    if (n < 2) return;
    // divide
    int i = n;
    Sequence S1 = new NodeSequence();
    do { // move the first n/2 elements to S1
      S1.insertLast(S.remove(S.first()));
      i--;
    } while (i > n/2);
    Sequence S2 = new NodeSequence();
    do { // move the remaining n/2 elements to S2
      S2.insertLast(S.remove(S.first()));
      i--;
    } while (i > 0); // sequence S is now empty
    // recur
    mergeSort(S1,c);
    mergeSort(S2,c);
    //conquer
    merge(S1,S2,c,S);
  }
