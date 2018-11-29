/*
 * Copyright 2014, Michael T. Goodrich, Roberto Tamassia, Michael H. Goldwasser
 *
 * Developed for use with the book:
 *
 *    Data Structures and Algorithms in Java, Sixth Edition
 *    Michael T. Goodrich, Roberto Tamassia, and Michael H. Goldwasser
 *    John Wiley & Sons, 2014
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package dsaj.sorting;

import net.datastructures.Queue;
import net.datastructures.LinkedQueue;
import java.util.Arrays;
import java.util.Comparator;

class MergeSort {

  //-------- support for top-down merge-sort of arrays --------
  /** Merge contents of arrays S1 and S2 into properly sized array S. */
  public static <K> void merge(K[] S1, K[] S2, K[] S, Comparator<K> comp) {
    int i = 0, j = 0;
    while (i + j < S.length) {
      if (j == S2.length || (i < S1.length && comp.compare(S1[i], S2[j]) < 0))
        S[i+j] = S1[i++];                     // copy ith element of S1 and increment i
      else
        S[i+j] = S2[j++];                     // copy jth element of S2 and increment j
    }
  }

  /** Merge-sort contents of array S. */
  public static <K> void mergeSort(K[] S, Comparator<K> comp) {
    int n = S.length;
    if (n < 2) return;                        // array is trivially sorted
    // divide
    int mid = n/2;
    K[] S1 = Arrays.copyOfRange(S, 0, mid);   // copy of first half
    K[] S2 = Arrays.copyOfRange(S, mid, n);   // copy of second half
    // conquer (with recursion)
    mergeSort(S1, comp);                      // sort copy of first half
    mergeSort(S2, comp);                      // sort copy of second half
    // merge results
    merge(S1, S2, S, comp);               // merge sorted halves back into original
  }

  //-------- support for top-down merge-sort of queues --------
  /** Merge contents of sorted queues S1 and S2 into empty queue S. */
  public static <K> void merge(Queue<K> S1, Queue<K> S2, Queue<K> S,
                                                        Comparator<K> comp) {
    while (!S1.isEmpty() && !S2.isEmpty()) {
      if (comp.compare(S1.first(), S2.first()) < 0)
        S.enqueue(S1.dequeue());           // take next element from S1
      else
        S.enqueue(S2.dequeue());           // take next element from S2
    }
    while (!S1.isEmpty())
      S.enqueue(S1.dequeue());             // move any elements that remain in S1
    while (!S2.isEmpty())
      S.enqueue(S2.dequeue());             // move any elements that remain in S2
  }

  /** Merge-sort contents of queue. */
  public static <K> void mergeSort(Queue<K> S, Comparator<K> comp) {
    int n = S.size();
    if (n < 2) return;                     // queue is trivially sorted
    // divide
    Queue<K> S1 = new LinkedQueue<>();     // (or any queue implementation)
    Queue<K> S2 = new LinkedQueue<>();
    while (S1.size() < n/2)
      S1.enqueue(S.dequeue());             // move the first n/2 elements to S1
    while (!S.isEmpty())
      S2.enqueue(S.dequeue());             // move remaining elements to S2
    // conquer (with recursion)
    mergeSort(S1, comp);                   // sort first half
    mergeSort(S2, comp);                   // sort second half
    // merge results
    merge(S1, S2, S, comp);                // merge sorted halves back into original
  }

  //-------- support for bottom-up merge-sort of arrays --------
  /** Merges in[start..start+inc-1] and in[start+inc..start+2*inc-1] into out. */
  public static <K> void merge(K[] in, K[] out, Comparator<K> comp,
                                                       int start, int inc) {
    int end1 = Math.min(start + inc, in.length);      // boundary for run 1
    int end2 = Math.min(start + 2 * inc, in.length);  // boundary for run 2
    int x=start;                                      // index into run 1
    int y=start+inc;                                  // index into run 2
    int z=start;                                      // index into output
    while (x < end1 && y < end2)
      if (comp.compare(in[x], in[y]) < 0)
        out[z++] = in[x++];                           // take next from run 1
      else
        out[z++] = in[y++];                           // take next from run 2
    if (x < end1) System.arraycopy(in, x, out, z, end1 - x);       // copy rest of run 1
    else if (y < end2) System.arraycopy(in, y, out, z, end2 - y);  // copy rest of run 2
  }

  @SuppressWarnings({"unchecked"})
  /** Merge-sort contents of data array. */
  public static <K> void mergeSortBottomUp(K[] orig, Comparator<K> comp) {
    int n = orig.length;
    K[] src = orig;                                   // alias for the original
    K[] dest = (K[]) new Object[n];                   // make a new temporary array
    K[] temp;                                         // reference used only for swapping
    for (int i=1; i < n; i *= 2) {                    // each iteration sorts all runs of length i
      for (int j=0; j < n; j += 2*i)                  // each pass merges two runs of length i
        merge(src, dest, comp, j, i);
      temp = src; src = dest; dest = temp;      // reverse roles of the arrays
    }
    if (orig != src)
      System.arraycopy(src, 0, orig, 0, n);           // additional copy to get result to original
  }
}
