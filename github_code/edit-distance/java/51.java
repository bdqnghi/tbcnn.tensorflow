package org.codeexample.algorithms.collected.spellchecker;

import java.util.ArrayList;
import java.util.List;

/**
 * Source: http://www.codeproject.com/Articles/36869/Fuzzy-Search
 * <p>
 * 
 */
public class FuzzySearch
{
    public static void main(
            String[] args)
    {
        String word = "Code Project";
        List<String> wordList = new ArrayList<String>();
        wordList.add("Code Project");
        wordList.add("Code project");
        wordList.add("codeproject");
        wordList.add("Code Projekt");
        wordList.add("Kode Project");
        wordList.add("Other Project");

        List<String> foundWords = FuzzySearch.Search(word, wordList, 0.70);
        for (String str : foundWords)
        {
            System.out.println(str);
        }
        System.out.println("************ Split line ************");
        foundWords = FuzzySearch.Search(word, wordList, 1);
        for (String str : foundWords)
        {
            System.out.println(str);
        }
        // foundWords.ForEach(i => Console.WriteLine(i));
    }

    public static List<String> Search(
            String word, List<String> wordList, double fuzzyness)
    {
        List<String> foundWords = new ArrayList<String>();

        for (String s : wordList)
        {
            // Calculate the Levenshtein-distance:
            int levenshteinDistance = LevenshteinDistanceMetric.distance(word, s);

            // Length of the longer string:
            int length = Math.max(word.length(), s.length());

            // Calculate the score:
            double score = 1.0 - (double) levenshteinDistance / length;

            // Match?
            if (score >= fuzzyness)
                foundWords.add(s);
        }
        return foundWords;
    }

}
