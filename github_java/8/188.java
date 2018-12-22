package editDistance;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import booleanModel.ReaderWriter;

public class MinEditDistance {

	public MinEditDistance() {

	}

	public void fileMinimumEditDistance(String filePath, String pathFileToSave) {
		BufferedReader reader = new ReaderWriter().reader(filePath);
		BufferedWriter writer = new ReaderWriter().writer(pathFileToSave);

		String line;
		String[] arrayLine;
		try {
			while ((line = reader.readLine()) != null) {
				arrayLine = line.split("\\s");
				writer.append(
						arrayLine[0] + " " + arrayLine[1] + " " + this.getMinEditDistance(arrayLine[0], arrayLine[1]))
						.append("\r\n");
			}
			writer.flush();
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void wordRecommenderMinimumEditDistance(String incorrectFilePath, String tokensFilePath,
			String pathFileToSave) {

		BufferedReader incorrectReader = new ReaderWriter().reader(incorrectFilePath);
		BufferedReader tokensReader = new ReaderWriter().reader(tokensFilePath);
		BufferedWriter writer = new ReaderWriter().writer(pathFileToSave);

		try {
			String line;
			List<String> tokens = new ArrayList<>();

			// tokens into arrayList
			int i = 0;
			while ((line = tokensReader.readLine()) != null) {
				tokens.add(i, line);
				i++;
			}

			while ((line = incorrectReader.readLine()) != null) {

				List<Node> recommended = new ArrayList<>();
				String token;
				for (int j = 0; j < tokens.size(); j++) {
					token = tokens.get(j);
					recommended.add(j, new Node(token, this.getMinEditDistance(token, line)));
				}

				Collections.sort(recommended, new Comparator<Node>() {
					@Override
					public int compare(Node o1, Node o2) {
						return o1.getValue().compareTo(o2.getValue());
					}
				});

				String candidate = "";
				for (int j = 0; j < 10; j++) {
					candidate += recommended.get(j) + "\t";
				}
				writer.append(line + "\t" + candidate).append("\r\n");

			}
			writer.flush();
			writer.close();

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	private int getMinEditDistance(String firstString, String secondString) {
		EditDistanceTable editDistanceTable = new EditDistanceTable(firstString, secondString);

		int cost;
		for (int i = 1; i < firstString.length() + 1; i++) {
			for (int j = 1; j < secondString.length() + 1; j++) {
				if (firstString.charAt(i - 1) == secondString.charAt(j - 1))
					cost = 0;
				else
					cost = 2;

				editDistanceTable.set(i, j, this.getMin(editDistanceTable.get(i - 1, j) + 1,
						editDistanceTable.get(i, j - 1) + 1, editDistanceTable.get(i - 1, j - 1) + cost));
			}
		}
		return editDistanceTable.get(firstString.length(), secondString.length());
	}

	private int getMin(int val1, int val2, int val3) {
		return Math.min(Math.min(val1, val2), val3);
	}

	private class Node {
		private String word;
		private Integer value;

		public Node(String word, Integer value) {
			this.word = word;
			this.value = value;
		}

		public Integer getValue() {
			return value;
		}

		@Override
		public String toString() {
			return "(" + this.word + ":" + this.value + ")";
		}

	}

}
