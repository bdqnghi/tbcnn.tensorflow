package com.company;

import static java.lang.Math.min;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Levenshtein {
	int levenshtein;
	String word1;
	String word2;

	public Levenshtein(String word1, String word2) {
		levenshtein = 0;
		this.word1 = word1;
		this.word2 = word2;
	}

	public Levenshtein() {
		this.levenshtein = 0;
		this.word1 = null;
		this.word2 = null;
	}

	/**
	 * Méthode get
	 * 
	 * @return la distance de Levenshtein
	 */
	public int getLevenshtein() {
		return levenshtein;
	}

	/**
	 * Crée le tableau des distances des préfixes
	 * 
	 * @return le tableau des distances
	 */
	public int[][] matrix() {
		int matrix[][] = new int[word2.length() + 1][word1.length() + 1];
		for (int j = 0; j < matrix[0].length; j++) {
			matrix[0][j] = j;
		}
		for (int i = 0; i < matrix.length; i++) {
			matrix[i][0] = i;
		}
		for (int i = 1; i < matrix.length; i++) {
			for (int j = 1; j < matrix[0].length; j++) {
				int up = matrix[i - 1][j];
				int left = matrix[i][j - 1];
				int diag = matrix[i - 1][j - 1];
				if (word2.charAt(i - 1) == word1.charAt(j - 1)) {
					matrix[i][j] = diag;
				} else {
					matrix[i][j] = min(min(up, left), diag) + 1;
				}
			}
		}
		/**
		 * for (int i=0; i< matrix.length; i++) { for (int j=0; j < matrix[0].length;
		 * j++) { System.out.print(matrix[i][j]+" "); } System.out.println(); }
		 */
		return matrix;
	}

	/**
	 * Donne la distance d'édition en faisant appelle à la méthode matrix
	 */
	public void distance() {
		int[][] m = matrix();
		levenshtein = m[m.length - 1][m[0].length - 1];
	}

	/**
	 * Calcule la distance de chaque mot d'une liste par rapport à word1
	 * 
	 * @param list la liste des mots dont on cherche la distance par rapport à word1
	 * @return la liste des mots associés à leur distance par rapport à word1
	 */
	public List<WordDistance> listDistances(List<String> list) {
		List<WordDistance> distances = new ArrayList<>();
		for (String word : list) {
			word2 = word;
			distance();
			WordDistance w = new WordDistance(levenshtein, word2);
			// System.out.println(w.getWord()+ " : "+ w.getDistance());
			distances.add(w);
		}
		return distances;
	}

	/**
	 * Détermine les cinq mots les plus proches de word1 parmis une liste de mots
	 * 
	 * @param list les mots candidats
	 * @return la liste des cinq mots les plus proches
	 */
	public List<String> proximityLevenshtein(List<String> list) {
		List<WordDistance> distances = listDistances(list);
		Collections.sort(distances);
		return Arrays.asList(distances.get(0).getWord(), distances.get(1).getWord(), distances.get(2).getWord(),
				distances.get(3).getWord(), distances.get(4).getWord());
	}
}
