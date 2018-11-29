import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;


/**
 * File: QuickSort.java
 *
 * Implementation von Quicksort. Verwendet generische ArrayList f�r Eingabedaten
 * und generischen Comparator um Datenelemente zu vergleichen. 
 */
public class QuickSort {

/**
 * Sortiert den array zwischen den Indizes left und right (mit Grenzen).
 */
public static <T> void quickSort(ArrayList<T> array, int left, int right, Comparator<T> comp) {
	
	Random rnd = new Random();
	if (right>left) {  // Abbruchbedingung der Rekursion
		T temp;        // temporaere Hilfsvariable zum swappen
  
		// *** 1. Pivotelement selektieren:
		T pivot = array.get((rnd.nextInt(right-left)+left));//Es wird ein zufälliger
  
		// *** 2. Aufteilung in Subsequenzen durchfuehren:
		int l = left-1;
		int r = right;
		do {
			do l++; while (comp.compare(array.get(l),pivot)<0);
			do r--; while (r>l && comp.compare(array.get(r),pivot)>0);

			// swap(array, l, r):
			temp = array.get(l);
			array.set(l, array.get(r));
			array.set(r, temp);
	
		} while (r>l);

		array.set(r, array.get(l));   // Korrektur: einmal zuviel getauscht

		// Pivotelement in sortierte Position bringen:
		array.set(l, pivot);
		array.set(right, temp);
  
		// *** 3. Rekursiv die beiden Subarrays sortieren:
		
		quickSort(array, left, l-1, comp);
		quickSort(array, l+1, right, comp);
		
    	}
  	}
}
/*
 * Output:
 *Anzahl zu sortierende Records: 100
   Erster QuickSort: 5 ms   QuickSort auf den bereits sortierten Daten: 3 ms
Anzahl zu sortierende Records: 200
   Erster QuickSort: 5 ms   QuickSort auf den bereits sortierten Daten: 4 ms
Anzahl zu sortierende Records: 400
   Erster QuickSort: 2 ms   QuickSort auf den bereits sortierten Daten: 2 ms
Anzahl zu sortierende Records: 800
   Erster QuickSort: 3 ms   QuickSort auf den bereits sortierten Daten: 4 ms
Anzahl zu sortierende Records: 1600
   Erster QuickSort: 6 ms   QuickSort auf den bereits sortierten Daten: 6 ms
Anzahl zu sortierende Records: 3200
   Erster QuickSort: 15 ms   QuickSort auf den bereits sortierten Daten: 16 ms
Anzahl zu sortierende Records: 6400
   Erster QuickSort: 76 ms   QuickSort auf den bereits sortierten Daten: 30 ms
Anzahl zu sortierende Records: 12800
   Erster QuickSort: 106 ms   QuickSort auf den bereits sortierten Daten: 60 ms
Anzahl zu sortierende Records: 25600
   Erster QuickSort: 358 ms   QuickSort auf den bereits sortierten Daten: 123 ms
Anzahl zu sortierende Records: 51200
   Erster QuickSort: 238 ms   QuickSort auf den bereits sortierten Daten: 234 ms
Anzahl zu sortierende Records: 102400
   Erster QuickSort: 507 ms   QuickSort auf den bereits sortierten Daten: 859 ms
Anzahl zu sortierende Records: 204800
   Erster QuickSort: 1376 ms   QuickSort auf den bereits sortierten Daten: 1329 ms
Anzahl zu sortierende Records: 409600
   Erster QuickSort: 2412 ms   QuickSort auf den bereits sortierten Daten: 1927 ms
Anzahl zu sortierende Records: 809600
   Erster QuickSort: 6142 ms   QuickSort auf den bereits sortierten Daten: 3957 ms
Anzahl zu sortierende Records: 1619200
Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
	at StudentIn.clone(StudentIn.java:34)
	at DataGenerator.deepCopyArray(DataGenerator.java:40)
	at DataGenerator.generateNewData(DataGenerator.java:27)
	at SortTestApp.main(SortTestApp.java:27)
 * */

