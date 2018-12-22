package nlp1;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author Administrator
 */
public class LevenshteinDistance {
    public int getMin(int a, int b, int c){
        ArrayList<Integer> arrNumber = new ArrayList<>();
        arrNumber.add(a);
        arrNumber.add(b);
        arrNumber.add(c);
        return Collections.min(arrNumber);
    }
    public int getMax(int a, int b, int c){
        ArrayList<Integer> arrNumber = new ArrayList<>();
        arrNumber.add(a);
        arrNumber.add(b);
        arrNumber.add(c);
        arrNumber.add(0);
        return Collections.max(arrNumber);
    }
    //thuat toan leven co xua:))
    public double levenshteinDistance(ArrayList<String> m, ArrayList<String> n){
        int mSize = m.size(); //size cua mang String m
        int nSize = n.size();// size cua mang String n
        int[][] d = new int[m.size() + 1][n.size() + 1];// tao mang d để tạo ma trận từ mảng kích thước m+1 x n+1
        //khoi tạo ma trận
        for(int i = 0; i <= mSize; i++){
            d[i][0] = i;
        }
        for(int j = 0; j <= nSize; j++){
            d[0][j] = j;
        }
        
        for(int i = 1; i <= mSize; i++){
            for(int j = 1; j <= nSize; j++){
                int cost = 0;
                if(m.get(i-1).toLowerCase().equals(n.get(j-1).toLowerCase()) == true){
                    cost = 0;
                }else{
                    cost = 1;
                }
                d[i][j] = getMin(d[i - 1][j] + 1, 
                        d[i][j - 1] + 1, 
                        d[i - 1][j - 1] + cost);
            }
        }
        
        return (double)d[mSize][nSize]/Math.max(mSize, nSize);
    }
    
    //cai thien thuat toan leven, tieu chuan k mình sẽ không cho vào vì trong code nó chả sd đến
    public double levenshteinDistanceImprovement(ArrayList<String> m, ArrayList<String> n){
        int mSize = m.size(); //size cua mang String m
        int nSize = n.size();// size cua mang String n
        int[][] d = new int[m.size() + 1][n.size() + 1];// tao mang d để tạo ma trận từ mảng kích thước m+1 x n+1
        //khoi tạo ma trận
        for(int i = 0; i <= mSize; i++){
            d[i][0] = i;
        }
        for(int j = 0; j <= nSize; j++){
            d[0][j] = j;
        }
        
        for(int i = 1; i <= mSize; i++){
            for(int j = 1; j <= nSize; j++){
                if( i == j){
                    d[i][j] = 0;
                }
                if(m.get(i-1).toLowerCase().equals(n.get(j-1).toLowerCase()) == true){
                    d[i][j] = d[i - 1][j - 1] + 1;
                }
                else
                {
                    d[i][j] = getMax(d[i - 1][j] - 1,
                            d[i][j - 1] - 1, 
                            d[i - 1][j - 1] -1);
                }
            }
        }
        return (double) d[mSize][nSize]/Math.max(mSize, nSize);
    }
    
    
    
}