package ro.unibuc.nlp.cognates.metrics;

import java.util.HashMap;
import java.util.Map;

import org.apache.log4j.Logger;

/**
 * Computes the edit distance or similarity between two input strings.
 * 
 * @author alina
 */
public class Edit implements Metric {

	private static final Logger logger = Logger.getLogger(Edit.class);
	
	private Map<String, Double> distanceMap;
	
	public Edit() {
		distanceMap = new HashMap<String, Double>();
	}

	/**
	 * Computes the unnormalized edit distance between the input strings.
	 * 
	 * @param a the first string
	 * @param b the second string
	 * @return the unnormalized edit distance between the input strings
	 * @throws IllegalArgumentException
	 */
	public double computeEdit(String a, String b) throws IllegalArgumentException {
		
		MetricUtils.validate(a, b);
		
		int cost = 0;

		 Double computedDistance = distanceMap.get(a + "__" + b);
		 
		 if (computedDistance != null && computedDistance != 0d) {
			 return computedDistance;
		 }
		 
		 if(a.length() == 0) {
			 return b.length();
		 }
		 else if(b.length() == 0) {
			 return a.length();
		 }
		 else {
			 if(a.charAt(0) != b.charAt(0)) {
				 cost = 1;
			 }
			 double distance =  Math.min(
					            	Math.min(computeEdit(a.substring(1), b) + 1,
					            			 computeEdit(a, b.substring(1)) + 1),
					            			 computeEdit(a.substring(1), b.substring(1)) + cost);
			 
			 distanceMap.put(a + "__" + b, distance);
			 
			 return distance;
		 }
	}
	
	/**
	 * Computes the normalized edit distance between the input strings.
	 * 
	 * @param a the first string
	 * @param b the second string
	 * @return the normalized edit distance between the input strings
	 * @throws IllegalArgumentException
	 */
	public double computeDistance(String a, String b) throws IllegalArgumentException {

		logger.info("Computing the edit distance between strings " + a + " " + b);
		
		double distance = computeEdit(a, b);
		int maxLength = Math.max(a.length(), b.length());
		
		if (maxLength == 0) {
			return 0;
		}
					
		return distance/maxLength;
	}
	/**
	 * Computes the normalized edit similarity between the input strings.
	 * 
	 * @param a the first string
	 * @param b the second string
	 * @return the normalized edit similarity between the input strings
	 * @throws IllegalArgumentException
	 */
	public double computeSimilarity(String a, String b) throws IllegalArgumentException {

		logger.info("Computing the edit similarity between strings " + a + " " + b);
		
		double distance = computeEdit(a, b);
		int maxLength = Math.max(a.length(), b.length());
		
		if (maxLength == 0) {
			return 1;
		}
		
		return 1 - distance/maxLength;
	}
}