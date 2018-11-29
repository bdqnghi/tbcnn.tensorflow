/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pr.corina.lab5pr.utils;

import com.pr.corina.lab5pr.utils.ChatConstants;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 *
 * @author corina
 */
public class Levenshtein {
    public static final int MAX_ADMISSIBLE_DISTANCE=3;
    
    public static List<String>commandsList;
    static{
        commandsList=new ArrayList<>();
        commandsList.add(ChatConstants.CMD_HELLO);
        commandsList.add(ChatConstants.CMD_HELP);
        commandsList.add(ChatConstants.CMD_JOKE);
        commandsList.add(ChatConstants.CMD_PASSWORD);
        commandsList.add(ChatConstants.CMD_QUIT);
        commandsList.add(ChatConstants.CMD_TIME);
    }
    
    
    public static String getMinumumDistanceToComand(String receivedCommand){
        int distance=10;
        String minCommand=null;
        for(String cmd:commandsList){
            int localDist=calculate(receivedCommand, cmd);
            if(localDist<distance){
                distance=localDist;
                minCommand=cmd;
            }
        }
        if(distance<=MAX_ADMISSIBLE_DISTANCE)
            return minCommand;
        else
            return null;
    }
    static int calculate(String x, String y) {
        int[][] dp = new int[x.length() + 1][y.length() + 1];

        for (int i = 0; i <= x.length(); i++) {
            for (int j = 0; j <= y.length(); j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1]
                            + costOfSubstitution(x.charAt(i - 1), y.charAt(j - 1)),
                            dp[i - 1][j] + 1,
                            dp[i][j - 1] + 1);
                }
            }
        }

        return dp[x.length()][y.length()];
    }

    public static int costOfSubstitution(char a, char b) {
        return a == b ? 0 : 1;
    }

    public static int min(int... numbers) {
        return Arrays.stream(numbers)
                .min().orElse(Integer.MAX_VALUE);
    }

    public static void main(String[] args) {
        int distance = calculate("hello", "ssfsgs");
        System.out.println("Distance=" + distance);
    }

}
