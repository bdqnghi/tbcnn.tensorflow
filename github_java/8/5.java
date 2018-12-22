package net.sprakle.homeAutomation.utilities.levenshtein;

import java.util.ArrayList;
import java.util.HashMap;

public class Levenshtein {

	/*
	 * Returns a hashmap with a distance integer for every string passed to it
	 */
	public static HashMap<Integer, String> getDistance(ArrayList<String> database, String target) {
		HashMap<Integer, String> result = new HashMap<>();

		for (String s : database) {
			int distance = getDistance(target, s);
			result.put(distance, s);
		}

		return result;
	}

	public static int getDistance(String s1, String s2) {
		s1 = s1.toLowerCase();
		s2 = s2.toLowerCase();

		int[] costs = new int[s2.length() + 1];
		for (int i = 0; i <= s1.length(); i++) {
			int lastValue = i;
			for (int j = 0; j <= s2.length(); j++) {
				if (i == 0)
					costs[j] = j;
				else {
					if (j > 0) {
						int newValue = costs[j - 1];
						if (s1.charAt(i - 1) != s2.charAt(j - 1))
							newValue = Math.min(Math.min(newValue, lastValue), costs[j]) + 1;
						costs[j - 1] = lastValue;
						lastValue = newValue;
					}
				}
			}
			if (i > 0)
				costs[s2.length()] = lastValue;
		}
		return costs[s2.length()];
	}
}
