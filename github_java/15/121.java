/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package com.quantum.algorithm.dp;


import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

/**
 *
 * @author canvera
 */
public class MaximumProfitOnRodCutting {   
    
 
    
     public static int maximumProfitOnRodCutting(Map<Integer,Integer>map,int length,Map<Integer,Integer>maxPrice)            
    {
        if(length==0)
        { 
            maxPrice.put(0,0);
            return 0;
        }
        if(length==1){
            maxPrice.put(1,map.get(1));
            maxPrice.put(0,0);
            return map.get(1);
        }
    maxPrice.put(length-1,maximumProfitOnRodCutting(map,length-1,maxPrice));
    maxPrice.put(length,map.get(length));
        for(int i=1;i<length;i++)
        {            
            for(int j=1;j<=length-i;j++)
            {  
              //  System.out.print(4-i-j+" ");
               int temp=maxPrice.get(i)+maxPrice.get(j)+maxPrice.get(length-i-j);
                if(maxPrice.get(length)< temp)
                    maxPrice.put(length, temp);            
                          
                    
            }       
        }
        return maxPrice.get(length);
    }
     
   static  Integer[] rodPieces(Integer i[],Integer j[],Integer k[])
     {
         Integer rod[]=new Integer[(i.length+j.length+k.length)];
         System.arraycopy(i,0, rod,0, i.length);
         System.arraycopy(j,0, rod,i.length, j.length);
         System.arraycopy(k,0, rod,i.length+j.length, k.length);
         return rod;
     }
     
     
public static int maximumProfitOnRodCutting(Map<Integer,Integer>map,int length,Map<Integer,Integer>maxPrice,Map<Integer,Integer[]>rodCuttingMap)            
    {
        if(length==0)
        { 
            maxPrice.put(0,0);
            rodCuttingMap.put(0,new Integer[]{0});
            return 0;
        }
        if(length==1){
            maxPrice.put(1,map.get(1));
            maxPrice.put(0,0);
            rodCuttingMap.put(0,new Integer[]{0});
            rodCuttingMap.put(1,new Integer[]{1});
            return map.get(1);
        }
    maxPrice.put(length-1,maximumProfitOnRodCutting(map,length-1,maxPrice,rodCuttingMap));
    maxPrice.put(length,map.get(length));
    rodCuttingMap.put(length, new Integer[]{length});
        for(int i=1;i<length;i++)
        {            
            for(int j=1;j<=length-i;j++)
            {  
              //  System.out.print(4-i-j+" ");
               int temp=maxPrice.get(i)+maxPrice.get(j)+maxPrice.get(length-i-j);
                if(maxPrice.get(length)< temp)
                {   
                    maxPrice.put(length, temp);
                    rodCuttingMap.put(length,rodPieces(rodCuttingMap.get(i),rodCuttingMap.get(j),rodCuttingMap.get(length-i-j)));
                }            
                          
                    
            }       
        }
//       int temp=maxPrice.get(i)+maxPrice.get(j)+maxPrice.get(length-i-j);
//       if(map.get(length)< temp )
//          maxPrice.put(length,temp);
//       else
//           maxPrice.put(length,map.get(length));
        return maxPrice.get(length);
    }

public static int buttomOfApproachByCorman(Map<Integer,Integer>priceMap,int length,Map<Integer,Integer>revenueMap)
{
    
    if(length==0)
    {   
        revenueMap.put(0,0);
        return 0;
    }      
        
   for(int i=1;i<=length;i++){
       int temp=priceMap.get(i);
       for(int j=1;j<=i;j++){
           temp=Math.max(temp,priceMap.get(j)+revenueMap.get(i-j));
       }
       revenueMap.put(i, temp);
   }
       
   
 return revenueMap.get(length);   
}   
     
     
        

    
    public static void main(String[] args) {
        Map<Integer,Integer> map=new HashMap<Integer,Integer>();
        Map<Integer,Integer> maxPrice=new HashMap<Integer,Integer>();
        map.put(0,0);
        map.put(1,1);
        map.put(2,5);
        map.put(3,8);
        map.put(4,9);
        map.put(5,10);
        //map.put(6,17);
        map.put(6,14);
        map.put(7,17);
        map.put(8,20);
        map.put(9,24);
        map.put(10,30);
        maxPrice.put(0,0);
        System.out.println("revenue"+buttomOfApproachByCorman(map,10,maxPrice));
        //int revenue=map.get(4);
//        int revenue=0;        
//        revenue=maximumProfitOnRodCutting(map,10,maxPrice);
//        System.out.println("maximum revenue "+revenue);
        System.out.println("by coreman concept");
        for(Entry<Integer,Integer>e:maxPrice.entrySet())
        {
            System.out.println(e.getKey() +"===="+e.getValue());
        }
       
        Map<Integer,Integer[]> rodCuttingMap=new HashMap<Integer,Integer[]>();
        int revenue=maximumProfitOnRodCutting(map,10,maxPrice,rodCuttingMap);
      for(Entry<Integer,Integer[]>e:rodCuttingMap.entrySet())
      {
            System.out.println(e.getKey() +"===="+maxPrice.get(e.getKey())+"====="+Arrays.toString(e.getValue()));
      }
//        
        
        
    }
    
}
