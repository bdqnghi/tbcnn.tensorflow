/**
 * @file Palindrome.cpp
 * @author Kylie Nicholson
 * @date 13 October 2015
 */
#include "Palindrome.h"
#include <iostream>
using namespace std;

Palindrome::Palindrome () 
{
   phrase = "";
}


Palindrome::Palindrome (string newPhrase) 
{
   phrase = newPhrase;
}
   

// After completing this method, submit the entire .cpp
// file as your solution for Lab 5. See method description in 
// Palindrome.h
/**
    * Evaluates the phrase to determine if it is a palindrome. Uses
    * a stack to reverse the order of the letters in the phrase and
    * to determine if the original phrase is a palindrome. A palindrome
    * is a sequence of letters that reads the same forward and backward;
    * however, all spaces and punctuation are ignored.
    * @return isPalindrome - true if phrase is a palindrome; false
    *                        otherwise
    * @param reversePhrase - orginal phrase in reverse order, including
    *                        all puncutation and spaces
    */

bool Palindrome::evalPalindrome (string& reversePhrase)
{
	// reversePhrase is passed by reference. 
	// you can access initial phrase through the phrase variable.

	// create a new stack
	ArrayStack<char> theStack;
	char current; 
	bool palin = false;
	string origStrip;
	string revStrip; 
	// push each character of reversePhrase into the stack
	for(int i=0; i<phrase.length(); i++)
		theStack.push(phrase[i]); 
	// pop each character of the stack back onto reversePhrase with a loop and using
	for(int i=0; i<phrase.length(); i++){
		current = theStack.peek(); 
		theStack.pop();
		// reversePhrase as an indexable array of characters
		reversePhrase+=current; 
		if(isalpha(current)){
			revStrip+= current;
		}
	}
	
	//test for palindrome 
	cout<<"Phrase: "<<phrase<<endl;
	cout<<"Reverse Phrase: "<<reversePhrase<<endl;
	cout<<"Reverse Strip: "<<revStrip<<endl;
	
	for (int i=0; i<phrase.length(); i++){
		//if not punctuation or blank
	
			
			toupper(phrase[i]);
			toupper(reversePhrase[i]); 
			if(phrase[i] != reversePhrase[i]){
				palin = false;
				return palin;
			}
			else
				palin = true; 
	}
	
	return palin;
}
