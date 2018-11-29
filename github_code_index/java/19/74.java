import java.util.*;
//import java.lang.Object;

class bucketsort{
	public static <E extends Comparable<E>> void main(String[] args){
		List<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i<10; i++)
			list.add(i);
		Integer[] a = list.toArray(new Integer[list.size()]);		
		
		List<Integer> array2 = new ArrayList<Integer>();
		for (int i = 1; i<4; i++)
			array2.add(i*2);
		Integer[] b = array2.toArray(new Integer[array2.size()]);
		E[] c = (E[])a;
		E[] d = (E[])b;
		c = sort(c, d);
		for (int i=0; i < a.length; i++)
			System.out.print(a[i]);
	}
	
	public static <E extends Comparable<E>> E[] sort(E[] array, E[] separator){
		//Buckets erstellen
		Bucket<Object>[] buckets = (Bucket<Object>[])new Bucket[separator.length +1];
		//in Buckets sortieren
		for (int i = 0; i<array.length; i++){
			int j = 0;
			while(separator[j].compareTo(array[i])==1 && j < separator.length -1){
				j++;
			}
			buckets[j].add(array[i]);
		}
		//in Buckets sortieren
		E[] bigarray = (E[]) new Object[0];
		for (int i = 0; i < buckets.length; i++){
			E[] arr = (E[])new Object[buckets[i].getElem().size()];
			buckets[i].getElem().toArray(arr);
			//Zusammensetzen und sortieren
			bigarray = addAll(bigarray, insertionsort(arr));
		}
		return bigarray;
	}
	
	public static <E extends Comparable<E>> E[] addAll(E[] eins, E[] zwei){		//addiert 2 arrays
		E[] neu = (E[])new Object[eins.length+zwei.length];
		for (int i = 0; i<eins.length;i++)
			neu[i] = eins[i];
		for (int i = 0; i<zwei.length;i++)
			neu[i+eins.length]= zwei[i];
		return neu;
	}
	
	public static <E extends Comparable<E>> E[] insertionsort (E[] array){ 		//Sortiert ein array
		int count = 0;
		for (int i = 1; i < array.length; i++){
				E a = array[i];
			int j = i;
			while(j > 0 && array[j-1].compareTo(a) > 0){
				array[j] = array[j-1];
				j--;
				count++;
			}
			if (j > 0)
				count++;
			array[j] = a;
		}
		return array;
	}	
	
	
}

class Bucket<E>{
	private LinkedList<E> elem;
	public Bucket(){
		this.elem = new LinkedList<E>();
	}
	public void add(E a){
		elem.add(a);
		return;		
	}
	public LinkedList<E> getElem(){
		return elem;
	}
	
}
