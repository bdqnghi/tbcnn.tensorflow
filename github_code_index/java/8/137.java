/*
 * DuDe - The Duplicate Detection Toolkit
 * 
 * Copyright (C) 2010  Hasso-Plattner-Institut für Softwaresystemtechnik GmbH,
 *                     Potsdam, Germany 
 *
 * This file is part of DuDe.
 * 
 * DuDe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DuDe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DuDe.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

package dude.similarityfunction.contentbased.util;

/**
 * <code>LevenshteinDistance</code> implements an Edit-Distance approach using the <code>Levenshtein Distance</code>
 * algorithm.
 * 
 * @author Matthias Pohl
 */
public class LevenshteinDistance {

	/**
	 * Returns the <code>Levenshtein Distance</code> of the passed Strings.
	 * 
	 * @param str1
	 *            The first String.
	 * @param str2
	 *            The second String.
	 * @return The <code>Levenshtein Distance</code> value related to the passed String.
	 */
	public int getValue(String str1, String str2) {

		/*
		 * This code fragment was copied from http://www.merriampark.com/ldjava.htm The original author is Chas Emerik.
		 */

		if (str1 == null || str2 == null) {
			throw new IllegalArgumentException("Strings must not be null");
		}

		int n = str1.length(); // length of s
		int m = str2.length(); // length of t

		if (n == 0) {
			return m;
		} else if (m == 0) {
			return n;
		}

		int p[] = new int[n + 1]; // 'previous' cost array, horizontally
		int d[] = new int[n + 1]; // cost array, horizontally
		int _d[]; // placeholder to assist in swapping p and d

		// indexes into strings s and t
		int i; // iterates through s
		int j; // iterates through t

		char t_j; // jth character of t

		int cost; // cost

		for (i = 0; i <= n; i++) {
			p[i] = i;
		}

		for (j = 1; j <= m; j++) {
			t_j = str2.charAt(j - 1);
			d[0] = j;

			for (i = 1; i <= n; i++) {
				cost = str1.charAt(i - 1) == t_j ? 0 : 1;
				// minimum of cell to the left+1, to the top+1, diagonally left
				// and up +cost
				d[i] = Math.min(Math.min(d[i - 1] + 1, p[i] + 1), p[i - 1] + cost);
			}

			// copy current distance counts to 'previous row' distance counts
			_d = p;
			p = d;
			d = _d;
		}

		// our last action in the above loop was to switch d and p, so p now
		// actually has the most recent cost counts
		return p[n];
	}
}
