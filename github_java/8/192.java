package ch.grafst.SITtoSHIT;


import org.jgrapht.graph.SimpleDirectedGraph;

import java.io.*;
import java.nio.charset.Charset;
import java.util.*;


/**
 * @author Stephan Graf
 * @version 2017-04-06
 *          time@04-07 01:50 --> 10h
 *          time@04-09 10:20 --> 12h
 *          Searches for the longest Word Chain in the English Language.
 *          A Word Chain is built by adding one letter to a word at any position.
 */
public class WordChain {
    private HashMap<Integer, ArrayList<String>> dictionary;
    private org.jgrapht.graph.SimpleDirectedGraph<String, Integer> graph;
    private ArrayList<String> chain;
    private Queue<String> queue;
    private long lastTime = 0;
    private int globcount = 0;


    WordChain() {
        graph = new SimpleDirectedGraph<String, Integer>(Integer.class);
        dictionary = new HashMap<Integer, ArrayList<String>>();
        queue = new LinkedList<String>();
        read("words3.txt", 5);
        buildGraph();
        //findLongest();
    }


    /**
     * Deine Mudda
     *
     * @param filename
     */
    public void read(String filename, int maxWordlength) {
        lastTime = System.nanoTime();
        String line;
        try {
            try (
                  InputStream fis = new FileInputStream(filename);
                  InputStreamReader isr = new InputStreamReader(fis, Charset.forName("UTF-8"));
                  BufferedReader br = new BufferedReader(isr);
            ) {
                while ((line = br.readLine()) != null) {
                    if (line.length() < maxWordlength) {
                        if (dictionary.containsKey(line.length())) {

                        } else {
                            dictionary.put(line.length(), new ArrayList<String>());
                        }
                        dictionary.get(line.length()).add(line.toLowerCase());
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(longestWord());
    }


    public void buildGraph() {
        queue.add("");
        //todo: remove
        String current = "";
        String last = "";
        while (!queue.isEmpty() && queue.peek().length() < longestWord()) {
            current = queue.peek();
            addVertex(queue.remove());
            //todo remove printout
            if (current.length() != last.length()) {
                System.out.println("------ length " + current.length() + " ------");
                System.out.println(current);
                lap();
                last = current;
            }
        }
        System.out.println(queue.remove());/*
        for (ArrayList<String> list : dictionary.values()) {
            for (String word : list) {
                graph.addVertex(word);
                for (String word2 : dictionary.get(word.length() + 1)) {
                    if (!graph.containsVertex(word2)) {
                        graph.addVertex(word2);
                        //System.out.println("add" + word2);
                    }
                    graph.addEdge(word, word2, 1);
                }
            }
        }*/
    }


    public void addVertex(String word) {
        // graph.addVertex(word);
        //System.out.println(word);
        for (String word2 : dictionary.get(word.length() + 1)) {
            globcount++;
            if (hasDistanceOne(word, word2)) {
                queue.add(word2);
                //graph.addVertex(word2);
                //graph.addEdge(word, word2,1);
            }
        }

    }


    /**
     * Determine if two words have a Levenshtein-distance of 1
     * Optimized for speed so the first word has to be one letter shorter than the second
     * Empt words are also permitted
     *
     * @param word1 first word. "" is also permitted
     * @param word2 second word (one letter longer than first
     *
     * @return true if the two words have a levensthein-distance of 1
     */
    public static boolean hasDistanceOne(String word1, String word2) {
        if (word1.length() + 1 != word2.length()) {
            return false;
        }
        int i = 0;
        int distance = 0;
        while (distance <= 1 && i < word1.length()) {
            if (word1.toCharArray()[i] != word2.toCharArray()[i + distance]) {
                distance++;
            } else {
                i++;
            }
        }
        return distance <= 1;
    }


    /**
     * @return the number of letters of the longest word in the dictionary
     */
    private int longestWord() {
        return Collections.max(dictionary.keySet());
    }


    private void lap() {
        System.out.println((System.nanoTime() - lastTime) / 100000000 + "ms");
        lastTime = System.nanoTime();
    }
}
