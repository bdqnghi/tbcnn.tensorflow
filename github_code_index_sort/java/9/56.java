package sortieralgorithmen;

public class Selection {
	
	/**
	 * Rekursive Umsetzung des Selection-Sort Algoritmus
	 * @param a Integer-Array
	 * @param sortiert bereits sortierte Stellen
	 * @return sortiertes Integer-Array
	 */
	public static int[] sortiereRekursiv(int[] a, int sortiert) {
		//Abbruchbedingung
		if (sortiert > a.length-1) return a;
		
		//Variablendeklaration
		int i = sortiert;
		int position = sortiert;
		
		//Suche der Position der kleinsten unsortierten Zahl
		while (i < a.length) {
			if (a[i] < a[position]) position = i;
			i++;
		}
		
		//Tauschen der kleinsten Zahl mit der letzten (ab sofort) sortierten Stelle
		a[0] = a[sortiert];
		a[sortiert] = a[position];
		a[position] = a[0];
		
		a[0] = -1;
		
		return sortiereRekursiv(a, sortiert+1);
	}
	
	/**
	 * Iterative Umsetzung des Selection-Sort Algorithmus
	 * @param a Integer-Array
	 * @return sortiertes Integer-Array
	 */
	public static int[] sortiereIterativ(int[] a) {
		//Variablendeklaration
		int i = 0;
		int position = 0;
		
		for (int sortiert = 0; sortiert < a.length; sortiert++) {
			
			//Wertezuweisung f�r Suche
			i = sortiert;
			position = sortiert;
			
			//Suche der Position der kleinsten unsortierten Zahl 
			while (i < a.length) {
				if (a[i] < a[position]) position = i;
				i++;
			}
			
			//Positionen tauschen
			a[0] = a[sortiert];
			a[sortiert] = a[position];
			a[position] = a[0];	
		}
		
		a[0] = -1;
		
		return a;
	}
}
