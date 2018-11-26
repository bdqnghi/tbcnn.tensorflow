//
//  main.cpp
//  SELECTION-SORT
//
//  Created by GangGongUi on 2016. 7. 28..
//  Copyright © 2016년 GangGongUi. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int>& A)
{
    for(int i = 0; i < A.size() - 1; i++)
    {
        int minIdx = i;
        
        for(int j = i + 1; j < A.size(); j++)
            if(A[minIdx] > A[j])
                minIdx = j;
        
        if(i != minIdx)
        {
            int temp = A[i];
            A[i] = A[minIdx];
            A[minIdx] = temp;
        }
    }
}

int main(int argc, const char * argv[])
{
    // insert code here...
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    vector<int> A;
    for(auto i : arr)
        A.push_back(i);
    
    selectionSort(A);
    
    for(auto value : A)
        cout << value << " ";
    
    return 0;
}
