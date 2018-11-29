/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * for rod of size 1, it checks max between 0 and 1 
 * //for rod of size 2, it checked max between (0, 2) and (1, 1), whichever is maximum, it updates in results[2] 
 * //for rod of size 3, it checked max between (0, 3), (1, 2), and (2, 1) whichever is maximum, it updates in results[3] 
 * //for rod of size 4, it checked max between (0, 4), (1, 3), (3, 1) and (2, 2) whichever is maximum, it updates in results[4]
 * @author Kushagra
 */
public class CuttingRod 
{
    private static int[] prices;
    public CuttingRod()
    {
        prices = new int[]{0, 1 , 5 , 8 , 9 , 10 , 17, 17 , 20 , 24 , 30};
    }
    
    
    //Top - down with memoization
    public int cuttingRod(int rod)
    {
        int [] results = new int[rod + 1];
        for(int i = 0 ; i < results.length ; i ++)
        {
            results[i] = Integer.MIN_VALUE;
        }
        return this._cuttingRod(rod, results);
    }
    
    private int _cuttingRod(int rod, int [] results)
    {
        int q;
        if(results[rod] >= 0)
            return results[rod];
        if(rod == 0)
            q = 0;
        else
        {
            q = Integer.MIN_VALUE;
            for(int i =  1 ; i <= rod ; i++)
            {
            //q = Integer.MIN_VALUE;
                q = this.max(q, prices[i] + this._cuttingRod(rod - i, results)); 
                System.out.println(i+" -- "+q);
            }
        }
        results[rod] = q;  
        return results[rod];
    }
    
    //bottom - up approach
    
    public int cuttingRod_BottomUp(int rod)
    {
        int [] results = new int [rod + 1] ;
        results[0] = 0;
        for(int i = 1 ; i <= rod ; i++)
        {
            for(int j = 0 ; j < i ; j++)
            {
                results[i] = this.max(results[j],prices[i] + results[i - j]);
            }
        }
        
        return results[rod];
    }
    
    // Recursion
    
    public int cuttingRod_Recursion(int rod)
    {
        if(rod == 0)
            return 0;
        int q = Integer.MIN_VALUE;
        for(int i = 1 ; i <= rod ; i++)
        {
            q = this.max(q, prices[i] + this.cuttingRod_Recursion(rod - i));
            System.out.println("Recursion: "+i+" -- "+(rod - i));
        }
        return q;
    }
    private int max(int a, int b)
    {
        return b ^ ( (a ^ b) & (a > b ? 1 : 0));
    }
}
