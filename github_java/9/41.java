/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package heapsort;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

/**
 *
 * @author Rangita
 */
public class Heapsort {

    public static void main(String args[]) throws IOException
    {
       File file = new File("C:\\Users\\Rangita\\Documents\\NetBeansProjects\\heapsort\\src\\heapsort\\heapsort.txt");
        byte[] bytes = new byte[(int) file.length()];
        FileInputStream fis = new FileInputStream(file);
        fis.read(bytes);
        fis.close();
        String[] valueStr = new String(bytes).trim().split("\\s+");
        int[] ec = new int[valueStr.length];
        for (int i = 0; i < valueStr.length; i++) 
        ec[i] = Integer.parseInt(valueStr[i]);
        Heapsort ob = new Heapsort();
        print(ec);
        ob.sort(ec);
        print(ec);
    }
    static void print(int sorted[])
    {
        int n = sorted.length;
        for (int i=0; i<n; ++i)
            System.out.print(sorted[i]+" ");
        System.out.println();
    }
 
    public void sort(int eCost[])
    {
        int n = eCost.length;
 
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify_eC(eCost, n, i);
 
        
        for (int i=n-1; i>=0; i--)
        {
            
            int temp = eCost[0];
            eCost[0] = eCost[i];
            eCost[i] = temp;
            heapify_eC(eCost, i, 0);
        }
    }
 
    void heapify_eC(int sorting[], int n, int i)
    {
        int root = i;  
        int r = 2*i + 2;  
        int l = 2*i + 1; 
         
        if (l < n && sorting[l] > sorting[root])
            root = l;
 
        if (r < n && sorting[r] > sorting[root])
            root = r;
         
        if (root != i)
        {
            int temp = sorting[i];
            sorting[i] = sorting[root];
            sorting[root] = temp;
            heapify_eC(sorting, n, root);
        }
    }
 
    
}
