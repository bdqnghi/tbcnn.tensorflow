package com.github.temptatio.shellsort;

/**
 * Diese Klasse implementiert Shell-Sort zum Sortieren eines Arrays mit der Abstandsfolge 2^k
 *
 */
public class Shellsort {

	/**
	 * Diese Methode sortiert ein double-Array
	 * 
	 * @param array Das zu sortierende Array
	 * @param unterteilungen Die Zahl der Sequenzen, in die das Array unterteilt wird
	 */
	public static void sort(double[] array, final Abstandsfolge abstandsfolge) {

		final int laenge = array.length;

		while (abstandsfolge.hasNext()) {
			final int aktuelleSchrittweite = abstandsfolge.next().intValue();

			for (int i = aktuelleSchrittweite; i < laenge; ++i) {
				for (int j = i % aktuelleSchrittweite; j < i; j += aktuelleSchrittweite) {
					if (array[j] > array[i]) {
						double tmp = array[i];
						array[i] = array[j];
						array[j] = tmp;
					}

				}
			}
		}

	}

}
