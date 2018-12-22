package edu.unh.cs.treccar.proj.similarities;

import edu.cmu.lti.lexical_db.ILexicalDatabase;
import edu.unh.cs.treccar.Data;
import edu.unh.cs.treccar.proj.util.ParaPair;
import edu.unh.cs.treccar.proj.util.ParaUtilities;

import org.apache.commons.lang3.StringUtils;

import java.util.ArrayList;

/**
 * This class computes the Levenshtein Distance similarity measures between two
 * paragraphs and returns it.
 * 
 * @author tarun
 *
 */

public class LevenshteinDistance implements SimilarityFunction
{
	private static ArrayList<String> paraText1;
	private static ArrayList<String> paraText2;
	private static ArrayList<Integer> scores;
	private double score;
	
	/**
	 * Returns the similarity score based on Levenshtein distance between two
	 * paragraphs
	 * 
	 * @param pp   ParaPair                  A ParaPair object representing a pair of paragraphs
	 * @param list ArrayList<Data.Paragraph> Contains a list of Data.Paragraph objects 
	 * 
	 * @return Mean Levenshtein distance between two paragraphs
	 */
	
	public double simScore(ParaPair pp, ILexicalDatabase db)
	{
		paraText1 = pp.getPara1tokens();
		paraText2 = pp.getPara2tokens();
		
		score = getParaScore(paraText1, paraText2);
		
		return score;		
	}
	
	/**
	 * Computes similarity score based on Levenshtein distance
	 * 
	 * @param list1 ArrayList<String> List of words from first paragraph
	 * @param list2 ArrayList<String> List of words from second paragraph
	 * 
	 * @return Mean Levenshtein distance between two paragraphs 
	 */
	private static double getParaScore(ArrayList<String> list1, ArrayList<String> list2)
	{
		double s = 0.0d;
		for(String w1 : list1)
		{
			for(String w2 : list2)
			{
				scores.add(StringUtils.getLevenshteinDistance(w1, w2));
			}
		}
		s = findMeanScore(scores);
		return s;
	}
	
	/**
	 * Returns the mean of the Levenshtein distances
	 * 
	 * @param list ArrayList<Integer> list of levenshtein distances between all pairs of words
	 * 
	 * @return mean Levenshtein distance
	 */
	private static double findMeanScore(ArrayList<Integer> list)
	{
		double total = 0.0d;
		double mean = 0.0d;
		for(double i : list )
			total += i;
		mean = total/list.size();
		return mean;
	}	
}