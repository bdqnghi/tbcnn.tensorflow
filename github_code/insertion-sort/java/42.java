/**
 * @author Luca Castelli Aleardi (Ecole Polytechnique, INF311, 2014) 
 * 
 * This class provides an implementation of insertion sorting algorithm
 */
public class InsertionSort implements SortingAlgorithm {

	final ElementComparator c; // comparator defining a total order
	final Element[] t; // array of elements to sort
	//Draw d = new Draw("InsertionSort", 1000, 200); // useful for drawings and
													// animations
	public InsertionSort(Element[] t, ElementComparator c) {
		this.t = t;
		this.c = c;
		//d.draw(t);
	}

	/**
	 * Copy the input element e at position k in the array this.t
	 */
	public void replace(int k, Element e) {
		//d.erase(k, t[k]);
		t[k] = e; // recopie finale
		//d.blink(k, t[k]);
	}

	public void run() {
		for(int i = 1; i < t.length; i++){
			Element tmps = t[i];
			int k=i;
			while((k > 0) && (tmps.isSmaller(t[k-1],c))){
				t[k]=t[k-1];
				k=k-1;
			}
			replace(k,tmps);
			//d.draw(t);
		}
	}
	
}
