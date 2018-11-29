/*
 * Copyright (c) 2015 cgomez. All rights reserved.
 */
package com.cgomez.ml.measure.distance.impl;

import com.cgomez.ml.measure.distance.IDistanceMeasure;

/**
 * The Class LevenshteinDistance.
 *
 * @author <a href="mailto:andres1537@gmail.com">Carlos Gomez</a>
 * @since ml-java-1.0
 */
public class LevenshteinDistance implements IDistanceMeasure<String> {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = 7976792892826282328L;

    /** The match. */
    private double match;
    
    /** The mismatch. */
    private double mismatch;
    
    /** The gap cost. */
    private double gapCost;
    
    /**
     * Instantiates a new levenshtein distance.
     */
    public LevenshteinDistance() {
	this.match = 0d;
	this.mismatch = 1d;
	this.gapCost = 1d;
    }
    
    /**
     * Instantiates a new levenshtein distance.
     *
     * @param match the match
     * @param mismatch the mismatch
     * @param gapCost the gap cost
     */
    public LevenshteinDistance(double match, double mismatch, double gapCost) {
	this.match = match;
	this.mismatch = mismatch;
	this.gapCost = gapCost;
    }

    /* (non-Javadoc)
     * @see com.cgomez.ml.distance.IDistanceMeasure#distance(java.lang.Object, java.lang.Object)
     */
    @Override
    public Double distance(String a, String b) {
	return similarity(a.toLowerCase().trim(), b.toLowerCase().trim()) / Math.max(a.trim().length(), b.trim().length());
    }
	
    /* (non-Javadoc)
     * @see com.cgomez.ml.distance.IDistanceMeasure#similarity(java.lang.Object, java.lang.Object)
     */
    @Override
    public Double similarity(String a, String b) {
	double[][] matrix = new double[a.length() + 1][b.length() + 1];

	for (int i = 0; i <= a.length(); i++) {
	    matrix[i][0] = i;
	}
	
	for (int j = 1; j <= b.length(); j++) {
	    matrix[0][j] = j;
	}

	for (int i = 1; i <= a.length(); i++) {
	    for (int j = 1; j <= b.length(); j++) {
		matrix[i][j] = min(matrix[i - 1][j] + gapCost, // left cell
				   matrix[i][j - 1] + gapCost, // right cell
			           matrix[i - 1][j - 1] + ((a.charAt(i - 1) == b.charAt(j - 1)) ? match : mismatch)); // diagonal cell
	    }
	}

	return matrix[a.length()][b.length()];
    }

    /**
     * Min.
     *
     * @param a the a
     * @param b the b
     * @param c the c
     * @return the double
     */
    private double min(double a, double b, double c) {
	return Math.min(Math.min(a, b), c);
    }
}