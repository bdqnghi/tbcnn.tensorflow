//
//  reverse_string.cpp
//
//  Created by Masatoshi Nishiguchi on 11/18/15.
//  Copyright (c) 2015 Masatoshi Nishiguchi. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;


// #4 - the heading of the function

/**
 * Reverses a string character by character.
 * @param string original : the original string
 * @param string& lanigiro : the reversed string
 */
//void Reverse(string original, string& lanigiro)


// #5 - the function prototype for the function

void Reverse(string original, string& lanigiro);


// #6 - the function definition of the function (as a void function)

/**
 * Reverses a string character by character.
 * @param string original : the original string
 * @param string& lanigiro : the reversed string
 */
void Reverse(string original, string& lanigiro) {

    // Initialize lanigiro.
    lanigiro.clear();

    // Process the reversing
    int len = (int)original.length();
    for (int i = len - 1; i >= 0; --i) {

        lanigiro.push_back( original.at(i) );

    }

}

// #7 - the function definition of the function (as a value-returning function)

/**
 * Returns the character-by-character reverse of the passed-in string.
 * @param string original : the original string
 * @return the reversed string
 */
string Reverse(string original) {

    char temp;
    int len = (int)original.length();

    // Swap first and last, 2nd first and 2nd last, ...
    for (int i = 0; i < (len / 2); ++i) {

        temp = original[i];
        original[i]           = original[len - 1 - i];
        original[len - 1 - i] = temp;

    }

    return original;
}


// ----------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------- //


int main() {

    string original, lanigiro;

    cout << "----------------------------------------" << endl;
    cout << "Text 1" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n==Reversing the stfing (Using void function)==\n" << endl;

    // Prompt user for two integers.
    cout << "Enter a string: ";
    cin >> original;
    cout << "==> ";

    // Prosess the reversing. (Using void function)
    Reverse(original, lanigiro);
    cout << lanigiro << endl;
    cout << endl;

    cout << "Clearing original and lanigiro variables..." << endl;
    original.clear();
    lanigiro.clear();
    cout << endl;

    cout << "----------------------------------------" << endl;
    cout << "Text 2" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n==Reversing the stfing (Using void function)==\n" << endl;

    // Prompt user for two integers.
    cout << "Enter a string: ";
    cin >> original;
    cout << "==> ";

    // Prosess the reversing. (Using value-returning function)
    lanigiro = Reverse(original);

    // Output the Reversed string.
    cout << lanigiro << endl;

    return 0;
}

