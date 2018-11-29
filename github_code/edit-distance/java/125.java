package levenshteinDistance;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


/*
 * This class is the Levenshtein Distance. This algorithm checks how different
 * each word is. An example:
 * 		input = Baach
 * 		intended word = Beach
 * There is 1 error in it, so the levenshtein distance is 1. We look for words
 * that have a levenshtein distance less than 3 (a maximum of 2 errors). In a 
 * dictionary of 58 000+ words, that returns a lot of options and it does not
 * sort them accordingly. After finding the words, it calls the Metaphone method
 * to sort the words.
 *                         
 * Created on: March 24, 2015
 * Last Edited on: March 26, 2015
 *
 * @authors Omar Almootassem and Talha Zia
 *
 */
public class LevenshteinDistance {
	
	//Arraylist to save all the levenshtein words for further sorting
	public static ArrayList <String> levenWords = new ArrayList<String>();
	
	private String line = "NULL";
	private int i = 0;
	
	/**
	 * Uses the Levenshtein Distance algorithm to check for the closeness of the
	 * correctness of the possible words
	 * @param word - the input word
	 */
	public LevenshteinDistance (String word) {
		
		try{
			BufferedReader reader = new BufferedReader(new FileReader("src/Dictionary.txt"));
			line = reader.readLine();
			/*
			 * The do while loop reads through the entire text file line by line. Each line has
			 * one word on it. It saves the word in "line" variable and compares it with "word".
			 * If they are the same word or the file ends, the loop stops.
			 */
			do{
				int len0 = word.length() + 1;                                                     
			    int len1 = line.length() + 1;                                                    
			 
			    // the array of distances                                                       
			    int[] cost = new int[len0];                                                     
			    int[] newcost = new int[len0];                                                  
			 
			    // initial cost of skipping prefix in String s0                                 
			    for (int i = 0; i < len0; i++){
			    	cost[i] = i;                                     
			    }
			    // dynamically computing the array of distances                                  
			 
			    // transformation cost for each letter in s1                                    
			    for (int j = 1; j < len1; j++) {                                                
			        // initial cost of skipping prefix in String s1                             
			        newcost[0] = j;                                                             
			 
			        // transformation cost for each letter in s0                                
			        for(int i = 1; i < len0; i++) {                                             
			            // matching current letters in both strings                             
			            int match = (word.charAt(i - 1) == line.charAt(j - 1)) ? 0 : 1;             
			 
			            // computing cost for each transformation                               
			            int cost_replace = cost[i - 1] + match;                                 
			            int cost_insert  = cost[i] + 1;                                         
			            int cost_delete  = newcost[i - 1] + 1;                                  
			 
			            // keep minimum cost                                                    
			            newcost[i] = Math.min(Math.min(cost_insert, cost_delete), cost_replace);
			        }                                                                           
			 
			        // swap cost/newcost arrays                                                 
			        int[] swap = cost; 
			        cost = newcost; 
			        newcost = swap;                          
			    }
			    
			    //if LevenshteinDistance is less than or equal to 2
			    if (cost[len0 - 1] <= 2){
			    	levenWords.add(line);
			    	System.out.println("word: " + line);
			    	i++;
			    }
			    
				//System.out.println(line + " " + word);	//DEBUG (prints out content of the Dictionary file)
			}while ((line = reader.readLine()) != null);
			
			//close the file
			reader.close();
			
		//catch the IOException if file is not found
		}catch (IOException e){
			e.printStackTrace();
		}
	}
}
