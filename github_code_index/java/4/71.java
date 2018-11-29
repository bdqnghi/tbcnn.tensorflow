package sortieralgorithmen;


public class Insertion {
	
	/**
	 * Rekursive Implementierung des Insertion-Sort Algorithmus
	 * @param a Integer-Array
	 * @param sortiert Anzahl der bereits sortierten Stellen
	 * @return sortiertes Array
	 */
	public static int[] sortiereRekursiv(int[] a, int sortiert) {
		//Abbruchkriterium
		if(sortiert >= a.length) return a;
		
		int i = 1;
		
		//Position der neuen Zahl finden
		while (a[i] < a[sortiert]) i++;
		
		//Zahlen tauschen bis Reihenfolge wiederhergestellt
		while (i < sortiert) {
			a[0] = a[i];
			a[i] = a[sortiert];
			a[sortiert] = a[0];
			i++;
		}
		//Sentinel resetten
		a[0] = -1;
		return sortiereRekursiv(a, sortiert + 1);
	}
	
	/**
	 * Rekursive Implementierung des Insertion-Sort Algorithmus
	 * @param a Integer-Array
	 * @return sortiertes Integer-Array
	 */
	public static int[] sortiereIterativ(int[] a){
		for(int sortiert = 0; sortiert < a.length; sortiert++) {
			int i = 1;
		
			//Position der neuen Zahl finden
			while (a[i] < a[sortiert]) i++;
			
			//Zahlen tauschen bis Reihenfolge wiederhergestellt
			while (i < sortiert) {
				a[0] = a[i];
				a[i] = a[sortiert];
				a[sortiert] = a[0];
				i++;
			}
			//Sentinel resetten
			a[0] = -1;
		}
		return a;
	}
}
