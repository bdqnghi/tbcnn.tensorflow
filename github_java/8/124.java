package com.sri.bolt.errordetection;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class ModifiedEditDistance {
	private static final double INSERTION_COST = 1.0;
	private static final double DELETION_COST = 1.0;
	private static final double REPLACE_COST = 1.0;
	private static final double MATCH_COST = 0.0;
	private static final double SPLIT_COST = 0.5;
	private static final double MERGE_COST = 0.5;
	
	public enum OPERATION{
		INSERT,
		DELETE,
		REPLACE,
		MATCH,
		MERGE, // split one mt input word to 2 asr words
		SPLIT, // split one asr word into 2 mt input words
		NONE;
	}
	
	private static boolean isMatch(String first, String second){
		// add other variations later, if needed
		return first.equals(second);
	}
	
	private static boolean isWordSplit(String merged, String first, String second){
		// add other variations later, if needed
		return merged.equals(first + second);
	}
	
	// first sentence is for asr output; second sentence is for mt input
	private static void computeDistance(String[] firstWords, String[] secondWords,double[][] distance, OPERATION[][] operations){
		
		int firstLen = firstWords.length;
		int secondLen = secondWords.length;
		
        for (int i = 0; i <= firstLen; i++){
                distance[i][0] = i * DELETION_COST;
                operations[i][0] = OPERATION.DELETE;
        }
        for (int j = 0; j <= secondLen; j++){
                distance[0][j] = j * INSERTION_COST;
                operations[0][j] = OPERATION.INSERT;
        }
        operations[0][0] = OPERATION.NONE;

        for (int i = 1; i <= firstLen; i++){
        	for (int j = 1; j <= secondLen; j++){
	        	double cost = distance[i-1][j-1] + REPLACE_COST;
	        	OPERATION op = OPERATION.REPLACE;
	        		
	    		if (isMatch(firstWords[i-1], secondWords[j-1]) && 
	    				distance[i-1][j-1] + MATCH_COST <= cost){
	    			cost = distance[i-1][j-1] + MATCH_COST;
	    			op = OPERATION.MATCH;
	    		}
	    		if (j >=2 && isWordSplit(firstWords[i-1], secondWords[j-2], secondWords[j-1]) &&
	    				distance[i-1][j-2] + SPLIT_COST < cost){
	    			cost = distance[i-1][j-2] + SPLIT_COST;
	    			op = OPERATION.SPLIT;
	    		}
	    		if (i >=2 && isWordSplit(secondWords[j-1], firstWords[i-2], firstWords[i-1]) &&
	    				distance[i-2][j-1] + MERGE_COST < cost){
	    			cost = distance[i-2][j-1] + MERGE_COST;
	    			op = OPERATION.MERGE;
	    		}
	    		if (distance[i-1][j] + DELETION_COST < cost){
	    			cost = distance[i-1][j] + DELETION_COST;
	    			op = OPERATION.DELETE;
	    		}
	    		if (distance[i][j-1] + INSERTION_COST < cost){
	    			cost = distance[i][j-1] + INSERTION_COST;
	    			op = OPERATION.INSERT;
	    		}
	    		distance[i][j] = cost;
	    		operations[i][j] = op;
        	}
		}
        
	}
	
	private static void addMapping(Map<Integer, Set<Integer>> mapping, int oldIndex, int newIndex){
		Set<Integer> list = mapping.get(oldIndex);
		if (list == null){
			list = new HashSet<Integer>();
			mapping.put(oldIndex, list);
		}
		list.add(newIndex);
	}
	
	private static Map<Integer, Set<Integer>> getMapping(String[] firstWords, String[] secondWords, OPERATION[][] operations){
		int firstLen = firstWords.length;
		int secondLen = secondWords.length;
		
		Map<Integer, Set<Integer>> mapping = new HashMap<Integer, Set<Integer>>();
		int i= firstLen;
		int j= secondLen;
		while (i >0 || j > 0){
			if (operations[i][j] == OPERATION.MATCH){
				addMapping(mapping, j-1, i-1); i--; j--;
			}
			else if (operations[i][j] == OPERATION.REPLACE){
				addMapping(mapping, j-1, i-1); i--; j--;
			}
			else if (operations[i][j] == OPERATION.INSERT){
				j--;
			}
			else if (operations[i][j] == OPERATION.DELETE){
				i--;
			}
			else if (operations[i][j] == OPERATION.SPLIT){
				addMapping(mapping, j-2, i-1); addMapping(mapping, j-1, i-1); i--; j-=2;
			}
			else if (operations[i][j] == OPERATION.MERGE){
				addMapping(mapping, j-1, i-2); addMapping(mapping, j-1, i-1); i-=2; j--;
			}
		}
		return mapping;
	}
	
	public static Map<Integer, Set<Integer>> getSecondStringToFirstStringMapping(String first, String second){
		String[] firstWords = first.trim().split("\\s+");
		String[] secondWords = second.trim().split("\\s+");
		int firstLen = firstWords.length;
		int secondLen = secondWords.length;
		double[][] distances = new double[firstLen + 1][secondLen + 1];
		OPERATION[][] operations = new OPERATION[firstLen + 1][secondLen + 1];
		computeDistance(firstWords, secondWords, distances, operations);
//		for (int i=0; i <= firstLen; i++){
//        	for (int j=0; j <= secondLen; j++)
//        		System.out.print(String.format("%-8s" , operations[i][j]));
//        	System.out.println();
//      }
		return getMapping(firstWords, secondWords, operations);
	}
	
	public static void main(String[] args){
	/*	try{
			while (true){
				BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
				System.out.print("Enter the first string: ");
				String first = br.readLine();
				System.out.print("Enter the second string: ");
				String second = br.readLine();
				System.out.println("----------");
				System.out.println("First : " + first + "\nSecond: " + second + "\n");
				String[] firstWords = first.trim().split("\\s+");
				String[] secondWords = second.trim().split("\\s+");
				Map<Integer, Set<Integer>> mapping = getSecondStringToFirstStringMapping(first, second);
				List<Integer> indices = new ArrayList<Integer>(mapping.keySet());
				Collections.sort(indices);
				System.out.println("=====================");
				for (int i : indices){
					System.out.print(i + ":" + secondWords[i] + " --> ");
					if (mapping.get(i) != null){
						List<Integer> list = new ArrayList<Integer>(mapping.get(i));
						Collections.sort(list);
						for (int j : list){
							System.out.print(j + ":" + firstWords[j] + " ");
						}
					}
					System.out.println();
				}
			}
		}
		catch (Exception e){
			e.printStackTrace();
		}*/

      String inputFile = "/home/pblasco/edit.input";
      String outputFile = "/home/pblasco/edit.out";
      try {
         BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(inputFile)));
         BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
                 new FileOutputStream(outputFile), "utf-8"));
         String line;
         while ((line = reader.readLine()) != null) {
            String[] inputs = line.split("\\|\\|\\|");
            String first = inputs[0].trim();
            String second = inputs[1].trim();
            writer.write(first + " ||| ");
            writer.write(second + " ||| ");
            Map<Integer, Set<Integer>> mapping = getSecondStringToFirstStringMapping(second, first);
            for (Entry<Integer, Set<Integer>> entry : mapping.entrySet()) {
               writer.write(String.valueOf(entry.getKey() + 1));
               writer.write("-");
               boolean isFirst = true;
               for (Integer val : entry.getValue()) {
                  if (!isFirst) {
                     writer.write(",");
                  }
                  writer.write(String.valueOf(val + 1));
               }
               writer.write(" ");
            }
            writer.newLine();
         }
         reader.close();
         writer.close();
      } catch (FileNotFoundException e) {
         e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
      } catch (IOException e) {
         e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
      }
   }
}
