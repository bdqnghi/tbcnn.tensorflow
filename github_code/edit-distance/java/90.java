/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package org.ucb.c5.sequtils;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 *
 * @author J. Christopher Anderson
 */
public class CalcEditDistance {
    
    public void initiate() throws Exception {
        
    }
    
    /**
     * Compute edit distance between two Strings using the Smith-Waterman
     * Algorithm
     *
     * @param s1
     * @param s2
     * @return
     */
    public int run(String s1, String s2) throws Exception {
        int s1len = s1.length();
        int s2len = s2.length();

        int[][] dist = new int[s1len + 1][s2len + 1];

        for (int a = 0; a <= s1len; a++) {
            for (int b = 0; b <= s2len; b++) {
                if (a == 0) {
                    dist[a][b] = b;
                } else if (b == 0) {
                    dist[a][b] = a;
                } else if (s1.charAt(a - 1) == s2.charAt(b - 1)) {
                    dist[a][b] = dist[a - 1][b - 1];
                } else {
                    dist[a][b] = 1 + Math.min(Math.min(dist[a][b - 1], dist[a - 1][b]), dist[a - 1][b - 1]);
                }
            }
        }

        return dist[s1len][s2len];
    }
    
    public static void main(String[] args) throws Exception {
        CalcEditDistance func = new CalcEditDistance();
        func.initiate();
        
        int distance = func.run("AACAAGATAT", "AATAAGATAT");
        System.out.println(distance);
        
        distance = func.run("AACAAGTTAT", "AATAAGATAT");
        System.out.println(distance);
    }
}
