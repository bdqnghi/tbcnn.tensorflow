//Author: Alex King
//Last Modified: 9/12/18
//This program take text input from the user and says whether or not it's a palindrome. It uses character arrays and converts all letters to lowercase and removes any other characters.
//then it checks whether the character array is the same backwards and forwards. 

#include <iostream>
#include <cstring>

using namespace std;

main() {
  char input[81];
  char rvString[81];
  while(true) {
    cout << "Please enter no more than 80 characters of text ";
    cin.get(input, 81);
    while(cin.get() != '\n'); //eats characters until a return is reached, eats the return then stops
    char string[81];
    int j = 0;
    for(int i = 0; i < strlen(input) + 1; i++) { //steps the number of time of the length of input + 1 for the null terminating character
      //friend: Nathan class: C++ Programming 5
      //I am using their idea to check what type of character a character is using ASCII ranges
      //This code checks whether a character is a capital or lowercase letter
      if(input[i] >= 65 && input[i] <= 90) { // it's a capital letter 
	string[j] = input[i] + 32; //converts the letter into a lowercase before copying it over into string
	j++;
      } else if (input[i] >= 97 && input[i] <= 122) { //it's a lowercase letter
	string[j] = input[i];
	j++;
	//End of code where I used idea
      } else if (input[i] == '\0') { // it's a null terminating character
	string[j] = input[i];
      }
    }
    for (int i = 0; i < strlen(string); i++) { //copy the character array into another character array backwards, leaving out the null terminating character 
	rvString[strlen(string) - 1 - i] = string[i];
      }
    rvString[strlen(string)] = '\0';
    //parent: Steve
    //I am using their idea to use check if a character array is empty and to do it with strlen
    //The code (part of next line) checks if a character array is empty
    if(strcmp(string, rvString) != 0 || strlen(string) == 0) { //check if the character array and the reverse character array are not the same, and if the character array is empty
      //End of code where idea is used
      cout << "not a palindrome" << "\n";
    } else {
      cout << "palindrome" << "\n";
    }
		      
  }

}
