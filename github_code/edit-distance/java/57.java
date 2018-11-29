/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package levenshteindistance;

import au.com.bytecode.opencsv.CSVWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

/**
 * @author Richard Coan
 */
public class Levenshtein {
    protected static Levenshtein instance = null;
    protected FileHelper fh;
    
    protected Levenshtein() {
        fh = FileHelper.getInstance();
    }

    /** 
     * Loading a file.
     * 
     * @param _path path to file.
     * @return array of strings to be processed.
     */
    protected String[] loadFile(String _path) {
        String s = fh.Load(_path);
        String[] t = {};
        
        if(s != null) {
            s = s.replaceAll("[^a-zA-Z\\s]+", "");
            t = s.split("\\s");
        }
        return t;
    }
    
    /** 
     * Calculates the Levenshtein distance and returns an ArrayList 
     * containing both words and the distance.
     * 
     * @param s
     * @param u
     * @return ArrayList<String[]>
     */
    protected ArrayList<String[]> calculate(String[] s, String[] u) {
        ArrayList<String[]> data = new ArrayList<String[]>();
                
        for(int x = 0; x < s.length - 1; x++) {
            if(s[x].length() != 0 && u[x].length() != 0 ) {
                int dist = this.distance(s[x], s[x].length(), u[x], u[x].length());
                data.add(new String[] {s[x], u[x], Integer.toString(dist)});
            }
        }
        
        return data;
    }
    
    /**
     * Recursive Levenshtein distance calculation using two strings.
     * Based on the Pseudocode available at:
     * http://en.wikipedia.org/wiki/Levenshtein_distance
     * 
     * @param s
     * @param u
     * @return distance
     */
    protected int distance(String s, int len_s, String u, int len_u) {
        // Testing for empty strings
        if(len_s == 0) return len_u;
        if(len_u == 0) return len_s;
        
        // Testing if last characters match
        int cost = 1;
        if(s.charAt(len_s - 1) == u.charAt(len_u - 1) ) cost = 0;
        
        // return minimum of delete char from s, from t, and from both
        return Math.min(this.distance(s, len_s - 1, u, len_u) + 1, 
               Math.min(this.distance(s, len_s, u, len_u - 1) + 1,
                        this.distance(s, len_s - 1, u, len_u - 1) + cost)
        );
    }
    
   /** 
    * Get the Instance of the class.
    * @return instance
    */
    public static Levenshtein getInstance() {
        if(instance == null) {
            instance = new Levenshtein();
        }
        
        return instance;
    }
    
    /**
     * Main Programs, Starts the magic.
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        instance = getInstance();
        
        if(args.length > 1) {
            String[] s = instance.loadFile(args[0]);
            String[] u = instance.loadFile(args[1]);
            
            if(s.length == 0 || u.length == 0) {
                System.out.println("ERROR: One or more of the specified files is empty.");
            } else {
                ArrayList<String[]> data = instance.calculate(s, u);
                data.add(0, new String[] {"Scrambled", "Unscrambled", "Distance"} );
                
                try {
                    CSVWriter writer = new CSVWriter(new FileWriter("output.csv"));
                    writer.writeAll(data);
                    writer.close();
                } catch(java.io.IOException err) {
                    System.out.println("Output File Could not be written:");
                    System.out.println("----"+err);
                    System.exit(0);
                }
            }
        } else {
            System.out.println("ERROR: Must include arguments: [path-to-scrambled.txt] [path-to-unscrambled.txt]");
        }
    }    
}
