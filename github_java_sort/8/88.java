package controller;

import java.util.Random;

import model.Matriz;
import model.TempoExecucao;

public class Controller {
	Matriz quick = new Matriz();
	Matriz insertion;
	Random random = new Random();
	double inicio, termino;

	
	public Matriz quickSort(int[] quickSort, int ini, int fim) {

		TempoExecucao t = new TempoExecucao();
		int meio;
		this.inicio = System.currentTimeMillis();
		if (ini < fim) {
			meio = particiona(quickSort, ini, fim);
			quickSort(quickSort, ini, meio);
			quickSort(quickSort, meio + 1, fim);
		}
		this.termino = System.currentTimeMillis();
		t.setTempo((this.termino - this.inicio) / 1000.0);
		quick.setTempo(t);
		quick.setMatriz(quickSort);
		return quick;
	}

	
	public int particiona(int[] quickSort, int ini, int fim) {

		int pivo, topo, i, compara = 0, swap = 0;
		pivo = quickSort[ini];
		topo = ini;

		for (i = ini + 1; i < fim; i++) {
			if (quickSort[i] < pivo) {
				quickSort[topo] = quickSort[i];
				quickSort[i] = quickSort[topo + 1];
				topo++;
				compara = compara + 1;
				swap = swap + 1;
			} else {
				compara = compara + 1;
			}
		}
		quickSort[topo] = pivo;
		quick.setComparacao(quick.getComparacao() + compara);
		quick.setSwap(quick.getSwap() + swap);
		return topo;
	}

	

	public Matriz insertionSort(int[] insertionSort) {
		insertion = new Matriz();

		TempoExecucao t = new TempoExecucao();
		int swap = 0;
		int compara = 0;
		this.inicio = System.currentTimeMillis();
		for (int fixo = 1; fixo <= insertionSort.length; fixo++) {

			int x = fixo - 1;
			int y = fixo;
			compara++;
			while (y != 0 && y != insertionSort.length
					&& insertionSort[x] > insertionSort[y]) {

				int a = insertionSort[x];
				insertionSort[x] = insertionSort[y];
				insertionSort[y] = a;
				x--;
				y--;
				swap++;

			}

		}
		this.termino = System.currentTimeMillis();
		t.setTempo((this.termino - this.inicio) / 1000.0);
		insertion.setComparacao(compara);
		insertion.setSwap(swap);
		insertion.setTempo(t);
		insertion.setMatriz(insertionSort);
		return insertion;
	}

}
