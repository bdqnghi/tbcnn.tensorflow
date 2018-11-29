package com.interviewbit.DP;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
 */
public class RodCutting
{
    public ArrayList<Integer> rodCutting( ArrayList<Integer> B, int N ) 
    {
        final ArrayList<Integer> res = new ArrayList<>();
        
        doCombine( B, new ArrayList<Integer>(), res, Integer.MAX_VALUE, N, 0 );
        
        return res;
    }
    
    private int doCombine(  ArrayList<Integer> B, ArrayList<Integer> path, ArrayList<Integer> res, int min, int N, int start  )
    {
        if( path.size() == B.size() )
        {
            int profit = calculateProfit( path, N );
            if( min > profit )
            {
                min = profit;
                res.clear();
                res.addAll( path );
            }
            
            return min;
        }
        
        for( int i =0; i <= path.size(); i++ )
        {
            ArrayList<Integer> path2 = new ArrayList<>(path);
            path2.add( i, B.get( start ) );
            min = doCombine( B, path2, res, min, N, start+1 );
        }
        
        return min;
    }
    
    private int calculateProfit( final ArrayList<Integer> path, int N )
    {
        int profit = N;
        final List<Integer> segments = new ArrayList<>();
        segments.add( path.get(0) );
        segments.add( N );
        Collections.sort( segments );
        
        for( int i = 1; i < path.size(); i++ )
        {
            int r = path.get( i );
            
            int k = 0;
            for( int j=0; j < segments.size(); j++ )
            {
                if( r <= segments.get(j) )
                {
                    k =j;
                    break;
                }
            }
            
            if( k==0)
            {
                k = segments.size()-1; 
            }
            
            int t = segments.get( k );
            profit += t ;
            
            segments.remove( k );
            segments.add( path.get( i ) );
            segments.add( t-path.get( i ) );
            Collections.sort( segments );
        }
        
        return profit;
    }
    
    public static void main( String[] args )
    {
        RodCutting hp = new RodCutting();
        
        Integer[] nums ={2,5,1};
        int n =6;
        final ArrayList<Integer> a = new ArrayList<>( Arrays.asList( nums ));
        
        System.out.println( " Minium Cost = " + hp.calculateProfit( a, n ) );
    }
}
