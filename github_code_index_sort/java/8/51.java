package unittest;
import java.util.Comparator;

import queues.LinkedQueue;
import queues.Queue;


class QuickSort {

  //-------- support for top-down quick-sort of queues --------
  /** Quick-sort contents of a queue. */
  public static <K> void quickSort(Queue<K> S, Comparator<K> comp) {
    int n = S.size();
    if (n < 2) return;                       // queue is trivially sorted
    // divide
    K pivot = S.first();                     // using first as arbitrary pivot
    Queue<K> L = new LinkedQueue<>();
    Queue<K> E = new LinkedQueue<>();
    Queue<K> G = new LinkedQueue<>();
    while (!S.isEmpty()) {                   // divide original into L, E, and G
      K element = S.dequeue();
      int c = comp.compare(element, pivot);
      if (c < 0)                             // element is less than pivot
        L.enqueue(element);
      else if (c == 0)                       // element is equal to pivot
        E.enqueue(element);
      else                                   // element is greater than pivot
        G.enqueue(element);
    }
    // conquer
    quickSort(L, comp);                      // sort elements less than pivot
    quickSort(G, comp);                      // sort elements greater than pivot
    // concatenate results
    while (!L.isEmpty())
      S.enqueue(L.dequeue());
    while (!E.isEmpty())
      S.enqueue(E.dequeue());
    while (!G.isEmpty())
      S.enqueue(G.dequeue());
  }

  //-------- support for in-place quick-sort of an array --------
  /** Quick-sort contents of a queue. */
  public static <K> void quickSortInPlace(K[] S, Comparator<K> comp) {
    quickSortInPlace(S, comp, 0, S.length-1);
  }

  /** Sort the subarray S[a..b] inclusive. */
  private static <K> void quickSortInPlace(K[] S, Comparator<K> comp,
                                                                   int a, int b) {
    if (a >= b) return;                // subarray is trivially sorted
    int left = a;
    int right = b-1;
    K pivot = S[b];
    K temp;                            // temp object used for swapping
    while (left <= right) {
      // scan until reaching value equal or larger than pivot (or right marker)
      while (left <= right && comp.compare(S[left], pivot) < 0) left++;
      // scan until reaching value equal or smaller than pivot (or left marker)
      while (left <= right && comp.compare(S[right], pivot) > 0) right--;
      if (left <= right) {             // indices did not strictly cross
        // so swap values and shrink range
        temp = S[left]; S[left] = S[right]; S[right] = temp;
        left++; right--;
      }
    }
    // put pivot into its final place (currently marked by left index)
    temp = S[left]; S[left] = S[b]; S[b] = temp;
    // make recursive calls
    quickSortInPlace(S, comp, a, left - 1);
    quickSortInPlace(S, comp, left + 1, b);
  }
}
