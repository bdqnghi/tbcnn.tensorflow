//
//  RodCutting.hpp
//  Algorithms
//
//  Created by Harshavardhan K K on 24/11/16.
//  Copyright © 2016 Harshavardhan K. All rights reserved.
//

#ifndef RodCutting_hpp
#define RodCutting_hpp

#include "Generics.h"

class RodCutting {
    
public:
    
    RodCutting(int* prices, int size) {
        
       // prices = new int[10];
        //arrayCopy(prices, this->prices, 0, 0, 10);
        
        this->prices = prices;
        this->size = size;
    }
    
    void cutRod() {
        
        cout << "Solution: ";
       // cout << simpleCutRod(prices, size) << endl;
        cout << bottomUp() << endl;
    }
    
private:
    
    int extendedBottomUp();
    int bottomUp();
    int simpleCutRod(int prices[10], int size);
    int* prices;
    int size;
    
};

int RodCutting::bottomUp() {
    
    int* memory = new int[this->size];
    memory[0] = 0;
    
    for (int j = 1; j <= size; j++) {
        int profit = -1;
        
        for (int i = 0; i < j; i++) {
            profit = max(profit, this->prices[i] + memory[j - i - 1]);
        }
        
        memory[j] = profit;
    }
    
    // displayArray(memory, size);
    
    return memory[size];
    
}

int RodCutting::simpleCutRod(int prices[10], int size) {
    
    if (size == 0) {
        return 0;
    }
    
    int profit = -1;
    
    for (int i = 0; i < size; i++) {
        profit = max(profit, prices[i] + simpleCutRod(prices, size - i - 1));
    }
    
    return profit;
}

int edit_distance(string str1, string str2, int m, int n) {
    
    if(m == 0)
        return n;
    if(n == 0)
        return m;
    
    if(str1[m-1] == str2[n-1])
        return edit_distance(str1, str2, m-1, n-1);
    
    int replace = edit_distance(str1, str2, m-1, n-1);
    int insert =  edit_distance(str1, str2, m, n-1);
    int del =  edit_distance(str1, str2, m-1, n);
    
    return 1 + min(min(replace, insert), del);
}



#endif /* RodCutting_hpp */
