/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sort.methods;

import mystrategy.IStrategy;
import sort.strategy.Stopwatch;

/**
 *
 * @author LeopardProMK
 */
public class Selectionsort implements IStrategy {
 private Stopwatch _stopWatch;
    private double _elapsedTime;
    @Override
    public double[] SortData(double[] data) {
        _stopWatch = new Stopwatch();
         this.sort(data);
            _elapsedTime = _stopWatch.elapsedTime();
        return data;
    }
    
    void sort(double arr[])
    {
        int n = arr.length;
         for (int i = 0; i < n-1; i++)
        {
            int min_idx = i;
            for (int j = i+1; j < n; j++)
                if (arr[j] < arr[min_idx])
                    min_idx = j;
 

            double temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }

    @Override
    public double ElapsedTime() {
        return _elapsedTime;
    }
}
