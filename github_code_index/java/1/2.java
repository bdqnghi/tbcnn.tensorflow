package recorrido;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * Clase que busca el recorrido de un nodo a otro dentro de un grafo.
 * <p>
 * El grafo puede ser dirigido o no, como ponderado y no ponderado. <br>
 */
public class BFS {
	// boolean[] estados;
	// int[] distancia;
	//
	// int[] padre;
	// LinkedList<Nodo> cola;
	// /**
	// * Nodo de origen. <br>
	// */
	// Nodo nodoOrigen;
	// /**
	// * Nodos del grafo. <br>
	// */
	// Nodo[] nodos;
	//
	// public BFS(int[][] matrizAdyacencia, Nodo nodoOrigen, Nodo[] nodos) {
	// cola = new LinkedList<Nodo>();
	// this.nodos = nodos;
	// this.nodoOrigen = nodoOrigen;
	// estados = new boolean[matrizAdyacencia.length];
	// distancia = new int[matrizAdyacencia.length];
	// padre = new int[matrizAdyacencia.length];
	//
	// for (int j = 0; j < matrizAdyacencia.length; j++) {
	// estados[j] = false;
	// distancia[j] = Integer.MAX_VALUE;
	// }
	//
	// estados[nodoOrigen.getNumero()] = true;
	// distancia[nodoOrigen.getNumero()] = 0;
	// cola.addFirst(nodoOrigen);
	//
	// while (!cola.isEmpty()) {
	// Nodo u = cola.removeFirst();
	// // Busco los adyacentes.
	// for (int i = 0; i < matrizAdyacencia.length; i++) {
	// int costo = matrizAdyacencia[u.numero][i];
	// if (costo < Integer.MAX_VALUE) {
	//
	// if (estados[i] == false) {
	// estados[i] = true;
	// distancia[i] = distancia[u.numero] + 1;
	// padre[i] = u.numero;
	// cola.addFirst(nodos[i]);
	// }
	// }
	// }
	// }
	// }
	//
	// public Stack<Integer> recorrido(Nodo NodoDestino) {
	//
	// Stack<Integer> pilaResultado = new Stack<Integer>();
	// int aVisitar = padre[NodoDestino.numero];
	//
	// if (this.nodoOrigen.numero != aVisitar && estados[aVisitar] == true) {
	// pilaResultado.push(NodoDestino.numero);
	// pilaResultado.push(aVisitar);
	// } else {
	// if (this.nodoOrigen.numero == aVisitar && this.nodoOrigen.numero ==
	// NodoDestino.numero
	// && estados[aVisitar] == true) {
	// pilaResultado.push(aVisitar);
	// return pilaResultado;
	// }
	//
	// pilaResultado.push(Integer.MIN_VALUE);
	// return pilaResultado;
	// }
	//
	// while (this.nodoOrigen.numero != aVisitar) {
	// pilaResultado.push(padre[aVisitar]);
	// aVisitar = padre[aVisitar];
	//
	// }
	// // pilaResultado.push(nodoOrigen.numero);
	// return pilaResultado;
	// }

	boolean[] estados;
	/**
	 * Distancia entre los nodos. <br>
	 */
	int[] distancia;
	/**
	 * Nodo de referencia para armar el camino. <br>
	 */
	int[] padre;
	/**
	 * Nodo de origen. <br>
	 */
	// Nodo nodoOrigen;
	private int nodoOrigen;
	/**
	 * Aristas del grafo. <br>
	 */
	Nodo[] nodos;
	/**
	 * Cantidad de nodos del grafo. <br>
	 */
	private int cantidadNodos;
	private int[][] matrizAdyacencia;

	// /**
	// *
	// * @param matrizAdyacencia
	// * Matriz de adyacencia del grafo. <br>
	// * @param nodoOrigen
	// * Nodo inicial del recorrido. <br>
	// * @param nodos
	// * Aristas entre nodos del grafo. <br>
	// */
	// public BFS(int[][] matrizAdyacencia, Nodo nodoOrigen, Nodo[] nodos) {
	// Queue<Nodo> cola = new LinkedList<Nodo>();
	// this.nodos = nodos;
	// this.nodoOrigen = nodoOrigen;
	// this.cantidadNodos = matrizAdyacencia.length;
	// this.estados = new boolean[this.cantidadNodos];
	// this.distancia = new int[this.cantidadNodos];
	// this.padre = new int[this.cantidadNodos];
	// for (int j = 0; j < this.cantidadNodos; j++) {
	// this.distancia[j] = Integer.MAX_VALUE;
	// this.padre[j] = Integer.MAX_VALUE;
	// }
	// estados[nodoOrigen.getNodoInicio()] = true;
	// distancia[nodoOrigen.getNodoInicio()] = 0;
	// Nodo actual;
	// cola.add(this.nodoOrigen);
	// while (!cola.isEmpty()) {
	// actual = cola.poll();
	// // Busco los adyacentes.
	// for (int i = 0; i < this.cantidadNodos; i++) {
	// if (actual.getCosto() != Integer.MAX_VALUE && estados[i] == false) {
	// estados[i] = true;
	// distancia[i] = distancia[actual.getNodoInicio()] + 1;
	// padre[i] = actual.getNodoInicio();
	// cola.addFirst(nodos[i]);
	// }
	// }
	// }
	// }

	/**
	 * Resuelve el recorrido BFS. <br>
	 * 
	 * @param matrizAdyacencia
	 *            Matriz de adyacencia del grafo. <br>
	 * @param nodoInicio
	 *            Nodo de inicio. <br>
	 */
	public BFS(final int[][] matrizAdyacencia, final int nodoInicio) {
		this.nodoOrigen = nodoInicio;
		this.matrizAdyacencia = matrizAdyacencia;
		this.cantidadNodos = matrizAdyacencia.length;
		this.distancia = new int[this.cantidadNodos];
		this.padre = new int[this.cantidadNodos];
		this.estados = new boolean[this.cantidadNodos];
		for (int i = 0; i < this.cantidadNodos; i++) {
			this.distancia[i] = Integer.MAX_VALUE;
			this.padre[i] = Integer.MAX_VALUE;
		}
		this.estados[nodoInicio] = true;
		this.distancia[nodoInicio] = 0;
		Queue<Integer> cola = new LinkedList<Integer>();
		cola.add(nodoInicio);
		int actual;
		while (!cola.isEmpty()) {
			actual = cola.poll().intValue();
			for (int i = 0; i < this.cantidadNodos; i++) {
				if (this.matrizAdyacencia[actual][i] != Integer.MAX_VALUE && this.estados[i] == false) {
					this.estados[i] = true;
					this.distancia[i] = this.distancia[actual] + 1;
					this.padre[i] = actual;
					cola.add(actual);
				}
			}
		}
	}

	public Stack<Integer> recorrido(final int nodoDestino) {
		Stack<Integer> pilaResultado = new Stack<Integer>();
		int aVisitar = padre[nodoDestino];
		if (this.nodoOrigen != aVisitar && this.estados[aVisitar] == true) {
			pilaResultado.push(nodoDestino);
			pilaResultado.push(aVisitar);
		} else {
			if (this.nodoOrigen == aVisitar && this.nodoOrigen == nodoDestino && this.estados[aVisitar] == true) {
				pilaResultado.push(aVisitar);
				return pilaResultado;
			}
			pilaResultado.push(Integer.MIN_VALUE);
			return pilaResultado;
		}
		while (this.nodoOrigen != aVisitar) {
			System.out.println(padre[aVisitar]);
			pilaResultado.push(padre[aVisitar]);
			aVisitar = padre[aVisitar];
		}
		return pilaResultado;
	}

	// public Stack<Integer> recorrido(Nodo NodoDestino) {
	// Stack<Integer> pilaResultado = new Stack<Integer>();
	// int aVisitar = padre[NodoDestino.cantidadAristas];
	// if (this.nodoOrigen.cantidadAristas != aVisitar && estados[aVisitar] ==
	// true) {
	// pilaResultado.push(NodoDestino.cantidadAristas);
	// pilaResultado.push(aVisitar);
	// } else {
	// if (this.nodoOrigen.cantidadAristas == aVisitar
	// && this.nodoOrigen.cantidadAristas == NodoDestino.cantidadAristas &&
	// estados[aVisitar] == true) {
	// pilaResultado.push(aVisitar);
	// return pilaResultado;
	// }
	// pilaResultado.push(Integer.MIN_VALUE);
	// return pilaResultado;
	// }
	// while (this.nodoOrigen.cantidadAristas != aVisitar) {
	// pilaResultado.push(padre[aVisitar]);
	// aVisitar = padre[aVisitar];
	//
	// }
	// // pilaResultado.push(nodoOrigen.numero);
	// return pilaResultado;
	// }

	public void recorrer(final int nodoDestino) {

	}
}