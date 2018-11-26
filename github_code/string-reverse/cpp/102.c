/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        07/29/18
** Description: 
*********************************************************************/
#include "stringReverse.hpp"
#include <iostream>
#include <string>

/********************************************************************* 
** Description: void enterString()
*               Menu information and prompt to enter necessary
*               function information.
*********************************************************************/
void enterString()
{
    std::string userIn;
    std::cout << "Please enter a string you'd like to have reversed: " << std::endl << std::endl;
    std::getline(std::cin, userIn);
    std::cout << std::endl;
    std::cout << "   Reverses to  --->   ";
    stringReverse(userIn);
    std::cout << std::endl << std::endl;
    startMenu();
}

/********************************************************************* 
** Description: void stringReverse(std::string stringIn)
*               Recursive function that takes a user inputted string
*               and outputs the smae string reversed
*********************************************************************/
void stringReverse(std::string stringIn)
{
    if (stringIn.length()==0)
        return;
    else
    {
        std::cout << stringIn[stringIn.length()-1];
        // https://cal-linux.com/tutorials/strings.html
        // Used to learn the .substr() function
        std::string newString=stringIn.substr(0, stringIn.length()-1);
        stringReverse(newString);
    }
}
