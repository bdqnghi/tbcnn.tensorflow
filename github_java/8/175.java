
/*
 * TMAdvanced: A tool to retrive semantically similar matches from a  Translation Memory using paraphrases
 * Copyright (C) 2015 Rohit Gupta, University of Wolverhampton.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Simple and efficient Levenshtein Distance implementation
 * @author Rohit Gupta
 * 
 */
package tmadvanced.matching;

import tmadvanced.data.Token;



public class LevenshteinDistance  {

    
    /** Maximal number of tokens compared. */
    private static final int MAX = 1000;

    /**
     * "Cost array instead of matrix" to avoid excessive allocation and garbage
     * collection.
     */
    private short[] distance = new short[MAX + 1];
    /**
     * "Previous" cost array, horizontally to avoid excessive allocation
     * and garbage collection.
     */
    private short[] previous_dist = new short[MAX + 1];

    /**
     * 
     * @param a
     * @param b
     * @param c
     * @return 
     */
    private static short minimum(int a, int b, int c) {
        return (short) Math.min(a, Math.min(b, c));
    }

    /**
     * 
     * Compute Levenshtein distance (edit-distance) between two lists.
     * 
     * @param source tokens of a segment
     * @param target tokens of a segment
     * @return minimum edit-distance between source and target (word/token based)
     */
    public int compute(Token[] source, Token[] target) {
        if (source == null || target == null)
                throw new IllegalArgumentException();
           
        int source_len = (source.length > MAX)? MAX: source.length;  //limit edit-distance calculation to the MAX 
        int target_len = (target.length > MAX)? MAX: target.length; //limit edit-distance calculation to the MAX
        
        if (source_len == 0){
            return target_len; //boundry case when source is empty
        } else if (target_len == 0){
            return source_len; //boundry case when target is empty
        }    
        
        short[] tmp; // temporary variable for swapping
        
        Token target_j = null; 

        short cost; // cost
        
        /*initialization */
        for (short i = 0; i <= source_len; i++){
            previous_dist[i] =  i;
        }
        
        /*Calcualtion of edit-distance*/
        for (short j = 1; j <= target_len; j++) {
            target_j = target[j - 1];
            distance[0] = j;

            Token source_i = null; 
            for (short i = 1; i <= source_len; i++) {
                source_i = source[i - 1];
                cost = source_i.equals(target_j) ? (short) 0 : (short) 1;
                distance[i] = minimum(distance[i - 1] + 1, previous_dist[i] + 1, previous_dist[i - 1] + cost); // minimum of cell to the left+1, to the top+1, diagonally up-left +cost
            }

            // update row
            tmp = previous_dist;
            previous_dist = distance;
            distance = tmp;
        }

        return previous_dist[source_len];
    }
}
