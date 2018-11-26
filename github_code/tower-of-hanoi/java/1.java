package com.pawan.algorithms.karumanchi.recursion_and_backtracking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created by Pawan on 09/04/17.
 */
public class TowerOfHanoi {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line  = "";
        while(!(line = br.readLine()).isEmpty()) {
            towerOfHanoi(Integer.parseInt(line), 'A', 'B', 'C');
        }
    }

    private static void towerOfHanoi(int n, char frompeg, char topeg, char auxpeg) {
        if(n==1) {
            System.out.format("Move 1 from peg %s to %s\n", frompeg, topeg);
            return;
        }
        //move n-1 disks from A to B using C as auxillary
        towerOfHanoi(n-1, frompeg, auxpeg, topeg);

        //move remaining disk from A to C
        System.out.format("Move disk from peg %s to peg %s", frompeg, topeg);

        //move disk from B to C using A as auxilary
        towerOfHanoi(n-1, auxpeg, topeg, frompeg);
    }
}
