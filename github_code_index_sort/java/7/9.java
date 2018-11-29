package clas_pes;

import java.util.Random;

public class shellsort {

	// M�todo de Inser��o Direta
	public static void insertionSort(int[] numeros, int tam) {
		int i, j, eleito;
		for (i = 1; i < tam; i++) {
			eleito = numeros[i];
			j = i - 1;
			while ((j >= 0) && (eleito < numeros[j])) {
				numeros[j + 1] = numeros[j];
				j--;
			}
			numeros[j + 1] = eleito;
		}
	}

	// M�todos ShellSort
	public static void shellSort(int[] vet, int size) {
		int i, j, value;
		int gap = 1;
		while (gap < size) {
			gap = 3 * gap + 1;
		}
		while (gap > 1) {
			gap /= 3;
			for (i = gap; i < size; i++) {
				value = vet[i];
				j = i - gap;
				while (j >= 0 && value < vet[j]) {
					vet[j + gap] = vet[j];
					j -= gap;
				}
				vet[j + gap] = value;
			}
		}
	}

	public static void main(String[] args) {
		Random gerador = new Random();
		int tv = 100; // Define quantos valores dever� ter dentro do vetor
		int vet[] = new int[tv];
		int i;
		System.out.println("Vetor desordenado");
		for (i = 0; i < tv; i++) {
			vet[i] = gerador.nextInt(tv);
			System.out.println(" " + vet[i]);
		}
		
		insertionSort (vet, tv);
		shellSort (vet, tv);

		System.out.println("Vetor ordenado");
		for (i = 0; i < tv; i++) {
			System.out.println(" " + vet[i]);
		}
	}
}
