/**
 * Progetto numero 2
 *
 * Ordinamento di Interi
 *
 * Algoritmi usati: Integersort, Quicksort, Mergesort, Heapsort, Radix-sort
 *
 * @author: Simone Martucci & Marco Notaro;
 *
 * @version 1.00 2012/5/24
 */
import asdlab.libreria.Ordinamento.*;

public class Ordinamento_Interi {

    public static void main(String[] args) {
    	String name, path, base_str;

    	/**
    	 * @param time_integer: vi verr� salvato il tempo impiegato dall'algoritmo integersort;
    	 * @param time_quick: vi verr� salvato il tempo impiegato dall'algoritmo quicksort;
    	 * @param time_merge: vi verr� salvato il tempo impiegato dall'algoritmo mergesort;
    	 * @param time_heap: vi verr� salvato il tempo impiegato dall'algoritmo heapsort;
    	 * @param time_radix: vi verr� salvato il tempo impiegato dall'algoritmo radix-sort;
    	 */
    	long time_integer=0, time_quick=0, time_merge=0, time_heap=0, time_radix=0;
    	/**
    	 * @param array_random[]: vi verr� salvato l'array da ordinare;
    	 * @param dimensione: questa sar� la dimensione dell'array decisa da utente successivamente;
    	 */
    	int array_random[], dimensione, scelta, base;
    	/**
    	 * @param alg: inizializzo l'oggetto come algoritmo di ordinamento;
    	 */
    	AlgoritmiOrdinamento alg= new AlgoritmiOrdinamento();

    	System.out.println("Crea un array di numeri casuali\n"); /*Per iniziare viene chiesto di creare un array di numeri casuali*/

		dimensione = CreaArray.decidi_dimensione(); /* Qui si inizializzera la dimensione dell'array richiamando la funzione dedicata */
		array_random = new int [dimensione]; 		/* Inizializzo array */
		CreaArray.interi(array_random, dimensione); /* Rimando alla funzione specifica per riempire l'array con numeri casuali */

		/**
		 * Il ciclo do-while serve per mandare in loop il programma e fare i test sull'array quante volte si vuole
		 * e seguendo il precorso che pi� si desidera;
		 */
		
		System.out.println("Inserisci il percorso dove salvare il file\nEs: C:\\percorso\\file\\\n");
		path = Read.readString();
		System.out.println("Inserisci il nome del file\nEs:test.txt\n");
		name = Read.readString();

		do {

		/*Slezione Algoritmo di ordinamento*/

			System.out.println("Crea un nuovo array di numeri casuali oppure scegli il tipo di algoritmo che vuoi utilizzare per ordinare l'array\n"+
							   "0 - Crea array random;\n"+
							   "1 - IntegerSort;\n"+
							   "2 - QuickSort;\n"+
							   "3 - MergeSort;\n"+
							   "4 - HeapSort;\n"+
							   "5 - RadixSort;\n"+
							   "6 - Se si desidera uscire;\n");
			scelta = Read.readInt();
			while(scelta<0 || scelta>6){
				System.out.println("Scelta non valida: Inserire un numero comreso tra 0 e 7\n");
				scelta = Read.readInt();
			}

		/* Algoritmo selezionato */

		 	/**
		 	 * invece di una serie di if-else � stata usata la funzione switch
		 	 * a seconda del caso si viene rimandati alla funzione di ordinamento scelta precedentemente
		 	 */

    	 	switch (scelta) {
 				case 0:														/* Il case 0 ricrea un'array con numeri random che sovrascriver� il precedente */
 					dimensione = CreaArray.decidi_dimensione();				/* Scelgo la dimensione del nuovo array */
 					array_random = new int [dimensione];					/* Inizializzo l'array */
 					CreaArray.interi(array_random, dimensione);	/* Invoco la funzione per ricreare l'array */
 				break;

 				case 1:
 					/* richiama la funzione di ordinamento relativa all'algoritmo integer sort */
					time_integer = Ordinamento.integersort(array_random, dimensione, alg);
					System.out.println("Tempo ordinamento array di "+dimensione+" elementi con IntegerSort: "+(double) time_integer/1000000+"ms\n");
					FileWrite.salva("IntegerSort", (double) time_integer/1000000, dimensione, path, name);
				break;

 				case 2:
 					/* richiama la funzione di ordinamento relativa all'algoritmo quick sort */
 					time_quick = Ordinamento.quicksort(array_random, dimensione, alg);
					System.out.println("Tempo ordinamento array di "+dimensione+" elementi con QuickSort: "+(double) time_quick/1000000+"ms\n");
					FileWrite.salva("QuickSort", (double) time_quick/1000000, dimensione, path, name);
 				break;

 				case 3:
 					/* richiama la funzione di ordinamento relativa all'algoritmo merge sort */
 					time_merge = Ordinamento.mergesort(array_random, dimensione, alg);
					System.out.println("Tempo ordinamento array di "+dimensione+" elementi con MergeSort: "+(double) time_merge/1000000+"ms\n");
					FileWrite.salva("MergeSort", (double) time_merge/1000000, dimensione, path, name);
 				break;

 				case 4:
 					/* richiama la funzione di ordinamento relativa all'algoritmo heap sort */
 					time_heap = Ordinamento.heapsort(array_random, dimensione, alg);
					System.out.println("Tempo ordinamento array di "+dimensione+" elementi con HeapSort: "+(double) time_heap/1000000+"ms\n");
					FileWrite.salva("HeapSort", (double) time_heap/1000000, dimensione, path, name);
 				break;

 				case 5:
 					/* richiama la funzione di ordinamento relativa all'algoritmo radix sort */
 					System.out.println("Scegliere la base del Radix-Sort: \n");
 					base = Read.readInt();
 					time_radix = Ordinamento.radixsort(array_random, dimensione, alg, base);
					System.out.println("Tempo ordinamento array di "+dimensione+" elementi con Radix-Sort: "+(double) time_radix/1000000+"ms\n");
					base_str = Integer.toString(base);
					FileWrite.salva("Radix-Sort base "+base_str+" " , (double) time_radix/1000000, dimensione, path, name);
 				break;
 			}

		} while (scelta != 6);

    }
}