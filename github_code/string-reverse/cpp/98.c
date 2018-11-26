//
//  main.cpp
//  firstxodeproject.cpp
//
//  Created by Wallace Obey on 2/6/16.
//  Copyright © 2016 Wallace Obey. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void reverseString(char word[], int length);    // Prototype reverse function

int main(){
    
    char userString[4];
    
    int length = strlen(userString);    // int length is equal to the length on the string (4)
    
    cout <<" Enter a word that has four letters " << "\n";
    
    cin >> userString;                  // user enters a word
    
    reverseString(userString, 4);       //runs reverse string function
    
    
    
    return 0;
}


void reverseString(char word[], int length)
{
    char *headP = &word[0];         // head pointer is pointing to first letter
    char *tailP = &word[length-1];  // tail pointer points to last letter. -1 because of null character
    char userString[4];
    
    cout << word << endl;           // displays the word
    
    char temp;                      // creats temporary variable
    
    while(headP < tailP){           //switch pointers until word is completley flipped       
        temp = *tailP;
        *tailP = *headP;
        *headP = temp;
        headP++;                    // increments head pointer
        tailP--;	                // decrements tail pointer
    }
    cout << word << endl;           // displayes reversed string
}

