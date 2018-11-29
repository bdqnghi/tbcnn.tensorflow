package com.giullianomorroni.jcorretor;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

/**
 * 
 * @author giulliano.morroni
 * @author monique.trevisan
 */
final class Levenshtein {

	public List<String> choiceBestOption(Collection<String> all, String keyWordSearch){
		if (all == null)
			return new ArrayList<String>();

		List<LevenshteinDistance> calculatedWords = new ArrayList<LevenshteinDistance>();
		List<String> values = new ArrayList<String>(all);

		// calcula a distancia de cada palavra 
		for(int i=0; i < values.size(); i++) {
			String similarWord = values.get(i);
			LevenshteinDistance ld = new LevenshteinDistance();
			if (similarWord.toLowerCase().contains(keyWordSearch.toLowerCase())){
				ld.setDistance(0);
				ld.setWord(similarWord);
			} else {
				ld.setDistance(calculateLevenshteinDistance(keyWordSearch, similarWord));
				ld.setWord(similarWord);
			}
			calculatedWords.add(ld);
		}

		//ordena a lista de acordo com a distancia
		Collections.sort(calculatedWords);

		List<String> ordenedList = new ArrayList<String>();
		for(int i=0; i < calculatedWords.size(); i++){
			LevenshteinDistance ld = calculatedWords.get(i);
			ordenedList.add(ld.getWord());
		}

		if (ordenedList.size() > 3)
			return ordenedList.subList(0, 3);
		return ordenedList;
	}

	private int calculateLevenshteinDistance(String keyWordSearched, String similarWord) {
	    return calculateDistance(keyWordSearched.toCharArray(), similarWord.toCharArray());
	}

	private int calculateDistance(char[] keyWordSearched, char[] similarWord) {
	    // matrix da distancia - usado para memorizar as distancias entre duas strings
	    int[][] distance = new int[keyWordSearched.length + 1][similarWord.length + 1];

	    //itera a string procurada
	    for(int i = 0; i < keyWordSearched.length + 1; i++) {
	        distance[i][0] = i;
	    }

	    //itera a string similar
	    for(int j = 0; j < similarWord.length + 1; j++) {
	        distance[0][j] = j;
	    }

	    for(int i=1; i < keyWordSearched.length + 1; i++) {
	        for(int j=1; j < similarWord.length + 1; j++) {
	            int deleteCost = distance[i - 1][j] + 1;
	            int insertCost = distance[i][j - 1] + 1;
	            int replaceCost = distance[i - 1][j - 1];
	            if (keyWordSearched[i - 1] != similarWord[j - 1]) {
	                replaceCost += 1;
	            }
	            distance[i][j] = Math.min(Math.min(deleteCost, insertCost), replaceCost);
	        }
	    }
	    return distance[keyWordSearched.length][similarWord.length];
	}

}
