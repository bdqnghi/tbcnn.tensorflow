package ArbolHeapSort;

import java.util.ArrayList;

public class HeapSortMax {
	public int aux, posicion,raiz,pad,hij;
	public NodoHeapSort[] arbolHeapSortMax;
	private ArrayList<String> arbol=new ArrayList<String>();
	
	public HeapSortMax(){
		aux=0;
		posicion=0;
		raiz=0;
		arbolHeapSortMax=new NodoHeapSort[255];
		
	}
	public synchronized void insertar(int pesoN, String urlN){
		NodoHeapSort nuevo= new NodoHeapSort(pesoN, urlN);
		NodoHeapSort auxiliarP;
		NodoHeapSort auxiliarH;
		if (posicion%2==1) {
			nuevo.padre=posicion/2;
		} else {
			nuevo.padre=posicion/2-1;
		}
		nuevo.hijoIzquierdo=posicion*2+1;
		nuevo.hijoDerecho=posicion*2+2;
		if (arbolHeapSortMax[0]==null) {
			arbolHeapSortMax[posicion]=nuevo;
			posicion++;
		} 
		else {
			if (arbolHeapSortMax[nuevo.padre].peso>=nuevo.peso) {
				arbolHeapSortMax[posicion]=nuevo;
				posicion++;
			}
			else {
				arbolHeapSortMax[posicion]=nuevo;
				hij=posicion;
				pad=nuevo.padre;
				aux=pad;
				while(arbolHeapSortMax[pad].peso<arbolHeapSortMax[hij].peso) {
					auxiliarP=arbolHeapSortMax[pad];
					auxiliarH=arbolHeapSortMax[hij];
					arbolHeapSortMax[pad]=auxiliarH;
					arbolHeapSortMax[hij]=auxiliarP;
					hij=pad;
					pad=hij/2;
				}
				posicion++;
				ordenarFamilia();
			}
			
			
		}
	}
	public synchronized void imprimir() {
		for (int i = 0; arbolHeapSortMax[i] != null; i++) {
			System.out.println(arbolHeapSortMax[i].peso+" : "+arbolHeapSortMax[i].url);
		}
		
	}
	public synchronized void ordenarFamilia(){
		for (int i = 0; arbolHeapSortMax[i]!=null; i++) {
			arbolHeapSortMax[i].hijoDerecho=i*2+2;
			arbolHeapSortMax[i].hijoIzquierdo=i*2+1;
			if (i%2==1) {
				arbolHeapSortMax[i].padre=i/2;
			} else {
				arbolHeapSortMax[i].padre=i/2-1;
			}
		}
	}
	public synchronized boolean buscar(String urln){
		for (int i = 0; arbolHeapSortMax[i] != null;) {
			if (arbolHeapSortMax[i].url.equalsIgnoreCase(urln)) {
				return true;
				
			} else {
				i++;

			}
		}
		return false;
	}
	public synchronized ArrayList<String> obtener(){
		for (int i = 0; arbolHeapSortMax[i]!=null; i++) {
			arbol.add(arbolHeapSortMax[i].url);
		}
		return arbol;
	}

	
	
	
	
	
	
	
	
	
}
